export PMEM_MMAP_HINT=0x40000000
src/jamvm -Xnoinlining -persistentheap:heap.ph HelloWorld
