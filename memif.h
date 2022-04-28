#ifndef __MEMIF_H_
#define __MEMIF_H_
#include <stdint.h>
#include <stddef.h>

typedef uint64_t reg_t;
typedef int64_t sreg_t;
typedef reg_t addr_t;

class ChunkedMemif {
public:
	virtual void ReadChunk(addr_t addr, size_t len, void* dst) = 0; // 从addr读取数据到dst
	virtual void WriteChunk(addr_t addr, size_t len, const void* src) = 0;
	virtual void ClearChunk(addr_t addr, size_t len) = 0;

	virtual size_t ChunkAlign() = 0;
	virtual size_t ChunkMaxSize() = 0;
};

class MemIf {
public:
	MemIf(ChunkedMemif* chunkMemIf): cmemIf(chunkMemIf) {}
	virtual ~MemIf(){}

	virtual void Read(addr_t addr, size_t len, void* bytes);
	virtual void Write(addr_t addr, size_t len, const void* bytes);

	virtual uint8_t ReadUint8(addr_t addr);
	virtual int8_t ReadInt8(addr_t addr);

	virtual void WriteUint8(addr_t addr, uint8_t val);
	virtual void WriteInt8(addr_t addr, int8_t val);
protected:
	ChunkedMemif * cmemIf;
};
#endif
