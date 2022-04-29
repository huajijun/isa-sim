#ifndef _RISCV_SIMIF_H_
#define _RISCV_SIMIF_H_
typedef int64_t sreg_t;
typedef uint64_t reg_t;

class SimIf {
public:
	virtual char* addr_to_mem(reg_t addr) = 0;
	virtual bool mmio_load(reg_t addr, size_t len, uint8_t* bytes) = 0;
	virtual bool mmio_store(reg_t addr, size_t len, const uint8_t* bytes) = 0;
	// Callback for processors to let the simulation know they were reset.
	virtual void proc_reset(unsigned id) = 0;

	virtual const char* get_symbol(uint64_t addr) = 0;


}
#endif