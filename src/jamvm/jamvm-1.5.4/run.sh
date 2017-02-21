export PMEM_MMAP_HINT=0x40000000
src/jamvm -Xnoinlining -Xms512M -Xmx512M -verbose:gc -persistentheap:heap.ph HelloWorld
