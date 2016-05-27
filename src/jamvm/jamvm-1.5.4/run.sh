export PMEM_MMAP_HINT=0x40000000
src/jamvm -Xnoinlining -Xms8192M -Xmx8192M -verbose:gc -persistentheap:heap.ph HelloWorld
