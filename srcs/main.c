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

int	f(char path[], int flags)
{
	(void) flags;
	if (!path)
		return (1);
	int	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	
	struct stat	stat_buf;
	if (fstat(fd, &stat_buf) == -1)
	{
		close(fd);
		return (1);
	}
	char	*addr = mmap(NULL, stat_buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (addr == MAP_FAILED)
	{
		perror("mmap");
		ft_printf("size: %d\nfd: %d\n", stat_buf.st_size, fd);
		close(fd);
		return (1);
	}
	if (close(fd) == -1)
		return (1);


	write(1, addr, stat_buf.st_size);

	

	if (munmap(addr, stat_buf.st_size) == -1)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	int	flags = parse_flags(argc - 1, argv + 1);
	if (flags == -1)
		return (1);
	if (!get_argc_left(argc - 1, argv + 1))
		return (f("a.out", flags));
	int	ret = 0;
	for (int i = 1; i < argc; i++)
		if (argv[i])
			if (f(argv[i], flags))
				ret = 1;
	return (ret);
}