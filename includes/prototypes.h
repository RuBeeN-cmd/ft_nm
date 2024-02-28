#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include "ft_nm.h"

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

// read_uint.c
uint16_t	read_uint16(uint16_t value, int endian);
uint32_t	read_uint32(uint32_t value, int endian);
uint64_t	read_uint64(uint64_t value, int endian);

#endif