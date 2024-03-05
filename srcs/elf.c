#include "ft_nm.h"

void	set_elf_values(unsigned char *header, t_elf *elf, uint64_t size, int flags)
{
	elf->flags = flags;
	elf->class = header[EI_CLASS];
	elf->endian = header[EI_DATA];
	elf->size = size;
}

int	check_ident(unsigned char *header, uint64_t size)
{
	if (!header || size < EI_NIDENT)
		return (1);
	if (ft_strncmp((char *) header, ELFMAG, SELFMAG))
		return (1);
	if (header[EI_CLASS] != ELFCLASS32
		&& header[EI_CLASS] != ELFCLASS64)
		return (1);
	if (header[EI_DATA] != ELFDATA2LSB
		&& header[EI_DATA] != ELFDATA2MSB)
		return (1);
	if (header[EI_VERSION] != EV_CURRENT)
		return (1);
	return (0);
}

int	check_elf_header(void *hdr, uint64_t size)
{
	uint8_t	class;
	uint8_t	endian;

	if (!hdr)
		return (1);
	class = EH_IDENT(hdr)[EI_CLASS];
	endian = EH_IDENT(hdr)[EI_DATA];
	if (size < EH_SSIZE(class))
		return (1);
	if (EH_SHOFF(hdr, class, endian)
		+ EH_SHNUM(hdr, class, endian) * SH_SSIZE(class) > size)
		return (1);
	if (EH_SHENTSIZE(hdr, class, endian) != SH_SSIZE(class))
		return (1);
	return (0);
}

int	define_symtab(uint8_t *addr, t_elf *elf)
{
	uint8_t		*header;
	char		*strtab;

	if (!addr || !elf)
		return (1);
	header = addr + EH_SHOFF(addr, elf->class, elf->endian);
	void	*sh = SH_INDEX(header, EH_SHSTRNDX(addr, elf->class, elf->endian), elf->class);
	if ((unsigned long) sh - (unsigned long) addr > elf->size)
		return (1);
	uint64_t	sh_offset = SH_OFFSET(sh, elf->class, elf->endian);
	strtab = (char *) (addr + sh_offset);
	for (uint16_t i = 0; i < EH_SHNUM(addr, elf->class, elf->endian); i++)
	{
		if (SH_TYPE(SH_INDEX(header, i, elf->class), elf->class, elf->endian) == SHT_SYMTAB)
		{
			elf->symtab.symtab = addr + SH_OFFSET(SH_INDEX(header, i, elf->class), elf->class, elf->endian);
			elf->symtab.len = SH_SIZE(SH_INDEX(header, i, elf->class), elf->class, elf->endian) / SYM_SSIZE(elf->class);
		}
		else if (SH_TYPE(SH_INDEX(header, i, elf->class), elf->class, elf->endian) == SHT_STRTAB)
		{
			if (!ft_strncmp(strtab + SH_NAME(SH_INDEX(header, i, elf->class), elf->class, elf->endian), ".strtab", 8))
				elf->symtab.strtab = (char *) addr + SH_OFFSET(SH_INDEX(header, i, elf->class), elf->class, elf->endian);
			if (!ft_strncmp(strtab + SH_NAME(SH_INDEX(header, i, elf->class), elf->class, elf->endian), ".shstrtab", 10))
				elf->shstrtab = (char *) addr + SH_OFFSET(SH_INDEX(header, i, elf->class), elf->class, elf->endian);
		}
	}
	return (0);
}

t_elf	init_elf(uint8_t *addr, uint64_t size, int flags)
{
	t_elf	elf;

	if (check_ident(addr, size))
		return (DEF_ELF);
	if (check_elf_header(addr, size))
		return (DEF_ELF);
	ft_bzero(&elf, sizeof(t_elf));
	set_elf_values(addr, &elf, size, flags);
	elf.shdr = addr + EH_SHOFF(addr, elf.class, elf.endian);
	elf.shnum = EH_SHNUM(addr, elf.class, elf.endian);
	if (!elf.shnum || define_symtab(addr, &elf))
		return (DEF_ELF);
	return (elf);
}

void	print_elf(t_elf elf, char *file_path)
{
	if (!elf.symtab.symtab || !elf.symtab.strtab)
	{
		print_error("no symbols", file_path, 0);
		return ;
	}
	t_sym_list	*all_sym = init_sym_list(elf.symtab, elf.class, elf.endian, elf.flags, elf.shdr, elf.shstrtab);
	if (!(elf.flags & NO_SORT))
		sort_sym_list(all_sym, elf.class, elf.endian, elf.flags & REVERSE_SORT);
	print_sym_list(all_sym, elf.shdr, elf.shnum, elf.class, elf.endian);
	free_sym_list(all_sym);
	return ;
}