#include "ft_nm.h"

int	get_long_flag(char str[])
{
	if (!str)
		return (-1);
	char	*flags_str[6] = {
		"debug-syms", "extern-only", "undefined-only",
		"reverse-sort", "no-sort"
	};
	for (int i = 0; flags_str[i]; i++)
		if (!ft_strncmp(str, flags_str[i], -1))
			return (1 << i);
	return (-1);
}

int	get_short_flag(char c)
{
	char	flags_letter[] = "agurp";

	char	*flag_ptr = ft_strchr(flags_letter, c);
	if (!flag_ptr)
		return (-1);
	return (1 << (flag_ptr - flags_letter));
}

int	get_short_flags(char str[])
{
	if (!str)
		return (-1);
	int		flags = 0;
	for (int i = 0; str[i]; i++)
	{
		int	ret = get_short_flag(str[i]);
		if (ret == -1)
			return (-1);
		flags |= ret;
	}
	return (flags);
}

int	parse_flags(int argc, char *argv[])
{
	int	flags = 0;

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
				argv[i] = NULL;
		}
	}
	return (flags);
}