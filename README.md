# About 

Collection of user mode, as well as kernel mode shellcodes to be utilized in exploits, or for "safe" staging purposes unavailable in commercial frameworks such as Metasploit or Cobalt Strike.

Currently the kernel mode shellcode is experimental, and only operates cleanly when running in the DISPATCH_LEVEL Irql, thusly will have issues when operating in situations such as EternalBlue. Efforts to port the MSR_LSTAR hook to hop into PASSIVE_LEVEL are in progress yet a timeline of completion is currently unknown.

The [CHANGELOG](CHANGELOG.md) can be found there for any major / minor changes after base setup.

## Development

Should you choose to develop your own shellcodes using the base templates, its relatively simple. Specify your function definitions such as WinExec, etc into the [winapi.h](include/winapi.h), and your module / function hashes into the [hashes.h](include/hashes.h) file. 

After doing so, place your function resolve code into the [main.c](src/main.c) WindowsEntrypoint function which will be called upon pointer execution. You'll be forced to manually resolve any required dependencies using the functions `GetPeBase` (acquire a module in memory), and `GetPeFunc` (acquire a function in memory). Upon building the shellcode, you should have an importless executable, as well as a `.bin` for the architecture to be delivered to targets.

## Building 

The shellcode are buildable using a mingw-w64 glibc compiler on a Unix or Mac OSX installation. Furthermore, subdependencies using nasm and Makefile are required, as some of the files are in pure ASM, and the build process utilizes Make for automation.

```sh 
$ make -f Makefile.x64 > /dev/null
$ md5sum payload.x64.bin
f0d85acc32acc78e23a68d69bf0f1e4b  payload.x64.bin
```

### Potential Features
  - Encrypted Shellcode using : RC6 / BlowFish
  - Implement bypasses for Export Address Table Filtering (EAF) by walking the import table of kernel32 for LdrLoadDll and LdrGetProceduralAddress
  - Auto-Migrate (maybe?)

