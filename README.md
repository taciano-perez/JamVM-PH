JamVM-PH
=========

Work in progress of a JamVM implementation that could benefit of non-volatile memory technology.

This is a fork of JamVM 1.5.4 from http://sourceforge.net/projects/jamvm/files/jamvm/ and classpath 0.98 from http://www.gnu.org/software/classpath/home.html.

# Building JamVM-PH

The following steps were validated with Ubuntu 14.04.

1. Clone the Github repository:
```
 git clone https://github.com/taciano-perez/JamVM-PH
```

2. Install GNU Classpath 0.98 dependencies. (TODO: document dependencies and their installation)

3. Build and install the modified version of GNU Classpath 0.98.
```
cd JamVM-PH/src/classpath
./configure --disable-Werror --disable-plugin --disable-gtk-peer --disable-gconf-peer --disable-tools --disable-examples
make
sudo make install
```

4. Install JamVM 1.5.4 dependencies. (TODO: document dependencies and their installation)

5. Build and install the modified version of JamVM 1.5.4.
```
cd JamVM-PH/src/jamvm/jamvm-1.5.4/
./configure --enable-ffi
python O2Remover.py
python IncludeMakefiles.py
make all
sudo make install
```

# Testing JamVM-PH

1. Compile the JamVM-PH examples:
```
cd JamVM-PH/src/jamvm/jamvm-1.5.4/
sh compile_java.sh
```

2. Execute the HelloWorld test:
```
sh run.sh
```

Each execution should increment the value presented after HI.
