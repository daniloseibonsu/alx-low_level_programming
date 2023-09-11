#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <elf.h>

void display_elf_header(const Elf64_Ehdr *header);

int main(int argc, char *argv[])
{
	const char *filename;
	int fd;
	Elf64_Ehdr elf_header;

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <ELF file>\n", argv[0]);
		return (1);
	}

	filename = argv[1];

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "Error opening file: %s\n", filename);
		return (98);
	}

	if (read(fd, &elf_header, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr))
	{
		fprintf(stderr, "Error reading ELF header: %s\n", filename);
		close(fd);
		return (98);
	}

	if (lseek(fd, 0, SEEK_SET) == -1)
	{
		fprintf(stderr, "Error seeking to the beginning of file: %s\n", filename);
		close(fd);
		return (98);
	}

	display_elf_header(&elf_header);

	close(fd);
	return (0);
}

void display_elf_header(const Elf64_Ehdr *header)
{
	int i;

	printf("ELF Header:\n");
	printf("Magic:\t");
	for (i = 0; i < EI_NIDENT; i++)
	{
		printf("%02x ", header->e_ident[i]);
	}
	printf("\n");
	printf("Class:\t\t\t\t\t\t%s\n",
	       header->e_ident[EI_CLASS] == ELFCLASS32 ? "ELF32" : "ELF64");
	printf("Data:\t\t\t\t\t\t%s\n",
	       header->e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little endian" : "2's complement, big endian");
	printf("Version:\t\t\t\t\t%d (current)\n", header->e_ident[EI_VERSION]);
	printf("OS/ABI:\t\t\t\t\t\t%d\n", header->e_ident[EI_OSABI]);
	printf("ABI Version:\t\t\t\t\t%d\n", header->e_ident[EI_ABIVERSION]);
	printf("Type:\t\t\t\t\t\t%d\n", header->e_type);
	printf("Machine:\t\t\t\t\t%d\n", header->e_machine);
	printf("Version:\t\t\t\t\t0x%08x\n", header->e_version);
	printf("Entry point address:\t\t\t0x%lx\n", header->e_entry);
	printf("Start of program headers:\t\t%ld (bytes into file)\n", header->e_phoff);
	printf("Start of section headers:\t\t%ld (bytes into file)\n", header->e_shoff);
	printf("Flags:\t\t\t\t\t\t0x%x\n", header->e_flags);
	printf("Size of this header:\t\t\t%d (bytes)\n", header->e_ehsize);
	printf("Size of program headers:\t\t%d (bytes)\n", header->e_phentsize);
	printf("Number of program headers:\t\t%d\n", header->e_phnum);
	printf("Size of section headers:\t\t%d (bytes)\n", header->e_shentsize);
	printf("Number of section headers:\t\t%d\n", header->e_shnum);
	printf("Section header string table index:\t%d\n", header->e_shstrndx);
}
