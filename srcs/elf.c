#include "ft_nm.h"

void	set_elf_header_values(unsigned char *header, t_elf *elf, uint64_t size)
{
	elf->class = header[EI_CLASS];
	elf->endian = header[EI_DATA];
	elf->size = size;
}

int	check_elf_header(unsigned char *header)
{
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
			elf->symtab.len = SH_SIZE(SH_INDEX(header, i, elf->class), elf->class, elf->endian) / SYM_SIZE(elf->class);
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

t_elf	init_elf(uint8_t *addr, uint64_t size)
{
	t_elf	elf;

	if (check_elf_header(addr))
		return (DEF_ELF);
	ft_bzero(&elf, sizeof(t_elf));
	set_elf_header_values(addr, &elf, size);
	elf.shdr = addr + EH_SHOFF(addr, elf.class, elf.endian);
	elf.shnum = EH_SHNUM(addr, elf.class, elf.endian);
	if (!elf.shnum || define_symtab(addr, &elf))
		return (DEF_ELF);
	return (elf);
}

void	swap_sym(Elf64_Sym *s1, Elf64_Sym *s2)
{
	Elf64_Sym	tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	sort_symtab(t_sym_section symtab, int class, int endian)
{
	Elf64_Sym	*tmp;
	Elf64_Sym	*sym = symtab.symtab;

	if (!sym || !symtab.strtab)
		return ;
	for (uint64_t i = 0; i < symtab.len; i++)
	{
		tmp = sym + i;
		for (uint64_t j = i + 1; j < symtab.len; j++)
		{
			if (ft_strcmp_escape(symtab.strtab + SYM_NAME(tmp, class, endian), symtab.strtab + SYM_NAME(sym + j, class, endian), "_", 1) > 0)
				swap_sym(tmp, sym + j);
		}
	}
}

void	print_elf(t_elf elf, char *file_path)
{
	if (!elf.symtab.symtab || !elf.symtab.strtab)
	{
		print_error("no symbols", file_path, 0);
		return ;
	}
	t_sym_list	*all_sym = init_sym_list(elf.symtab, elf.class, elf.endian);
	sort_sym_list(all_sym, elf.class, elf.endian);
	print_sym_list(all_sym, elf.shdr, elf.shnum, elf.class, elf.endian);
	free_sym_list(all_sym);
	return ;
}