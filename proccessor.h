#ifndef __RISCV__PROCESSOR_
#define __RISCV__PROCESSOR_ 
#include "decode.h"
#include <vector>
#include "common.h"
#include "SimIf.h"
#include "abstract_device.h"
#include "csrs.h"

#define IRQ_U_SOFT   0
#define IRQ_S_SOFT   1
#define IRQ_VS_SOFT  2
#define IRQ_M_SOFT   3
#define IRQ_U_TIMER  4
#define IRQ_S_TIMER  5
#define IRQ_VS_TIMER 6
#define IRQ_M_TIMER  7
#define IRQ_U_EXT    8
#define IRQ_S_EXT    9
#define IRQ_VS_EXT   10
#define IRQ_M_EXT    11
#define IRQ_S_GEXT   12
#define IRQ_COP      12
#define IRQ_HOST     13

#define MIP_USIP            (1 << IRQ_U_SOFT)
#define MIP_SSIP            (1 << IRQ_S_SOFT)
#define MIP_VSSIP           (1 << IRQ_VS_SOFT)
#define MIP_MSIP            (1 << IRQ_M_SOFT)
#define MIP_UTIP            (1 << IRQ_U_TIMER)
#define MIP_STIP            (1 << IRQ_S_TIMER)
#define MIP_VSTIP           (1 << IRQ_VS_TIMER)
#define MIP_MTIP            (1 << IRQ_M_TIMER)
#define MIP_UEIP            (1 << IRQ_U_EXT)
#define MIP_SEIP            (1 << IRQ_S_EXT)
#define MIP_VSEIP           (1 << IRQ_VS_EXT)
#define MIP_MEIP            (1 << IRQ_M_EXT)
#define MIP_SGEIP           (1 << IRQ_S_GEXT)



typedef std::shared_ptr<mip_csr_t> mip_csr_t_p;


class processor_t;
class mmu_t;
template<uint64_t N>
struct type_usew_t;

template<>
struct type_usew_t<8>
{
  using type=uint8_t;
};

template<>
struct type_usew_t<16>
{
  using type=uint16_t;
};

template<>
struct type_usew_t<32>
{
  using type=uint32_t;
};

template<>
struct type_usew_t<64>
{
  using type=uint64_t;
};

typedef reg_t(*insn_func_t)(processor_t*,insn_t,reg_t);
reg_t illegal_instruction(processor_t* p, insn_t insn, reg_t pc);
struct insn_desc_t {
	bool supported;
	insn_bits_t match;
	insn_bits_t mask;
	insn_func_t rv32i;
	insn_func_t rv64i;
	insn_func_t rv32e;
	insn_func_t rv64e;

	insn_func_t func(int xlen, bool rve) {
		if (!supported) {
			return NULL;
		}
		if (rve)
			return xlen == 64? rv64e:rv32e;
		else
			return xlen == 64? rv64i:rv32i;
	}
	static insn_desc_t illegal()
	{
		return {true, 0, 0, &illegal_instruction, &illegal_instruction, &illegal_instruction, &illegal_instruction};
	}


};

struct state_t {
	void reset(processor_t* const proc, reg_t max_isa);

	reg_t pc;
	regfile_t<reg_t, NXPR, true> XPR;
	regfile_t<freg_t, NFPR, false> FPR;
	mip_csr_t_p mip;
};

class processor_t : public AbstractDevice {
public:
	processor_t(SimIf* sim);
	~processor_t(){};
	state_t* get_state() { return &state; }
	void step(size_t n);
private:
	SimIf* sim;
	mmu_t* mmu;
	state_t state;
//	disassembler_t* disassembler;
	void register_base_instructions();
	void register_insn(insn_desc_t desc);
	std::vector<insn_desc_t> instructions;
	void build_opcode_map();
	static const size_t OPCODE_CACHE_SIZE = 8191;
	insn_desc_t opcode_cache[OPCODE_CACHE_SIZE];
	bool load(reg_t addr, size_t len , uint8_t *bytes);
	bool store(reg_t addr, size_t len, const uint8_t* bytes);
	



};
#endif