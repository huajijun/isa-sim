#ifndef _RISCV_SIM_H
#define _RISCV_SIM_H
// Description : Add Sim Module
#include "htif.h"
#include "SimIf.h"
#include "devices.h"
#include "proccessor.h"
#include "mmu.h"
#include "context.h"

class Sim: public Htif, public SimIf {
public:
	Sim(const cfg_t *cfg, bool halted,
        std::vector<std::pair<reg_t, Mem*>> mems,
        const std::vector<std::string>& args);
	~Sim(){};

	int run();
private:
//	isa_parser_t isa;
	const cfg_t * const cfg;
	std::vector<std::pair<reg_t, Mem*>> mems;
	mmu_t* debug_mmu;  // debug port into main memory
	std::vector<processor_t*> procs;
	bus_t bus;

	size_t current_proc;


	context_t* host;
	context_t target;

	char* addr_to_mem(reg_t addr);
	bool mmio_store(reg_t addr, size_t len, const uint8_t* bytes);
	bool mmio_load(reg_t addr, size_t len, uint8_t* bytes);
	void proc_reset(unsigned id);
	const char* get_symbol(uint64_t addr);

	void ReadChunk(addr_t addr, size_t len, void* dst); // 从addr读取数据到dst
	void WriteChunk(addr_t addr, size_t len, const void* src);
	void ClearChunk(addr_t addr, size_t len);

	size_t ChunkAlign();
	size_t ChunkMaxSize();

	friend void sim_thread_main(void*);
	void main();
	void reset();
	void set_rom();
	void idle();

	void step(size_t n);
};
#endif