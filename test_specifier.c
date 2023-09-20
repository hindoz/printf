#include"main.h"

unsigned int (*test_specifiers(const char *specifier))(va_list, buf_t *,
		unsigned char, int, int, unsigned char);
unsigned char test_flags(const char *flag, char *index);
int test_precision(va_list ptr, const char *modifier, char *index);
unsigned char test_length(const char *modifier, char *index);
int test_width(va_list ptr, const char *modifier, char *index);

/**
 * test_specifiers - Matches format specifier with
 *                     a corresponding conversion function.
 * @specifier:  pointer to a potential conversion specifier.
 * @int : int number
 * @char : any character
 * Return: If a conversion function is matched - a pointer to the function.
 *         Otherwise - NULL.
 *
 *Description: this function will compare argument with those given specifiers
 */
unsigned int (*test_specifiers(const char *specifier))(va_list, buf_t *,
		unsigned char, int, int, unsigned char)
{
	int i;
	test_t converters[] = {
		{'c', test_c},
		{'s', test_s},
		{'d', test_di},
		{'i', test_di},
		{'%', test_percent},
		{'b', test_b},
		{'u', test_u},
		{'o', test_o},
		{'x', test_x},
		{'X', test_X},
		{'S', test_S},
		{'p', test_p},
		{'r', test_r},
		{'R', test_R},
		{0, NULL}
	};

	for (i = 0; converters[i].func; i++)
	{
		if (converters[i].specifier == *specifier)
			return (converters[i].func);
	}

	return (NULL);
}


/**
 * test_flags - Matches flags with corresponding values.
 * @flag:  pointer to a potential string of flags.
 * @index: An index counter for the original format string.
 *
 * Return: If flag characters are matched - a corresponding value.
 *         Otherwise - 0.
 */
unsigned char test_flags(const char *flag, char *index)
{
	int i, j;
	unsigned char retr = 0;
	flag_t flags[] = {
		{'+', PLUS},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{'-', NEG},
		{0, 0}
	};

	for (i = 0; flag[i]; i++)
	{
		for (j = 0; flags[j].flag != 0; j++)
		{
			if (flag[i] == flags[j].flag)
			{
				(*index)++;
				if (retr == 0)
					retr = flags[j].value;
				else
					retr |= flags[j].value;
				break;
			}
		}
		if (flags[j].value == 0)
			break;
	}

	return (retr);
}


/**
 * test_precision - Matches a precision modifier with
 *                    its corresponding value.
 * @ptr:  va_list of arguments.
 * @modifier:  pointer to a potential precision modifier.
 * @index:  index counter for the original format string.
 *
 * Return: If a precision modifier is matched - its value.
 *         If the precision modifier is empty, zero, or negative - 0.
 *         Otherwise - -1.
 */
int test_precision(va_list ptr, const char *modifier, char *index)
{
	int value = 0;

	if (*modifier != '.')
		return (-1);

	modifier++;
	(*index)++;

	if ((*modifier <= '0' || *modifier > '9') &&
		 *modifier != '*')
	{
		if (*modifier == '0')
			(*index)++;
		return (0);
	}

	while ((*modifier >= '0' && *modifier <= '9') ||
		   (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(ptr, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * test_length - Matches length modifiers with their corresponding value.
 * @modifier: pointer to a potential length modifier.
 * @index: An index counter for the original format string.
 *
 * Return: If a lenth modifier is matched - its corresponding value.
 *         Otherwise - 0.
 */
unsigned char test_length(const char *modifier, char *index)
{
	if (*modifier == 'h')
	{
		(*index)++;
		return (SHORT);
	}

	else if (*modifier == 'l')
	{
		(*index)++;
		return (LONG);
	}

	return (0);
}

/**
 * test_width - Matches a width modifier with its corresponding value.
 * @ptr:  va_list of arguments.
 * @modifier: A pointer to a potential width modifier.
 * @index: An index counter for the original format string.
 *
 * Return: If a width modifier is matched - its value.
 *         Otherwise - 0.
 */
int test_width(va_list ptr, const char *modifier, char *index)
{
	int value = 0;

	while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(ptr, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}
