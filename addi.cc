#include "common.h"
#include "proccessor.h"
#include "encoding.h"
reg_t rv32i_addi(processor_t* p, insn_t insn, reg_t pc)
{
  #define xlen 32
	reg_t npc = sext_xlen(pc + insn_length( MATCH_ADDI));
	#include "addi.h"
  #undef xlen
	return npc;
}

reg_t rv64i_addi(processor_t* p, insn_t insn, reg_t pc)
{
  #define xlen 64
  reg_t npc = sext_xlen(pc + insn_length( MATCH_ADDI));
  #include "addi.h"
  #undef xlen
  return npc;
}

reg_t rv32e_addi(processor_t* p, insn_t insn, reg_t pc)
{
  #define xlen 32
  reg_t npc = sext_xlen(pc + insn_length( MATCH_ADDI));
  #include "addi.h"
  #undef xlen
  return npc;
}

reg_t rv64e_addi(processor_t* p, insn_t insn, reg_t pc)
{
  #define xlen 64
  reg_t npc = sext_xlen(pc + insn_length( MATCH_ADDI));
  #include "addi.h"
  #undef xlen
  return npc;
}