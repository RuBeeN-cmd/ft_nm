#ifndef FT_NM_H
#define FT_NM_H

#include <libft.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>
#include <elf.h>

#define DEBUG_SYMS		1 << 0 // -a, --debug-syms
#define EXTERN_ONLY		1 << 1 // -g, --extern-only
#define UNDEFINED_ONLY	1 << 2 // -u, --undefined-only
#define REVERSE_SORT	1 << 3 // -r, --reverse-sort
#define NO_SORT			1 << 4 // -p, --no-sort

#define DEF_ELF  ((t_elf) { 0, {NULL}, {NULL}, {NULL}, NULL, NULL, {NULL}, 0, {NULL}, 0, NULL})

typedef struct	s_elf
{
	uint8_t	e_class;
	union {
		Elf32_Ehdr	*e32_ehdr;
		Elf64_Ehdr	*e64_ehdr;
	};
	
	union {
		Elf32_Phdr	*e32_phdr;
		Elf64_Phdr	*e64_phdr;
	};

	union {
		Elf32_Shdr	*e32_shdr;
		Elf64_Shdr	*e64_shdr;
	};

	char	*str_table;
	char	*sh_str_table;

	union {
		Elf32_Sym	*e32_sym;
		Elf64_Sym	*e64_sym;
	};

	uint64_t	sym_len;

	union {
		Elf32_Sym	*e32_dynsym;
		Elf64_Sym	*e64_dynsym;
	};

	uint64_t	dynsym_len;
	char		*dynstr;
}				t_elf;

typedef struct	s_symlist
{
	char				*name;
	struct	s_symlist	*next;
	union {
		Elf32_Sym	*sym32;
		Elf64_Sym	*sym64;
	};
}				t_symlist;

// flags.c
int	parse_flags(int argc, char *argv[]);

// elf.c
t_elf	init_elf(uint8_t *addr);
int		print_elf(t_elf elf);

// elf_header.c
void	print_32elf_header(Elf32_Ehdr *hdr);
void	print_64elf_header(Elf64_Ehdr *hdr);

// program_header.c
void	print_32program_header(Elf32_Phdr *hdr, int hdr_number);
void	print_64program_header(Elf64_Phdr *hdr, int hdr_number);

// section_header.c
void	print_32section_header(Elf32_Shdr *hdr, int hdr_number, char *str_table);
void	print_64section_header(Elf64_Shdr *hdr, int hdr_number, char *str_table);

// symbol.c
void	print_32symbol_table(Elf32_Sym *sym, uint64_t sym_len, char *str_table);
void	print_64symbol_table(Elf64_Sym *sym, uint64_t sym_len, char *str_table);

// print_utils.c
void	print_column(char *str, char c, unsigned int s);
void	print_number_column(unsigned long n, char c, unsigned int s, char *b);

#endif