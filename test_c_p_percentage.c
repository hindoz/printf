#include "main.h"

unsigned int test_c(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);
unsigned int test_percent(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);
unsigned int test_p(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);

/**
 * test_c - Converts an argument to an unsigned char
 * @ptr: va_list pointing to the argument to be converted.
 * @flag: Flag modifiers.
 * @width:  width modifier.
 * @prec: precision modifier.
 * @length: length modifier.
 * @output:  buf_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int test_c(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length)
{
	char c;
	unsigned int retr = 0;

	(void)prec;
	(void)length;

	c = va_arg(ptr, int);

	retr += print_width(output, retr, flag, width);
	retr += mem_cpy(output, &c, 1);
	retr += print_neg_width(output, retr, flag, width);

	return (retr);
}

/**
 * test_percent - Stores a percent sign to a
 * buffer contained in a struct.
 * @ptr: va_list pointing to the argument to be converted.
 * @flag: Flag modifiers.
 * @width:  width modifier.
 * @prec: precision modifier.
 * @length:  length modifier.
 * @output:  buf_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer (always 1).
 */
unsigned int test_percent(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length)
{
	char percent = '%';
	unsigned int retr = 0;

	(void)ptr;
	(void)prec;
	(void)length;

	retr += print_width(output, retr, flag, width);
	retr += mem_cpy(output, &percent, 1);
	retr += print_neg_width(output, retr, flag, width);

	return (retr);
}

/**
 * test_p - Converts the address of an argument to hex and
 * stores it to a buffer contained in a struct.
 * @ptr:  va_list pointing to the argument to be converted.
 * @flag: Flag modifiers.
 * @width:  width modifier.
 * @prec: precision modifier.
 * @length:  length modifier.
 * @output:  buf_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int test_p(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length)
{
	char *null = "(nil)";
	unsigned long int address;
	unsigned int retr = 0;

	(void)length;

	address = va_arg(ptr, unsigned long int);
	if (address == '\0')
		return (mem_cpy(output, null, 5));

	flag |= 32;
	retr += test_ubase(output, address, "0123456789abcdef",
			flag, width, prec);
	retr += print_neg_width(output, retr, flag, width);

	return (retr);
}
