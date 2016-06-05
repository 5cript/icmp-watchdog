# icmp-watchdog (WINDOWS ONLY!)
An icmp echo network scanner for windows that tracks the devices in the local network.

this is a small program to scan the network for changes of logged in devices.

## Building the program:

### Using cmake:
For msys2 64bit build: 
- mkdir build
- cd build
- cmake .. -G"MSYS Makefiles" -DCMAKE_INSTALL_PREFIX=/mingw64/x86_64-w64-mingw64
  
For msys2 32bit build
- mkdir build
- cd build
- cmake .. -G"MSYS Makefiles" -DCMAKE_INSTALL_PREFIX=/mingw64/x86_64-w64-mingw64
  
### I hate cmake

Stuff it all in a project of your favorite IDE and set the following compiler options
- fexceptions
- std=c++14
- O2

and the following linker options:
- liphlpapi 
- lws2_32 
- static
- static-libgcc 
- static-libstdc++  
