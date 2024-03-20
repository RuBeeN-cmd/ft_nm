#include "ft_nm.h"

/**
 * @brief		Print the value of a symbol
 * @param[in]	value The value to print
 * @param[in]	shndx The section index of the symbol
 * @param[in]	sym_value_size The size of the symbol value
 */
void	print_value(uint64_t value, uint16_t shndx, uint64_t sym_value_size)
{
	if (shndx == SHN_UNDEF)
		for (uint64_t i = 0; i < sym_value_size << 1; i++)
			ft_printf(" ");	
	else
	{
		for (int i = 0; i < (int) (sym_value_size << 1); i++)
		{
			if (!(value & (0xful << (((sym_value_size << 1) - i - 1) << 2))))
				ft_printf("0");
			else
				break ;
		}
		if (value)
			ft_printf("%x", value);
	}	
	ft_printf(" ");
}

/**
 * @brief		Print the letter of a symbol
 * @param[in]	sym The symbol to print
 * @param[in]	shdr The section header to use
 * @param[in]	shnum The number of section headers
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 */
void	print_letter(void *sym, void *shdr, uint16_t shnum, int class, int endian)
{
	uint16_t	st_info = get_st_info(sym, class);
	uint8_t		st_type = ELF32_ST_TYPE(st_info);
	uint8_t		st_bind = ELF32_ST_BIND(st_info);
	uint16_t	shndx = get_st_shndx(sym, class, endian);

	unsigned char c = '?';

	if (st_bind == STB_WEAK)
	{
		if (st_type == STT_OBJECT)
			c = 'V';
		else
			c = 'W';
		if (shndx == SHN_UNDEF)
			c += 32;
	}
	else if (st_bind == STB_GNU_UNIQUE)
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
				uint32_t	sh_type = get_sh_type(shdr + shndx * SHDR_SIZE(class), class, endian);
				uint64_t	sh_flags = get_sh_flags(shdr + shndx * SHDR_SIZE(class), class, endian);
				if (sh_type == SHT_GROUP)
					c = 'n';
				else if (sh_type == SHT_NOBITS)
					c = 'b';
				else if (sh_flags == (SHF_ALLOC | SHF_WRITE))
					c = 'd';
				else if (sh_type == SHT_PROGBITS
					&& sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
					c = 't';
				else if ((sh_flags & SHF_ALLOC && !(sh_flags & SHF_WRITE)))
					c = 'r';
				else if (st_type == STT_SECTION)
					c = 'N';
			}
			if (st_bind == STB_GLOBAL && c != '?' && c != 'N')
				c -= 32;
		}
	}
	ft_printf("%c ", c);
}

/**
 * @brief		Print the symbols of a file
 * @param[in]	sym The symbol list to print
 * @param[in]	shdr The section header to use
 * @param[in]	shnum The number of section headers
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 */
void	print_sym_list(t_sym_list *sym, void *shdr, uint16_t shnum, int class, int endian)
{
	while (sym)
	{
		print_value(get_st_value(sym->addr, class, endian), get_st_shndx(sym->addr, class, endian), SIZE(class));
		print_letter(sym->addr, shdr, shnum, class, endian);
		ft_printf("%s\n", sym->name);
		sym = sym->next;
	}
}