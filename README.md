# About

Shellcodes is a collection of user-mode and kernel-mode position-independent-(code) (pic) stubs for locating functions and portable executables (drivers/libraries) in memory. For building the shellcode, you will need `python2.7 ` (fuck you 3!), `nasm`, `make`, and a mingw-w64 compiler, and the python `pefile` module.

## Table of Contents
 - [What is PIC?](#Position-Independent-Code)
 - [Using the Stubs](#How-To-Use)

### Position Independent Code

Position Independent Code, herein referenced as "pic/PIC" is a set of instructions that can be referenced / used anywhere in memory, without knowing its location, due to its lack of reliance on other parts of a, in this case portable executable (pe). For example, a typical PE when calling a function stores its address in its Import-Address-Table (IAT), and the portable executable will _reference_ that address in that table, thusly having a reliance on knowing where that address is at the start. However, with PIC code, we _cannot_ rely on knowing the address of ourselves & where the function is in memory, so we will have to find and locate it ourselves.

As such, I've provided emulations of GetModuleHandle [GetPeBase](src/pe_util.c#L32) and GetProcAddress [GetPeFunc](src/pe_util.c#L60). However, they accept hashes of the requested modules compared to the string names, as we cannot store the names of the modules in the shellcode _safely_ without hex'ing them / arbitrarily increasing the size.

Thusly, to locate the base address of an executable, you calculate its hash and pass the hash to GetPeBase() in the `WindowsEntrypoint` function, and then pass the base address + hash of the function you want to GetPeFunc() to find its location in memory.

### How To Use

Using the stubs are relatively easy. You can build the stubs using make by running `make -f Makefile.x64` for x64 shellcode, and `make -f Makefile.x86` for x86 shellcode. Keep in mind _all of your code must be position independent_. I've kept the project to be stable by storing all the hashes I'll need in [include/hashes.h](include/hashes.h), and the function typedef definitions under [include/winapi.h](include/winapi.h).

Please store all your code under the main.c WindowsEntrypoint function. What happens is, when the shellcode is executed, this is the first function that is called / that will perform all the functionality of the code. You can create other functions and pass execution to them on the whim if needed.

I'll provide some sample codes for later. The Kernel Mode Stubs are under the `experimental_km` branch, and the user mode stubs are under `master`. To calculate hashes for strings, simply build hash.c and run it like `hash.exe MyStringToGEnerateHash` etc.
