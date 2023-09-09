#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void analyze_elf(const char *filename);

/**
 * main - Entry point of the program.
 *
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the command-line arguments.
 * Return: Always 0 (Success)
 *
 * Description: Returns 0 upon successful execution,fails - exit code 98.
 *
 */

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <ELF file>\n", argv[0]);
		return (1);
	}

	const char *filename = argv[1];

	analyze_elf(filename);

	return (0);
}

/**
 *analyze_elf - Analyzes the specified ELF file.
 *
 * @filename: The name of the ELF file to analyze.
 *
 * Description: If the file is not an ELF file - exit code 98.
 */
void analyze_elf(const char *filename)
{
	int elf = open(filename, O_RDONLY);

	if (elf == -1)
	{
		perror("Error opening file");
		exit(1);
	}

	unsigned char e_ident[EI_NIDENT];

	if (read(elf, e_ident, EI_NIDENT) != EI_NIDENT)
	{
		perror("Error reading ELF identification");
		close(elf);
		exit(1);
	}

	if (e_ident[EI_MAG0] != ELFMAG0 ||
	    e_ident[EI_MAG1] != ELFMAG1 ||
	    e_ident[EI_MAG2] != ELFMAG2 ||
	    e_ident[EI_MAG3] != ELFMAG3)
	{
		fprintf(stderr, "Error: Not an ELF file\n");
		close(elf);
		exit(1);
	}

	close(elf);
}
