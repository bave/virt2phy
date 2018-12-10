#include "v2p.hpp"

#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>

static int pages = 10;

int main()
{
    uint8_t* addr;

    uint32_t ps = getpagesize();

    printf("ps:%d\n", ps);

    posix_memalign((void**)&addr, ps, ps*pages);

    for (int i=0; i<(ps*pages); i++) {
        addr[i] = (uint8_t)i;
    }

    printf("virtual  : physical\n");
    for (int i=0; i<pages*2; i++) {
        printf("%p : 0x%012lx\n", (void*)&addr[ps/2*i], hoge::v2p((void*)&addr[ps/2*i]));
    }

    free(addr);

    return 0;
}
