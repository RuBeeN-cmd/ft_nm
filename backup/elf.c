#include "ft_nm.h"

void	init_sym32list(t_symlist **list, Elf32_Sym *sym, char *strtab, uint64_t len)
{
	if (!list || len == 0)
		return ;
	while (*list)
		list = &(*list)->next;
	*list = malloc(sizeof(t_symlist));
	(*list)->name = strtab + sym->st_name;
	(*list)->sym32 = sym;
	init_sym32list(&(*list)->next, (Elf32_Sym *) (((uint8_t *) sym) + sizeof(*sym)), strtab, len - 1);
}

void	init_sym64list(t_symlist **list, Elf64_Sym *sym, char *strtab, uint64_t len)
{
	if (!list)
		return ;
	if (len == 0)
	{
		*list = NULL;
		return ;
	}
	while (*list)
		list = &((*list)->next);
	*list = malloc(sizeof(t_symlist));
	(*list)->name = strtab + sym->st_name;
	(*list)->sym64 = sym;
	init_sym64list(&((*list)->next), (Elf64_Sym *) (((uint8_t *) sym) + sizeof(*sym)), strtab, len - 1);
}

void	print_letter(Elf64_Sym *sym)
{
	int		upper = 0;
	char	letter = '?';
	if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
	{
		if (sym->st_value)
			upper = 32;
		letter = 'W';
	}
	else
	{
		if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
			upper = 32;
		if (sym->st_shndx == SHN_ABS)
			letter = 'A';
		else if (sym->st_shndx == SHN_UNDEF)
			letter = 'U';
		else if (ELF64_ST_TYPE(sym->st_info) == STT_FUNC)
			letter = 'T';
		else if (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
			letter = 'D';
		else if (ELF64_ST_TYPE(sym->st_info) == STT_COMMON)
			letter = 'C';
		/*
		- "A" Absolute value
		"B/b" BSS data section
		- "C/c" Common symbol
		- "D/d" Data section
		"G/g" Data section small objects
		"i" Indirect function
		"I" Indirect ref to symbol
		"N" Debugging symbol
		"n" Read only data section
		"p" Stack symbol
		"R/r" Read only data section
		"S/s" Small object
		- "T/t" Text section
		- "U" Undefined symbol
		"u" Unique global symbol
		"V" Weak object (value specified)
		"v" Weak object
		"W" Weak symbol
		"w" Weak symbol (value specified)
		"-" stabs symbol
		"?" Unknown
		*/
	}
	ft_putchar_fd(letter + (upper << 5), 1);
}

void	show_symbol(t_symlist list)
{
	// if (!list.name || !list.name[0])
	// 	return ;
	// if (!ft_strncmp(list.name + ft_strlen(list.name) - 2, ".c", 2)
	// || !ft_strncmp(list.name + ft_strlen(list.name) - 2, ".o", 2))
	// 	return ;
	if (list.sym64->st_value)
		print_number_column(list.sym64->st_value, '0', 16, "0123456789abcdef");
	else
		print_column("", ' ', 16);
	ft_putchar_fd(' ', 1);
	print_letter(list.sym64);
	ft_printf(" %s\n", list.name);
}

int     contain_char(char c, char *set)
{
        if (!set)
                return (0);
        for (int i = 0; set[i]; i++)
                if (c == set[i])
                        return (1);
        return (0);
}

int     is_less_by_name(char *n1, char *n2)
{
        if (!n1 || !n2)
                return (1);
        int i = 0;
        int j = 0;
        while (contain_char(n1[i], " @%-_+.,:{}#!$^&*()=<>?;[]~\"\'"))
                i++;
        while (contain_char(n2[j], " @%-_+.,:{}#!$^&*()=<>?;[]~\"\'"))
                j++;
        while (n1[i] && ft_tolower(n1[i]) == ft_tolower(n2[j]))
        {
                i++;
                j++;
                while (contain_char(n1[i], " @%-_+.,:{}#!$^&*()=<>?;[]~\"\'"))
                        i++;
                while (contain_char(n2[j], " @%-_+.,:{}#!$^&*()=<>?;[]~\"\'"))
                        j++;
        }
        if (n1[i] || n2[j])
                return (ft_tolower(n1[i]) < ft_tolower(n2[j]));
        i = 0;
        j = 0;
        while (contain_char(n1[i], " @%-_+.,:{}#!$^&*()=<>?;[]~\"\'"))
                i++;
        while (contain_char(n2[j], " @%-_+.,:{}#!$^&*()=<>?;[]~\"\'"))
                j++;
        while (n1[i] && n1[i] == n2[j])
        {
                i++;
                j++;
                while (contain_char(n1[i], " @%-_+.,:{}#!$^&*()=<>?;[]~\"\'"))
                        i++;
                while (contain_char(n2[j], " @%-_+.,:{}#!$^&*()=<>?;[]~\"\'"))
                        j++;
        }
        if (n1[i] || n2[j])
                return (n1[i] > n2[j]);
        i = 0;
        while (n1[i] && n1[i] == n2[i])
                i++;
        return (ft_tolower(n1[i]) < ft_tolower(n2[i]));
}

t_symlist	*get_min(t_symlist **list)
{
	if (!list || !*list)
		return (NULL);
	if (!(*list)->next)
	{
		t_symlist	*ret = *list;
		*list = NULL;
		return (ret);
	}
	t_symlist	*min = *list;
	t_symlist	*prev = *list;
	t_symlist	*tmp = *list;
	while (tmp->next)
	{
		if (!is_less_by_name(min->name, tmp->next->name))
		{
			min = tmp->next;
			prev = tmp;
		}
		tmp = tmp->next;
	}
	if (min == *list)
		*list = min->next;
	else
		prev->next = min->next;
	min->next = NULL;
	return (min);
}

int	print_elf(t_elf elf)
{
	t_symlist	*list = NULL;
	if (elf.e_class != ELFCLASS32 && elf.e_class != ELFCLASS64)
		return (1);
	if (elf.e_class == ELFCLASS32)
	{
		init_sym32list(&list, elf.e32_sym, elf.str_table, elf.sym_len);
		init_sym32list(&list, elf.e32_dynsym, elf.dynstr, elf.dynsym_len);
	}
	else
	{
		init_sym64list(&list, elf.e64_sym, elf.str_table, elf.sym_len);
		init_sym64list(&list, elf.e64_dynsym, elf.dynstr, elf.dynsym_len);
		while (list)
		{
			t_symlist	*tmp = get_min(&list);
			if (tmp)
			{
				show_symbol(*tmp);
				free(tmp);
			}
		}
	}
	return (0);
}

void	fill_elf32_tables(t_elf *elf)
{
	if (!elf)
		return;
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
	if (!elf)
		return;
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