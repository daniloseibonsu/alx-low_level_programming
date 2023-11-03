#include "main.h"
#include <stdio.h>
#include <stdlib.h>

void close_file(int fd);
char *create_buffer(char *file);

/**
 * create_buffer - allocates memory of  1024 bytes for a buffer.
 *
 * @file: The file name for the file the buffer is storing chars for.
 *
 * Return:Retunns a pointer to the newly allocated buffer.
 */
char *create_buffer(char *file)
{
	char *n_buffer;

	n_buffer = malloc(sizeof(char) * 1024);

	if (n_buffer == NULL)
	{
		dprintf(STDERR_FILENO,
				"Error: Can't write to %s\n", file);
		exit(99);
	}

	return (n_buffer);
}

/**
 * close_file - Closes or terminates the file descriptors.
 *
 *  @fd: The name of the file descriptor to be closed.
 */
void close_file(int fd)
{
	int a;

	a = close(fd);
	if (a == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * main - A function that copies the content of one file to another file.
 *
 * @argc:Represents the  number of arguments given  to the program.
 *
 * @argv: Is an array of pointers to the arguments.
 *
 * Return:Returns 0 if successfu;.
 *
 * Description: If the argument count is incorrect, then  exit code is 97.
 * If file_from does not exist or cannot be read, then exit code is 98.
 *If file_to creation fails or it can't be written to,then the exit code is 99
 *
 * If the files  file_to or file_from cannot be closed, then the exit code 100.
 */
int main(int argc, char *argv[])
{
	int from, to, x, w;
	char *buffer;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	buffer = create_buffer(argv[2]);
	from = open(argv[1], O_RDONLY);
	x = read(from, buffer, 1024);
	to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);

	do {
		if (from == -1 || x == -1)
		{
			dprintf(STDERR_FILENO,
					"Error: Can't read from file %s\n", argv[1]);
			free(buffer);
			exit(98);
		}

		w = write(to, buffer, x);
		if (to == -1 || w == -1)
		{
			dprintf(STDERR_FILENO,
					"Error: Can't write to %s\n", argv[2]);
			free(buffer);
			exit(99);
		}

		x = read(from, buffer, 1024);
		to = open(argv[2], O_WRONLY | O_APPEND);

	} while (x > 0);

	free(buffer);
	close_file(from);
	close_file(to);

	return (0);
}
