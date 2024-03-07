#include "ft_nm.h"

/**
 * @brief		Get the long flag from a string
 * @param[in]	str The string to parse
 * @return		The flag parsed
 */
static uint8_t	get_long_flag(char str[])
{
	if (!str)
		return (-1);
	for (int i = 0; i < FLAGS_NB; i++)
		if (!ft_strncmp(str, LONG_FLAGS[i], -1))
			return (1 << i);
	return (-1);
}

/**
 * @brief			Get the flags from a char
 * @param[in]		c The char to parse
 * @return			The flag parsed
 */
static uint8_t	get_short_flag(const char c)
{
	const char	flags_letter[] = FLAGS;

	char	*flag_ptr = ft_strchr(flags_letter, c);
	if (!flag_ptr)
		return (-1);
	return (1 << (flag_ptr - flags_letter));
}

/**
 * @brief			Get the flags from a string
 * @param[in]		str The string to parse
 * @return			The flags parsed
 */
static uint8_t	get_short_flags(const char str[])
{
	int	ret;

	if (!str)
		return (-1);
	uint8_t		flags = 0;
	for (int i = 0; str[i]; i++)
	{
		ret = get_short_flag(str[i]);
		if (ret == -1)
			return (-1);
		flags |= ret;
	}
	return (flags);
}

/**
 * @brief			Parse the flags, and set them to NULL
 * @param[in]		argc The number of arguments
 * @param[in,out]	argv The arguments
 * @return			The flags parsed
 */
int	parse_flags(int argc, char *argv[])
{
	uint8_t	flags = 0;

	if (!argv)
		return (-1);
	for (int i = 0; i < argc; i++)
	{
		if (!argv[i])
			return (-1);
		if (argv[i][0] == '-')
		{
			int	ret = 0;
			if (argv[i][1] == '-')
				ret = get_long_flag(argv[i] + 2);
			else if (argv[i][1])
				ret = get_short_flags(argv[i] + 1);
			if (ret == -1)
				return (-1);
			flags |= ret;
			if (ret)
				argv[i] = NULL; // Set argv to NULL if it was parsed
		}
	}
	return (flags);
}