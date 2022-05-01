#include <fcntl.h>
#include <sys/stat.h>
std::map<std::string, uint64_t> load_elf(const char* fn, memif_t* memif, reg_t* entry) {
	int fd = open(fn, O_RDONLY);
	fstat(fd, &s);
	size_t size = s.st_size;

	char* buf = (char*)mmap(NULL,size,PROT_READ,MAP_PRIVATE,fd,0);

	close(fd);

	std::vector<uint8_t> zeros;

	std::map<std::string, uint64_t> symbols;

	#define LOAD_ELF(ehdr_t, phdr_t, shdr_t, sym_t, bswap)
}