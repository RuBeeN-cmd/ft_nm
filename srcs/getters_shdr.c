#include "ft_nm.h"

/**
 * @brief		Get the name of a section
 * @param[in]	shdr A pointer to the section header
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The index of the name of the section in the sh string table
 */
uint32_t	get_sh_name(void *shdr, uint8_t class, uint8_t endian)
{
	if (class == ELFDATA2LSB)
		return (read_uint32(((Elf32_Shdr *) shdr)->sh_name, endian));
	return (read_uint32(((Elf64_Shdr *) shdr)->sh_name, endian));
}

/**
 * @brief		Get the type of a section
 * @param[in]	shdr A pointer to the section header
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The type of the section
 */
uint32_t	get_sh_type(void *shdr, uint8_t class, uint8_t endian)
{
	if (class == ELFDATA2LSB)
		return (read_uint32(((Elf32_Shdr *) shdr)->sh_type, endian));
	return (read_uint32(((Elf64_Shdr *) shdr)->sh_type, endian));
}

/**
 * @brief		Get the flags of a section
 * @param[in]	shdr A pointer to the section header
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The flags of the section
 */
uint64_t	get_sh_flags(void *shdr, uint8_t class, uint8_t endian)
{
	if (class == ELFDATA2LSB)
		return (read_uint32(((Elf32_Shdr *) shdr)->sh_flags, endian));
	return (read_uint64(((Elf64_Shdr *) shdr)->sh_flags, endian));
}

/**
 * @brief		Get the address of a section
 * @param[in]	shdr A pointer to the section header
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The address of the section
 */
uint64_t	get_sh_addr(void *shdr, uint8_t class, uint8_t endian)
{
	if (class == ELFDATA2LSB)
		return (read_uint32(((Elf32_Shdr *) shdr)->sh_addr, endian));
	return (read_uint64(((Elf64_Shdr *) shdr)->sh_addr, endian));
}

/**
 * @brief		Get the offset of a section
 * @param[in]	shdr A pointer to the section header
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The offset of the section
 */
uint64_t	get_sh_offset(void *shdr, uint8_t class, uint8_t endian)
{
	if (class == ELFDATA2LSB)
		return (read_uint32(((Elf32_Shdr *) shdr)->sh_offset, endian));
	return (read_uint64(((Elf64_Shdr *) shdr)->sh_offset, endian));
}

/**
 * @brief		Get the size of a section
 * @param[in]	shdr A pointer to the section header
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The size of the section
 */
uint64_t	get_sh_size(void *shdr, uint8_t class, uint8_t endian)
{
	if (class == ELFDATA2LSB)
		return (read_uint32(((Elf32_Shdr *) shdr)->sh_size, endian));
	return (read_uint64(((Elf64_Shdr *) shdr)->sh_size, endian));
}

/**
 * @brief		Get the link of a section
 * @param[in]	shdr A pointer to the section header
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The link of the section
 */
uint32_t	get_sh_link(void *shdr, uint8_t class, uint8_t endian)
{
	if (class == ELFDATA2LSB)
		return (read_uint32(((Elf32_Shdr *) shdr)->sh_link, endian));
	return (read_uint32(((Elf64_Shdr *) shdr)->sh_link, endian));
}

/**
 * @brief		Get the info of a section
 * @param[in]	shdr A pointer to the section header
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The info of the section
 */
uint32_t	get_sh_info(void *shdr, uint8_t class, uint8_t endian)
{
	if (class == ELFDATA2LSB)
		return (read_uint32(((Elf32_Shdr *) shdr)->sh_info, endian));
	return (read_uint32(((Elf64_Shdr *) shdr)->sh_info, endian));
}

/**
 * @brief		Get the addralign of a section
 * @param[in]	shdr A pointer to the section header
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The addralign of the section
 */
uint64_t	get_sh_addralign(void *shdr, uint8_t class, uint8_t endian)
{
	if (class == ELFDATA2LSB)
		return (read_uint32(((Elf32_Shdr *) shdr)->sh_addralign, endian));
	return (read_uint64(((Elf64_Shdr *) shdr)->sh_addralign, endian));
}

/**
 * @brief		Get the entsize of a section
 * @param[in]	shdr A pointer to the section header
 * @param[in]	class The class of the elf file
 * @param[in]	endian The endian of the elf file
 * @return		The entsize of the section
 */
uint64_t	get_sh_entsize(void *shdr, uint8_t class, uint8_t endian)
{
	if (class == ELFDATA2LSB)
		return (read_uint32(((Elf32_Shdr *) shdr)->sh_entsize, endian));
	return (read_uint64(((Elf64_Shdr *) shdr)->sh_entsize, endian));
}