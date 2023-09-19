#incude"main.h"

void free_buf(buf_t *output);
buf_t *locate_size(void);
unsigned int mem_cpy(buf_t *output, const char *src, unsigned int n);

/**
 * locate_size - Initialise buf_t variable.
 *
 * Return:  pointer to initialized buf_t.
 */
buf_t *locate_size(void)
{
	buf_t *output;

	output = malloc(sizeof(buf_t));
	if (output == NULL)
		return (NULL);

	output->buf = malloc(sizeof(char) * 1024);
	if (output->buf == NULL)
	{
		free(output);
		return (NULL);
	}

	output->start = output->buf;
	output->length = 0;

	return (output);
}

/**
 * free_buf - release a buf_t struct.
 * @output:  buf_t struct to be freed.
 */
void free_buf(buf_t *output)
{
	free(output->start);
	free(output);
}


/**
 * mem_cpy - Copies n bytes from memory area src to
 *           the buffer contained in a buf_t struct.
 * @output:  buf_t struct.
 * @src: pointer to the memory area to copy.
 * @n: number of bytes to be copied.
 *
 * Return: number of bytes copied.
 */
unsigned int mem_cpy(buf_t *output, const char *src, unsigned int n)
{
	unsigned int index;

	for (index = 0; index < n; index++)
	{
		*(output->buf) = *(src + index);
		(output->length)++;

		if (output->length == 1024)
		{
			write(1, output->start, output->length);
			output->buf = output->start;
			output->length = 0;
		}

		else
			(output->buf)++;
	}

	return (n);
}
