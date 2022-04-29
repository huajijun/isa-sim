#ifndef _RISCV_SIM_H
#define _RISCV_SIM_H
// Description : Add Sim Module

class Sim: public Htif, public SimIf {
public:
	Sim(const cfg_t *cfg, bool halted,
        std::vector<std::pair<reg_t, mem_t*>> mems,
        const std::vector<std::string>& args);
	~Sim();
private:
	isa_parser_t isa;
	const cfg_t * const cfg;
	std::vector<std::pair<reg_t, mem_t*>> mems;
	mmu_t* debug_mmu;  // debug port into main memory
	std::vector<processor_t*> procs;
	bus_t bus;
};
#endif