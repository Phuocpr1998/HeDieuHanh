# use normal make for this Makefile
#
# Makefile for building user programs to run on top of Nachos
#
# Several things to be aware of:
#
#    Nachos assumes that the location of the program startup routine (the
# 	location the kernel jumps to when the program initially starts up)
#       is at location 0.  This means: start.o must be the first .o passed 
# 	to ld, in order for the routine "Start" to be loaded at location 0
#

# if you are cross-compiling, you need to point to the right executables
# and change the flags to ld and the build procedure for as

GCCDIR = ../../../gnu-decstation-ultrix/decstation-ultrix/2.95.3/

LDFLAGS = -T script -N
ASFLAGS = -mips2
CPPFLAGS = $(INCDIR)

# if you aren't cross-compiling:
# GCCDIR =
# LDFLAGS = -N -T 0
# ASFLAGS =
# CPPFLAGS = -P $(INCDIR)

PATH = $(GCCDIR):/lib:/usr/bin:/bin

CC = $(GCCDIR)gcc -B../../../gnu-decstation-ultrix/
AS = $(GCCDIR)as
LD = $(GCCDIR)ld

CPP = gcc -E
INCDIR =-I../userprog -I../threads
CFLAGS = -G 0 -c $(INCDIR)

all: halt shell matmult sort createfile copy echo cat ping pong testExec testShell produce consume testProduceConsume

start.o: start.s ../userprog/syscall.h
	$(CPP) $(CPPFLAGS) start.c > strt.s
	$(AS) $(ASFLAGS) -o start.o strt.s
	rm strt.s

halt.o: halt.c
	$(CC) $(CFLAGS) -c halt.c
halt: halt.o start.o
	$(LD) $(LDFLAGS) start.o halt.o -o halt.coff
	../bin/coff2noff halt.coff halt

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c
shell: shell.o start.o
	$(LD) $(LDFLAGS) start.o shell.o -o shell.coff
	../bin/coff2noff shell.coff shell

sort.o: sort.c
	$(CC) $(CFLAGS) -c sort.c
sort: sort.o start.o
	$(LD) $(LDFLAGS) start.o sort.o -o sort.coff
	../bin/coff2noff sort.coff sort

matmult.o: matmult.c
	$(CC) $(CFLAGS) -c matmult.c
matmult: matmult.o start.o
	$(LD) $(LDFLAGS) start.o matmult.o -o matmult.coff
	../bin/coff2noff matmult.coff matmult

createfile.o: createfile.c
	$(CC) $(CFLAGS) -c createfile.c
createfile: createfile.o start.o
	$(LD) $(LDFLAGS) start.o createfile.o -o createfile.coff
	../bin/coff2noff createfile.coff createfile
	
copy.o: copy.c
	$(CC) $(CFLAGS) -c copy.c
copy: copy.o start.o
	$(LD) $(LDFLAGS) start.o copy.o -o copy.coff
	../bin/coff2noff copy.coff copy

echo.o: echo.c
	$(CC) $(CFLAGS) -c echo.c
echo: echo.o start.o
	$(LD) $(LDFLAGS) start.o echo.o -o echo.coff
	../bin/coff2noff echo.coff echo	

cat.o: cat.c
	$(CC) $(CFLAGS) -c cat.c
cat: cat.o start.o
	$(LD) $(LDFLAGS) start.o cat.o -o cat.coff
	../bin/coff2noff cat.coff cat

ping.o: ping.c
	$(CC) $(CFLAGS) -c ping.c
ping: ping.o start.o
	$(LD) $(LDFLAGS) start.o ping.o -o ping.coff
	../bin/coff2noff ping.coff ping

pong.o: pong.c
	$(CC) $(CFLAGS) -c pong.c
pong: pong.o start.o
	$(LD) $(LDFLAGS) start.o pong.o -o pong.coff
	../bin/coff2noff pong.coff pong

testExec.o: testExec.c
	$(CC) $(CFLAGS) -c testExec.c
testExec: testExec.o start.o
	$(LD) $(LDFLAGS) start.o testExec.o -o testExec.coff
	../bin/coff2noff testExec.coff testExec

testShell.o: testShell.c
	$(CC) $(CFLAGS) -c testShell.c
testShell: testShell.o start.o
	$(LD) $(LDFLAGS) start.o testShell.o -o testShell.coff
	../bin/coff2noff testShell.coff testShell

produce.o: produce.c
	$(CC) $(CFLAGS) -c produce.c
produce: produce.o start.o
	$(LD) $(LDFLAGS) start.o produce.o -o produce.coff
	../bin/coff2noff produce.coff produce

consume.o: consume.c
	$(CC) $(CFLAGS) -c consume.c
consume: consume.o start.o
	$(LD) $(LDFLAGS) start.o consume.o -o consume.coff
	../bin/coff2noff consume.coff consume

testProduceConsume.o: testProduceConsume.c
	$(CC) $(CFLAGS) -c testProduceConsume.c
testProduceConsume: testProduceConsume.o start.o
	$(LD) $(LDFLAGS) start.o testProduceConsume.o -o testProduceConsume.coff
	../bin/coff2noff testProduceConsume.coff testProduceConsume