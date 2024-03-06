#ifndef FT_NM_H
#define FT_NM_H

#include <libft.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>
#include <elf.h>

#ifndef EM_ARC_COMPACT2
# define EM_ARC_COMPACT2 195
# endif


#define RESET "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define CYAN "\033[0;36m"

typedef struct s_elf			t_elf;
typedef struct s_sym_section	t_sym_section;
typedef struct s_sym_list		t_sym_list;

#include "flags.h"
#include "class.h"
#include "prototypes.h"

#define DEF_SYM ((Elf64_Sym) {0})
#define DEF_ELF ((t_elf) {0})

/**
 * @struct		s_sym_section
 * @brief		Structure to hold the symbol table and string table
 */
struct	s_sym_section
{
	void		*symtab;
	uint64_t	len;
	char		*strtab;
};

/**
 * @struct		s_elf
 * @brief		Structure to hold the information of an elf file
 */
struct	s_elf
{
	int				flags;
	uint8_t			class;
	uint8_t			endian;
	uint64_t		size;
	void			*shdr;
	uint16_t		shnum;
	t_sym_section	symtab;
	char			*shstrtab;
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