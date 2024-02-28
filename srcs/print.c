#include "ft_nm.h"

void	print_value(uint64_t value, uint16_t shndx, uint64_t sym_value_size)
{
	if (shndx == SHN_UNDEF)
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

void	print_letter(void *sym, void *shdr, uint16_t shnum, int class, int endian)
{
	uint8_t		type = SYM_TYPE(sym, class);
	uint8_t		bind = SYM_BIND(sym, class);
	uint16_t	shndx = SYM_SHNDX(sym, class, endian);

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
				uint32_t	sh_type = SH_TYPE(SH_INDEX(shdr, shndx, class), class, endian);
				uint64_t	sh_flags = SH_FLAGS(SH_INDEX(shdr, shndx, class), class, endian);
				if (sh_type == SHT_NOBITS)
					c = 'b';
				else if (sh_flags == (SHF_ALLOC | SHF_WRITE))
					c = 'd';
				else if (sh_type == SHT_PROGBITS
					&& sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
					c = 't';
				else if ((sh_type == SHT_PROGBITS || sh_type == SHT_REL || sh_type == SHT_HASH
					|| sh_type == SHT_GNU_versym || sh_type == SHT_GNU_verdef || sh_type == SHT_STRTAB
					|| sh_type == SHT_DYNSYM || sh_type == SHT_NOTE)
					&& sh_flags & SHF_ALLOC)
					c = 'r';
			}
			if (bind == STB_GLOBAL && c != '?')
				c -= 32;
		}
	}
	// if (c == '?')
	// {
	// 	uint32_t	sh_type = SH_TYPE(SH_INDEX(shdr, shndx, class), class, endian);
	// 	ft_printf("\n-- Type ");
	// 	if (sh_type == SHT_NULL)
	// 		ft_printf("SHT_NULL --\n");
	// 	else if (sh_type == SHT_PROGBITS)
	// 		ft_printf("SHT_PROGBITS --\n");
	// 	else if (sh_type == SHT_SYMTAB)
	// 		ft_printf("SHT_SYMTAB --\n");
	// 	else if (sh_type == SHT_STRTAB)
	// 		ft_printf("SHT_STRTAB --\n");
	// 	else if (sh_type == SHT_RELA)
	// 		ft_printf("SHT_RELA --\n");
	// 	else if (sh_type == SHT_HASH)
	// 		ft_printf("SHT_HASH --\n");
	// 	else if (sh_type == SHT_DYNAMIC)
	// 		ft_printf("SHT_DYNAMIC --\n");
	// 	else if (sh_type == SHT_NOTE)
	// 		ft_printf("SHT_NOTE --\n");
	// 	else if (sh_type == SHT_NOBITS)
	// 		ft_printf("SHT_NOBITS --\n");
	// 	else if (sh_type == SHT_REL)
	// 		ft_printf("SHT_REL --\n");
	// 	else if (sh_type == SHT_SHLIB)
	// 		ft_printf("SHT_SHLIB --\n");
	// 	else if (sh_type == SHT_DYNSYM)
	// 		ft_printf("SHT_DYNSYM --\n");
	// 	else if (sh_type == SHT_INIT_ARRAY)
	// 		ft_printf("SHT_INIT_ARRAY --\n");
	// 	else if (sh_type == SHT_FINI_ARRAY)
	// 		ft_printf("SHT_FINI_ARRAY --\n");
	// 	else if (sh_type == SHT_PREINIT_ARRAY)
	// 		ft_printf("SHT_PREINIT_ARRAY --\n");
	// 	else if (sh_type == SHT_GROUP)
	// 		ft_printf("SHT_GROUP --\n");
	// 	else if (sh_type == SHT_SYMTAB_SHNDX)
	// 		ft_printf("SHT_SYMTAB_SHNDX --\n");
	// 	else if (sh_type == SHT_NUM)
	// 		ft_printf("SHT_NUM --\n");
	// 	else if (sh_type == SHT_LOOS)
	// 		ft_printf("SHT_LOOS --\n");
	// 	else if (sh_type == SHT_GNU_ATTRIBUTES)
	// 		ft_printf("SHT_GNU_ATTRIBUTES --\n");
	// 	else if (sh_type == SHT_GNU_HASH)
	// 		ft_printf("SHT_GNU_HASH --\n");
	// 	else if (sh_type == SHT_GNU_LIBLIST)
	// 		ft_printf("SHT_GNU_LIBLIST --\n");
	// 	else if (sh_type == SHT_CHECKSUM)
	// 		ft_printf("SHT_CHECKSUM --\n");
	// 	else if (sh_type == SHT_LOSUNW)
	// 		ft_printf("SHT_LOSUNW --\n");
	// 	else if (sh_type == SHT_SUNW_move)
	// 		ft_printf("SHT_SUNW_move --\n");
	// 	else if (sh_type == SHT_SUNW_COMDAT)
	// 		ft_printf("SHT_SUNW_COMDAT --\n");
	// 	else if (sh_type == SHT_SUNW_syminfo)
	// 		ft_printf("SHT_SUNW_syminfo --\n");
	// 	else if (sh_type == SHT_GNU_verdef)
	// 		ft_printf("SHT_GNU_verdef --\n");
	// 	else if (sh_type == SHT_GNU_verneed)
	// 		ft_printf("SHT_GNU_verneed --\n");
	// 	else if (sh_type == SHT_GNU_versym)
	// 		ft_printf("SHT_GNU_versym --\n");
	// 	else if (sh_type == SHT_HISUNW)
	// 		ft_printf("SHT_HISUNW --\n");
	// 	else if (sh_type == SHT_HIOS)
	// 		ft_printf("SHT_HIOS --\n");
	// 	else if (sh_type == SHT_LOPROC)
	// 		ft_printf("SHT_LOPROC --\n");
	// 	else if (sh_type == SHT_HIPROC)
	// 		ft_printf("SHT_HIPROC --\n");
	// 	else if (sh_type == SHT_LOUSER)
	// 		ft_printf("SHT_LOUSER --\n");
	// 	else if (sh_type == SHT_HIUSER)
	// 		ft_printf("SHT_HIUSER --\n");
	// }
	ft_printf("%c ", c);
}

void	print_sym_list(t_sym_list *sym, void *shdr, uint16_t shnum, int class, int endian)
{
	while (sym)
	{
		print_value(SYM_VALUE(sym->addr, class, endian), SYM_SHNDX(sym->addr, class, endian), SYM_VALUE_SSIZE(class));
		print_letter(sym->addr, shdr, shnum, class, endian);
		ft_printf("%s\n", sym->name);
		sym = sym->next;
	}
}