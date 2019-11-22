#
# Builds:
#	pe_util.c hs_util.c main.c (x64)
#
# Property of GuidePoint Security LLC, Threat & Attack Simulation Team
#
CC      := x86_64-w64-mingw32-gcc
SRCS    := $(wildcard src/*.c)
#EXTSRC := $(wildcard third-party/*.c)
#OBJS   := $(SRCS:%.c=%.o) $(EXTSRC:%.c=%.o)
OBJS    := $(SRCS:%.c=%.o)
CFLAGS  := -Os -O2 -ffunction-sections -fno-asynchronous-unwind-tables -nostdlib -fno-ident -falign-functions
INCS    := -Iinclude -Iinclude/subhook
LFLAGS  := -Wl,-s,--no-seh,-Tinclude/linked.x64.ld

all: payload.exe payload.bin

payload.bin:
	python2.7 pedump.py 

payload.exe: $(OBJS) src/StackAdjust.o
	$(CC) -o $@ $^ $(INCS) $(CFLAGS) $(LFLAGS)

.c.o:
	$(CC) -o $@ -c $< $(INCS) $(CFLAGS)

src/StackAdjust.o: src/StackAdjust.asm
	nasm -f win64 $< -o $@

clean:
	rm -rf $(OBJS) payload.exe payload.bin src/StackAdjust.o
