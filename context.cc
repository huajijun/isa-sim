#include "context.h"
static __thread context_t* cur;


context_t::context_t()
  : creator(NULL), func(NULL), arg(NULL),context(new ucontext_t)
  {

  }
void context_t::wrapper(context_t* ctx)
{
	ctx->creator->switch_to();
	ctx->func(ctx->arg);
}

void context_t::init(void (*f)(void*), void* a)
{
  func = f;
  arg = a;
  creator = current();
  getcontext(context.get());
  context->uc_link = creator->context.get();
  context->uc_stack.ss_size = 64*1024;
  context->uc_stack.ss_sp = new void*[context->uc_stack.ss_size/sizeof(void*)];
  makecontext(context.get(), (void(*)(void))&context_t::wrapper, 1, this);
  switch_to();
}

context_t::~context_t()
{
  assert(this != cur);
}

void context_t::switch_to()
{
  assert(this != cur);
  context_t* prev = cur;
  cur = this;
  if (swapcontext(prev->context.get(), context.get()) != 0)
    return;
}

context_t* context_t::current()
{
  if (cur == NULL)
  {
    cur = new context_t;
    getcontext(cur->context.get());
  }
  return cur;
}