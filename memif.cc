#include "memif.h"

#include <algorithm>
#include <stdlib.h>
#include <string.h>

void MemIf::Read(addr_t addr, size_t len, void* bytes) {
	size_t align = cmemIf->ChunkAlign();
	if (len && (addr & (align - 1))) {
		size_t this_len = std::min(len , align - size_t(addr & (align - 1 )));
		uint8_t chunk[align];
		cmemIf->ReadChunk(addr &~(align - 1),align,chunk);
		memcpy(bytes, chunk+(addr&(align -1)),this_len);

		bytes = (char*)bytes + this_len;
		addr +=this_len;
		len -= this_len;
	}

	if (len & (align -1)) {
		size_t this_len = len & (align - 1);
		size_t start = len - this_len;
		uint8_t chunk[align];
		cmemIf->ReadChunk(addr + start,align,chunk);
		memcpy((char*)bytes + start, chunk, this_len);
		len -= this_len;
	}

	for (size_t pos = 0; pos < len; pos += cmemIf->ChunkMaxSize())
		cmemIf->ReadChunk(addr + pos, std::min(cmemIf->ChunkMaxSize(),len-pos),(char*)bytes+pos);
}


void MemIf::Write(addr_t addr, size_t len, const void* bytes) {
	bool all_zero = len != 0;
	for (size_t i = 0; i < len; i++)
		all_zero &= ((const char*)bytes)[i] == 0;

	if (all_zero) {
		cmemIf->ClearChunk(addr,len);
	} else {
		size_t max_chunk = cmemIf->ChunkMaxSize();
		for (size_t pos = 0; pos < len; pos += max_chunk)
			cmemIf->WriteChunk(addr + pos, std::min(max_chunk,len - pos),(char*)bytes + pos);
	}
}

#define MEMIF_READ_FUNC \
	this->Read(addr,sizeof(val),&val); \
	return val

#define MEMIF_WRITE_FUNC \
	this->Write(addr, sizeof(val), &val)
	

uint8_t MemIf::ReadUint8(addr_t addr) {
	uint8_t val;
	MEMIF_READ_FUNC;
}

int8_t MemIf::ReadInt8(addr_t addr) {
	int8_t val;
	MEMIF_READ_FUNC;
}


void MemIf::WriteUint8(addr_t addr, uint8_t val) {
	MEMIF_WRITE_FUNC;
}

void MemIf::WriteInt8(addr_t addr, int8_t val) {
	MEMIF_WRITE_FUNC;
}
//void MemIf::WriteUint8
