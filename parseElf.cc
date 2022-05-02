#include <cstring>
#include <string>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <assert.h>
#include <unistd.h>
#include <stdexcept>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>

#include "parseElf.h"
std::map<std::string, uint64_t> load_elf(const char* fn, MemIf* memif, reg_t* entry) {
	int fd = open(fn, O_RDONLY);
	struct stat s;
	fstat(fd, &s);
	size_t size = s.st_size;

	char* buf = (char*)mmap(NULL,size,PROT_READ,MAP_PRIVATE,fd,0);

	close(fd);

	std::vector<uint8_t> zeros;

	std::map<std::string, uint64_t> symbols;

	#define LOAD_ELF(ehdr_t, phdr_t, shdr_t, sym_t)                         					\
		do {                                                                					\
			ehdr_t* eh = (ehdr_t*)buf;															\
			phdr_t* ph = (phdr_t*)(buf+eh->e_phoff);											\
			*entry = eh->e_entry;																\
			for (unsigned i = 0; i < eh->e_phnum; i++) {										\
				if (ph[i].p_filesz) {															\
					memif->Write(ph[i].p_paddr,ph[i].p_filesz, (uint8_t*)buf+ph[i].p_offset);	\
				}																				\
			}																					\
		} while(0) 																			
	LOAD_ELF(Elf64_Ehdr, Elf64_Phdr, Elf64_Shdr, Elf64_Sym);
	munmap(buf,size);
	return symbols;
}