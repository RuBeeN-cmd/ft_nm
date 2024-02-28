#ifndef FT_NM_H
#define FT_NM_H

#include <libft.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>
#include <elf.h>

#define FLAGS_NB 6
#define FLAGS "agurph"
#define LONG_FLAGS (char *[]) { "debug-syms", "extern-only", "undefined-only", "reverse-sort", "no-sort", "help" }

#define DEBUG_SYMS		1 << 0
#define EXTERN_ONLY		1 << 1
#define UNDEFINED_ONLY	1 << 2
#define REVERSE_SORT	1 << 3
#define NO_SORT			1 << 4
#define HELP			1 << 5

#define USAGE "\
Usage: nm [option(s)] [file(s)]\n\
 List symbols in [file(s)] (a.out by default).\n\
 The options are:\n\
  -a, --debug-syms       Display debugger-only symbols\n\
  -g, --extern-only      Display only external symbols\n\
  -p, --no-sort          Do not sort the symbols\n\
  -r, --reverse-sort     Reverse the sense of the sort\n\
  -u, --undefined-only   Display only undefined symbols\n\
  -h, --help             Display this information\n\
"

#define SYM_INFO(sym, class) (class == ELFCLASS32 ? ((Elf32_Sym *) sym)->st_info : ((Elf64_Sym *) sym)->st_info)
#define SYM_NAME(sym, class, endian) read_uint32(class == ELFCLASS32 ? ((Elf32_Sym *) sym)->st_name : ((Elf64_Sym *) sym)->st_name, endian)
#define SYM_VALUE(sym, class, endian) (class == ELFCLASS32 ? read_uint32(((Elf32_Sym *) sym)->st_value, endian) : read_uint64(((Elf64_Sym *) sym)->st_value, endian))
#define SYM_VALUE_SIZE(class) (class == ELFCLASS32 ? sizeof(uint32_t) : sizeof(uint64_t))
#define SYM_SIZE(class) (class == ELFCLASS32 ? sizeof(Elf32_Sym) : sizeof(Elf64_Sym))
#define SYM_SHNDX(sym, class, endian) read_uint16(class == ELFCLASS32 ? ((Elf32_Sym *) sym)->st_shndx : ((Elf64_Sym *) sym)->st_shndx, endian)
#define SYM_BIND(sym, class) (class == ELFCLASS32 ? ELF32_ST_BIND(((Elf32_Sym *) sym)->st_info) : ELF64_ST_BIND(((Elf64_Sym *) sym)->st_info))
#define SYM_TYPE(sym, class) (class == ELFCLASS32 ? ELF32_ST_TYPE(((Elf32_Sym *) sym)->st_info) : ELF64_ST_TYPE(((Elf64_Sym *) sym)->st_info))
#define SYM_VISIBILITY(sym, class) (class == ELFCLASS32 ? ELF32_ST_VISIBILITY(((Elf32_Sym *) sym)->st_other) : ELF64_ST_VISIBILITY(((Elf64_Sym *) sym)->st_other))
#define NEXT_SYM(sym, class) (class == ELFCLASS32 ? (void *) (((Elf32_Sym *) sym) + 1) : (void *) (((Elf64_Sym *) sym) + 1))

#define EH_SHOFF(ehdr, class, endian) (class == ELFCLASS32 ? read_uint32(((Elf32_Ehdr *) ehdr)->e_shoff, endian) : read_uint64(((Elf64_Ehdr *) ehdr)->e_shoff, endian))
#define EH_SHNUM(ehdr, class, endian) read_uint16(class == ELFCLASS32 ? ((Elf32_Ehdr *) ehdr)->e_shnum : ((Elf64_Ehdr *) ehdr)->e_shnum, endian)
#define EH_SHSTRNDX(ehdr, class, endian) read_uint16(class == ELFCLASS32 ? ((Elf32_Ehdr *) ehdr)->e_shstrndx : ((Elf64_Ehdr *) ehdr)->e_shstrndx, endian)

#define SH_INDEX(addr, i, class) (class == ELFCLASS32 ? ((void *) ((Elf32_Shdr *) addr + i)) : ((void *) ((Elf64_Shdr *) addr + i)))
#define SH_OFFSET(shdr, class, endian) (class == ELFCLASS32 ? read_uint32(((Elf32_Shdr *) shdr)->sh_offset, endian) : read_uint64(((Elf64_Shdr *) shdr)->sh_offset, endian))
#define SH_SIZE(shdr, class, endian) (class == ELFCLASS32 ? read_uint32(((Elf32_Shdr *) shdr)->sh_size, endian) : read_uint64(((Elf64_Shdr *) shdr)->sh_size, endian))
#define SH_TYPE(shdr, class, endian) read_uint32(class == ELFCLASS32 ? ((Elf32_Shdr *) shdr)->sh_type : ((Elf64_Shdr *) shdr)->sh_type, endian)
#define SH_NAME(shdr, class, endian) read_uint32(class == ELFCLASS32 ? ((Elf32_Shdr *) shdr)->sh_name : ((Elf64_Shdr *) shdr)->sh_name, endian)
#define SH_FLAGS(shdr, class, endian) (class == ELFCLASS32 ? read_uint32(((Elf32_Shdr *) shdr)->sh_flags, endian) : read_uint64(((Elf64_Shdr *) shdr)->sh_flags, endian))

#define DEF_SYM ((Elf64_Sym) {0})
#define DEF_ELF ((t_elf) {0})



typedef struct	s_sym_section
{
	void		*symtab;
	uint64_t	len;
	char		*strtab;
}				t_sym_section;

typedef struct	s_elf
{
	int				flags;
	uint8_t			class;
	uint8_t			endian;
	uint64_t		size;
	void			*shdr;
	uint16_t		shnum;
	t_sym_section	symtab;
	char			*shstrtab;
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
t_elf	init_elf(uint8_t *addr, uint64_t size, int flags);
int		define_symtab(uint8_t *addr, t_elf *elf);
void	print_elf(t_elf elf, char *file_path);

// sym_list.c
t_sym_list	*init_sym_list(t_sym_section section, int class, int endian, int flags, void *shdr, char *shstrtab);
void		free_sym_list(t_sym_list *sym_list);
void		sort_sym_list(t_sym_list *sym, int class, int endian, int reverse);
int     	ft_strcmp_escape(char *n1, char *n2, char *set, int lower);

// error.c
void	print_error(char *str, char *file, int quotes);

// print.c
void	print_sym_list(t_sym_list *sym, void *shdr, uint16_t shnum, int class, int endian);

// read.c
uint16_t	read_uint16(uint16_t value, int endian);
uint32_t	read_uint32(uint32_t value, int endian);
uint64_t	read_uint64(uint64_t value, int endian);

#endif