#ifndef _HTIF_H_
#define _HTIF_H_

#include "memif.h"
#include <vector>
#include <string>
#include <map>
class Htif : public  ChunkedMemif {
public:
	Htif();
	Htif(int argc, char** argv);
	Htif(const std::vector<std::string>& args);
	virtual ~Htif();
	int run();
	void start();

private:
	void ParseArguments(int argc, char** argv);
	MemIf mem;
	reg_t entry;
	addr_t tohost_addr;
	addr_t fromhost_addr;
	unsigned int line_size;
	friend class memif_t;
	std::vector<std::string> targs;
	virtual void load_program();
	virtual std::map<std::string, uint64_t> load_payload(const std::string& payload, reg_t* entry);

};
#endif 