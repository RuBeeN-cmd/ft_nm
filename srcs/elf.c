#include "ft_nm.h"

/**
 * @brief		Set the values of the elf structure
 * @param[in]	header The header to use
 * @param[out]	elf The elf structure to fill
 * @param[in]	size The size of the file
 * @param[in]	flags The flags to use
 * @param[in]	path The path of the file
 */
static void	set_elf_values(unsigned char *header, t_elf *elf, uint64_t size, uint8_t flags, char *path)
{
	elf->flags = flags;
	elf->class = header[EI_CLASS];
	elf->endian = header[EI_DATA];
	elf->size = size;
	elf->path = path;
}

/**
 * @brief		Check the elf header identification
 * @param[in]	header The header to check
 * @param[in]	size The size of the header
 * @return		0 on success, 1 on error
 */
static int	check_ident(unsigned char *ident, uint64_t size)
{
	if (!ident || size < EI_NIDENT)
		return (1);
	if (ft_strncmp((char *) ident, ELFMAG, SELFMAG))
		return (1);
	if (ident[EI_CLASS] != ELFCLASS32
		&& ident[EI_CLASS] != ELFCLASS64)
		return (1);
	if (ident[EI_DATA] != ELFDATA2LSB
		&& ident[EI_DATA] != ELFDATA2MSB)
		return (1);
	if (ident[EI_VERSION] != EV_CURRENT)
		return (1);
	return (0);
}

/**
 * @brief		Check the elf header
 * @param[in]	ehdr The header to check
 * @param[in]	size The size of the header
 * @return		0 on success, 1 on error 
 */
static int	check_elf_header(void *ehdr, uint64_t size)
{
	uint8_t	class;
	uint8_t	endian;

	if (!ehdr)
		return (1);
	class = get_e_ident(ehdr)[EI_CLASS];
	endian = get_e_ident(ehdr)[EI_DATA];
	if (size < EHDR_SIZE(class))
		return (1);
	if (get_e_shoff(ehdr, class, endian)
		+ get_e_shnum(ehdr, class, endian) * SHDR_SIZE(class) > size)
		return (1);
	if (get_e_shentsize(ehdr, class, endian) != SHDR_SIZE(class))
		return (1);
	return (0);
}

/**
 * @brief		Find the section header string table and the symbol table
 * @param[in]	addr The address of the mapped file
 * @param[out]	elf The elf structure to fill
 * @return		0 on success, 1 on error
 */
static int	define_shdr(void *ehdr, t_elf *elf)
{
	if (!ehdr || !elf)
		return (1);
	uint16_t	e_shstrndx = get_e_shstrndx(ehdr, elf->class, elf->endian);
	if (e_shstrndx >= elf->shnum)
		return (0);
	char	*shstrtab = (char *) ehdr + get_sh_offset(elf->shdr + e_shstrndx * SHDR_SIZE(elf->class), elf->class, elf->endian);
	char	*shdr = elf->shdr;
	for (uint16_t i = 0; i < elf->shnum; i++)
	{
		uint32_t	type = get_sh_type(shdr, elf->class, elf->endian);
		if (type == SHT_SYMTAB)
		{
			elf->symtab = ehdr + get_sh_offset(shdr, elf->class, elf->endian);
			elf->symnum = get_sh_size(shdr, elf->class, elf->endian) / SYM_SIZE(elf->class);
		}
		else if (type == SHT_STRTAB)
		{
			if (i == e_shstrndx)
				elf->shstrtab = (char *) ehdr + get_sh_offset(shdr, elf->class, elf->endian);
			if (!ft_strncmp(shstrtab + get_sh_name(shdr, elf->class, elf->endian), ".strtab", 8))
				elf->strtab = (char *) ehdr + get_sh_offset(shdr, elf->class, elf->endian);
		}
		shdr += SHDR_SIZE(elf->class);
	}
	return (0);
}

/**
 * @brief		Initialize an elf structure
 * @param[in]	addr The address of the mapped file
 * @param[in]	size The size of the mapped file
 * @param[in]	flags The flags to use
 * @param[in]	path The path of the file
 * @return		The initialized elf structure
 */
t_elf	init_elf(uint8_t *addr, uint64_t size, uint8_t flags, char *path)
{
	t_elf	elf;

	if (check_ident(addr, size))
		return (DEF_ELF);
	if (check_elf_header(addr, size))
		return (DEF_ELF);
	ft_bzero(&elf, sizeof(t_elf));
	set_elf_values(addr, &elf, size, flags, path);
	elf.shdr = addr + get_e_shoff(addr, elf.class, elf.endian);
	elf.shnum = get_e_shnum(addr, elf.class, elf.endian);
	if (!elf.shnum || define_shdr(addr, &elf))
		return (DEF_ELF);
	if (!elf.shstrtab)
		print_warning("has a corrupt string table index - ignoring", elf.path);
	return (elf);
}

/**
 * @brief		Print the symbols of an elf file
 * @param[in]	elf The elf structure to print
 */
void	print_elf(t_elf elf)
{
	if (!elf.symtab || !elf.strtab || !elf.shstrtab)
	{
		print_error("no symbols", elf.path, 0);
		return ;
	}
	t_sym_list	*all_sym = init_sym_list(elf);
	if (!(elf.flags & NO_SORT))
		sort_sym_list(all_sym, elf.class, elf.endian, elf.flags & REVERSE_SORT);
	print_sym_list(all_sym, elf.shdr, elf.shnum, elf.class, elf.endian);
	free_sym_list(all_sym);
	return ;
}