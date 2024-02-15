#include "ft_nm.h"

void	print_error(char *str, char *file, int quotes)
{
	ft_putstr_fd("nm: ", 2);
	if (quotes)
		ft_putchar_fd('\'', 2);
	ft_putstr_fd(file, 2);
	if (quotes)
		ft_putchar_fd('\'', 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
}