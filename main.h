#ifndef MAIN_H
#define MAIN_H

#include<stdio.h>
#include<stdarg.h>
#include<string.h>
#include<unistd.h>

typedef struct buffer 
{
	char *buf;
	char *start;
	unsigned int length;
} buf_t;




buf_t *locate_size(void);


#endif
