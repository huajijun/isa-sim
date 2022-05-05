#include "proccessor.h"
#include "decode.h"
#include <cstring>
#include <algorithm>
#include "mmu.h"
reg_t illegal_instruction(processor_t* p, insn_t insn, reg_t pc)
{
	return 0;
}
processor_t::processor_t(SimIf* sim) {
	register_base_instructions();
}

void processor_t::register_insn(insn_desc_t desc) {
	instructions.push_back(desc);
}

void processor_t::register_base_instructions() {
	#define DECLARE_INSN(name, match, mask) \
		insn_bits_t name##_match = (match), name##_mask = (mask); \
		bool name##_supported = true;
	#include "encoding.h"
	#undef DECLARE_INSN

	#define DEFINE_INSN(name) \
    extern reg_t rv32i_##name(processor_t*, insn_t, reg_t); \
    extern reg_t rv64i_##name(processor_t*, insn_t, reg_t); \
    extern reg_t rv32e_##name(processor_t*, insn_t, reg_t); \
    extern reg_t rv64e_##name(processor_t*, insn_t, reg_t); \
    register_insn((insn_desc_t) { \
      name##_supported, \
      name##_match, \
      name##_mask, \
      rv32i_##name, \
      rv64i_##name, \
      rv32e_##name, \
      rv64e_##name});
	#include "insn_list.h"
	#undef DEFINE_INSN
  	build_opcode_map();
}

void processor_t::build_opcode_map()
{

	struct cmp {
	    bool operator()(const insn_desc_t& lhs, const insn_desc_t& rhs) {
	      if (lhs.match == rhs.match)
	        return lhs.mask > rhs.mask;
	      return lhs.match > rhs.match;
	    }
	};
	std::sort(instructions.begin(), instructions.end(), cmp());
	for (size_t i = 0; i < OPCODE_CACHE_SIZE; i++)
		opcode_cache[i] = insn_desc_t::illegal();
}


bool processor_t::load(reg_t addr, size_t len, uint8_t* bytes)
{
  switch (addr)
  {
    case 0:
      if (len <= 4) {
        memset(bytes, 0, len);
        bytes[0] = get_field(state.mip->read(), MIP_MSIP);
        return true;
      }
      break;
  }

  return false;
}

bool processor_t::store(reg_t addr, size_t len, const uint8_t* bytes)
{
  switch (addr)
  {
    case 0:
      if (len <= 4) {
        //state.mip->write_with_mask(MIP_MSIP, bytes[0] << IRQ_M_SOFT);
        return true;
      }
      break;
  }

  return false;
}

void processor_t::step(size_t n){
  while(n) {
    reg_t pc = state.pc;
    mmu_t* _mmu = mmu;
    insn_fetch_t fetch = mmu->load_insn(pc);

    pc = execute_insn(this, pc, fetch);
  }
}

