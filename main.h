#ifndef MAIN_H
#define MAIN_H

#include<stdio.h>
#include<stdarg.h>
#include<string.h>
#include<unistd.h>

/**
 * struct buffer_s - A new type defining a buffer struct.
 * @buf:  pointer to a character array.
 * @start:  pointer to the start of buffer.
 * @length:  length of the string stored in buffer.
 */
typedef struct buffer_s
{
	char *buf;
	char *start;
	unsigned int length;
} buf_t;

/**
 * struct test_s -  new type defining a converter struct.
 * @specifier: character representing a conversion specifier.
 * @func: pointer to a conversion function corresponding to specifier.
 */
typedef struct test_s
{
	unsigned char specifier;
	unsigned int (*func)(va_list, buf_t *,
			unsigned char, int, int, unsigned char);
} test_t;

/**
 * struct flag_s -  new type defining a flags struct.
 * @flag:  character representing a flag.
 * @value: The integer value of the flag.
 */
typedef struct flag_s
{
	unsigned char flag;
	unsigned char value;
} flag_t;


int _printf(const char *format, ...);
buf_t *locate_size(void);

unsigned int test_c(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);
unsigned int testt_s(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);
unsigned int test_di(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);
unsigned int test_percent(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);
unsigned int test_b(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);
unsigned int test_u(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);
unsigned int test_o(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);
unsigned int test_x(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);
unsigned int test_X(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);
unsigned int test_S(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);
unsigned int test_p(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);
unsigned int test_r(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);
unsigned int test_R(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);

unsigned char test_flags(const char *flag, char *index);
unsigned char test_length(const char *modifier, char *index);
int test_width(va_list ptr, const char *modifier, char *index);
int test_precision(va_list ptr, const char *modifier, char *index);
unsigned int (*test_specifiers(const char *specifier))(va_list, buf_t *,
		unsigned char, int, int, unsigned char);

unsigned int print_width(buf_t *output, unsigned int printed,
		unsigned char flag, int width);
unsigned int print_string_width(buf_t *output,
		unsigned char flag, int width, int prec, int size);
unsigned int print_neg_width(buf_t *output, unsigned int printed,
		unsigned char flag, int width);


buf_t *locate_size(void);
void free_buf(buf_t *output);
unsigned int mem_cpy(buf_t *output, const char *src, unsigned int n);
unsigned int test_sbase(buf_t *output, long int num, char *base,
		unsigned char flag, int width, int prec);
unsigned int test_ubase(buf_t *output, unsigned long int num, char *base,
		unsigned char flag, int width, int prec);


#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define NEG 16
#define PLUS_FLAG (flags & 1)
#define SPACE_FLAG ((flags >> 1) & 1)
#define HASH_FLAG ((flags >> 2) & 1)
#define ZERO_FLAG ((flags >> 3) & 1)
#define NEG_FLAG ((flags >> 4) & 1)

#define SHORT 1
#define LONG 2

#endif
