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
			ret = ft_strcmp_escape(sym->name, tmp->name, "", 0);
			if (!ret)
			{
				sym_value = SYM_VALUE(sym->addr, class, endian);
				tmp_value = SYM_VALUE(tmp->addr, class, endian);
			}
			if ((reverse && (ret < 0 || (!ret && sym_value < tmp_value)))
				|| (!reverse && (ret > 0 || (!ret && sym_value > tmp_value))))
				swap_sym_list(sym, tmp);
			tmp = tmp->next;
		}
		sym = sym->next;
	}
}

/**
 * @brief		Check if a symbol is printable
 * @param[in]	addr The address of the symbol
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @param[in]	flags The flags to use
 * @return		1 if the symbol is printable, 0 otherwise
 */
int	is_printable(void *addr, int class, int endian, int flags)
{
	if (!(flags & DEBUG_SYMS)
		&& (SYM_INFO(addr, class) == STT_FILE || SYM_INFO(addr, class) == STT_SECTION))
		return (0);
	if (flags & EXTERN_ONLY && SYM_BIND(addr, class) == STB_LOCAL)
		return (0);
	if (flags & UNDEFINED_ONLY && SYM_SHNDX(addr, class, endian) != SHN_UNDEF)
		return (0);
	if (!ft_memcmp(addr, &DEF_SYM, SYM_SSIZE(class)))
		return (0);
	return (1);
}

/**
 * @brief		Initialize a symbol list
 * @param[in]	section The section to use
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @param[in]	flags The flags to use
 * @param[in]	shdr The section headers of the elf file
 * @param[in]	shstrtab The section header string table of the elf file
 * @return		The initialized symbol list
 */
t_sym_list	*init_sym_list(t_sym_section section, int class, int endian, int flags, void *shdr, char *shstrtab)
{
	t_sym_list	*sym_list;

	if (!section.len)
		return (NULL);
	if  (!is_printable(section.symtab, class, endian,  flags))
		return (init_sym_list((t_sym_section) {NEXT_SYM(section.symtab, class), section.len - 1, section.strtab}, class, endian, flags, shdr, shstrtab));
	sym_list = malloc(sizeof(t_sym_list));
	if (!sym_list)
		return (NULL);
	sym_list->addr = section.symtab;
	if (SYM_INFO(sym_list->addr , class) == STT_SECTION)
		sym_list->name = shstrtab + SH_NAME(SH_INDEX(shdr, SYM_SHNDX(sym_list->addr, class, endian), class), class, endian);
	else
		sym_list->name = section.strtab + SYM_NAME(section.symtab, class, endian);
	sym_list->next = init_sym_list((t_sym_section) {NEXT_SYM(section.symtab, class), section.len - 1, section.strtab}, class, endian, flags, shdr, shstrtab);
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