#!/bin/bash

clear

export PMEM_MMAP_HINT=0x7fdd4d1a3440

export LD_LIBRARY_PATH=/usr/lib/nvml_debug

export PMEMOBJ_LOG_LEVEL=1

sudo mount -t pmfs -o physaddr=0x100000000,init=2G none /mnt/pmfs/

sudo chown -R pmfs:pmfs /mnt/pmfs

echo EXPORTS AND CONFIGURE DONE

echo 
