# icmp-watchdog (WINDOWS ONLY!)
An icmp echo network scanner for windows that tracks the devices in the local network.

this is a small program to scan the network for changes of logged in devices.

## Building the program:

### Using cmake:
- mkdir build
- cd build
- cmake .. -G"MSYS Makefiles"
- make

If you want to rebuild everything from scratch, delete the contents in the "build" directory and start over.
  
### I hate cmake and use mingw-w64

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
 
### I hate cmake and use Visual Studio

Make sure that your compiler version supports enough C++11 and hope that it works.. I don't test with Visual Studio. But I am very confident, that if problems exist, they are very small and can be fixed fast.
pragma comment(lib, ...) directives exist.
