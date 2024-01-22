#include "ft_nm.h"

void	print_32section_header(Elf32_Shdr *hdr, int hdr_number, char *str_table)
{
	ft_printf("Section Headers:\n");
	ft_printf("  [Nr] Name              Type             Address           Offset\n");
	ft_printf("       Size              EntSize          Flags  Link  Info  Align\n");
	for (int i = 0; i < hdr_number; i++)
	{
		ft_printf("  [%d]", i);
		ft_printf("  %s", str_table + hdr->sh_name);
		ft_printf("  %u", hdr->sh_name);
		ft_printf("  %u", hdr->sh_type);
		ft_printf("  %p", (void *) (long) hdr->sh_addr);
		ft_printf("  %p", (void *) (long) hdr->sh_offset);
		ft_printf("  %p", (void *) (long) hdr->sh_size);
		ft_printf("  %lu", hdr->sh_entsize);
		ft_printf("  %lu", hdr->sh_flags);
		ft_printf("  %u", hdr->sh_link);
		ft_printf("  %u", hdr->sh_info);
		ft_printf("  %lu", hdr->sh_addralign);
		ft_printf("\n");
		hdr++;
	}
}

void	print_64section_header(Elf64_Shdr *hdr, int hdr_number, char *str_table)
{
	ft_printf("Section Headers:\n");
	ft_printf("  [Nr]  Name  Type  Address  Offset");
	ft_printf("  Size  EntSize  Flags  Link  Info  Align\n");
	for (int i = 0; i < hdr_number; i++)
	{
		ft_printf("  [%d]", i);
		ft_printf("  %s", str_table + hdr->sh_name);
		ft_printf("  %u", hdr->sh_name);
		ft_printf("  %u", hdr->sh_type);
		ft_printf("  %p", (void *) (long) hdr->sh_addr);
		ft_printf("  %p", (void *) (long) hdr->sh_offset);
		ft_printf("  %p", (void *) (long) hdr->sh_size);
		ft_printf("  %lu", hdr->sh_entsize);
		ft_printf("  %lu", hdr->sh_flags);
		ft_printf("  %u", hdr->sh_link);
		ft_printf("  %u", hdr->sh_info);
		ft_printf("  %lu", hdr->sh_addralign);
		ft_printf("\n");
		hdr++;
	}
}