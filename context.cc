#include "context.h"
static __thread context_t* cur;


context_t::context_t()
: creator(NULL),func(NULL), arg(NULL),context(new ucontext_t) {
	
}

void context_t::init(void (*f)(void*), void* a) {
	func = f;
	arg = a;
	creator = current();
	getcontext(context.get());
	context->uc_link = creator->context.get();
	context->uc_stack.ss_size = 64*1024;
	context->uc_stack.ss_sp = new void*[context->uc_stack.ss_size/sizeof(void*)];

	unsigned int hi(reinterpret_cast<unsigned long>(this) >> 32);
	unsigned int lo(reinterpret_cast<unsigned long>(this));
	makecontext(context.get(), (void(*)(void))&context_t::wrapper, 2, hi, lo);
	switch_to();
}

context_t::~context_t()
{
	assert(this != cur);
}
void context_t::wrapper(unsigned int hi, unsigned int lo){
	context_t* ctx = reinterpret_cast<context_t*>(static_cast<unsigned long>(lo) | (static_cast<unsigned long>(hi) << 32));
	ctx->creator->switch_to();
	ctx->func(ctx->arg);
}

context_t* context_t::current() {
	if (cur == NULL) {
		cur = new context_t;
		getcontext(cur->context.get());
	}
	return cur;
}

void context_t::switch_to() {
	assert(this != cur);
	context_t* prev = cur;
	cur = this;
	if (swapcontext(prev->context.get(), context.get()) != 0)
		return;
}