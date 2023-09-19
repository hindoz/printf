#incude"main.h"

void free_buf(buf_t *output);
buf_t *locate_size(void);


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

