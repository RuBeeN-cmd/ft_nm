#include "ft_nm.h"

void	print_label(char *label, int label_len)
{
	ft_printf("  %s:", label);
	while (label_len-- - ft_strlen(label))
		ft_putchar_fd(' ', 1);	
}

void	print_ident(uint8_t indent[], int label_len)
{
	print_label("Magic", label_len);
	for (int i = 0; i < EI_NIDENT; i++)
	{
		ft_printf("%x", indent[i]);
		if (i != EI_NIDENT - 1)
			ft_printf(" ");
	}
	ft_printf("\n");
}

void	print_class(uint8_t class, int label_len)
{
	print_label("Class", label_len);
	switch (class)
	{
	case ELFCLASSNONE:
		ft_printf("None (Invalid)\n");
		break;
	case ELFCLASS32:
		ft_printf("ELF32\n");
		break;
	case ELFCLASS64:
		ft_printf("ELF64\n");
		break;
	default:
		ft_printf("Error class\n");
		break;
	}
}

void	print_data(uint8_t data, int label_len)
{
	print_label("Data", label_len);
	switch (data)
	{
	case ELFDATANONE:
		ft_printf("None (Invalid)\n");
		break;
	case ELFDATA2LSB:
		ft_printf("LSB - Least Significant Byte First\n");
		break;
	case ELFDATA2MSB:
		ft_printf("MSB - Most Significant Byte First\n");
		break;
	default:
		ft_printf("Error data\n");
		break;
	}
}

void	print_version(uint8_t version, int label_len)
{
	print_label("Version", label_len);
	switch (version)
	{
	case EV_CURRENT:
		ft_printf("%d (current)\n", EV_CURRENT);
		break;
	default:
		ft_printf("Error version\n");
		break;
	}
}

void	print_osabi(uint8_t osabi, int label_len)
{
	print_label("OS/ABI", label_len);
	switch (osabi)
	{
	case ELFOSABI_NONE:
		ft_printf("UNIX System V ABI\n");
		break;
	case ELFOSABI_HPUX:
		ft_printf("HP-UX\n");
		break;
	case ELFOSABI_NETBSD:
		ft_printf("NetBSD\n");
		break;
	case ELFOSABI_GNU:
		ft_printf("Object uses GNU ELF extensions\n");
		break;
	case ELFOSABI_SOLARIS:
		ft_printf("Sun Solaris\n");
		break;
	case ELFOSABI_AIX:
		ft_printf("IBM AIX\n");
		break;
	case ELFOSABI_IRIX:
		ft_printf("SGI Irix\n");
		break;
	case ELFOSABI_FREEBSD:
		ft_printf("FreeBSD\n");
		break;
	case ELFOSABI_TRU64:
		ft_printf("Compaq TRU64 UNIX\n");
		break;
	case ELFOSABI_MODESTO:
		ft_printf("Novell Modesto\n");
		break;
	case ELFOSABI_OPENBSD:
		ft_printf("OpenBSD\n");
		break;
	case ELFOSABI_ARM_AEABI:
		ft_printf("ARM EABI\n");
		break;
	case ELFOSABI_ARM:
		ft_printf("ARM\n");
		break;
	case ELFOSABI_STANDALONE:
		ft_printf("Standalone (embedded) application\n");
		break;
	default:
		ft_printf("Error os/abi\n");
		break;
	}
}

void	print_type(uint16_t type, int label_len)
{
	print_label("Type", label_len);
	switch (type)
	{
		case ET_NONE:
			ft_printf("No file type\n");
			break;
		case ET_REL:
			ft_printf("Relocatable file\n");
			break;
		case ET_EXEC:
			ft_printf("Executable file\n");
			break;
		case ET_DYN:
			ft_printf("Shared object file\n");
			break;
		case ET_CORE:
			ft_printf("Core file\n");
			break;
		case ET_NUM:
			ft_printf("Number of defined types\n");
			break;
		case ET_LOOS:
			ft_printf("OS-specific range start\n");
			break;
		case ET_HIOS:
			ft_printf("OS-specific range end\n");
			break;
		case ET_LOPROC:
			ft_printf("Processor-specific range start\n");
			break;
		case ET_HIPROC:
			ft_printf("Processor-specific range end\n");
			break;
		default:
			ft_printf("Error type\n");
			break;
	}
}

void	print_machine(uint16_t machine, int label_len)
{
	print_label("Machine", label_len);
	switch (machine)
	{
		case 0x03:
			ft_printf("x86\n");
			break;
		case 0x08:
			ft_printf("MIPS\n");
			break;
		case 0x28:
			ft_printf("ARM\n");
			break;
		case 0x3E:
			ft_printf("amd64\n");
			break;
		case 0xB7:
			ft_printf("ARMv8\n");
			break;
		case 0xF3:
			ft_printf("RISC-V\n");
			break;
		default:
			ft_printf("Error machine\n");
			break;
	}
}

void	print_32elf_header(Elf32_Ehdr *hdr)
{
	int	label_max_len = ft_strlen("Section header string table index ");
	ft_printf("ELF Header:\n");
	print_ident(hdr->e_ident, label_max_len);
	print_class(hdr->e_ident[EI_CLASS], label_max_len);
	print_data(hdr->e_ident[EI_DATA], label_max_len);
	print_version(hdr->e_ident[EI_VERSION], label_max_len);
	print_osabi(hdr->e_ident[EI_OSABI], label_max_len);
	print_label("ABI Version", label_max_len);
	ft_printf("%u\n", hdr->e_ident[EI_ABIVERSION]);
	print_type(hdr->e_type, label_max_len);
	print_machine(hdr->e_machine, label_max_len);
	print_label("Version", label_max_len);
	ft_printf("%u\n", hdr->e_version);
	print_label("Entry point address", label_max_len);
	ft_printf("%p\n", (void *) (long) hdr->e_entry);
	print_label("Start of program headers", label_max_len);
	ft_printf("%lu\n", hdr->e_phoff);
	print_label("Start of section headers", label_max_len);
	ft_printf("%lu\n", hdr->e_shoff);
	print_label("Flags", label_max_len);
	ft_printf("%p\n", (void *) (long) hdr->e_flags);
	print_label("Size of this header", label_max_len);
	ft_printf("%u (bytes)\n", hdr->e_ehsize);
	print_label("Size of program headers", label_max_len);
	ft_printf("%u (bytes)\n", hdr->e_phentsize);
	print_label("Number of program headers", label_max_len);
	ft_printf("%u\n", hdr->e_phnum);
	print_label("Size of section headers", label_max_len);
	ft_printf("%u (bytes)\n", hdr->e_shentsize);
	print_label("Number of section headers", label_max_len);
	ft_printf("%u\n", hdr->e_shnum);
	print_label("Section header string table index", label_max_len);
	ft_printf("%u\n", hdr->e_shstrndx);
}

void	print_64elf_header(Elf64_Ehdr *hdr)
{
	int	label_max_len = ft_strlen("Section header string table index ");
	ft_printf("ELF Header:\n");
	print_ident(hdr->e_ident, label_max_len);
	print_class(hdr->e_ident[EI_CLASS], label_max_len);
	print_data(hdr->e_ident[EI_DATA], label_max_len);
	print_version(hdr->e_ident[EI_VERSION], label_max_len);
	print_osabi(hdr->e_ident[EI_OSABI], label_max_len);
	print_label("ABI Version", label_max_len);
	ft_printf("%u\n", hdr->e_ident[EI_ABIVERSION]);
	print_type(hdr->e_type, label_max_len);
	print_machine(hdr->e_machine, label_max_len);
	print_label("Version", label_max_len);
	ft_printf("%u\n", hdr->e_version);
	print_label("Entry point address", label_max_len);
	ft_printf("%p\n", (void *) (long) hdr->e_entry);
	print_label("Start of program headers", label_max_len);
	ft_printf("%lu\n", hdr->e_phoff);
	print_label("Start of section headers", label_max_len);
	ft_printf("%lu\n", hdr->e_shoff);
	print_label("Flags", label_max_len);
	ft_printf("%p\n", (void *) (long) hdr->e_flags);
	print_label("Size of this header", label_max_len);
	ft_printf("%u (bytes)\n", hdr->e_ehsize);
	print_label("Size of program headers", label_max_len);
	ft_printf("%u (bytes)\n", hdr->e_phentsize);
	print_label("Number of program headers", label_max_len);
	ft_printf("%u\n", hdr->e_phnum);
	print_label("Size of section headers", label_max_len);
	ft_printf("%u (bytes)\n", hdr->e_shentsize);
	print_label("Number of section headers", label_max_len);
	ft_printf("%u\n", hdr->e_shnum);
	print_label("Section header string table index", label_max_len);
	ft_printf("%u\n", hdr->e_shstrndx);
}