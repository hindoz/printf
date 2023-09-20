#include "main.h"

unsigned int test_st(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);
unsigned int test_S(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);
unsigned int test_r(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);
unsigned int test_R(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length);

/**
 * test_st - Converts an argument to a string
 * @ptr: va_list pointing to the argument to be converted.
 * @flag: Flag modifiers.
 * @width:  width modifier.
 * @prec:  precision modifier.
 * @length:  length modifier.
 * @output:  buf_t struct containing a character array.
 *
 * Return:  number of bytes stored to the buffer.
 */
unsigned int test_st(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length)
{
	char *str, *null = "(null)";
	int size;
	unsigned int retr = 0;

	(void)flag;
	(void)length;

	str = va_arg(ptr, char *);
	if (str == NULL)
		return (mem_cpy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	retr += print_string_width(output, flag, width, prec, size);

	prec = (prec == -1) ? size : prec;
	while (*str != '\0' && prec > 0)
	{
		retr += mem_cpy(output, str, 1);
		prec--;
		str++;
	}

	retr += print_neg_width(output, retr, flag, width);

	return (retr);
}

/**
 * test_S - Converts an argument to a string
 * @ptr: va_list pointing to the argument to be converted.
 * @flag: Flag modifiers.
 * @width:  width modifier.
 * @prec:  precision modifier.
 * @length:  length modifier.
 * @output: buf_t struct containing a character array.
 *
 * Return: number of bytes stored to the buffer.
 */
unsigned int test_S(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length)
{
	char *str, *null = "(null)", *hex = "\\x", zero = '0';
	int size, index;
	unsigned int retr = 0;

	(void)length;
	str = va_arg(ptr, char *);
	if (str == NULL)
		return (mem_cpy(output, null, 6));

	for (size = 0; str[size];)
		size++;

	retr += print_string_width(output, flag, width, prec, size);

	prec = (prec == -1) ? size : prec;
	for (index = 0; *(str + index) != '\0' && index < prec; index++)
	{
		if (*(str + index) < 32 || *(str + index) >= 127)
		{
			retr += mem_cpy(output, hex, 2);
			if (*(str + index) < 16)
				retr += mem_cpy(output, &zero, 1);
			retr += test_ubase(output, *(str + index),
						 "0123456789ABCDEF", flag, 0, 0);
			continue;
		}
		retr += mem_cpy(output, (str + index), 1);
	}

	retr += print_neg_width(output, retr, flag, width);

	return (retr);
}

/**
 * test_r - Reverses a string
 * @ptr: va_list pointing to the string to be reversed.
 * @flag: Flag modifiers.
 * @width:  width modifier.
 * @prec:  precision modifier.
 * @length:  length modifier.
 * @output:  buf_t struct containing a character array.
 *
 * Return: number of bytes stored to the buffer.
 */
unsigned int test_r(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length)
{
	char *str, *null = "(null)";
	int size, end, i;
	unsigned int retr = 0;

	(void)flag;
	(void)length;

	str = va_arg(ptr, char *);
	if (str == NULL)
		return (mem_cpy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	retr += print_string_width(output, flag, width, prec, size);

	end = size - 1;
	prec = (prec == -1) ? size : prec;
	for (i = 0; end >= 0 && i < prec; i++)
	{
		retr += mem_cpy(output, (str + end), 1);
		end--;
	}

	retr += print_neg_width(output, retr, flag, width);

	return (retr);
}

/**
 * test_R - Converts a string to ROT13
 * @ptr: va_list pointing to the string to be converted.
 * @flag: Flag modifiers.
 * @width: width modifier.
 * @prec: precision modifier.
 * @length:  length modifier.
 * @output:  buf_t struct containing a character array.
 *
 * Return: number of bytes stored to the buffer.
 */
unsigned int test_R(va_list ptr, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length)
{
	char *alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *rot13 = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
	char *str, *null = "(null)";
	int i, j, size;
	unsigned int retr = 0;

	(void)flag;
	(void)length;

	str = va_arg(ptr, char *);
	if (str == NULL)
		return (mem_cpy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	retr += print_string_width(output, flag, width, prec, size);

	prec = (prec == -1) ? size : prec;
	for (i = 0; *(str + i) != '\0' && i < prec; i++)
	{
		for (j = 0; j < 52; j++)
		{
			if (*(str + i) == *(alpha + j))
			{
				retr += mem_cpy(output, (rot13 + j), 1);
				break;
			}
		}
		if (j == 52)
			retr += mem_cpy(output, (str + i), 1);
	}

	retr += print_neg_width(output, retr, flag, width);

	return (retr);
}
