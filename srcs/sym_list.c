#include "ft_nm.h"

/**
 * @brief		Swap two symbol list elements
 * @param[in]	a The first element to swap
 * @param[in]	b The second element to swap
 */
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

/**
 * @brief		Compare two strings with an escape set
 * @param[in]	n1 The first string to compare
 * @param[in]	n2 The second string to compare
 * @param[in]	set The escape set
 * @param[in]	lower The lower flag
 * @return		The difference between the two strings
 */
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
		if (set && *set && !n1[i] && !n2[j])
			return (ft_strcmp_escape(n1, n2, "", lower));
		if (lower)
			return (ft_tolower(n1[i]) - ft_tolower(n2[j]));
		return (n1[i] - n2[j]);
}

/**
 * @brief		Sort a symbol list
 * @param[in]	sym The symbol list to sort
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @param[in]	reverse The reverse flag
 */
void	sort_sym_list(t_sym_list *sym, int class, int endian, int reverse)
{
	t_sym_list	*tmp;
	int			ret;
	uint64_t	sym_value;
	uint64_t	tmp_value;

	while (sym)
	{
		tmp = sym->next;
		while (tmp)
		{
			ret = ft_strcmp_escape(sym->name, tmp->name, "_.@", 1);
			if (!ret)
			{
				sym_value = get_st_value(sym->addr, class, endian);
				tmp_value = get_st_value(tmp->addr, class, endian);
			}
			if ((!ret && sym_value < tmp_value)
				|| (reverse && ret < 0)
				|| (!reverse && ret > 0))
				swap_sym_list(sym, tmp);
			tmp = tmp->next;
		}
		sym = sym->next;
	}
}

/**
 * @brief		Check if a symbol is printable
 * @param[in]	sym The symbol
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @param[in]	flags The flags to use
 * @return		1 if the symbol is printable, 0 otherwise
 */
int	is_printable(void *sym, int class, int endian, int flags)
{
	uint8_t	st_info = get_st_info(sym, class);
	uint8_t	bind = ELF32_ST_BIND(st_info);
	uint8_t	type = ELF32_ST_TYPE(st_info);
	if (!(flags & DEBUG_SYMS)
		&& (type == STT_FILE || type == STT_SECTION))
		return (0);
	if (flags & EXTERN_ONLY && bind == STB_LOCAL)
		return (0);
	if (flags & UNDEFINED_ONLY && get_st_shndx(sym, class, endian) != SHN_UNDEF)
		return (0);
	if (!ft_memcmp(sym, &DEF_SYM, SYM_SIZE(class)))
		return (0);
	return (1);
}

/**
 * @brief		Initialize a symbol list
 * @param[in]	elf The elf structure to use
 * @return		The initialized symbol list
 */
t_sym_list	*init_sym_list(t_elf elf)
{
	t_sym_list	*sym_list;

	if (!elf.symnum)
		return (NULL);
	if  (!is_printable(elf.symtab, elf.class, elf.endian, elf.flags))
	{
		elf.symtab += SYM_SIZE(elf.class);
		elf.symnum--;
		return (init_sym_list(elf));
	}
	sym_list = malloc(sizeof(t_sym_list));
	if (!sym_list)
		return (NULL);
	sym_list->addr = elf.symtab;
	if (ELF32_ST_TYPE(get_st_info(sym_list->addr, elf.class)) == STT_SECTION)
		sym_list->name = elf.shstrtab + get_sh_name(elf.shdr + get_st_shndx(sym_list->addr, elf.class, elf.endian) * SHDR_SIZE(elf.class), elf.class, elf.endian);
	else
		sym_list->name = elf.strtab + get_st_name(elf.symtab, elf.class, elf.endian);
	
	elf.symtab += SYM_SIZE(elf.class);
	elf.symnum--;
	sym_list->next = init_sym_list(elf);
	return (sym_list);
}

/**
 * @brief		Free a symbol list
 * @param[in]	sym_list The symbol list to free
 */
void	free_sym_list(t_sym_list *sym_list)
{
	if (!sym_list)
		return ;
	free_sym_list(sym_list->next);
	free(sym_list);
}