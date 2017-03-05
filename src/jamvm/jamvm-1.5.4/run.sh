export PMEM_MMAP_HINT=0x40000000
set LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/
src/jamvm -Xnoinlining -Xms512M -Xmx512M -verbose:gc -persistentheap:heap.ph HelloWorld
