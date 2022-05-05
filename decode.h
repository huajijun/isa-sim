#ifndef __RISCV_DECODE_
#define __RISCV_DECODE_
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef uint64_t freg_t;
typedef uint64_t insn_bits_t;
const int NXPR = 32;
const int NFPR = 32;

#define READ_REG(reg) ({STATE.XPR[reg]; })
#define sext_xlen(x) (((sreg_t)(x) << (64 - xlen)) >> (64 - xlen))

#define get_field(reg, mask) (((reg) & (decltype(reg))(mask)) / ((mask) & ~((mask) << 1)))
#define insn_length(x) \
	( ((x) & 0x03) < 0x03 ? 2 : \
	  ((x) & 0x1f) < 0x1f ? 4 : \
	  ((x) & 0x3f) < 0x3f ? 6 : \
	  ((x) & 0x7f) < 0x7f ? 4 : \
	  8)

#define RS1 READ_REG(insn.rs1())
#define STATE (*p->get_state())
#define WRITE_REG(reg, value) ({STATE.XPR.write(reg, value); }) 
#define WRITE_RD(value) WRITE_REG(insn.rd(), value)

class insn_t {
public:
	insn_t() = default;
	insn_t(insn_bits_t bits):b(bits){}
	insn_bits_t bits() { return b & ~((UINT64_MAX) << (length() * 8)); }
	int length() { return insn_length(b); }
	int64_t i_imm() { return int64_t(b) >> 20; }
	int64_t shamt() { return x(20, 6); }
	int64_t s_imm() { return x(7, 5) + (xs(25, 7) << 5); }
	int64_t sb_imm() { return (x(8, 4) << 1) + (x(25, 6) << 5) + (x(7, 1) << 11) + (imm_sign() << 12); }
	int64_t u_imm() { return int64_t(b) >> 12 << 12; }
	int64_t uj_imm() { return (x(21, 10) << 1) + (x(20, 1) << 11) + (x(12, 8) << 12) + (imm_sign() << 20); }
	uint64_t rd() { return x(7, 5); }
	uint64_t rs1() { return x(15, 5); }
	uint64_t rs2() { return x(20, 5); }
	uint64_t rs3() { return x(27, 5); }
	uint64_t rm() { return x(12, 3); }
	uint64_t csr() { return x(20, 12); }
	uint64_t iorw() { return x(20, 8); }
	uint64_t bs() { return x(30, 2); } // Crypto ISE - SM4/AES32 byte select.
	uint64_t rcon() { return x(20, 4); } // Crypto ISE - AES64 round const.

	int64_t rvc_imm() { return x(2, 5) + (xs(12, 1) << 5); }
	int64_t rvc_zimm() { return x(2, 5) + (x(12, 1) << 5); }
	int64_t rvc_addi4spn_imm() { return (x(6, 1) << 2) + (x(5, 1) << 3) + (x(11, 2) << 4) + (x(7, 4) << 6); }
	int64_t rvc_addi16sp_imm() { return (x(6, 1) << 4) + (x(2, 1) << 5) + (x(5, 1) << 6) + (x(3, 2) << 7) + (xs(12, 1) << 9); }
	int64_t rvc_lwsp_imm() { return (x(4, 3) << 2) + (x(12, 1) << 5) + (x(2, 2) << 6); }
	int64_t rvc_ldsp_imm() { return (x(5, 2) << 3) + (x(12, 1) << 5) + (x(2, 3) << 6); }
	int64_t rvc_swsp_imm() { return (x(9, 4) << 2) + (x(7, 2) << 6); }
	int64_t rvc_sdsp_imm() { return (x(10, 3) << 3) + (x(7, 3) << 6); }
	int64_t rvc_lw_imm() { return (x(6, 1) << 2) + (x(10, 3) << 3) + (x(5, 1) << 6); }
	int64_t rvc_ld_imm() { return (x(10, 3) << 3) + (x(5, 2) << 6); }
	int64_t rvc_j_imm() { return (x(3, 3) << 1) + (x(11, 1) << 4) + (x(2, 1) << 5) + (x(7, 1) << 6) + (x(6, 1) << 7) + (x(9, 2) << 8) + (x(8, 1) << 10) + (xs(12, 1) << 11); }
	int64_t rvc_b_imm() { return (x(3, 2) << 1) + (x(10, 2) << 3) + (x(2, 1) << 5) + (x(5, 2) << 6) + (xs(12, 1) << 8); }
	int64_t rvc_simm3() { return x(10, 3); }
	uint64_t rvc_rd() { return rd(); }
	uint64_t rvc_rs1() { return rd(); }
	uint64_t rvc_rs2() { return x(2, 5); }
	uint64_t rvc_rs1s() { return 8 + x(7, 3); }
	uint64_t rvc_rs2s() { return 8 + x(2, 3); }

	uint64_t v_vm() { return x(25, 1); }
	uint64_t v_wd() { return x(26, 1); }
	uint64_t v_nf() { return x(29, 3); }
	uint64_t v_simm5() { return xs(15, 5); }
	uint64_t v_zimm5() { return x(15, 5); }
	uint64_t v_zimm10() { return x(20, 10); }
	uint64_t v_zimm11() { return x(20, 11); }
	uint64_t v_lmul() { return x(20, 2); }
	uint64_t v_frac_lmul() { return x(22, 1); }
	uint64_t v_sew() { return 1 << (x(23, 3) + 3); }
	uint64_t v_width() { return x(12, 3); }
	uint64_t v_mop() { return x(26, 2); }
	uint64_t v_lumop() { return x(20, 5); }
	uint64_t v_sumop() { return x(20, 5); }
	uint64_t v_vta() { return x(26, 1); }
	uint64_t v_vma() { return x(27, 1); }
	uint64_t v_mew() { return x(28, 1); }

	uint64_t p_imm2() { return x(20, 2); }
	uint64_t p_imm3() { return x(20, 3); }
	uint64_t p_imm4() { return x(20, 4); }
	uint64_t p_imm5() { return x(20, 5); }
	uint64_t p_imm6() { return x(20, 6); }

private:
	insn_bits_t b;
	uint64_t x(int lo, int len) {
		return (b >> lo) & ((insn_bits_t(1) << len) - 1);
	}
	uint64_t xs(int lo, int len) {
		return int64_t(b) << (64 - lo - len) >>(64 -len);
	}

	uint64_t imm_sign() { return xs(63,1); }
};

template <class T, size_t N, bool zero_reg>
class regfile_t {
public:
	void write(size_t i, T value) {
		if (!zero_reg || i != 0)
			data[i] = value;
	}
	const T& operator[] (size_t i) const {
		return data[i];
	}

	regfile_t(){
		reset();
	}
	void reset() {
		memset(data, 0, sizeof(data));
	}
private:
	T data[N];
};

#endif