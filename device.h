
#include "common.h"
#include <map>
#include <string.h>
class abstract_device_t {
 public:
  virtual bool load(reg_t addr, size_t len, uint8_t* bytes) = 0;
  virtual bool store(reg_t addr, size_t len, const uint8_t* bytes) = 0;
  virtual ~abstract_device_t() {}
};



class mem_t : public abstract_device_t {
 public:
  mem_t(reg_t size);
  mem_t(const mem_t& that) = delete;
  ~mem_t();

  bool load(reg_t addr, size_t len, uint8_t* bytes) { return load_store(addr, len, bytes, false); }
  bool store(reg_t addr, size_t len, const uint8_t* bytes) { return load_store(addr, len, const_cast<uint8_t*>(bytes), true); }
  char* contents(reg_t addr);
  reg_t size() { return sz; }

 private:
  bool load_store(reg_t addr, size_t len, uint8_t* bytes, bool store);

  std::map<reg_t, char*> sparse_memory_map;
  reg_t sz;
};



