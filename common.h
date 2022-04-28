#ifndef zzy
#define zzy
#include <assert.h>
#include <stdint.h>
typedef uint64_t reg_t;
typedef reg_t addr_t;
#define PGSIZE (1 << 12)
#define PGSHIFT 12
#define DEFAULT_ISA "RV64IMAFDC"
#define DEFAULT_PRIV "MSU"
#define DEFAULT_VARCH "vlen:128,elen:64"
#define DRAM_BASE          0x80000000
#endif 
