#include "stdio.h"
#include "stdlib.h"

void printInt(long int num){
	fprintf(stdout, "%ld\n", num);
}

void printString(const char * str){
	fprintf(stdout, "%s\n", str);
}

long int getInt(){
	char buffer[32];
	fgets(buffer, 32, stdin);
	long int res = atol(buffer);
	fprintf(stdout, "read from buffer: %ld\n", res);
	return res;
}
