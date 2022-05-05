#ifndef __RISCV_CSRS_
#define __RISCV_CSRS_
#include "common.h"
class processor_t;
struct state_t;

class csr_t {
public:
	csr_t(processor_t* const  proc, const reg_t addr);
	virtual reg_t read() const noexcept = 0;
	void write(const reg_t val) noexcept;
	virtual ~csr_t();
protected:
	processor_t* const proc;
	state_t* const state;
public:
	const reg_t address;
};

class mip_or_mie_csr_t: public csr_t {
public:
	mip_or_mie_csr_t(processor_t* const proc, const reg_t addr);
	virtual reg_t read() const noexcept override final;
	virtual reg_t write_mask() const noexcept = 0;
	reg_t val;
};

class  mip_csr_t :public mip_or_mie_csr_t {
public:
	mip_csr_t(processor_t* const proc, const reg_t addr);
	virtual reg_t write_mask() const noexcept override;
	reg_t read(){}
};


typedef std::shared_ptr<mip_csr_t> mip_csr_t_p;

#endif 