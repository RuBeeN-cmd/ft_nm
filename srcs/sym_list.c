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
			ret = ft_strcmp_escape(sym->name, tmp->name, "_.", 1);
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