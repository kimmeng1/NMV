#include <memory.h>
#include <printk.h>
#include <string.h>
#include <x86.h>


#define PHYSICAL_POOL_PAGES  64
#define PHYSICAL_POOL_BYTES  (PHYSICAL_POOL_PAGES << 12)
#define BITSET_SIZE          (PHYSICAL_POOL_PAGES >> 6)


extern __attribute__((noreturn)) void die(void);

static uint64_t bitset[BITSET_SIZE];

static uint8_t pool[PHYSICAL_POOL_BYTES] __attribute__((aligned(0x1000)));


paddr_t alloc_page(void)
{
	size_t i, j;
	uint64_t v;

	for (i = 0; i < BITSET_SIZE; i++) {
		if (bitset[i] == 0xffffffffffffffff)
			continue;

		for (j = 0; j < 64; j++) {
			v = 1ul << j;
			if (bitset[i] & v)
				continue;

			bitset[i] |= v;
			return (((64 * i) + j) << 12) + ((paddr_t) &pool);
		}
	}

	printk("[error] Not enough identity free page\n");
	return 0;
}

void free_page(paddr_t addr)
{
	paddr_t tmp = addr;
	size_t i, j;
	uint64_t v;

	tmp = tmp - ((paddr_t) &pool);
	tmp = tmp >> 12;

	i = tmp / 64;
	j = tmp % 64;
	v = 1ul << j;

	if ((bitset[i] & v) == 0) {
		printk("[error] Invalid page free %p\n", addr);
		die();
	}

	bitset[i] &= ~v;
}


/*
 * Memory model for Rackdoll OS
 *
 * +----------------------+ 0xffffffffffffffff
 * | Higher half          |
 * | (unused)             |
 * +----------------------+ 0xffff800000000000
 * | (impossible address) |
 * +----------------------+ 0x00007fffffffffff
 * | User                 |
 * | (text + data + heap) | 
 * +----------------------+ 0x2000000000
 * | User                 |   
 * | (stack)              |	
 * +----------------------+ 0x40000000
 * | Kernel               |
 * | (valloc)             |
 * +----------------------+ 0x201000
 * | Kernel               |
 * | (APIC)               |
 * +----------------------+ 0x200000
 * | Kernel               |
 * | (text + data)        |
 * +----------------------+ 0x100000
 * | Kernel               |
 * | (BIOS + VGA)         |
 * +----------------------+ 0x0
 *
 * This is the memory model for Rackdoll OS: the kernel is located in low
 * addresses. The first 2 MiB are identity mapped and not cached.
 * Between 2 MiB and 1 GiB, there are kernel addresses which are not mapped
 * with an identity table.
 * Between 1 GiB and 128 GiB is the stack addresses for user processes growing
 * down from 128 GiB.
 * The user processes expect these addresses are always available and that
 * there is no need to map them explicitely.
 * Between 128 GiB and 128 TiB is the heap addresses for user processes.
 * The user processes have to explicitely map them in order to use them.
 */


void map_page(struct task *ctx, vaddr_t vaddr, paddr_t paddr)
{
	int lvl, index;
	vaddr_t *page_entry = (vaddr_t *) ctx->pgt;
	paddr_t addr_mask = 0x0000FFFFFFFFF000;

	for (lvl = 4; lvl > 1; --lvl){	
		index = ((vaddr>>(12+((lvl-1)*9)))<<55)>>55;
		page_entry = page_entry + index;
		
		if (!(*page_entry & 0x1)) /* if empty or invalid */
			*page_entry = (paddr_t)alloc_page() | 0x7; /* U/S + R/W + P */
		
		page_entry = *page_entry & addr_mask; /* mask the bits */
	}

	index = ((vaddr>>(12+((lvl-1)*9)))<<55)>>55;
	page_entry = page_entry + index;
	*page_entry = paddr | 0x7; /* U/S + R/W + P */
}

void load_task(struct task *ctx)
{
	paddr_t pml4 = alloc_page();
	paddr_t pml3 = alloc_page();
	paddr_t pml2 = alloc_page();
	paddr_t pml1 = alloc_page();

	((paddr_t*)pml4)[0] = pml3 | 0x7;  // U/S | R/W | P
	((paddr_t*)pml3)[0] = pml2 | 0x7;  // U/S | R/W | P

	// kernel
	((paddr_t*)pml2)[0] = 0x0 | 0x19b; // G | PS | PCD | PWT | R/W | P
	((paddr_t*)pml1)[0] = 0xfee00000 | 0x11b;

	ctx->pgt = pml4;

	map_page(ctx, ctx->load_vaddr, ctx->load_paddr);

}

void set_task(struct task *ctx)
{
	load_cr3(ctx->pgt);
}

void mmap(struct task *ctx, vaddr_t vaddr)
{
	paddr_t paddr = alloc_page();
	map_page(ctx, vaddr, paddr);
}

void munmap(struct task *ctx, vaddr_t vaddr)
{	
	int lvl, index;
		vaddr_t *page_entry = (vaddr_t *) ctx->pgt;
		paddr_t addr_mask = 0x0000FFFFFFFFF000;

		for (lvl = 4; lvl > 1; --lvl){	
			index = ((vaddr>>(12+((lvl-1)*9)))<<55)>>55;
			page_entry = page_entry + index;
			
			// if ((*page_entry & 0x1)) /* if empty or invalid */
			// 	free_page(*page_entry);
			
			page_entry = *page_entry & addr_mask; /* mask the bits */
		}

		index = ((vaddr>>(12+((lvl-1)*9)))<<55)>>55;
		page_entry = page_entry + index;
		free_page(*page_entry);
}

void pgfault(struct interrupt_context *ctx)
{
	/* if legitimate memory access */
	if(store_cr2() > 0x40000000 && store_cr2() < 0x00007fffffffffff) {
		//task.h: struct task *current(void); /* Get the current task */
		mmap(current(), store_cr2());
	}else{
		("Page fault at %p\n", ctx->rip);
		printk("  cr2 = %p\n", store_cr2());
		asm volatile ("hlt");
	}
}

void duplicate_task(struct task *ctx)
{
}
