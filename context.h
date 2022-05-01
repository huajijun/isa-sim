#ifndef _HTIF_CONTEXT_H
#define _HTIF_CONTEXT_H
#include <pthread.h>
#include <ucontext.h>
#include <memory> 
#include <cassert>

class context_t {
public:
	context_t();
	~context_t();
	void init(void (*func)(void*), void* arg);
	void switch_to();
	static context_t* current();
private:
	context_t* creator;
	void (*func)(void*);
	void *arg;
	std::unique_ptr<ucontext_t> context;
	void wrapper(unsigned int hi, unsigned int lo);
};
#endif