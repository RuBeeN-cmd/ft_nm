#include "ft_nm.h"

/**
 * @brief		Parse the flags from the command line
 * @param[in]	argc The number of arguments
 * @param[in]	argv The arguments
 * @return		The flags parsed from the command line
 */
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

/**
 * @brief		Map a file into memory
 * @param[in]	path The path to the file to map
 * @param[out]	size_buf A pointer to an unsigned long to store the size of the file
 * @return		A pointer to the mapped file, or NULL if an error occurred
 */
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
		if (errno == ENOENT)
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

/**
 * @brief		Print the symbols of a file
 * @param[in]	path The path to the file to print
 * @param[in]	flags The flags to use
 * @param[in]	multiple_files Whether or not multiple files are being printed
 * @return		0 if the symbols were printed successfully, 1 otherwise
 */
int	list_file_symbols(char path[], int flags, int multiple_files)
{
	uint64_t		size;
	void			*addr;
	t_elf			elf;

	if (!path)
		return (1);
	addr = map_file(path, &size);
	if (!addr)
		return (1);
	elf = init_elf(addr, size, flags);
	if (!ft_memcmp(&elf, &DEF_ELF, sizeof(t_elf)))
	{
		print_error("file format not recognized", path, 0);	
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
	if (flags & HELP)
	{
		ft_printf(USAGE);
		return (0);
	}
	int argc_left = get_argc_left(argc - 1, argv + 1);
	if (!argc_left)
		return (list_file_symbols("a.out", flags, 0));
	int	ret = 0;
	for (int i = 1; i < argc; i++)
		if (argv[i])
			if (list_file_symbols(argv[i], flags, argc_left > 1))
				ret = 1;
	return (ret);
}