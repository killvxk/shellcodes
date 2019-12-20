#
# Builds:
#	pe_util.c hs_util.c main.c (x64)
#
CC      := x86_64-w64-mingw32-gcc
SRCS    := $(wildcard src/*.c)
OBJS    := $(SRCS:%.c=%.o)
CFLAGS  := -O3 -ffunction-sections -fno-asynchronous-unwind-tables -nostdlib -fno-ident -falign-functions
INCS    := -Iinclude -Iinclude/subhook
LFLAGS  := -Wl,-s,--no-seh,-Tinclude/linked.x64.ld

all: payload.x64.exe payload.x64.bin

payload.x64.bin:
	python2.7 pedump.py payload.x64.exe $@

payload.x64.exe: $(OBJS) src/StackAdjust.o
	$(CC) -o $@ $^ $(INCS) $(CFLAGS) $(LFLAGS)

.c.o:
	$(CC) -o $@ -c $< $(INCS) $(CFLAGS)

src/StackAdjust.o: src/StackAdjust.asm
	nasm -f win64 $< -o $@

clean:
	rm -rf $(OBJS) payload.x64.exe payload.x64.bin src/StackAdjust.o
