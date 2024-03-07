#include "ft_nm.h"

/**
 * @brief		Get the endian of the machine
 * @return		The endian of the machine
 */
int	get_machine_endian()
{
	int	n = 1;
	if (*(char *)&n == 1)
		return (ELFDATA2LSB);
	else
		return (ELFDATA2MSB);
}

/**
 * @brief		Reverse the bytes of an address
 * @param[in]	addr The address to reverse
 * @param[in]	size The size of the address
 */
void	reverse_bytes(uint8_t *addr, size_t size)
{
	uint8_t	tmp;

	for (size_t i = 0; i < size / 2; i++)
	{
		tmp = addr[i];
		addr[i] = addr[size - i - 1];
		addr[size - i - 1] = tmp;
	}
}

/**
 * @brief		Read a uint16_t from a file
 * @param[in]	value The value to read
 * @param[in]	endian The endian of the file
 * @return		The value read 
 */
uint16_t	read_uint16(uint16_t value, int endian)
{
	if (endian != get_machine_endian())
		reverse_bytes((uint8_t *)&value, sizeof(uint16_t));
	return (value);
}

/**
 * @brief		Read a uint32_t from a file
 * @param[in]	value The value to read
 * @param[in]	endian The endian of the file
 * @return		The value read 
 */
uint32_t	read_uint32(uint32_t value, int endian)
{
	if (endian != get_machine_endian())
		reverse_bytes((uint8_t *)&value, sizeof(uint32_t));
	return (value);
}

/**
 * @brief		Read a uint64_t from a file
 * @param[in]	value The value to read
 * @param[in]	endian The endian of the file
 * @return		The value read 
 */
uint64_t	read_uint64(uint64_t value, int endian)
{
	if (endian != get_machine_endian())
		reverse_bytes((uint8_t *)&value, sizeof(uint64_t));
	return (value);
}