#ifndef _HTIF_CONTEXT_H
#define _HTIF_CONTEXT_H
#include <pthread.h>
#include <ucontext.h>
#include <memory> 
#include <cassert>

static_assert (sizeof(unsigned int)  == 4, "uint size doesn't match expected 32bit");
static_assert (sizeof(unsigned long) == 8, "ulong size doesn't match expected 64bit");
static_assert (sizeof(void*)         == 8, "ptr size doesn't match expected 64bit");

class context_t
{
 public:
  context_t();
  ~context_t();
  void init(void (*func)(void*), void* arg);
  void switch_to();
  static context_t* current();
 private:
  context_t* creator;
  void (*func)(void*);
  void* arg;
  std::unique_ptr<ucontext_t> context;
  //static void wrapper(unsigned int, unsigned int);
  static void wrapper(context_t* ctx);
};
#endif