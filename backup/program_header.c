#include "ft_nm.h"

void	print_32program_header(Elf32_Phdr *hdr, int hdr_number)
{
	ft_printf("Program Headers:\n");
	ft_printf("  Type           Offset             VirtAddr           PhysAddr\n");
	ft_printf("                 FileSiz            MemSiz              Flags  Align\n");
	for (int i = 0; i < hdr_number; i++)
	{
		ft_printf("  %u", hdr->p_type);
		ft_printf("  %u", hdr->p_flags);
		ft_printf("  %lu", hdr->p_offset);
		ft_printf("  %p", (void *) (long) hdr->p_vaddr);
		ft_printf("  %p", (void *) (long) hdr->p_paddr);
		ft_printf("  %u", hdr->p_filesz);
		ft_printf("  %u", hdr->p_memsz);
		ft_printf("  %u", hdr->p_align);
		ft_printf("\n");
		hdr++;
	}
}

void	print_64program_header(Elf64_Phdr *hdr, int hdr_number)
{
	ft_printf("Program Headers:\n");
	ft_printf("  Type           Offset             VirtAddr           PhysAddr\n");
	ft_printf("                 FileSiz            MemSiz              Flags  Align\n");
	for (int i = 0; i < hdr_number; i++)
	{
		ft_printf("  %u", hdr->p_type);
		ft_printf("  %u", hdr->p_flags);
		ft_printf("  %lu", hdr->p_offset);
		ft_printf("  %p", (void *) (long) hdr->p_vaddr);
		ft_printf("  %p", (void *) (long) hdr->p_paddr);
		ft_printf("  %u", hdr->p_filesz);
		ft_printf("  %u", hdr->p_memsz);
		ft_printf("  %u", hdr->p_align);
		ft_printf("\n");
		hdr++;
	}
}