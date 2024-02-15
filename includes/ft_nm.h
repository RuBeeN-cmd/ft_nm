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

#define SYM_INFO(sym, class) (class == ELFCLASS32 ? ((Elf32_Sym *) sym)->st_info : ((Elf64_Sym *) sym)->st_info)
#define SYM_NAME(sym, class) (class == ELFCLASS32 ? ((Elf32_Sym *) sym)->st_name : ((Elf64_Sym *) sym)->st_name)
#define SYM_VALUE(sym, class) (class == ELFCLASS32 ? ((Elf32_Sym *) sym)->st_value : ((Elf64_Sym *) sym)->st_value)
#define SYM_VALUE_SIZE(class) (class == ELFCLASS32 ? sizeof(uint32_t) : sizeof(uint64_t))
#define SYM_SIZE(class) (class == ELFCLASS32 ? sizeof(Elf32_Sym) : sizeof(Elf64_Sym))
#define SYM_SHNDX(sym, class) (class == ELFCLASS32 ? ((Elf32_Sym *) sym)->st_shndx : ((Elf64_Sym *) sym)->st_shndx)
#define SYM_BIND(sym, class) (class == ELFCLASS32 ? ELF32_ST_BIND(((Elf32_Sym *) sym)->st_info) : ELF64_ST_BIND(((Elf64_Sym *) sym)->st_info))
#define SYM_TYPE(sym, class) (class == ELFCLASS32 ? ELF32_ST_TYPE(((Elf32_Sym *) sym)->st_info) : ELF64_ST_TYPE(((Elf64_Sym *) sym)->st_info))
#define NEXT_SYM(sym, class) (class == ELFCLASS32 ? (void *) (((Elf32_Sym *) sym) + 1) : (void *) (((Elf64_Sym *) sym) + 1))

#define EH_SHOFF(ehdr, class) (class == ELFCLASS32 ? ((Elf32_Ehdr *) ehdr)->e_shoff : ((Elf64_Ehdr *) ehdr)->e_shoff)
#define EH_SHNUM(ehdr, class) (class == ELFCLASS32 ? ((Elf32_Ehdr *) ehdr)->e_shnum : ((Elf64_Ehdr *) ehdr)->e_shnum)
#define EH_SHSTRNDX(ehdr, class) (class == ELFCLASS32 ? ((Elf32_Ehdr *) ehdr)->e_shstrndx : ((Elf64_Ehdr *) ehdr)->e_shstrndx)

#define SH_INDEX(addr, i, class) (class == ELFCLASS32 ? ((void *) ((Elf32_Shdr *) addr + i)) : ((void *) ((Elf64_Shdr *) addr + i)))
#define SH_OFFSET(shdr, class) (class == ELFCLASS32 ? ((Elf32_Shdr *) shdr)->sh_offset : ((Elf64_Shdr *) shdr)->sh_offset)
#define SH_SIZE(shdr, class) (class == ELFCLASS32 ? ((Elf32_Shdr *) shdr)->sh_size : ((Elf64_Shdr *) shdr)->sh_size)
#define SH_TYPE(shdr, class) (class == ELFCLASS32 ? ((Elf32_Shdr *) shdr)->sh_type : ((Elf64_Shdr *) shdr)->sh_type)
#define SH_NAME(shdr, class) (class == ELFCLASS32 ? ((Elf32_Shdr *) shdr)->sh_name : ((Elf64_Shdr *) shdr)->sh_name)
#define SH_FLAGS(shdr, class) (class == ELFCLASS32 ? ((Elf32_Shdr *) shdr)->sh_flags : ((Elf64_Shdr *) shdr)->sh_flags)

#define DEF_ELF ((t_elf) {0, 0, NULL, 0, (t_sym_section) {NULL, 0, NULL}})

typedef struct	s_sym_section
{
	void		*symtab;
	uint64_t	len;
	char		*strtab;
}				t_sym_section;

typedef struct	s_elf
{
	uint8_t			class;
	uint8_t			endian;
	void			*shdr;
	uint16_t		shnum;
	t_sym_section	symtab;
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
void		print_sym_list(t_sym_list *sym, void *shdr, uint16_t shnum, int class);
void		sort_sym_list(t_sym_list *sym, int class);
int     	ft_strcmp_escape(char *n1, char *n2, char *set, int lower);

#endif