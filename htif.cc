#include "htif.h"
#include "common.h"
#include <unistd.h>
#include <algorithm>
#include <assert.h>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <getopt.h>

std::map<std::string, uint64_t> Htif::load_payload(const std::string& payload, reg_t* entry) {
	std::string path;
	if (access(payload.c_str(), F_OK) == 0)
		path = payload;
	else {

	}
	if (path.empty()) {

	}
	class preload_aware_memif_t : public MemIf {
	public:
		preload_aware_memif_t(Htif* htif) : MemIf(htif), htif(htif) {}

		void Write(addr_t addr, size_t len, const void* bytes) override {
			MemIf::Write(addr, len, bytes);
		}

		private:
			Htif* htif;
	}preload_aware_memif(this);

	return load_elf(path.c_str(), &preload_aware_memif, entry);
}
void Htif::load_program(){
	std::map<std::string, uint64_t> symbols = load_payload(targs[0], &entry);
}

void Htif::start()
{
	if (!targs.empty() && (targs[0] != "none"))
		load_program();

	reset();
}

int Htif::run()
{
	start();
	if (tohost_addr == 0) {
		while(true)
			idle();
	}

}

Htif::Htif()
	:mem(this), entry(DRAM_BASE),tohost_addr(0),fromhost_addr(0)
	{

	}

Htif::Htif(const std::vector<std::string>& args) : Htif()
{
	int argc = args.size() + 1;
	char * argv[argc];
	argv[0] = (char*) "htif";
	for(unsigned int i = 0; i < args.size(); i++) {
		argv[i + 1] = (char*)args[i].c_str();
	}

	line_size = 16;
	ParseArguments(argc,argv);
}


Htif::~Htif()
{

}
void Htif::ParseArguments(int argc, char** argv) {
	/*
	*Description:
	*	Add Parse
	*
	*/
}