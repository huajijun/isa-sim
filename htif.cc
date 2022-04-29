#include "Htif.h"
Htif::Htif()
	:mem(this), entry(DRAM_BASE),tohost_addr(0),fromhost_addr(0)
	{

	}

Htif::Htif(const std::std::vector<string>& args) : Htif()
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

void Htif::ParseArguments(int argc, char** argv) {
	/*
	*Description:
	*	Add Parse
	*
	*/
}