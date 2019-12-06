TESTFILES := $(wildcard *.lake)
TESTS := $(TESTFILES:.lake=.test)
LIBLINUX := -dynamic-linker /lib64/ld-linux-x86-64.so.2

.PHONY: all

all: $(TESTS)

%.test:
	@rm -f $*.err $*.3ac $*.s
	@touch $*.err $*.3ac $*.s
	@echo "TEST $*"
	@../lakec $*.lake -o $*.s ;\
	PROG_EXIT_CODE=$$?;\
	as -o $*.o;\
	ld -o $*.out $(LIBLINUX) -lc ../entry.o ../stdlake.o $*.o; \
	./$*.out < $*.in > $*.out; \
	diff -B --ignore-all-space $*.out $*.out.expected;\
	TAC_DIFF_EXIT=$$?;\
	exit $$TAC_DIFF_EXIT

clean:
	rm -f *.3ac *.out *.err
