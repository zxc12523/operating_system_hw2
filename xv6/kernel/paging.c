#include "param.h"
#include "types.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "defs.h"
#include "proc.h"

/* NTU OS 2022 */
/* Page fault handler */
int handle_pgfault(uint64 addr)
{
  /* Find the address that caused the fault */
  /* uint64 va = r_stval(); */

  /* TODO */

  struct proc *p = myproc();

  char *mem = kalloc();

  if (mem == 0)
  {
    // printf("lazy_alloc: kalloc failed\n");
    return -3;
  }

  memset(mem, 0, PGSIZE);

  pte_t *pte = walk(p->pagetable, addr, 1);

  if (*pte & PTE_S)
  {
    begin_op();
    read_page_from_disk(1, mem, PTE2BLOCKNO(*pte));
    bfree_page(1, PTE2BLOCKNO(*pte));
    end_op();
    // printf("%p\n", pg);
    *pte &= PXMASK;
    *pte |= PA2PTE((uint64)mem);
    *pte ^= PTE_V;
  }
  else
  {
    // printf("addr: %p p->sz: %p\n", addr, p->sz);
    if (addr >= p->sz)
    {
      // printf("lazy_alloc: access invalid address\n");
      return -1;
    }

    if (addr < p->trapframe->sp)
    {
      // printf("lazy_alloc: access address below stack\n");
      return -2;
    }

    addr = PGROUNDDOWN(addr);

    if (mappages(p->pagetable, addr, PGSIZE, (uint64)mem, PTE_R | PTE_W | PTE_X | PTE_U) < 0)
    {
      kfree(mem);
      return -4;
    }
  }
  return 0;
}
