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

#define DEF_ELF ((t_elf) {0, 0, (t_sym_section) {NULL, 0, NULL}, (t_sym_section) {NULL, 0, NULL}})

#define SYM_INFO(sym, class) ((class == ELFCLASS32) ? ((Elf32_Sym *) sym)->st_info : ((Elf64_Sym *) sym)->st_info)
#define SYM_NAME(sym, class) ((class == ELFCLASS32) ? ((Elf32_Sym *) sym)->st_name : ((Elf64_Sym *) sym)->st_name)
#define SYM_VALUE(sym, class) ((class == ELFCLASS32) ? ((Elf32_Sym *) sym)->st_value : ((Elf64_Sym *) sym)->st_value)
#define NEXT_SYM(sym, class) ((class == ELFCLASS32) ? (void *) (((Elf32_Sym *) sym) + 1) : (void *) (((Elf64_Sym *) sym) + 1))

#define EH_SHOFF(ehdr, class) ((class == ELFCLASS32) ? ((Elf32_Ehdr *) ehdr)->e_shoff : ((Elf64_Ehdr *) ehdr)->e_shoff)
#define EH_SHNUM(ehdr, class) ((class == ELFCLASS32) ? ((Elf32_Ehdr *) ehdr)->e_shnum : ((Elf64_Ehdr *) ehdr)->e_shnum)
#define EH_SHSTRNDX(ehdr, class) ((class == ELFCLASS32) ? ((Elf32_Ehdr *) ehdr)->e_shstrndx : ((Elf64_Ehdr *) ehdr)->e_shstrndx)

#define SH_INDEX(addr, i, class) ((class == ELFCLASS32) ? ((void *) ((Elf32_Shdr *) addr + i)) : ((void *) ((Elf64_Shdr *) addr + i)))
#define SH_OFFSET(shdr, class) ((class == ELFCLASS32) ? ((Elf32_Shdr *) shdr)->sh_offset : ((Elf64_Shdr *) shdr)->sh_offset)
#define SH_SIZE(shdr, class) ((class == ELFCLASS32) ? ((Elf32_Shdr *) shdr)->sh_size : ((Elf64_Shdr *) shdr)->sh_size)
#define SH_TYPE(shdr, class) ((class == ELFCLASS32) ? ((Elf32_Shdr *) shdr)->sh_type : ((Elf64_Shdr *) shdr)->sh_type)
#define SH_NAME(shdr, class) ((class == ELFCLASS32) ? ((Elf32_Shdr *) shdr)->sh_name : ((Elf64_Shdr *) shdr)->sh_name)

typedef struct	s_sym_section
{
	void		*symtab;
	uint64_t	len;
	char		*strtab;
}				t_sym_section;

typedef struct	s_elf
{
	int				class;
	int				endian;

	t_sym_section	symtab;
	t_sym_section	dynsym;
}				t_elf;

typedef struct	s_sym_list
{
	char				*name;
	void				*addr;
	struct s_sym_list	*next;
}				t_sym_list;

// flags.c
int	parse_flags(int argc, char *argv[]);

// elf.c
void	print_elf(t_elf elf);
t_elf	init_elf(uint8_t *addr);

// def_symtab.c
void	define_symtab(uint8_t *addr, t_elf *elf);


// sym_list.c
t_sym_list	*init_sym_list(t_sym_section section, int class);
void		free_sym_list(t_sym_list *sym_list);
void		sym_list_add_back(t_sym_list **sym_list, t_sym_list *new);
void		print_sym_list(t_sym_list *sym, int class);
void		sort_sym_list(t_sym_list *sym);

#endif

// 00 00 00 00 00 00 11 60