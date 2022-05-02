#include <stdio.h>
#include <ucontext.h>
#include <iostream>


static ucontext_t ctx[3];


static void
f1 (unsigned int a, unsigned int b)
{
    puts("start f1");
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    swapcontext(&ctx[1], &ctx[2]);
    puts("finish f1");
}


static void
f2 (void)
{
    puts("start f2");
    swapcontext(&ctx[2], &ctx[1]);
    puts("finish f2");
}


int
main (void)
{
    char st1[8192];
    char st2[8192];

    int a = 2;
    int b= 3;
    getcontext(&ctx[1]);
    ctx[1].uc_stack.ss_sp = st1;
    ctx[1].uc_stack.ss_size = sizeof st1;
    ctx[1].uc_link = &ctx[0];
    makecontext(&ctx[1], f1, 2, a,b);


    getcontext(&ctx[2]);
    ctx[2].uc_stack.ss_sp = st2;
    ctx[2].uc_stack.ss_size = sizeof st2;
    ctx[2].uc_link = &ctx[1];
    makecontext(&ctx[2], f2, 0);


    swapcontext(&ctx[0], &ctx[2]);
    return 0;
}
