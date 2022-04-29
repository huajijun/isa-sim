#include "devices.h"
#include <string>
void bus_t::add_device(reg_t addr, AbstractDevice* dev) {
	devices[addr] = dev;
}

bool bus_t::load(reg_t addr, size_t len , uint8_t *bytes) {
	auto it = devices.upper_bound(addr);
	if (devices.empty() || it == devices.begin()) {
		return false;
	}

	it--;
	return it->second->load(addr - it->first,len,bytes);
}

bool bus_t::store(reg_t addr, size_t len, const uint8_t* bytes) {
	auto it = devices.upper_bound(addr);
	if (devices.empty() || it == devices.begin()) {
		return false;
	}
	it--;
	return it->second->store(addr - it->first,len,bytes);
}


std::pair<reg_t,AbstractDevice*>  bus_t::find_device(reg_t addr) {
	auto it = devices.upper_bound(addr);
	if (devices.empty() || it == devices.begin()) {
		return std::make_pair((reg_t)0, (AbstractDevice*)NULL);
	}
	it--;
	return std::make_pair(it->first,it->second);
}





Mem::Mem(reg_t size)
  : sz(size)
{
}

Mem::~Mem()
{
  for (auto& entry : sparse_memory_map)
    free(entry.second);
}



bool Mem::load_store(reg_t addr, size_t len, uint8_t* bytes, bool store)
{
  if (addr + len < addr || addr + len > sz)
    return false;

  while (len > 0) {
    auto n = std::min(PGSIZE - (addr % PGSIZE), reg_t(len));

    if (store)
      memcpy(this->contents(addr), bytes, n);
    else
      memcpy(bytes, this->contents(addr), n);

    addr += n;
    bytes += n;
    len -= n;
  }

  return true;
}

char* Mem::contents(reg_t addr) {
  reg_t ppn = addr >> PGSHIFT, pgoff = addr % PGSIZE;
  auto search = sparse_memory_map.find(ppn);
  if (search == sparse_memory_map.end()) {
    auto res = (char*)calloc(PGSIZE, 1);
    if (res == nullptr)
      throw std::bad_alloc();
    sparse_memory_map[ppn] = res;
    return res + pgoff;
  }
  return search->second + pgoff;
}