#pragma once

#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

class hoge {

    public:
    static uintptr_t v2p(void* v)
    {
        uintptr_t p = 0;
        uint32_t ps = getpagesize();

        int fd = open("/proc/self/pagemap", O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        //printf("%p\n", v);

        ssize_t ret = pread(fd, &p, sizeof(p), (uintptr_t)v/ps*sizeof(uintptr_t));
        if (ret == - 1) {
            perror("pread");
            exit(EXIT_FAILURE);
        }

        close(fd);

        //printf("%lx\n", p);

        p = p & 0x7fffffffffffffULL;

        if (p==0) {
            printf("failed to trans vaddr %p to paddr", v);
            return 0;
        }

        return p * ps + ((uintptr_t)v) % ps;
    }
    private:
    int _hoge;
};

/*
int main()
{
    void* addr = malloc(1024*1024*2);
    printf("v:%p\n", addr);
    printf("p:0x%012lx\n", v2p(addr));
    free(addr);
    return 0;
}
*/
