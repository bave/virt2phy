#include "v2p.hpp"

#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>

static int pages = 10;

#define PROT (PROT_READ | PROT_WRITE)
#define FLAG (MAP_PRIVATE |  MAP_ANONYMOUS | MAP_HUGETLB)
//#define FLAG (MAP_PRIVATE |  MAP_ANONYMOUS | MAP_HUGE_2MB)
//#define FLAG (MAP_PRIVATE |  MAP_ANONYMOUS | MAP_HUGE_1GB)


int main()
{
    uint8_t* addr;

    uint32_t ps = getpagesize();

    printf("ps:%d\n", ps);

    addr = (uint8_t*)mmap(NULL, ps*pages, PROT, FLAG, 0, 0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    for (int i=0; i<(ps*pages); i++) {
        addr[i] = (uint8_t)i;
    }

    printf("virtual  : physical\n");
    for (int i=0; i<pages*2; i++) {
        printf("%p : 0x%012lx\n", (void*)&addr[ps/2*i], hoge::v2p((void*)&addr[ps/2*i]));
    }

    munmap(addr, ps*pages);

    return 0;
}
