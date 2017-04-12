CC=gcc
CLANGCC=clang-3.9
OPTCC=opt-3.9
CXX=g++
RM=rm -f
CPPFLAGS=

CFLAGS := -O3 -I .

SRCS := $(shell find . -name '*.c')
OBJS := $(subst .cpp,.o,$(SRCS))

all: deepbelief
gcc: deepbelief
llvm: deepbeliefLLVM
opt: deepbeliefOpt

deepbelief: $(OBJS)
	gcc -o deepbelief.out $(OBJS) -O3 -L/usr/lib -ljpcnn

deepbeliefLLVM: $(OBJS)
	$(CLANGCC) -o deepbeliefLLVM.out $(OBJS) -L/usr/lib -ljpcnn	

deepbeliefOpt:
	$(CLANGCC) main.c -c -emit-llvm 
	$(OPTCC) -insert-gcov-profiling -adce -break-crit-edges main.bc -o mainOpt.bc
	$(CLANGCC) mainOpt.bc -o deepbeliefOpt.out -L/usr/lib -ljpcnn

%.o: %.cpp
	$(CC) $(CPPFLAGS) -fPIC -c $< -o $(basename $@).o

clean:
	find . -iname "*.o" -exec rm '{}' ';'

myclean:
	rm *.out	

