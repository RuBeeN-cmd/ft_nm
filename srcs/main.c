#include "ft_nm.h"

int	get_argc_left(int argc, char *argv[])
{
	if (argc < 0 || !argv)
		return (-1);
	int	ret = 0;
	for (int i = 0; i < argc; i++)
		if (argv[i])
			ret++;
	return (ret);
}

void	*map_file(char path[], unsigned long *size_buf)
{
	void		*addr;
	struct stat	stat_buf;
	int	fd;

	*size_buf = 0;
	if (!path)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		print_error("No such file", path, 1);
		return (NULL);
	}
	if (fstat(fd, &stat_buf) == -1)
	{
		close(fd);
		return (NULL);
	}
	addr = mmap(NULL, stat_buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (addr == MAP_FAILED)
		addr = NULL;
	close(fd);
	*size_buf = stat_buf.st_size;
	return (addr);
}

int	list_symbols(char path[], int flags, int multiple_files)
{
	unsigned long	size;
	void			*addr;
	t_elf			elf;
	(void) flags;

	if (!path)
		return (1);
	addr = map_file(path, &size);
	if (!addr)
		return (1);
	elf = init_elf(addr, path);
	if (!ft_memcmp(&elf, &DEF_ELF, sizeof(t_elf)))
	{
		munmap(addr, size);
		return (1);
	}
	if (multiple_files)
		ft_printf("\n%s:\n", path);
	print_elf(elf, path);
	if (munmap(addr, size) == -1)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	int	flags = parse_flags(argc - 1, argv + 1);
	if (flags == -1)
		return (1);
	if (!get_argc_left(argc - 1, argv + 1))
		return (list_symbols("a.out", flags, 0));
	int	ret = 0;
	for (int i = 1; i < argc; i++)
		if (argv[i])
			if (list_symbols(argv[i], flags, argc - 1 > 0))
				ret = 1;
	return (ret);
}