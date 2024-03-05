#include "ft_nm.h"

/**
 * @brief		Get the name of a symbol
 * @param[in]	sym A pointer to the symbol
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The index of the name of the symbol in the string table
 */
uint8_t	*get_e_ident(void *ehdr)
{
	return (ehdr);
}

/**
 * @brief		Get the type of an elf file
 * @param[in]	ehdr A pointer to the elf header
 * @param[in]	endian The endian of the elf file
 * @return		The type of the elf file
 */
uint16_t	get_e_type(void *ehdr, uint8_t endian)
{
	if (endian == ELFDATA2LSB)
		return (read_uint16(((Elf32_Ehdr *) ehdr)->e_type, endian));
	return (read_uint16(((Elf64_Ehdr *) ehdr)->e_type, endian));
}

/**
 * @brief		Get the machine of an elf file
 * @param[in]	ehdr A pointer to the elf header
 * @param[in]	endian The endian of the elf file
 * @return		The machine of the elf file
 */
uint16_t	get_e_machine(void *ehdr, uint8_t endian)
{
	if (endian == ELFDATA2LSB)
		return (read_uint16(((Elf32_Ehdr *) ehdr)->e_machine, endian));
	return (read_uint16(((Elf64_Ehdr *) ehdr)->e_machine, endian));
}

/**
 * @brief		Get the version of an elf file
 * @param[in]	ehdr A pointer to the elf header
 * @param[in]	endian The endian of the elf file
 * @return		The version of the elf file
 */
uint32_t	get_e_version(void *ehdr, uint8_t endian)
{
	if (endian == ELFDATA2LSB)
		return (read_uint32(((Elf32_Ehdr *) ehdr)->e_version, endian));
	return (read_uint32(((Elf64_Ehdr *) ehdr)->e_version, endian));
}

/**
 * @brief		Get the entry point of an elf file
 * @param[in]	ehdr A pointer to the elf header
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The entry point of the elf file
 */
uint64_t	get_e_entry(void *ehdr, uint8_t class, uint8_t endian)
{
	if (class == ELFCLASS32)
		return (read_uint32(((Elf32_Ehdr *) ehdr)->e_entry, endian));
	return (read_uint64(((Elf64_Ehdr *) ehdr)->e_entry, endian));
}

/**
 * @brief		Get the program header offset of an elf file
 * @param[in]	ehdr A pointer to the elf header
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The program header offset of the elf file
 */
uint64_t	get_e_phoff(void *ehdr, uint8_t class, uint8_t endian)
{
	if (class == ELFCLASS32)
		return (read_uint32(((Elf32_Ehdr *) ehdr)->e_phoff, endian));
	return (read_uint64(((Elf64_Ehdr *) ehdr)->e_phoff, endian));
}

/**
 * @brief		Get the section header offset of an elf file
 * @param[in]	ehdr A pointer to the elf header
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The section header offset of the elf file
 */
uint64_t	get_e_shoff(void *ehdr, uint8_t class, uint8_t endian)
{
	if (class == ELFCLASS32)
		return (read_uint32(((Elf32_Ehdr *) ehdr)->e_shoff, endian));
	return (read_uint64(((Elf64_Ehdr *) ehdr)->e_shoff, endian));
}

/**
 * @brief		Get the flags of an elf file
 * @param[in]	ehdr A pointer to the elf header
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The flags of the elf file
 */
uint32_t	get_e_flags(void *ehdr, uint8_t class, uint8_t endian)
{
	if (class == ELFCLASS32)
		return (read_uint32(((Elf32_Ehdr *) ehdr)->e_flags, endian));
	return (read_uint32(((Elf64_Ehdr *) ehdr)->e_flags, endian));
}

/**
 * @brief		Get the size of the elf header
 * @param[in]	ehdr A pointer to the elf header
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The size of the elf header
 */
uint16_t	get_e_ehsize(void *ehdr, uint8_t class, uint8_t endian)
{
	if (class == ELFCLASS32)
		return (read_uint16(((Elf32_Ehdr *) ehdr)->e_ehsize, endian));
	return (read_uint16(((Elf64_Ehdr *) ehdr)->e_ehsize, endian));
}

/**
 * @brief		Get the size of a program header
 * @param[in]	ehdr A pointer to the elf header
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The size of a program header
 */
uint16_t	get_e_phentsize(void *ehdr, uint8_t class, uint8_t endian)
{
	if (class == ELFCLASS32)
		return (read_uint16(((Elf32_Ehdr *) ehdr)->e_phentsize, endian));
	return (read_uint16(((Elf64_Ehdr *) ehdr)->e_phentsize, endian));
}

/**
 * @brief		Get the number of program headers
 * @param[in]	ehdr A pointer to the elf header
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The number of program headers
 */
uint16_t	get_e_phnum(void *ehdr, uint8_t class, uint8_t endian)
{
	if (class == ELFCLASS32)
		return (read_uint16(((Elf32_Ehdr *) ehdr)->e_phnum, endian));
	return (read_uint16(((Elf64_Ehdr *) ehdr)->e_phnum, endian));
}

/**
 * @brief		Get the size of a section header
 * @param[in]	ehdr A pointer to the elf header
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The size of a section header
 */
uint16_t	get_e_shentsize(void *ehdr, uint8_t class, uint8_t endian)
{
	if (class == ELFCLASS32)
		return (read_uint16(((Elf32_Ehdr *) ehdr)->e_shentsize, endian));
	return (read_uint16(((Elf64_Ehdr *) ehdr)->e_shentsize, endian));
}

/**
 * @brief		Get the number of section headers
 * @param[in]	ehdr A pointer to the elf header
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The number of section headers
 */
uint16_t	get_e_shnum(void *ehdr, uint8_t class, uint8_t endian)
{
	if (class == ELFCLASS32)
		return (read_uint16(((Elf32_Ehdr *) ehdr)->e_shnum, endian));
	return (read_uint16(((Elf64_Ehdr *) ehdr)->e_shnum, endian));
}

/**
 * @brief		Get the index of the section header string table
 * @param[in]	ehdr A pointer to the elf header
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The index of the section header string table
 */
uint16_t	get_e_shstrndx(void *ehdr, uint8_t class, uint8_t endian)
{
	if (class == ELFCLASS32)
		return (read_uint16(((Elf32_Ehdr *) ehdr)->e_shstrndx, endian));
	return (read_uint16(((Elf64_Ehdr *) ehdr)->e_shstrndx, endian));
}