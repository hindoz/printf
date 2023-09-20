#include"main.h"

int _printf(const char *format, ...);
int main_printf(const char *format, va_list ptr, buf_t *output);
void clean_up(va_list ptr, buf_t *output);

/**
 * _printf - print its arguments based on the specifier.
 * @format: format specifier
 * Return: number of characters to be printed.
 */

int _printf(const char *format, ...)
{
	buf_t *output;
	va_list ptr;
	int retrn_value;

	if (format == NULL)
		return (-1);
	output = locate_size();
	if (output == NULL)
		return (-1);

	va_start(ptr, format);

	retrn_value = main_printf(format, ptr, output);

	return (retrn_value);
}

/**
 * main_printf - Reads through the format string.
 * @format: arguments to print.
 * @output: A buf_t struct containing a buffer.
 * @ptr: A va_list of arguments.
 *
 * Return: The number of characters stored to output.
 */
int main_printf(const char *format, va_list ptr, buf_t *output)
{
	int i, retrn_value = 0, prec, width;
	char tmp;
	unsigned char length, flag;
	unsigned int (*f)(va_list, buf_t *,
			unsigned char, int, int, unsigned char);

	for (i = 0; *(format + i); i++)
	{
		length = 0;
		if (*(format + i) == '%')
		{
			tmp = 0;
			flag = test_flags(format + i + 1, &tmp);
			width = test_width(ptr, format + i + tmp + 1, &tmp);
			prec = test_precision(ptr, format + i + tmp + 1, &tmp);

			length = test_length(format + i + tmp + 1, &tmp);

			f = test_specifiers(format + i + tmp + 1);
			if (f != NULL)
			{
				i += tmp + 1;
				retrn_value += f(ptr, output, flag, width, prec, length);
				continue;
			}
			else if (*(format + i + tmp + 1) == '\0')
			{
				retrn_value = -1;
				break;
			}
		}
		retrn_value += mem_cpy(output, (format + i), 1);
		i += (length != 0) ? 1 : 0;
	}
	clean_up(ptr, output);
	return (retrn_value);
}

/**
 * clean_up - Peforms cleanup operations for _printf.
 * @ptr: va_list of arguments provided to _printf.
 * @output:  buf_t struct.
 */
void clean_up(va_list ptr, buf_t *output)
{
	va_end(ptr);
	write(1, output->start, output->length);
	free_buf(output);
}
