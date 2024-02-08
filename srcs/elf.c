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
			elf->symtab.len = SH_SIZE(SH_INDEX(header, i, elf->class), elf->class) / sizeof(Elf64_Sym);
		}
		else if (SH_TYPE(SH_INDEX(header, i, elf->class), elf->class) == SHT_DYNSYM)
		{
			elf->dynsym.symtab = addr + SH_OFFSET(SH_INDEX(header, i, elf->class), elf->class);
			elf->dynsym.len = SH_SIZE(SH_INDEX(header, i, elf->class), elf->class) / sizeof(Elf64_Sym);
		}
		else if (SH_TYPE(SH_INDEX(header, i, elf->class), elf->class) == SHT_STRTAB)
		{
			if (!ft_strncmp(strtab + SH_NAME(SH_INDEX(header, i, elf->class), elf->class), ".strtab", 8))
				elf->symtab.strtab = (char *) addr + SH_OFFSET(SH_INDEX(header, i, elf->class), elf->class);
			else if  (!ft_strncmp(strtab + SH_NAME(SH_INDEX(header, i, elf->class), elf->class), ".dynstr", 8))
				elf->dynsym.strtab = (char *) addr + SH_OFFSET(SH_INDEX(header, i, elf->class), elf->class);
		}
	}
}

t_elf	init_elf(uint8_t *addr)
{
	t_elf	elf;

	if (check_elf_header(addr))
		return (DEF_ELF);
	ft_bzero(&elf, sizeof(t_elf));
	set_elf_header_values(addr, &elf);
	define_symtab(addr, &elf);
	return (elf);
}

void	print_elf(t_elf elf)
{
	if (!elf.symtab.symtab || !elf.symtab.strtab)
		return ;
	t_sym_list	*all_sym = init_sym_list(elf.symtab, elf.class);
	// sym_list_add_back(&all_sym, init_sym_list(elf.dynsym, elf.class));
	sort_sym_list(all_sym);
	print_sym_list(all_sym, elf.class);
	free_sym_list(all_sym);
}