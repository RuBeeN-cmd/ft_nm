#include "ft_nm.h"




/**
 * @brief		Get the name of a symbol
 * @param[in]	sym A pointer to the symbol
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The index of the name of the symbol in the string table
 */
uint32_t	get_st_name(void *sym, uint8_t class, uint8_t endian)
{
	if (class == ELFDATA2LSB)
		return (read_uint32(((Elf32_Sym *) sym)->st_name, endian));
	return (read_uint32(((Elf64_Sym *) sym)->st_name, endian));
}

/**
 * @brief		Get the info of a symbol
 * @param[in]	sym A pointer to the symbol
 * @param[in]	class The class of the elf file
 * @return		The info of the symbol
 */
uint8_t	get_st_info(void *sym, uint8_t class)
{
	if (class == ELFCLASS32)
		return (((Elf32_Sym *) sym)->st_info);
	return (((Elf64_Sym *) sym)->st_info);
}

/**
 * @brief		Get the other of a symbol
 * @param[in]	sym A pointer to the symbol
 * @param[in]	class The class of the elf file
 * @return		The other of the symbol
 */
uint8_t	get_st_other(void *sym, uint8_t class)
{
	if (class == ELFCLASS32)
		return (((Elf32_Sym *) sym)->st_other);
	return (((Elf64_Sym *) sym)->st_other);
}

/**
 * @brief		Get the shndx of a symbol
 * @param[in]	sym A pointer to the symbol
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The shndx of the symbol
 */
uint16_t	get_st_shndx(void *sym, uint8_t class, uint8_t endian)
{
	if (class == ELFCLASS32)
		return (read_uint16(((Elf32_Sym *) sym)->st_shndx, endian));
	return (read_uint16(((Elf64_Sym *) sym)->st_shndx, endian));
}

/**
 * @brief		Get the value of a symbol
 * @param[in]	sym A pointer to the symbol
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The value of the symbol
 */
uint64_t	get_st_value(void *sym, uint8_t class, uint8_t endian)
{
	if (class == ELFCLASS32)
		return (read_uint32(((Elf32_Sym *) sym)->st_value, endian));
	return (read_uint64(((Elf64_Sym *) sym)->st_value, endian));
}

/**
 * @brief		Get the size of a symbol
 * @param[in]	sym A pointer to the symbol
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The size of the symbol
 */
uint64_t	get_st_size(void *sym, uint8_t class, uint8_t endian)
{
	if (class == ELFCLASS32)
		return (read_uint32(((Elf32_Sym *) sym)->st_size, endian));
	return (read_uint64(((Elf64_Sym *) sym)->st_size, endian));
}