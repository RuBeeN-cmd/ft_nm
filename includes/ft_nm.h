#ifndef FT_NM_H
#define FT_NM_H

#include <libft.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>
#include <elf.h>

typedef struct s_elf			t_elf;
typedef struct s_sym_section	t_sym_section;
typedef struct s_sym_list		t_sym_list;

#include "flags.h"
#include "prototypes.h"

#define EHDR_SIZE(class) (class == ELFCLASS32 ? sizeof(Elf32_Ehdr) : sizeof(Elf64_Ehdr))
#define SHDR_SIZE(class) (class == ELFCLASS32 ? sizeof(Elf32_Shdr) : sizeof(Elf64_Shdr))
#define SYM_SIZE(class) (class == ELFCLASS32 ? sizeof(Elf32_Sym) : sizeof(Elf64_Sym))
#define SIZE(class) (class == ELFCLASS32 ? sizeof(uint32_t) : sizeof(uint64_t))

#define DEF_SYM ((Elf64_Sym) {0})
#define DEF_ELF ((t_elf) {0})

/**
 * @struct		s_elf
 * @brief		Structure to hold the information of an elf file
 */
struct	s_elf
{
	char			*path;
	uint64_t		size;
	
	uint8_t			flags;
	uint8_t			class;
	uint8_t			endian;

	uint16_t		shnum;
	void			*shdr;
	char			*shstrtab;

	uint64_t		symnum;
	void			*symtab;
	char			*strtab;
};

/**
 * @struct		s_sym_list
 * @brief		Structure to hold a list of symbols
 */
struct	s_sym_list
{
	char				*name;
	void				*addr;
	struct s_sym_list	*next;
};

#endif