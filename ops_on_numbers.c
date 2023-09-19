#include"main.h"

unsigned int test_di(va_list ptr, buf_t *output, unsigned char flag, int width, int prec, unsigned char length);
unsigned int test_u(va_list ptr, buf_t *output, unsigned char flag, int width, int prec, unsigned char length);
unsigned int test _b(va_list ptr, buf_t *output, unsigned char flag, int width, int prec, unsigned char length);
unsigned int test_o(va_list ptr, buf_t *output, unsigned char flag, int width, int prec, unsigned char length);

/**
 * test_di - Converts an argument to a signed int
 * @ptr: va_list pointing to the argument to be converted.
 * @flag: Flag modifiers.
 * @width:  width modifier.
 * @prec:  precision modifier.
 * @length:  length modifier.
 * @output:  buf_t struct containing a character array.
 *
 * Return: number of bytes stored to the buffer.
 */
unsigned int test_di(va_list test, buf_t *output,
		unsigned char flag, int width, int prec, unsigned char length)
{
	long int d, copy;
	unsigned int retrn_value = 0, count = 0;
	char pad, space = ' ', neg = '-', plus = '+';

	if (length == LONG)
		d = va_arg(ptr, long int);
	else
		d = va_arg(ptr, int);
	if (length == SHORT)
		d = (short)d;

	/* Handle space flag */
	if (SPACE_FLAG == 1 && d >= 0)
		retrn_value += mem_cpy(output, &space, 1);

	if (prec <= 0 && NEG_FLAG == 0) /* Handle width  */
	{
		if (d == LONG_MIN)
			count += 19;
		else
		{
			for (copy = (d < 0) ? -d : d; copy > 0; copy /= 10)
				count++;
		}
		count += (d == 0) ? 1 : 0;
		count += (d < 0) ? 1 : 0;
		count += (PLUS_FLAG == 1 && d >= 0) ? 1 : 0;
		count += (SPACE_FLAG == 1 && d >= 0) ? 1 : 0;

		/* Handle plus flag when zero flag is active */
		if (ZERO_FLAG == 1 && PLUS_FLAG == 1 && d >= 0)
			retrn_value += mem_cpy(output, &plus, 1);
		/*Print negative sign when zero flag is active */
		if (ZERO_FLAG == 1 && d < 0)
			retrn_valuet += mem_cpy(output, &neg, 1);

		pad = (ZERO_FLAG == 1) ? '0' : ' ';
		for (width -= count; wid > 0; wid--)
			retrn_value += mem_cpy(output, &pad, 1);
	}

	/* Print negative sign when zero flag is not active */
	if (ZERO_FLAG == 0 && d < 0)
		retrn_value += mem_cpy(output, &neg, 1);
	/* Handle plus flag when zero flag is not active */
	if (ZERO_FLAG == 0 && (PLUS_FLAG == 1 && d >= 0))
		retrn_value += mem_cpy(output, &plus, 1);

	if (!(d == 0 && prec == 0))
		retrn_value += test_sbase(output, d, "0123456789",
				flag, 0, prec);

	retrn_value += print_neg_width(output, retrn_value, flag, width);

	return (retrn_value);
}


/**
 * test_u - Converts an unsigned int argument to decimal
 * @ptr: A va_list pointing to the argument to be converted.
 * @flag: Flag modifiers.
 * @width: A width modifier.
 * @prec: A precision modifier.
 * @length: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int test_u(va_list ptr, buf_t *output, unsigned char flag, int width, int prec, unsigned char length)
{
	unsigned long int num;
	unsigned int retrn_value = 0;

	if (length == LONG)
		num = va_arg(ptr, unsigned long int);
	else
		num = va_arg(ptr, unsigned int);
	if (length == SHORT)
		num = (unsigned short)num;

	if (!(num == 0 && prec == 0))
		retrn_value += test_ubase(output, num, "0123456789",
				flag, width, prec);

	retrn_value += print_neg_width(output, retrn_value, flag, width);

	return (retrn_value);
}

/**
 * test_b - Converts an unsigned int argument to binary
 * @ptr: A va_list pointing to the argument to be converted.
 * @flag: Flag modifiers.
 * @width: A width modifier.
 * @prec: A precision modifier.
 * @length: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int test_b(va_list ptr, buf_t *output, unsigned char flag, int width, int prec, unsigned char length)
{
	unsigned int num;

	num = va_arg(ptr, unsigned int);

	(void)length;

	return (test_ubase(output, num, "01", flag, width, prec));
}

/**
 * test_o - Converts an unsigned int to octal
 * @ptr: A va_list poinitng to the argument to be converted.
 * @flag: Flag modifiers.
 * @width:  width modifier.
 * @prec:  precision modifier.
 * @length:  length modifier.
 * @output:  buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int test_o(va_list ptr, buf_t *output, unsigned char flag, int width, int prec, unsigned char length)
{
	unsigned long int num;
	unsigned int retrn_value = 0;
	char zero = '0';

	if (length == LONG)
		num = va_arg(ptr, unsigned long int);
	else
		num = va_arg(ptr, unsigned int);
	if (length == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		retrn_value += mem_cpy(output, &zero, 1);

	if (!(num == 0 && prec == 0))
		retrn_valuet += convert_ubase(output, num, "01234567", flag, width, prec);

	retrn_value += print_neg_width(output, retrn_value, flag, width);

	return (retrn_value);
}
