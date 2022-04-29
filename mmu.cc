#include "mmu.h"
#include <string>
#include <memory>
bool mmu_t::mmio_load(reg_t addr, size_t len, uint8_t* bytes) {
	return sim->mmio_load(addr, len, bytes);
}


reg_t mmu_t::translate(reg_t addr, reg_t len, access_type type, uint32_t xlate_flags) {
	if (!proc)
		return addr;
	return addr;
}

tlb_entry_t mmu_t::refill_tlb(reg_t vaddr, reg_t paddr, char* host_addr, access_type type)
{
  reg_t idx = (vaddr >> PGSHIFT) % TLB_ENTRIES;
  reg_t expected_tag = vaddr >> PGSHIFT;

  tlb_entry_t entry = {host_addr - vaddr, paddr - vaddr};

  // if (proc && get_field(proc->state.mstatus->read(), MSTATUS_MPRV))
  //   return entry;

  if ((tlb_load_tag[idx] & ~TLB_CHECK_TRIGGERS) != expected_tag)
    tlb_load_tag[idx] = -1;
  if ((tlb_store_tag[idx] & ~TLB_CHECK_TRIGGERS) != expected_tag)
    tlb_store_tag[idx] = -1;
  if ((tlb_insn_tag[idx] & ~TLB_CHECK_TRIGGERS) != expected_tag)
    tlb_insn_tag[idx] = -1;

  // if ((check_triggers_fetch && type == FETCH) ||
  //     (check_triggers_load && type == LOAD) ||
  //     (check_triggers_store && type == STORE))
  //   expected_tag |= TLB_CHECK_TRIGGERS;

 // if (pmp_homogeneous(paddr & ~reg_t(PGSIZE - 1), PGSIZE)) {
    if (type == FETCH) tlb_insn_tag[idx] = expected_tag;
    else if (type == STORE) tlb_store_tag[idx] = expected_tag;
    else tlb_load_tag[idx] = expected_tag;
  //}

  tlb_data[idx] = entry;
  return entry;
}

void mmu_t::load_slow_path(reg_t addr, reg_t len, uint8_t* bytes, uint32_t xlate_flags) {
	reg_t paddr = translate(addr, len, LOAD,xlate_flags);
	if (auto host_addr = sim->addr_to_mem(paddr)) {
		memcpy(bytes, host_addr, len);
		refill_tlb(addr, paddr, host_addr, LOAD);
	} else if (!mmio_load(paddr, len, bytes)) {

	}
}

