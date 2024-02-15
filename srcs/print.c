#include "ft_nm.h"

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
				uint32_t	sh_type = SH_TYPE(SH_INDEX(shdr, shndx, class), class);
				uint64_t	sh_flags = SH_FLAGS(SH_INDEX(shdr, shndx, class), class);
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