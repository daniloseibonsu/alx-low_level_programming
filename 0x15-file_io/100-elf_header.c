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

    display_elf_header(&elf_header);

    close(fd);
    return (0);
}

void display_elf_header(const Elf64_Ehdr *header)
{
    printf("GNU readelf (GNU Binutils for Ubuntu) 2.26.1\n");
    printf("Copyright (C) 2015 Free Software Foundation, Inc.\n");
    printf("This program is free software; you may redistribute it under the terms of\n");
    printf("the GNU General Public License version 3 or (at your option) any later version.\n");
    printf("This program has absolutely no warranty.\n\n");

    printf("ELF Header:\n");
    printf("Magic:   ");
    {
        int i;
        for (i = 0; i < EI_NIDENT; i++)
        {
            printf("%02x ", header->e_ident[i]);
        }
    }
    printf("\n");
    printf("Class:                             %s\n",
           header->e_ident[EI_CLASS] == ELFCLASS32 ? "ELF32" : "ELF64");
    printf("Data:                              %s\n",
           header->e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little endian" : "2's complement, big endian");
    printf("Version:                           %d (current)\n", header->e_ident[EI_VERSION]);
    printf("OS/ABI:                            %d\n", header->e_ident[EI_OSABI]);
    printf("ABI Version:                       %d\n", header->e_ident[EI_ABIVERSION]);
    printf("Type:                              %d\n", header->e_type);
    printf("Machine:                           %d\n", header->e_machine);
    printf("Version:                           0x%08x\n", header->e_version);
    printf("Entry point address:               0x%lx\n", header->e_entry);
    printf("Start of program headers:          %ld (bytes into file)\n", header->e_phoff);
    printf("Start of section headers:          %ld (bytes into file)\n", header->e_shoff);
    printf("Flags:                             0x%x\n", header->e_flags);
    printf("Size of this header:               %d (bytes)\n", header->e_ehsize);
    printf("Size of program headers:           %d (bytes)\n", header->e_phentsize);
    printf("Number of program headers:         %d\n", header->e_phnum);
    printf("Size of section headers:           %d (bytes)\n", header->e_shentsize);
    printf("Number of section headers:         %d\n", header->e_shnum);
    printf("Section header string table index: %d\n", header->e_shstrndx);
}
