#ifndef _RISCV_DEVICES_H_
#define _RISCV_DEVICES_H_
#include <map>
#include <vector>
#include <utility>
#include <cstring>
#include "common.h"
#include "abstract_device.h"


class bus_t : public AbstractDevice {
public:
	bool load(reg_t addr, size_t len , uint8_t *bytes);
	bool store(reg_t addr, size_t len, const uint8_t* bytes);
	void add_device(reg_t addr, AbstractDevice* dev);

	std::pair<reg_t,AbstractDevice*>  find_device(reg_t addr);

private:
	std::map<reg_t,AbstractDevice*> devices;
};

// class RomDevice :public AbstractDevice {
// public:
// 	RomDevice(std::vector<char> data);
// 	bool load(reg_t addr, size_t len , uint8_t *bytes);
// 	bool store(reg_t addr, size_t len, const uint8_t* bytes);
// 	const std::vector<char>& contents() {return data;}
// private:
// 	std::vector<char> data;
// };

class Mem:public AbstractDevice {
public:
  Mem(reg_t size);
  Mem(const Mem& that) = delete;
  ~Mem();

  bool load(reg_t addr, size_t len, uint8_t* bytes) { return load_store(addr, len, bytes, false); }
  bool store(reg_t addr, size_t len, const uint8_t* bytes) { return load_store(addr, len, const_cast<uint8_t*>(bytes), true); }
  reg_t size() { return sz; }
  char* contents(reg_t addr);

 private:
  bool load_store(reg_t addr, size_t len, uint8_t* bytes, bool store);

  std::map<reg_t, char*> sparse_memory_map;
  reg_t sz;
};
#endif