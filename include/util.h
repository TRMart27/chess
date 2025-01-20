#ifndef UTIL_H_
#define  UTIL_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


///user-defined macros
#define NUM_COLS 8
#define NUM_ROWS 8
#define TRUE 1
#define FALSE 0
#define FAILURE -1

typedef struct Move
{
	short origin[2];
	short dest[2];
} Move;

void error_nomem(void);
void error_noexist(const char* variable, const char* location);
#if UTIL_IMPLEMENTATION_


void error_noexist(const char* variable, const char* location)
{
	assert(variables);
	assert(location);

	fprintf("Variable %s does not exist at function %s\n", variable, location);
	return;
}

void error_nomem(void)
{
	fprintf(stderr, "No memory remaining\n");
	exit(-1);
}


#endif //UTIL_IMPLEMENTATION_
#endif //UTIL_H_
