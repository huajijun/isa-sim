#include "csrs.h"

csr_t::csr_t(processor_t* const proc, const reg_t addr):
  proc(proc),
  state(proc->get_state()),
  address(addr) {
}

csr_t::~csr_t() {
}

void csr_t::write(const reg_t val) noexcept {

}


mip_or_mie_csr_t::mip_or_mie_csr_t(processor_t* const proc, const reg_t addr):
  csr_t(proc, addr),
  val(0) {
}


reg_t mip_or_mie_csr_t::read() const noexcept {
  return val;
}



mip_csr_t::mip_csr_t(processor_t* const proc, const reg_t addr):
  mip_or_mie_csr_t(proc, addr) {
}

reg_t mip_csr_t::write_mask() const noexcept {
	return 0;
}

