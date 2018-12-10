#include "v2p.hpp"

#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 200
#include "cl2.hpp"

#include <iostream>

#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>

static int pages = 10;

#define UTIL_THROW(EXP, msg) throw EXP(msg)
#define UTIL_THROW_IF(cond, EXP, msg) if (cond) UTIL_THROW(EXP, "if ("#cond") " msg)

int main()
{
    uint8_t* addr;

    uint32_t ps = getpagesize();

    printf("ps:%d\n", ps);

    const int platform_number = 1;
    const int device_number = 0;

    try {

        std::vector<cl::Platform> cl_platforms;
        cl::Platform::get(&cl_platforms);
        UTIL_THROW_IF(cl_platforms.size()==0, std::runtime_error, "no cl platform");
        cl::Platform default_platform = cl_platforms[platform_number];

        // get device
        std::vector<cl::Device> cl_devices;
        default_platform.getDevices(CL_DEVICE_TYPE_ALL, &cl_devices);
        UTIL_THROW_IF(cl_devices.size()==0, std::runtime_error, "no cl device");
        cl::Device default_device = cl_devices[device_number];

        // mk context
        cl::Context ctx({default_device});

        cl::SVMAllocator<uint8_t, cl::SVMTraitCoarse<>> _svm_allocator(ctx);
        addr = (uint8_t*)_svm_allocator.allocate(ps*pages);

        for (int i=0; i<(ps*pages); i++) {
            addr[i] = (uint8_t)i;
        }

        for (int i=0; i<pages*2; i++) {
            printf("%p : 0x%012lx\n", (void*)&addr[ps/2*i], hoge::v2p((void*)&addr[ps/2*i]));
        }

        _svm_allocator.deallocate(addr, ps*pages);

        sleep(1000);

    } catch (cl::Error const& ex) {

        std::cerr << "OpenCL Error: " << ex.what() << " (code " << ex.err() << ")" << std::endl;
        exit(1);

    } catch (std::exception const& ex) {

        std::cerr << "Exception: " << ex.what() << std::endl;
        exit(1);

    }

    return 0;
}
