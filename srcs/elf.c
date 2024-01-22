#include "ft_nm.h"

int	print_elf(t_elf elf)
{
	if (elf.e_class != ELFCLASS32 && elf.e_class != ELFCLASS64)
		return (1);
	if (elf.e_class == ELFCLASS32)
	{
		// print_32elf_header(elf.e32_ehdr);
		// ft_printf("\n");
		// print_32program_header(elf.e32_phdr, elf.e32_ehdr->e_phnum);
		// ft_printf("\n");
		// print_32section_header(elf.e32_shdr, elf.e32_ehdr->e_shnum, elf.sh_str_table);
		// ft_printf("\n");
		print_32symbol_table(elf.e32_sym, elf.sym_len, elf.str_table);
		print_32dynsymbol_table(elf.e32_dynsym, elf.dynsym_len, elf.dynstr);
	}
	else
	{
		// print_64elf_header(elf.e64_ehdr);
		// ft_printf("\n");
		// print_64program_header(elf.e64_phdr, elf.e64_ehdr->e_phnum);
		// ft_printf("\n");
		// print_64section_header(elf.e64_shdr, elf.e64_ehdr->e_shnum, elf.sh_str_table);
		// ft_printf("\n");
		print_64symbol_table(elf.e64_sym, elf.sym_len, elf.str_table);
		print_64dynsymbol_table(elf.e64_dynsym, elf.dynsym_len, elf.dynstr);
	}
	return (0);
}

void	fill_elf32_tables(t_elf *elf)
{
	if (!elf) return;
	elf->sh_str_table = (char *) ((uint8_t *) elf->e32_ehdr + elf->e32_shdr[elf->e32_ehdr->e_shstrndx].sh_offset);
	for (uint16_t i = 0; i < elf->e32_ehdr->e_shnum; i++)
	{
		if (elf->e32_shdr[i].sh_type == SHT_SYMTAB)
		{
			elf->e32_sym = (Elf32_Sym *) ((uint8_t *) elf->e32_ehdr + elf->e32_shdr[i].sh_offset);
			elf->sym_len = elf->e32_shdr[i].sh_size / sizeof(Elf32_Sym);
		}
		else if (elf->e32_shdr[i].sh_type == SHT_DYNSYM)
		{
			elf->e32_dynsym = (Elf32_Sym *) ((uint8_t *) elf->e32_ehdr + elf->e32_shdr[i].sh_offset);
			elf->dynsym_len = elf->e32_shdr[i].sh_size / sizeof(Elf32_Sym);
		}
		else if (elf->e32_shdr[i].sh_type == SHT_STRTAB && i != elf->e32_ehdr->e_shstrndx)
		{
			if (ft_strncmp(elf->sh_str_table + elf->e32_shdr[i].sh_name, ".strtab", -1))
				elf->str_table = (char *) ((uint8_t *) elf->e32_ehdr + elf->e32_shdr[i].sh_offset);
			else if (ft_strncmp(elf->sh_str_table + elf->e32_shdr[i].sh_name, ".dynstr", -1))
				elf->dynstr = (char *) ((uint8_t *) elf->e32_ehdr + elf->e32_shdr[i].sh_offset);
		}
	}
}

void	fill_elf64_tables(t_elf *elf)
{
	if (!elf) return;
	elf->sh_str_table = (char *) ((uint8_t *) elf->e64_ehdr + elf->e64_shdr[elf->e64_ehdr->e_shstrndx].sh_offset);
	for (uint16_t i = 0; i < elf->e64_ehdr->e_shnum; i++)
	{
		if (elf->e64_shdr[i].sh_type == SHT_SYMTAB)
		{
			elf->e64_sym = (Elf64_Sym *) ((uint8_t *) elf->e64_ehdr + elf->e64_shdr[i].sh_offset);
			elf->sym_len = elf->e64_shdr[i].sh_size / sizeof(Elf64_Sym);
		}
		else if (elf->e64_shdr[i].sh_type == SHT_DYNSYM)
		{
			elf->e64_dynsym = (Elf64_Sym *) ((uint8_t *) elf->e64_ehdr + elf->e64_shdr[i].sh_offset);
			elf->dynsym_len = elf->e64_shdr[i].sh_size / sizeof(Elf64_Sym);
		}
		else if (elf->e64_shdr[i].sh_type == SHT_STRTAB && i != elf->e64_ehdr->e_shstrndx)
		{
			if (!ft_strncmp(elf->sh_str_table + elf->e64_shdr[i].sh_name, ".strtab", -1))
				elf->str_table = (char *) ((uint8_t *) elf->e64_ehdr + elf->e64_shdr[i].sh_offset);
			else if (!ft_strncmp(elf->sh_str_table + elf->e64_shdr[i].sh_name, ".dynstr", -1))
				elf->dynstr = (char *) ((uint8_t *) elf->e64_ehdr + elf->e64_shdr[i].sh_offset);
		}
	}
}

t_elf	init_elf(uint8_t *addr)
{
	t_elf	elf;

	if (!addr)
		return (DEF_ELF);
	elf.e_class = addr[EI_CLASS];
	if (elf.e_class != ELFCLASS32 && elf.e_class != ELFCLASS64)
		return (DEF_ELF);
	if (elf.e_class == ELFCLASS32)
	{
		elf.e32_ehdr = (Elf32_Ehdr *) addr;
		elf.e32_phdr = (Elf32_Phdr *) (addr + elf.e32_ehdr->e_phoff);
		elf.e32_shdr = (Elf32_Shdr *) (addr + elf.e32_ehdr->e_shoff);
		fill_elf32_tables(&elf);
	}
	else
	{
		elf.e64_ehdr = (Elf64_Ehdr *) addr;
		elf.e64_phdr = (Elf64_Phdr *) (addr + elf.e64_ehdr->e_phoff);
		elf.e64_shdr = (Elf64_Shdr *) (addr + elf.e64_ehdr->e_shoff);
		fill_elf64_tables(&elf);
	}
	return (elf);
}