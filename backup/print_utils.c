#include "ft_nm.h"

int	get_nb_len_base(unsigned long n, char *b)
{
	if (n < ft_strlen(b))
		return (1);
	return (1 + get_nb_len_base(n / ft_strlen(b), b));
}

char	*ft_itoa_base(unsigned long n, char *b)
{
	if (!b)
		b = "0123456789";
	int		n_len = get_nb_len_base(n, b);
	char	*ret = malloc(n_len + 1);
	ret[n_len--] = 0;
	while (n_len >= 0)
	{
		ret[n_len--] = b[n % ft_strlen(b)];
		n /= ft_strlen(b);
	}
	return (ret);
}

void	print_column(char *str, char c, unsigned int s)
{
	for (unsigned int i = 0; i < s - ft_strlen(str); i++)
		ft_putchar_fd(c, 1);
	ft_putstr_fd(str, 1);
}

void	print_number_column(unsigned long n, char c, unsigned int s, char *b)
{
	char	*n_str = ft_itoa_base(n, b);
	print_column(n_str, c, s);
	free(n_str);
}