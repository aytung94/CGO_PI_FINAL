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

deepbeliefGccProf: $(OBJS)
	gcc -fno-omit-frame-pointer -o deepbeliefGccProf.out $(OBJS) -O3 -L/usr/lib -ljpcnn
	perf record ./deepbeliefGccProf.out image_000L.jpg ccv2012.ntwk banana
	perf report --stdio -g none --sort comm,dso -i ./perf.data > module_report.txt
	perf report --stdio -g none -i ./perf.data|c++filt > function_report.txt
	
deepbeliefLLVM: $(OBJS)
	$(CLANGCC) -o deepbeliefLLVM.out $(OBJS) -O3 -L/usr/lib -ljpcnn	

deepbeliefOpt:
	$(CLANGCC) main.c -c -emit-llvm -o main.bc 
	$(OPTCC) -insert-gcov-profiling -adce -break-crit-edges main.bc -o mainOpt.bc
	$(CLANGCC) mainOpt.bc -o deepbeliefOpt.out -L/usr/lib -ljpcnn

deepbeliefProfiling:
	$(CLANGCC) main.c -c -emit-llvm -o main.bc
	$(OPTCC) -insert-edge-profiling main.bc -o mainProfiled.bc
	$(CLANGCC) mainProfiled.bc -L/usr/lib -ljpcnn -L/usr/lib/llvm-3.3/lib -lprofile_rt -o llvmprof.out
	# $(CLANGCC) -L/usr/lib -ljpcnn -L/usr/lib/llvm-3.3/lib -lprofile_rt mainProfiled.bc -o main.profile.s
	# llc-3.3 -mattr=+vfp3  mainProfiled.bc -o main.profile.s
	# $(CLANGCC) -L/usr/lib -ljpcnn -L/usr/lib/llvm-3.3/lib -lprofile_rt -o main.profile main.profile.s

%.o: %.cpp
	$(CC) $(CPPFLAGS) -fPIC -c $< -o $(basename $@).o

clean:
	find . -iname "*.o" -exec rm '{}' ';'

myclean:
	rm *.out *.bc *.s	

