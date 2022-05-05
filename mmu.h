#ifndef __RISCV_MMU_H_
#define __RISCV_MMU_H_
#include "SimIf.h"
#include <stdlib.h>
#include <vector>  
#include <stdint.h>
#include <cstring>
#include <memory>
#include "proccessor.h"

#define PGSHIFT 12
const reg_t PGSIZE1 = 1 << PGSHIFT;
const reg_t PGMASK = ~(PGSIZE1-1);
#define MAX_PADDR_BITS 56 // imposed by Sv39 / Sv48
#define READ_MEM(addr, size) ({})
# define   likely(x) (x)
# define unlikely(x) (x)

struct insn_fetch_t
{
  insn_func_t func;
  insn_t insn;
};


enum access_type {
  LOAD,
  STORE,
  FETCH,
};

struct tlb_entry_t {
	char* host_offset;
	reg_t target_offset;
};

struct icache_entry_t {
  reg_t tag;
  struct icache_entry_t* next;
  insn_fetch_t data;
};




class mmu_t {
private:
//	std::map<reg_t,reg_t> alloc_cache
	static const reg_t TLB_ENTRIES = 256; 
	static const reg_t TLB_CHECK_TRIGGERS = reg_t(1) << 63;
	SimIf* sim;
	processor_t* proc;
	std::vector<std::pair<reg_t,reg_t>> addr_tbl;
	tlb_entry_t tlb_data[TLB_ENTRIES];
	reg_t tlb_insn_tag[TLB_ENTRIES];
	reg_t tlb_load_tag[TLB_ENTRIES];
	reg_t tlb_store_tag[TLB_ENTRIES];

	reg_t translate(reg_t addr, reg_t len, access_type type, uint32_t xlate_flags);
	bool mmio_load(reg_t addr, size_t len, uint8_t* bytes);
	void load_slow_path(reg_t addr, reg_t len, uint8_t* bytes, uint32_t xlate_flags);
	tlb_entry_t refill_tlb(reg_t vaddr, reg_t paddr, char* host_addr, access_type type);
public:
	mmu_t(SimIf* sim, processor_t* proc);
	~mmu_t();

	// #define load_func(type, prefix, xlate_flag) \
	// 	inline 	type##_t prefix##_##type(reg_t addr, bool require_alignment = false) { \
	// 		reg_t vpn = addr >> PGSHIFT; \
	// 		size_t size = sizeof(type##_t); \
	// 		if ((xlate_flags) == 0 && likely(tlb_load_tag[vpn % TLB_ENTRIES] == vpn)) { \
	// 			if (proc) READ_MEM(addr, size); \
	// 			return tlb_data[vpn % TLB_ENTRIES].host_offset + addr; \
	// 		} \
	// 		if ((xlate_flags) == 0 && unlikely(tlb_load_tag[vpn % TLB_ENTRIES] == (vpn | TLB_CHECK_TRIGGERS))) { \
	// 			type##_t data = tlb_data[vpn % TLB_ENTRIES].host_offset + addr; \
	// 			if (proc) READ_MEM(addr, size); \
	// 			return data; \
	// 		} \
	// 		type##_t res; \
	// 		load_slow_path(addr, sizeof(type##_t),(uint8_t*)&res,(xlate_flag)); \
	// 		if (proc) READ_MEM(addr, size); \
	// 		return res;
	// 	}
 #define load_func(type, prefix, xlate_flags) \
    inline type##_t prefix##_##type(reg_t addr, bool require_alignment = false) { \
      reg_t vpn = addr >> PGSHIFT; \
      size_t size = sizeof(type##_t); \
      if ((xlate_flags) == 0 && likely(tlb_load_tag[vpn % TLB_ENTRIES] == vpn)) { \
        if (proc) READ_MEM(addr, size); \
        return (type##_t)(tlb_data[vpn % TLB_ENTRIES].host_offset + addr); \
      } \
      if ((xlate_flags) == 0 && unlikely(tlb_load_tag[vpn % TLB_ENTRIES] == (vpn | TLB_CHECK_TRIGGERS))) { \
        type##_t data = (type##_t)(tlb_data[vpn % TLB_ENTRIES].host_offset + addr); \
        if (proc) READ_MEM(addr, size); \
        return data; \
      } \
      type##_t res; \
      load_slow_path(addr, sizeof(type##_t), (uint8_t*)&res, (xlate_flags)); \
      if (proc) READ_MEM(addr, size); \
      return res; \
    }

	load_func(uint8, load, 0)
	load_func(uint16, load, 0)
	load_func(uint32, load, 0)
	load_func(uint64, load, 0)


	inline icache_entry_t* refill_icache(reg_t addr, icache_entry_t* entry)
	{
		// auto tlb_entry = translate_insn_addr(addr);
		// insn_bits_t insn = from_le(*(uint16_t*)(tlb_entry.host_offset + addr));
		// int length = insn_length(insn);

		// if (likely(length == 4)) {
		//   insn |= (insn_bits_t)from_le(*(const int16_t*)translate_insn_addr_to_host(addr + 2)) << 16;
		// } else if (length == 2) {
		//   insn = (int16_t)insn;
		// } else if (length == 6) {
		//   insn |= (insn_bits_t)from_le(*(const int16_t*)translate_insn_addr_to_host(addr + 4)) << 32;
		//   insn |= (insn_bits_t)from_le(*(const uint16_t*)translate_insn_addr_to_host(addr + 2)) << 16;
		// } else {
		//   static_assert(sizeof(insn_bits_t) == 8, "insn_bits_t must be uint64_t");
		//   insn |= (insn_bits_t)from_le(*(const int16_t*)translate_insn_addr_to_host(addr + 6)) << 48;
		//   insn |= (insn_bits_t)from_le(*(const uint16_t*)translate_insn_addr_to_host(addr + 4)) << 32;
		//   insn |= (insn_bits_t)from_le(*(const uint16_t*)translate_insn_addr_to_host(addr + 2)) << 16;
		// }

		// insn_fetch_t fetch = {proc->decode_insn(insn), insn};
		// entry->tag = addr;
		// entry->next = &icache[icache_index(addr + length)];
		// entry->data = fetch;

		// reg_t paddr = tlb_entry.target_offset + addr;;
		// if (tracer.interested_in_range(paddr, paddr + 1, FETCH)) {
		//   entry->tag = -1;
		//   tracer.trace(paddr, length, FETCH);
		// }
		return entry;
	}



	inline insn_fetch_t load_insn(reg_t addr)
	{
		icache_entry_t entry;
		return refill_icache(addr, &entry)->data;
	}



};
#endif