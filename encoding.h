#ifndef RISCV_CSR_ENCODING_H
#define RISCV_CSR_ENCODING_H


#define MATCH_SLLI_RV32 0x1013
#define MASK_SLLI_RV32  0xfe00707f
#define MATCH_SRLI_RV32 0x5013
#define MASK_SRLI_RV32  0xfe00707f
#define MATCH_SRAI_RV32 0x40005013
#define MASK_SRAI_RV32  0xfe00707f
#define MATCH_FRFLAGS 0x102073
#define MASK_FRFLAGS  0xfffff07f
#define MATCH_FSFLAGS 0x101073
#define MASK_FSFLAGS  0xfff0707f
#define MATCH_FSFLAGSI 0x105073
#define MASK_FSFLAGSI  0xfff0707f
#define MATCH_FRRM 0x202073
#define MASK_FRRM  0xfffff07f
#define MATCH_FSRM 0x201073
#define MASK_FSRM  0xfff0707f
#define MATCH_FSRMI 0x205073
#define MASK_FSRMI  0xfff0707f
#define MATCH_FSCSR 0x301073
#define MASK_FSCSR  0xfff0707f
#define MATCH_FRCSR 0x302073
#define MASK_FRCSR  0xfffff07f
#define MATCH_RDCYCLE 0xc0002073
#define MASK_RDCYCLE  0xfffff07f
#define MATCH_ADDI 0x13
#define MASK_ADDI  0x707f

DECLARE_INSN(addi, MATCH_ADDI, MASK_ADDI)

#endif