#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>

#define BUFF_SZ 1024

#define PML4_ENTRY(addr)	(( addr >> 39 ) & ENTRY_MASK)
#define PDPT_ENTRY(addr)	(( addr >> 30 ) & ENTRY_MASK)
#define PD_ENTRY(addr)		(( addr >> 21 ) & ENTRY_MASK)
#define PT_ENTRY(addr)		(( addr >> 12 ) & ENTRY_MASK)

#define ENTRY_TABLE_ADDR(entry, page_sz) 	(( ( entry >> 12 ) & 0xFFFFFFFFFF ) * page_sz)

#define FETCH_IO_DATA_U32   (*(uint32_t*)( (uint8_t*)vm.kvm_run + vm.kvm_run->io.data_offset ))
#define FETCH_IO_DATA_U8    (*( (uint8_t*)vm.kvm_run + vm.kvm_run->io.data_offset ))
#define VM_MEM_AT(vaddr)    (vm.mem + (uint64_t)vaddr)

#define ENTRY_MASK              0x1FF
#define ENTRY_TABLE_ADDR_MASK   0xFFFFFFFFFF000

#define PDE64_PRESENT   1
#define PDE64_RW        (1U << 1)
#define PDE64_USER      (1U << 2)
#define PDE64_PS        (1U << 7)

// CR4
#define CR4_PAE (1U << 5)

// CR0
#define CR0_PE 1u
#define CR0_PG (1U << 31)

#define EFER_LME (1U << 8)
#define EFER_LMA (1U << 10)

struct vm_args {
	size_t mem_sz;
	size_t page_sz; 
	const char* guest_image;
	char** files;
    int file_cnt;
	int id;
};


struct vm {
	int kvm_fd;
	int vm_fd;
	int vcpu_fd;
	char *mem;
	struct kvm_run *kvm_run;
};


/*  Structures and constants needed for working with files  */

#ifndef O_RDONLY
# define O_RDONLY   00
#endif
#ifndef O_WRONLY
# define O_WRONLY   01
#endif
#ifndef O_RDWR
# define O_RDWR     02
#endif
#ifndef O_CREAT
# define O_CREAT    0100
#endif
#ifndef O_TRUNC
# define O_TRUNC    01000	
#endif
#ifndef O_APPEND
# define O_APPEND   02000
#endif

#ifndef SEEK_SET
# define SEEK_SET	0	
#endif
#ifndef SEEK_SET
# define SEEK_CUR	1
#endif
#ifndef SEEK_SET	
# define SEEK_END	2
#endif

#define OPEN    1
#define CLOSE   2
#define READ    3
#define WRITE   4
#define SEEK    5

#if !defined(ssize_t)
    typedef long ssize_t;
#endif
#if !defined(size_t)
    typedef long unsigned int size_t;
#endif
#if !defined(off_t)
    typedef long off_t;
#endif

struct io_open {
    const char* filename;
    int flags;
};

struct io_rw {
    const void* buffer;
    int n;
};

struct io_seek {
    off_t offset;
    int whence;
};

struct io_struct {
    union {
        struct  io_open io_open;
        struct  io_rw io_rw;
        struct  io_seek io_seek;
    };
    uint8_t type;  
    int fd;
    uint64_t ret;
};




#endif