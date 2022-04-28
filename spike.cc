#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
//nclude <optional>
#include "device.h"
#include "common.h"
#include "option_parser.h"

using namespace std;



template <typename T>
class cfg_arg_t {
public:
  cfg_arg_t(T default_val)
    : value(default_val), was_set(false) {}

  bool overridden() const { return was_set; }

  T operator()() const { return value; }

  T operator=(const T v) {
    value = v;
    was_set = true;
    return value;
  }

private:
  T value;
  bool was_set;
};

class mem_cfg_t
{
public:
  mem_cfg_t(reg_t base, reg_t size)
    : base(base), size(size)
  {
    // The truth of these assertions should be ensured by whatever is creating
    // the regions in the first place, but we have them here to make sure that
    // we can't end up describing memory regions that don't make sense. They
    // ask that the page size is a multiple of the minimum page size, that the
    // page is aligned to the minimum page size, that the page is non-empty and
    // that the top address is still representable in a reg_t.
    assert((size % PGSIZE == 0) &&
           (base % PGSIZE == 0) &&
           (base + size > base));
  }

  reg_t base;
  reg_t size;
};

class cfg_t
{
public:
  cfg_t(std::pair<reg_t, reg_t> default_initrd_bounds,
        const char *default_bootargs,
        const char *default_isa, const char *default_priv,
        const char *default_varch,
        const std::vector<mem_cfg_t> &default_mem_layout,
        const std::vector<int> default_hartids,
        bool default_real_time_clint)
    : initrd_bounds(default_initrd_bounds),
      bootargs(default_bootargs),
      isa(default_isa),
      priv(default_priv),
      varch(default_varch),
      mem_layout(default_mem_layout),
      hartids(default_hartids),
      explicit_hartids(false),
      real_time_clint(default_real_time_clint)
  {}

  cfg_arg_t<std::pair<reg_t, reg_t>> initrd_bounds;
  cfg_arg_t<const char *>            bootargs;
  cfg_arg_t<const char *>            isa;
  cfg_arg_t<const char *>            priv;
  cfg_arg_t<const char *>            varch;
  cfg_arg_t<std::vector<mem_cfg_t>>  mem_layout;
//  std::optional<reg_t>               start_pc;
  cfg_arg_t<std::vector<int>>        hartids;
  bool                               explicit_hartids;
  cfg_arg_t<bool>                    real_time_clint;

  size_t nprocs() const { return hartids().size(); }
};


static std::vector<mem_cfg_t> parse_mem_layout(const char* arg)
{
  std::vector<mem_cfg_t> res;

  // handle legacy mem argument
  char* p;
  auto mb = strtoull(arg, &p, 0);
  if (*p == 0) {
    reg_t size = reg_t(mb) << 20;
    if (size != (size_t)size)
      throw std::runtime_error("Size would overflow size_t");
    res.push_back(mem_cfg_t(reg_t(DRAM_BASE), size));
    return res;
  }

  // handle base/size tuples
  while (true) {
    auto base = strtoull(arg, &p, 0);
	if (!*p || *p != ':')
		return res; 
    auto size = strtoull(p + 1, &p, 0);

    // page-align base and size
    auto base0 = base, size0 = size;
    size += base0 % PGSIZE;
    base -= base0 % PGSIZE;
    if (size % PGSIZE != 0)
      size += PGSIZE - size % PGSIZE;

	if (base + size < base)
		return res;

    if (size != size0) {
      fprintf(stderr, "Warning: the memory at  [0x%llX, 0x%llX] has been realigned\n"
                      "to the %ld KiB page size: [0x%llX, 0x%llX]\n",
              base0, base0 + size0 - 1, long(PGSIZE / 1024), base, base + size - 1);
    }

    res.push_back(mem_cfg_t(reg_t(base), reg_t(size)));
    if (!*p)
      break;
	if (*p != ',')
		return res; 
    arg = p + 1;
  }

 // merge_overlapping_memory_regions(res);

  return res;
}


static std::vector<std::pair<reg_t, mem_t*>> make_mems(const std::vector<mem_cfg_t> &layout)
{
  std::vector<std::pair<reg_t, mem_t*>> mems;
  mems.reserve(layout.size());
  for (const auto &cfg : layout) {
    mems.push_back(std::make_pair(cfg.base, new mem_t(cfg.size)));
  }
  return mems;
}



int main(int argc, char** argv)
{
  bool debug = false;
  bool halted = false;
  bool histogram = false;
  bool log = false;
  bool socket = false;  // command line option -s
  bool dump_dts = false;
  bool dtb_enabled = true;
  uint64_t ddr_size = 0x100000000;
  const char* kernel = NULL;
  reg_t kernel_offset, kernel_size;
  std::vector<std::pair<reg_t, abstract_device_t*>> plugin_devices;

  bool log_cache = false;
  bool log_commits = false;
  const char *log_path = nullptr;
  //std::vector<std::function<extension_t*()>> extensions;
  const char* initrd = NULL;
  const char* dtb_file = NULL;
  uint16_t rbb_port = 0;
  bool use_rbb = false;
  unsigned dmi_rti = 0;
  reg_t blocksz = 64;
  cfg_t cfg(/*default_initrd_bounds=*/std::make_pair((reg_t)0, (reg_t)0),
            /*default_bootargs=*/nullptr,
            /*default_isa=*/DEFAULT_ISA,
            /*default_priv=*/DEFAULT_PRIV,
            /*default_varch=*/DEFAULT_VARCH,
            /*default_mem_layout=*/parse_mem_layout("2048"),
            /*default_hartids=*/std::vector<int>(),
            /*default_real_time_clint=*/false);


  option_parser_t parser;
//  parser.help(&suggest_help);
//  parser.option('h', "help", 0, [&](const char* s){help(0);});
  parser.option('d', 0, 0, [&](const char* s){debug = true;});
  parser.option('g', 0, 0, [&](const char* s){histogram = true;});
  parser.option('l', 0, 0, [&](const char* s){log = true;});
  // parser.option('p', 0, 1, [&](const char* s){nprocs = atoul_nonzero_safe(s);});
  parser.option('m', 0, 1, [&](const char* s){cfg.mem_layout = parse_mem_layout(s);});
  // // I wanted to use --halted, but for some reason that doesn't work.
  // parser.option('H', 0, 0, [&](const char* s){halted = true;});
  // parser.option(0, "rbb-port", 1, [&](const char* s){use_rbb = true; rbb_port = atoul_safe(s);});
  // parser.option(0, "pc", 1, [&](const char* s){cfg.start_pc = strtoull(s, 0, 0);});
  // parser.option(0, "hartids", 1, [&](const char* s){
  //   cfg.hartids = parse_hartids(s);
  //   cfg.explicit_hartids = true;
  // });
  // parser.option(0, "ic", 1, [&](const char* s){ic.reset(new icache_sim_t(s));});
  // parser.option(0, "dc", 1, [&](const char* s){dc.reset(new dcache_sim_t(s));});
 // parser.option(0, "l2", 1, [&](const char* s){l2.reset(cache_sim_t::construct(s, "L2$"));});
  parser.option(0, "log-cache-miss", 0, [&](const char* s){log_cache = true;});
  parser.option(0, "isa", 1, [&](const char* s){cfg.isa = s;});
  parser.option(0, "priv", 1, [&](const char* s){cfg.priv = s;});
  parser.option(0, "varch", 1, [&](const char* s){cfg.varch = s;});
 // parser.option(0, "device", 1, device_parser);
//  parser.option(0, "extension", 1, [&](const char* s){extensions.push_back(find_extension(s));});
  parser.option(0, "dump-dts", 0, [&](const char *s){dump_dts = true;});
  parser.option(0, "disable-dtb", 0, [&](const char *s){dtb_enabled = false;});
  parser.option(0, "dtb", 1, [&](const char *s){dtb_file = s;});
  parser.option(0, "kernel", 1, [&](const char* s){kernel = s;});
  parser.option(0, "initrd", 1, [&](const char* s){initrd = s;});
  parser.option(0, "bootargs", 1, [&](const char* s){cfg.bootargs = s;});
  parser.option(0, "real-time-clint", 0, [&](const char *s){cfg.real_time_clint = true;});
  // parser.option(0, "extlib", 1, [&](const char *s){
  //   void *lib = dlopen(s, RTLD_NOW | RTLD_GLOBAL);
  //   if (lib == NULL) {
  //     fprintf(stderr, "Unable to load extlib '%s': %s\n", s, dlerror());
  //     exit(-1);
  //   }
  // });
  // parser.option(0, "dm-progsize", 1,
  //     [&](const char* s){dm_config.progbufsize = atoul_safe(s);});
  // parser.option(0, "dm-no-impebreak", 0,
  //     [&](const char* s){dm_config.support_impebreak = false;});
  // parser.option(0, "dm-sba", 1,
  //     [&](const char* s){dm_config.max_sba_data_width = atoul_safe(s);});
  // parser.option(0, "dm-auth", 0,
  //     [&](const char* s){dm_config.require_authentication = true;});
  // parser.option(0, "dmi-rti", 1,
  //     [&](const char* s){dmi_rti = atoul_safe(s);});
  // parser.option(0, "dm-abstract-rti", 1,
  //     [&](const char* s){dm_config.abstract_rti = atoul_safe(s);});
  // parser.option(0, "dm-no-hasel", 0,
  //     [&](const char* s){dm_config.support_hasel = false;});
  // parser.option(0, "dm-no-abstract-csr", 0,
  //     [&](const char* s){dm_config.support_abstract_csr_access = false;});
  // parser.option(0, "dm-no-halt-groups", 0,
  //     [&](const char* s){dm_config.support_haltgroups = false;});
  parser.option(0, "log-commits", 0,
                [&](const char* s){log_commits = true;});
  // parser.option(0, "log", 1,
  //               [&](const char* s){log_path = s;});
  // FILE *cmd_file = NULL;
  // parser.option(0, "debug-cmd", 1, [&](const char* s){
  //    if ((cmd_file = fopen(s, "r"))==NULL) {
  //       fprintf(stderr, "Unable to open command file '%s'\n", s);
  //       exit(-1);
  //    }
  // });
  // parser.option(0, "blocksz", 1, [&](const char* s){
  //   blocksz = strtoull(s, 0, 0);
  //   if (((blocksz & (blocksz - 1))) != 0) {
  //     fprintf(stderr, "--blocksz should be power of 2\n");
  //     exit(-1);
  //   }
  // });

  auto argv1 = parser.parse(argv);
  std::vector<std::string> htif_args(argv1, (const char*const*)argv + argc);





  return 0;
}
