#include "ft_nm.h"

void	print_32dynsymbol_table(Elf32_Sym *sym, uint32_t sym_len, char *str_table)
{
	if (!sym)
		return ;
	for (uint32_t i = 0; i < sym_len; i++)
	{
		if ((ELF32_ST_BIND(sym[i].st_info) == STB_GLOBAL
			&& (ELF32_ST_TYPE(sym[i].st_info) == STT_OBJECT
				|| ELF32_ST_TYPE(sym[i].st_info) == STT_FUNC
				|| ELF32_ST_TYPE(sym[i].st_info) == STT_COMMON))
			|| (ELF32_ST_BIND(sym[i].st_info) == STB_WEAK
			&& (ELF32_ST_TYPE(sym[i].st_info) == STT_OBJECT
				|| ELF32_ST_TYPE(sym[i].st_info) == STT_FUNC)))
		{
			if (ELF32_ST_TYPE(sym[i].st_info) == STT_OBJECT
				|| ELF32_ST_TYPE(sym[i].st_info) == STT_FUNC
				|| ELF32_ST_TYPE(sym[i].st_info) == STT_COMMON)
			{
				if (sym[i].st_value)
					print_number_column(sym[i].st_value, '0', 16, "0123456789abcdef");
				else
					print_column("", ' ', 16);
				ft_printf("%lu  ", sym[i].st_size);
				ft_printf("%d  ", sym[i].st_info);
				ft_printf("%d  ", sym[i].st_other);
				ft_printf("%d  ", sym[i].st_shndx);
				ft_printf("%s\n", str_table + sym[i].st_name);
			}
		}
	}
}

void	print_32symbol_table(Elf32_Sym *sym, uint64_t sym_len, char *str_table)
{
	for (uint64_t i = 0; i < sym_len; i++)
	{
		if ((ELF32_ST_BIND(sym[i].st_info) == STB_GLOBAL
			&& (ELF32_ST_TYPE(sym[i].st_info) == STT_OBJECT
				|| ELF32_ST_TYPE(sym[i].st_info) == STT_FUNC
				|| ELF32_ST_TYPE(sym[i].st_info) == STT_COMMON))
			|| (ELF32_ST_BIND(sym[i].st_info) == STB_WEAK
			&& (ELF32_ST_TYPE(sym[i].st_info) == STT_OBJECT
				|| ELF32_ST_TYPE(sym[i].st_info) == STT_FUNC)))
		{
			if (ELF32_ST_TYPE(sym[i].st_info) == STT_OBJECT
				|| ELF32_ST_TYPE(sym[i].st_info) == STT_FUNC
				|| ELF32_ST_TYPE(sym[i].st_info) == STT_COMMON)
			{
				if (sym[i].st_value)
					print_number_column(sym[i].st_value, '0', 16, "0123456789abcdef");
				else
					print_column("", ' ', 16);
				ft_printf("%lu  ", sym[i].st_size);
				ft_printf("%d  ", sym[i].st_info);
				ft_printf("%d  ", sym[i].st_other);
				ft_printf("%d  ", sym[i].st_shndx);
				ft_printf("%s\n", str_table + sym[i].st_name);
			}
		}
	}
}

void	print_64dynsymbol_table(Elf64_Sym *sym, uint64_t sym_len, char *str_table)
{
	(void) str_table;
	if (!sym)
		return ;
	for (uint64_t i = 0; i < sym_len; i++)
	{
		if ((ELF64_ST_BIND(sym[i].st_info) == STB_GLOBAL
			&& (ELF64_ST_TYPE(sym[i].st_info) == STT_OBJECT
				|| ELF64_ST_TYPE(sym[i].st_info) == STT_FUNC
				|| ELF64_ST_TYPE(sym[i].st_info) == STT_COMMON))
			|| (ELF64_ST_BIND(sym[i].st_info) == STB_WEAK
			&& (ELF64_ST_TYPE(sym[i].st_info) == STT_OBJECT
				|| ELF64_ST_TYPE(sym[i].st_info) == STT_FUNC)))
		{
			if (ELF64_ST_TYPE(sym[i].st_info) == STT_OBJECT
				|| ELF64_ST_TYPE(sym[i].st_info) == STT_FUNC
				|| ELF64_ST_TYPE(sym[i].st_info) == STT_COMMON)
			{
				if (sym[i].st_value)
					print_number_column(sym[i].st_value, '0', 16, "0123456789abcdef");
				else
					print_column("", ' ', 16);
				ft_printf("%lu  ", sym[i].st_size);
				ft_printf("%d  ", sym[i].st_info);
				ft_printf("%d  ", sym[i].st_other);
				ft_printf("%d  ", sym[i].st_shndx);
				ft_printf("%s\n", str_table + sym[i].st_name);
			}
		}
	}
}

void	print_64symbol_table(Elf64_Sym *sym, uint64_t sym_len, char *str_table)
{
	if (!sym)
		return ;
	for (uint64_t i = 0; i < sym_len; i++)
	{
		if ((ELF64_ST_BIND(sym[i].st_info) == STB_GLOBAL
			&& (ELF64_ST_TYPE(sym[i].st_info) == STT_OBJECT
				|| ELF64_ST_TYPE(sym[i].st_info) == STT_FUNC
				|| ELF64_ST_TYPE(sym[i].st_info) == STT_COMMON))
			|| (ELF64_ST_BIND(sym[i].st_info) == STB_WEAK
			&& (ELF64_ST_TYPE(sym[i].st_info) == STT_OBJECT
				|| ELF64_ST_TYPE(sym[i].st_info) == STT_FUNC)))
		{
			if (ELF64_ST_TYPE(sym[i].st_info) == STT_OBJECT
				|| ELF64_ST_TYPE(sym[i].st_info) == STT_FUNC
				|| ELF64_ST_TYPE(sym[i].st_info) == STT_COMMON)
			{
				if (sym[i].st_value)
					print_number_column(sym[i].st_value, '0', 16, "0123456789abcdef");
				else
					print_column("", ' ', 16);
				ft_printf("%lu  ", sym[i].st_size);
				ft_printf("%d  ", sym[i].st_info);
				ft_printf("%d  ", sym[i].st_other);
				ft_printf("%d  ", sym[i].st_shndx);
				ft_printf("%s\n", str_table + sym[i].st_name);
			}
		}
	}
}