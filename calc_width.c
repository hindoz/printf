#include "main.h"

unsigned int print_width(buf_t *output, unsigned int printed,
		unsigned char flag, int width);
unsigned int print_string_width(buf_t *output,
		unsigned char flag, int width, int prec, int size);
unsigned int print_neg_width(buf_t *output, unsigned int printed,
		unsigned char flag, int width);

/**
 * print_width - Stores leading spaces to a buffer for a width modifier.
 * @output:  buf_t struct containing a character array.
 * @printed: The current number of characters already printed to output
 *           for a given number specifier.
 * @flag: Flag modifiers.
 * @width: width modifier.
 *
 * Return: number of bytes stored to the buffer.
 */
unsigned int print_width(buf_t *output, unsigned int printed,
		unsigned char flag, int width)
{
	unsigned int retr = 0;
	char wid = ' ';

	if (NEG_FLAG == 0)
	{
		for (width -= printed; width > 0;)
			retr += mem_cpy(output, &wid, 1);
	}

	return (retr);
}

/**
 * print_string_width - Stores leading spaces to a buffer for a width modifier.
 * @output:  buf_t struct containing a character array.
 * @flag: Flag modifiers.
 * @width: width modifier.
 * @prec:  precision modifier.
 * @size:  size of the string.
 *
 * Return: number of bytes stored to the buffer.
 */
unsigned int print_string_width(buf_t *output,
		unsigned char flag, int width, int prec, int size)
{
	unsigned int retr = 0;
	char wid = ' ';

	if (NEG_FLAG == 0)
	{
		width -= (prec == -1) ? size : prec;
		for (; width > 0; width--)
			retr += mem_cpy(output, &wid, 1);
	}

	return (retr);
}

/**
 * print_neg_width - Stores trailing spaces to a buffer for a '-' flag.
 * @output:  buf_t struct containing a character array.
 * @printed:  current number of bytes already stored to output
 *           for a given specifier.
 * @flag: Flag modifiers.
 * @width: width modifier.
 *
 * Return:  number of bytes stored to the buffer.
 */
unsigned int print_neg_width(buf_t *output, unsigned int printed,
		unsigned char flag, int width)
{
	unsigned int retr = 0;
	char wid = ' ';

	if (NEG_FLAG == 1)
	{
		for (width -= printed; width > 0; width--)
			retr += mem_cpy(output, &wid, 1);
	}

	return (retr);
}
