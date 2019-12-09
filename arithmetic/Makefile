all: imulq subq addq idivq

imulq: 
	as -o imulq.o imulq.s
	ld imulq.o -o imulq

idivq: 
	as -o idivq.o idivq.s
	ld idivq.o -o idivq

subq:
	as -o subq.o subq.s
	ld subq.o -o subq

addq:
	as -o addq.o addq.s
	ld addq.o -o addq

clean:
	rm -f *.o imulq subq addq idivq
