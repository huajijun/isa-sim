#include "sim.h"
#include "mmu.h"

void sim_thread_main(void* arg)
{
	(((Sim*)arg)->main());
}

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
	procs[0] = new processor_t(this);
}

char* Sim::addr_to_mem(reg_t addr) {
	auto desc = bus.find_device(addr);

	if (auto mem = dynamic_cast<Mem*>(desc.second))
		if (addr - desc.first  < mem->size())
			return mem->contents(addr - desc.first);
	return NULL;
}


int Sim::run() {
	host = context_t::current();
	target.init(sim_thread_main,this);
	return Htif::run();
}



bool Sim::mmio_store(reg_t addr, size_t len, const uint8_t* bytes) {
	if (addr + len < addr)
		return false;
	return bus.store(addr, len, bytes);
}


bool Sim::mmio_load(reg_t addr, size_t len, uint8_t* bytes) 
{ 
	return false; 
}
	// Callback for processors to let the simulation know they were reset.
void Sim::proc_reset(unsigned id) {

}

const char* Sim::get_symbol(uint64_t addr) { 
	return NULL; 
}

void Sim::main()
{
	step(50000);
}

void Sim::step(size_t n)
{

}









void Sim::ReadChunk(addr_t addr, size_t len, void* dst) 
{

}
void Sim::WriteChunk(addr_t addr, size_t len, const void* src) 
{

}
void Sim::ClearChunk(addr_t addr, size_t len)
{

}

size_t Sim::ChunkAlign() 
{
	return 0;
}
size_t Sim::ChunkMaxSize() 
{
	return 0;
}

void Sim::set_rom() 
{
	/* need do*/
}
void Sim::reset()
{
	set_rom();
}

void Sim::idle()
{
	target.switch_to();
}