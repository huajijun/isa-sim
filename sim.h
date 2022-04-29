#ifndef _RISCV_SIM_H
#define _RISCV_SIM_H
// Description : Add Sim Module
#include "htif.h"
#include "SimIf.h"
#include "devices.h"
#include "proccessor.h"
#include "mmu.h"
class Sim: public Htif, public SimIf {
public:
	Sim(const cfg_t *cfg, bool halted,
        std::vector<std::pair<reg_t, Mem*>> mems,
        const std::vector<std::string>& args);
	~Sim();


private:
//	isa_parser_t isa;
	const cfg_t * const cfg;
	std::vector<std::pair<reg_t, Mem*>> mems;
	mmu_t* debug_mmu;  // debug port into main memory
	std::vector<processor_t*> procs;
	bus_t bus;

	char* addr_to_mem(reg_t addr);
	bool mmio_store(reg_t addr, size_t len, const uint8_t* bytes);
};
#endif