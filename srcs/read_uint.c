#include "ft_nm.h"

int	get_machine_endian()
{
	int	n = 1;
	if (*(char *)&n == 1)
		return (ELFDATA2LSB);
	else
		return (ELFDATA2MSB);
}

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

uint16_t	read_uint16(uint16_t value, int endian)
{
	if (endian != get_machine_endian())
		reverse_bytes((uint8_t *)&value, sizeof(uint16_t));
	return (value);
}

uint32_t	read_uint32(uint32_t value, int endian)
{
	if (endian != get_machine_endian())
		reverse_bytes((uint8_t *)&value, sizeof(uint32_t));
	return (value);
}

uint64_t	read_uint64(uint64_t value, int endian)
{
	if (endian != get_machine_endian())
		reverse_bytes((uint8_t *)&value, sizeof(uint64_t));
	return (value);
}