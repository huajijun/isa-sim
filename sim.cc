#include "sim.h"
#include "mmu.h"
Sim::Sim(const cfg_t *cfg, bool halted,
        std::vector<std::pair<reg_t, Mem*>> mems,
        const std::vector<std::string>& args)
        :Htif(args),
        cfg(cfg),
        mems(mems)
{
	for (auto &it : mems)
		bus.add_device(it.first, it.second);

	debug_mmu = new mmu_t(this,NULL);
}

char* Sim::addr_to_mem(reg_t addr) {
	auto desc = bus.find_device(addr);

	if (auto mem = dynamic_cast<Mem*>(desc.second))
		if (addr - desc.first  < mem->size())
			return mem->contents(addr - desc.first);
	return NULL;
}

bool Sim::mmio_store(reg_t addr, size_t len, const uint8_t* bytes) {
	if (addr + len < addr)
		return false;
	return bus.store(addr, len, bytes);
}