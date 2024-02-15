#include "ft_nm.h"

void	set_elf_header_values(unsigned char *header, t_elf *elf)
{
	elf->class = header[EI_CLASS];
	elf->endian = header[EI_DATA];
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

void	define_symtab(uint8_t *addr, t_elf *elf)
{
	uint8_t		*header;
	char		*strtab;

	if (!addr || !elf)
		return ;
	header = addr + EH_SHOFF(addr, elf->class);
	strtab = (char *) (addr + SH_OFFSET(SH_INDEX(header, EH_SHSTRNDX(addr, elf->class), elf->class), elf->class));
	for (uint16_t i = 0; i < EH_SHNUM(addr, elf->class); i++)
	{
		if (SH_TYPE(SH_INDEX(header, i, elf->class), elf->class) == SHT_SYMTAB)
		{
			elf->symtab.symtab = addr + SH_OFFSET(SH_INDEX(header, i, elf->class), elf->class);
			elf->symtab.len = SH_SIZE(SH_INDEX(header, i, elf->class), elf->class) / SYM_SIZE(elf->class);
		}
		else if (SH_TYPE(SH_INDEX(header, i, elf->class), elf->class) == SHT_STRTAB)
			if (!ft_strncmp(strtab + SH_NAME(SH_INDEX(header, i, elf->class), elf->class), ".strtab", 8))
				elf->symtab.strtab = (char *) addr + SH_OFFSET(SH_INDEX(header, i, elf->class), elf->class);
	}
	return ;
}

t_elf	init_elf(uint8_t *addr, char *file_path)
{
	t_elf	elf;

	if (check_elf_header(addr))
	{
		print_error("file format not recognized", file_path, 0);
		return (DEF_ELF);
	}
	ft_bzero(&elf, sizeof(t_elf));
	set_elf_header_values(addr, &elf);
	elf.shdr = addr + EH_SHOFF(addr, elf.class);
	elf.shnum = EH_SHNUM(addr, elf.class);
	define_symtab(addr, &elf);
	return (elf);
}

void	swap_sym(Elf64_Sym *s1, Elf64_Sym *s2)
{
	Elf64_Sym	tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	sort_symtab(t_sym_section symtab, int class)
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
			if (ft_strcmp_escape(symtab.strtab + SYM_NAME(tmp, class), symtab.strtab + SYM_NAME(sym + j, class), "_", 1) > 0)
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
	t_sym_list	*all_sym = init_sym_list(elf.symtab, elf.class);
	sort_sym_list(all_sym, elf.class);
	print_sym_list(all_sym, elf.shdr, elf.shnum, elf.class);
	free_sym_list(all_sym);
	return ;
}