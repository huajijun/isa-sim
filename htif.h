#ifndef _HTIF_H_
#define _HTIF_H_

#include "memif.h"

class Htif : public  ChunkedMemif {
public:
	Htif();
	Htif(int argc, char** argv);
	Htif(const std::std::vector<string>& args);
	virtual ~Htif();

private:
	void ParseArguments(int argc, char** argv);
	MemIf mem;
	reg_t entry;
	addr_t tohost_addr;
	addr_t fromhost_addr;
	unsigned int line_size;
	friend class memif_t;
	std::vector<std::string> targs;
};
#endif 