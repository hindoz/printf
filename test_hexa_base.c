#include "main.h"

unsigned int test_x(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);
unsigned int test_X(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);
unsigned int test_sbase(buf_t *output, long int num, char *base,
		unsigned char flag, int width, int prec);
unsigned int test_ubase(buf_t *output,
		unsigned long int num, char *base,
		unsigned char flag, int width, int prec);


/**
 * test_x - Converts an unsigned int argument to hex
 * @ptr: va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width:  width modifier.
 * @prec:  precision modifier.
 * @length:  length modifier.
 * @output:  buf_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int test_x(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length)
{
	unsigned long int num;
	unsigned int retr = 0;
	char *lead = "0x";

	if (length == LONG)
		num = va_arg(ptr, unsigned long int);
	else
		num = va_arg(ptr, unsigned int);
	if (length == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		retr += mem_cpy(output, lead, 2);

	if (!(num == 0 && prec == 0))
		retr += test_ubase(output, num, "0123456789abcdef",
				flag, width, prec);

	retr += print_neg_width(output, retr, flag, width);

	return (retr);
}

/**
 * test_X - Converts an unsigned int argument to hex using ABCDEF
 * @ptr:  va_list pointing to the argument to be converted.
 * @flag: Flag modifiers.
 * @width:  width modifier.
 * @prec:  precision modifier.
 * @length:  length modifier.
 * @output:  buf_t struct containing a character array.
 *
 * Return:  number of bytes stored to the buffer.
 */
unsigned int test_X(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length)
{
	unsigned long int num;
	unsigned int retr = 0;
	char *lead = "0X";

	if (length == LONG)
		num = va_arg(ptr, unsigned long);
	else
		num = va_arg(ptr, unsigned int);
	if (length == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		retr += mem_cpy(output, lead, 2);

	if (!(num == 0 && prec == 0))
		retr += test_ubase(output, num, "0123456789ABCDEF",
				flag, width, prec);

	retr += print_neg_width(output, retr, flag, width);

	return (retr);
}


/**
 * test_sbase - Converts a signed long to an inputted base
 * @output:  buf_t struct containing a character array.
 * @num:  signed long to be converted.
 * @base:  pointer to a string containing the base to convert to.
 * @flag: Flag modifiers.
 * @width: width modifier.
 * @prec:  precision modifier.
 *
 * Return: number of bytes stored to the buffer.
 */
unsigned int test_sbase(buf_t *output, long int num, char *base,
		unsigned char flag, int width, int prec)
{
	int size;
	char digit, pad = '0';
	unsigned int retr = 1;

	for (size = 0; *(base + size);)
		size++;

	if (num >= size || num <= -size)
		retr += test_sbase(output, num / size, base,
				flag, wid - 1, prec - 1);

	else
	{
		for (; prec > 1; prec--, width--) /* Handle precision */
			retr += mem_cpy(output, &pad, 1);

		if (NEG_FLAG == 0) /* Handle width */
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; width > 1; width--)
				retr += mem_cpy(output, &pad, 1);
		}
	}

	digit = base[(num < 0 ? -1 : 1) * (num % size)];
	mem_cpy(output, &digit, 1);

	return (retr);
}

/**
 * test_ubase - Converts an unsigned long to an inputted base
 * @output: buf_t struct containing a character array.
 * @num:  unsigned long to be converted.
 * @base: pointer to a string containing the base to convert to.
 * @flag: Flag modifiers.
 * @width:  width modifier.
 * @prec:  precision modifier.
 *
 * Return:  number of bytes stored to the buffer.
 */
unsigned int test_ubase(buf_t *output, unsigned long int num, char *base,
		unsigned char flag, int width, int prec)
{
	unsigned int size, retr = 1;
	char digit, pad = '0', *lead = "0x";

	for (size = 0; *(base + size);)
		size++;

	if (num >= size)
		retr += test_ubase(output, num / size, base,
				flag, width - 1, prec - 1);

	else
	{
		if (((flag >> 5) & 1) == 1) /* Printing a ptr address */
		{
			width -= 2;
			prec -= 2;
		}
		for (; prec > 1; prec--, width--) /* Handle precision */
			retr += mem_cpy(output, &pad, 1);

		if (NEG_FLAG == 0) /* Handle width */
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; width > 1; width--)
				retr += mem_cpy(output, &pad, 1);
		}
		if (((flag >> 5) & 1) == 1) /* Print 0x for ptr address */
			retr += mem_cpy(output, lead, 2);
	}

	digit = base[(num % size)];
	mem_cpy(output, &digit, 1);

	return (retr);
}
