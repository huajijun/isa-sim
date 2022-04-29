#ifndef _RISCV_ABSTRACT_DEVICE_H_
#define _RISCV_ABSTRACT_DEVICE_H_

#include <cstdint>
#include <cstddef>

class AbstractDevice {
public:
	virtual bool load(reg_t addr, size_t len , uint8_t *bytes) = 0;
	virtual bool store(reg_t addr, size_t len, const uint8_t* bytes) = 0;
	virtual ~AbstractDevice() {}
};

#endif