#include "ft_nm.h"

void	swap_sym_list(t_sym_list *a, t_sym_list *b)
{
	char		*tmp_name;
	void		*tmp_addr;

	tmp_name = a->name;
	tmp_addr = a->addr;
	a->name = b->name;
	a->addr = b->addr;
	b->name = tmp_name;
	b->addr = tmp_addr;
}

int     ft_strcmp_escape(char *n1, char *n2, char *set, int lower)
{
        if (!n1 || !n2)
                return (1);
        int i = 0;
        int j = 0;
		while (n1[i] && ft_strchr(set, n1[i]))
			i++;
		while (n2[j] && ft_strchr(set, n2[j]))
			j++;
        while ((n1[i] && ft_tolower(n1[i]) == ft_tolower(n2[j]) && lower)
			|| (n1[i] && n1[i] == n2[j] && !lower))
        {
                i++;
                j++;
                while (n1[i] && ft_strchr(set, n1[i]))
                        i++;
                while (n2[j] && ft_strchr(set, n2[j]))
                        j++;
        }
		if (!n1[i] && !n2[j])
			return (ft_strcmp_escape(n1, n2, "", lower));
		if (lower)
			return (ft_tolower(n1[i]) - ft_tolower(n2[j]));
		return (n1[i] - n2[j]);
}


void	sort_sym_list(t_sym_list *sym, int class)
{
	t_sym_list	*tmp;
	int			ret = 0;

	while (sym)
	{
		tmp = sym->next;
		while (tmp)
		{
			ret = ft_strcmp_escape(sym->name, tmp->name, "_", 1);
			if (ret > 0)
				swap_sym_list(sym, tmp);
			else if (!ret && SYM_VALUE(sym->addr, class) > SYM_VALUE(tmp->addr, class))
				swap_sym_list(sym, tmp);
			tmp = tmp->next;
		}
		sym = sym->next;
	}
}

int	is_printable(void *addr, int class)
{
	if (SYM_INFO(addr, class) == STT_FILE)
		return (0);
	if (SYM_NAME(addr, class) == 0)
		return (0);
	return (1);
}

t_sym_list	*init_sym_list(t_sym_section section, int class)
{
	t_sym_list	*sym_list;

	if (!section.len)
		return (NULL);
	if  (!is_printable(section.symtab, class))
		return (init_sym_list((t_sym_section) {NEXT_SYM(section.symtab, class), section.len - 1, section.strtab}, class));
	sym_list = malloc(sizeof(t_sym_list));
	if (!sym_list)
		return (NULL);
	sym_list->addr = section.symtab;
	sym_list->name = section.strtab + SYM_NAME(section.symtab, class);
	sym_list->next = init_sym_list((t_sym_section) {NEXT_SYM(section.symtab, class), section.len - 1, section.strtab}, class);
	return (sym_list);
}

void	free_sym_list(t_sym_list *sym_list)
{
	if (!sym_list)
		return ;
	free_sym_list(sym_list->next);
	free(sym_list);
}

void	print_value(uint64_t value, uint16_t shndx, uint64_t sym_value_size)
{
	if (!shndx)
		for (uint64_t i = 0; i < sym_value_size << 1; i++)
			ft_printf(" ");	
	else
	{
		for (int i = 0; i < (int) (sym_value_size << 1); i++)
		{
			if (!(value & (0xful << (((sym_value_size << 1) - i - 1) * 4))))
				ft_printf("0");
			else
				break ;
		}
		if (value)
			ft_printf("%x", value);
	}	
	ft_printf(" ");	
}

void	print_letter(void *sym, void *shdr, uint16_t shnum, int class)
{
	uint8_t		type = SYM_TYPE(sym, class);
	uint8_t		bind = SYM_BIND(sym, class);
	uint16_t	shndx = SYM_SHNDX(sym, class);
	uint32_t	sh_type = SH_TYPE(SH_INDEX(shdr, SYM_SHNDX(sym, class), class), class);
	uint64_t	sh_flags = SH_FLAGS(SH_INDEX(shdr, SYM_SHNDX(sym, class), class), class);

	unsigned char c = '?';

	if (bind == STB_WEAK)
	{
		if (type == STT_OBJECT)
			c = 'V';
		else
			c = 'W';
		if (shndx == SHN_UNDEF)
			c += 32;
	}
	else if (bind == STB_GNU_UNIQUE)
		c = 'u';
	else
	{
		if (shndx == SHN_UNDEF)
			c = 'U';
		else
		{
			if (shndx == SHN_ABS)
				c = 'a';
			else if (shndx == SHN_COMMON)
				c = 'c';
			else if (shndx < shnum)
			{
				if (sh_type == SHT_NOBITS
					&& sh_flags == (SHF_ALLOC | SHF_WRITE))
					c = 'b';
				else if ((sh_type == SHT_PROGBITS || sh_type == SHT_REL || sh_type == SHT_HASH
					|| sh_type == SHT_GNU_versym || sh_type == SHT_GNU_verdef || sh_type == SHT_STRTAB
					|| sh_type == SHT_DYNSYM || sh_type == SHT_NOTE)
					&& sh_flags == SHF_ALLOC)
					c = 'r';
				else if ((sh_type == SHT_PROGBITS
					&& sh_flags == (SHF_ALLOC | SHF_WRITE))
					|| sh_type == SHT_INIT_ARRAY || sh_type == SHT_FINI_ARRAY
					|| sh_type == SHT_DYNAMIC)
					c = 'd';
				else if (sh_type == SHT_PROGBITS
					&& sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
					c = 't';
			}
			if (bind == STB_GLOBAL && c != '?')
				c -= 32;
		}
	}
	ft_printf("%c ", c);
}

void	print_sym_list(t_sym_list *sym, void *shdr, uint16_t shnum, int class)
{
	while (sym)
	{
		print_value(SYM_VALUE(sym->addr, class), SYM_SHNDX(sym->addr, class), SYM_VALUE_SIZE(class));
		print_letter(sym->addr, shdr, shnum, class);
		ft_printf("%s\n", sym->name);
		sym = sym->next;
	}
}