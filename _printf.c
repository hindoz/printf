#include"main.h"

int _printf(const char *format, ...);


/**
 * _printf - print its arguments based on the specifier.
 * @format: format specifier
 * Return: number of characters to be printed.
 */

int _printf(const char *format, ...)
{
	buf_t *output;
	va_list ptr;
	int return_value;

	if (format == NULL)
		return (-1);
	output = locate_size();
	if (output == NULL)
		return (-1);

	va_start(ptr, format);

	return_value = main_printf(format, ptr, output);

	return (return_value);
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
	int i, return_value = 0;
	char tmp;
	unsigned char length;
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
			prec = test_precision(ptr, format + i + tmp + 1,&tmp);
		
			length = handle_length(format + i + tmp + 1, &tmp);

			f = test_specifiers(format + i + tmp + 1);
			if (f != NULL)
			{
				i += tmp + 1;
				ret += f(ptr, output, flag, width, prec, length);
				continue;
			}
			else if (*(format + i + tmp + 1) == '\0')
			{
				return_value = -1;
				break;
			}
		}
		return_value += _memcpy(output, (format + i), 1);
		i += (length != 0) ? 1 : 0;
	}
	cleanup(args, output);
	return (return_value);
}
