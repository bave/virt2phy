
all: malloc align mmap svm dev

malloc: malloc.cpp
	c++ -std=c++11 $^ -o $@

align: align.cpp
	c++ -std=c++11 $^ -o $@

mmap: mmap.cpp
	c++ -std=c++11 $^ -o $@

svm: svm.cpp
	c++ -std=c++11 $^ -o $@ -lOpenCL

dev: ck_device.cpp
	c++ -std=c++11 $^ -o $@ -lOpenCL

clean:
	rm -rf ./malloc ./align ./mmap ./svm ./dev
