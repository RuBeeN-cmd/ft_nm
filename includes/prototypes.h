#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include "ft_nm.h"

// flags.c
int	parse_flags(int argc, char *argv[]);

// elf.c
t_elf	init_elf(uint8_t *addr, uint64_t size, uint8_t flags, char *path);
void	print_elf(t_elf elf);

// sym_list.c
t_sym_list	*init_sym_list(t_elf elf);
void		free_sym_list(t_sym_list *sym_list);
void		sort_sym_list(t_sym_list *sym, int class, int endian, int reverse);
int     	ft_strcmp_escape(char *n1, char *n2, char *set, int lower);

// error.c
void	print_error(char *str, char *file, int quotes);
void	print_warning(char *str, char *file);

// print.c
void	print_sym_list(t_sym_list *sym, void *shdr, uint16_t shnum, int class, int endian);

// read_uint.c
uint16_t	read_uint16(uint16_t value, int endian);
uint32_t	read_uint32(uint32_t value, int endian);
uint64_t	read_uint64(uint64_t value, int endian);

// getters_ehdr.c
uint8_t		*get_e_ident(void *ehdr);
uint16_t	get_e_type(void *ehdr, uint8_t endian);
uint16_t	get_e_machine(void *ehdr, uint8_t endian);
uint32_t	get_e_version(void *ehdr, uint8_t endian);
uint64_t	get_e_entry(void *ehdr, uint8_t class, uint8_t endian);
uint64_t	get_e_shoff(void *ehdr, uint8_t class, uint8_t endian);
uint64_t	get_e_phoff(void *ehdr, uint8_t class, uint8_t endian);
uint32_t	get_e_flags(void *ehdr, uint8_t class, uint8_t endian);
uint16_t	get_e_ehsize(void *ehdr, uint8_t class, uint8_t endian);
uint16_t	get_e_phentsize(void *ehdr, uint8_t class, uint8_t endian);
uint16_t	get_e_phnum(void *ehdr, uint8_t class, uint8_t endian);
uint16_t	get_e_shentsize(void *ehdr, uint8_t class, uint8_t endian);
uint16_t	get_e_shnum(void *ehdr, uint8_t class, uint8_t endian);
uint16_t	get_e_shstrndx(void *ehdr, uint8_t class, uint8_t endian);

// getters_shdr.c
uint32_t	get_sh_name(void *shdr, uint8_t class, uint8_t endian);
uint32_t	get_sh_type(void *shdr, uint8_t class, uint8_t endian);
uint64_t	get_sh_flags(void *shdr, uint8_t class, uint8_t endian);
uint64_t	get_sh_addr(void *shdr, uint8_t class, uint8_t endian);
uint64_t	get_sh_offset(void *shdr, uint8_t class, uint8_t endian);
uint64_t	get_sh_size(void *shdr, uint8_t class, uint8_t endian);
uint32_t	get_sh_link(void *shdr, uint8_t class, uint8_t endian);
uint32_t	get_sh_info(void *shdr, uint8_t class, uint8_t endian);
uint64_t	get_sh_addralign(void *shdr, uint8_t class, uint8_t endian);
uint64_t	get_sh_entsize(void *shdr, uint8_t class, uint8_t endian);

// getters_sym.c
uint32_t	get_st_name(void *sym, uint8_t class, uint8_t endian);
uint64_t	get_st_value(void *sym, uint8_t class, uint8_t endian);
uint64_t	get_st_size(void *sym, uint8_t class, uint8_t endian);
uint8_t		get_st_info(void *sym, uint8_t class);
uint8_t		get_st_other(void *sym, uint8_t class);
uint16_t	get_st_shndx(void *sym, uint8_t class, uint8_t endian);

#endif