JamVM-PH
=========

Work in progress of a JamVM implementation that could benefit of non-volatile memory technology.

This is a fork of JamVM 1.5.4 from http://sourceforge.net/projects/jamvm/files/jamvm/ and GNU Classpath 0.98 from http://www.gnu.org/software/classpath/home.html. It uses NVML (https://github.com/pmem/nvml).

# Building JamVM-PH using Docker

The simplest way to build JamVM-PH is using a Docker container. If you have Docker installed, the following steps should do the trick:

1. Clone the Github repository:
```
 git clone https://github.com/taciano-perez/JamVM-PH
```

2. Build the JamVM-PH Docker image
```
cd JamVM-PH
docker build -t japhavm .
```

3. Run a container interactively with the newly created image
```
docker run --privileged -t -i japhavm /bin/bash
```

## Testing JamVM-PH (Docker build)

1. In the container shell, mount an in-memory file system to emulate Persistent Memory (example: tmpfs):
```
mkdir /mnt/pmfs
sudo mount -t tmpfs -o size=512M tmpfs /mnt/pmfs
```

2. Compile the JamVM-PH examples:
```
cd /src/jamvm/jamvm-1.5.4/
sh compile_java.sh
```

3. Execute the HelloWorld test:
```
sh run.sh
```

Each execution should increment the value presented after HI.


# Building JamVM-PH manually in a Linux system

If you don't want to use Docker, use the following steps, which were validated with Ubuntu 14.04.

1. Clone the Github repository:
```
 git clone https://github.com/taciano-perez/JamVM-PH
```

2. Install GNU Classpath 0.98 dependencies.
```
sudo apt-get install build-essential openjdk-7-jdk
```

3. Build and install the modified version of GNU Classpath 0.98.
```
cd JamVM-PH/src/classpath
./configure --disable-Werror --disable-plugin --disable-gtk-peer --disable-gconf-peer --disable-tools --disable-examples
make
sudo make install
```

4. Install NVML dependencies.
```
sudo apt-get install git pkg-config autoconf man-db
```

5. Build and install NVML (tested with NVML 1.1).
```
cd JamVM-PH
git clone https://github.com/pmem/nvml.git
cd nvml
git checkout tags/1.1
make
sudo make install
```

6. Install JamVM 1.5.4 dependencies.
```
sudo apt-get install zlib1g-dev libffi-dev zip
```

7. Build and install the modified version of JamVM 1.5.4.
```
cd JamVM-PH/src/jamvm/jamvm-1.5.4/
./configure --enable-ffi
python O2Remover.py
python IncludeMakefiles.py
LD_LIBRARY_PATH=/usr/local/lib
export LD_LIBRARY_PATH
make all
sudo make install
```

## Testing JamVM-PH (manual build)

1. Mount an in-memory file system to emulate Persistent Memory (example: tmpfs):
```
mkdir /mnt/pmfs
sudo mount -t tmpfs -o size=512M tmpfs /mnt/pmfs
```

2. Compile the JamVM-PH examples:
```
cd JamVM-PH/src/jamvm/jamvm-1.5.4/
sh compile_java.sh
```

3. Execute the HelloWorld test:
```
sh run.sh
```

Each execution should increment the value presented after HI.
