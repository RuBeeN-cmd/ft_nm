#include "ft_nm.h"

void	print_ident(uint8_t *ident)
{
	ft_printf("Magic: "CYAN);
	for (int i = 0; i < EI_NIDENT; i++)
		ft_printf("%x ", ident[i]);
	ft_printf("\n"RESET);
}

void	print_type(uint16_t type)
{
	ft_printf("Type: "CYAN"%d ", type);
	if (type == ET_NONE)
		ft_printf("NONE (Unknown type)\n"RESET);
	else if (type == ET_REL)
		ft_printf("REL (Relocatable file)\n"RESET);
	else if (type == ET_EXEC)
		ft_printf("EXEC (Executable file)\n"RESET);
	else if (type == ET_DYN)
		ft_printf("DYN (Shared object file)\n"RESET);
	else if (type == ET_CORE)
		ft_printf("CORE (Core file)\n"RESET);
	else
		ft_printf("Unknown type\n"RESET);
}

void	print_machine(uint16_t machine)
{
	ft_printf("Machine: "CYAN"%d ", machine);
	if (machine == EM_NONE)
		ft_printf("NONE (Unknown machine)\n"RESET);
	else if (machine == EM_M32)
		ft_printf("M32 (AT&T WE 32100)\n"RESET);
	else if (machine == EM_SPARC)
		ft_printf("SPARC (Sun SPARC)\n"RESET);
	else if (machine == EM_386)
		ft_printf("386 (Intel 80386)\n"RESET);
	else if (machine == EM_68K)
		ft_printf("68K (Motorola 68000)\n"RESET);
	else if (machine == EM_88K)
		ft_printf("88K (Motorola 88000)\n"RESET);
	else if (machine == EM_IAMCU)
		ft_printf("IAMCU (Intel MCU)\n"RESET);
	else if (machine == EM_860)
		ft_printf("860 (Intel 80860)\n"RESET);
	else if (machine == EM_MIPS)
		ft_printf("MIPS (MIPS R3000 Big-Endian only)\n"RESET);
	else if (machine == EM_S370)
		ft_printf("S370 (IBM System/370)\n"RESET);
	else if (machine == EM_MIPS_RS3_LE)
		ft_printf("MIPS_RS3_LE (MIPS R3000 Little-Endian)\n"RESET);
	else if (machine == EM_PARISC)
		ft_printf("PARISC (HPPA)\n"RESET);
	else if (machine == EM_VPP500)
		ft_printf("VPP500 (Fujitsu VPP500)\n"RESET);
	else if (machine == EM_SPARC32PLUS)
		ft_printf("SPARC32PLUS (SPARC with enhanced instruction set)\n"RESET);
	else if (machine == EM_960)
		ft_printf("960 (Intel 80960)\n"RESET);
	else if (machine == EM_PPC)
		ft_printf("PPC (PowerPC)\n"RESET);
	else if (machine == EM_PPC64)
		ft_printf("PPC64 (PowerPC 64-bit)\n"RESET);
	else if (machine == EM_S390)
		ft_printf("S390 (IBM S/390)\n"RESET);
	else if (machine == EM_SPU)
		ft_printf("SPU (Sony/Toshiba/IBM SPU)\n"RESET);
	else if (machine == EM_V800)
		ft_printf("V800 (NEC V800)\n"RESET);
	else if (machine == EM_FR20)
		ft_printf("FR20 (Fujitsu FR20)\n"RESET);
	else if (machine == EM_RH32)
		ft_printf("RH32 (TRW RH-32)\n"RESET);
	else if (machine == EM_RCE)
		ft_printf("RCE (Motorola RCE)\n"RESET);
	else if (machine == EM_ARM)
		ft_printf("ARM (Advanced RISC Machines)\n"RESET);
	else if (machine == EM_FAKE_ALPHA)
		ft_printf("FAKE_ALPHA (Digital Alpha)\n"RESET);
	else if (machine == EM_SH)
		ft_printf("SH (Hitachi SH)\n"RESET);
	else if (machine == EM_SPARCV9)
		ft_printf("SPARCV9 (SPARC v9 64-bit)\n"RESET);
	else if (machine == EM_TRICORE)
		ft_printf("TRICORE (Siemens Tricore)\n"RESET);
	else if (machine == EM_ARC)
		ft_printf("ARC (Argonaut RISC Core)\n"RESET);
	else if (machine == EM_H8_300)
		ft_printf("H8_300 (Hitachi H8/300)\n"RESET);
	else if (machine == EM_H8_300H)
		ft_printf("H8_300H (Hitachi H8/300H)\n"RESET);
	else if (machine == EM_H8S)
		ft_printf("H8S (Hitachi H8S)\n"RESET);
	else if (machine == EM_H8_500)
		ft_printf("H8_500 (Hitachi H8/500)\n"RESET);
	else if (machine == EM_IA_64)
		ft_printf("IA_64 (Intel IA-64)\n"RESET);
	else if (machine == EM_MIPS_X)
		ft_printf("MIPS_X (Stanford MIPS-X)\n"RESET);
	else if (machine == EM_COLDFIRE)
		ft_printf("COLDFIRE (Motorola Coldfire)\n"RESET);
	else if (machine == EM_68HC12)
		ft_printf("68HC12 (Motorola M68HC12)\n"RESET);
	else if (machine == EM_MMA)
		ft_printf("MMA (Fujitsu MMA Multimedia Accelerator)\n"RESET);
	else if (machine == EM_PCP)
		ft_printf("PCP (Siemens PCP)\n"RESET);
	else if (machine == EM_NCPU)
		ft_printf("NCPU (Sony nCPU embedded RISC processor)\n"RESET);
	else if (machine == EM_NDR1)
		ft_printf("NDR1 (Denso NDR1 microprocessor)\n"RESET);
	else if (machine == EM_STARCORE)
		ft_printf("STARCORE (Motorola Star*Core processor)\n"RESET);
	else if (machine == EM_ME16)
		ft_printf("ME16 (Toyota ME16 processor)\n"RESET);
	else if (machine == EM_ST100)
		ft_printf("ST100 (STMicroelectronics ST100 processor)\n"RESET);
	else if (machine == EM_TINYJ)
		ft_printf("TINYJ (Advanced Logic Corp. TinyJ embedded processor)\n"RESET);
	else if (machine == EM_X86_64)
		ft_printf("X86_64 (Advanced Micro Devices X86-64)\n"RESET);
	else if (machine == EM_PDSP)
		ft_printf("PDSP (Sony DSP Processor)\n"RESET);
	else if (machine == EM_PDP10)
		ft_printf("PDP10 (Digital Equipment Corp. PDP-10)\n"RESET);
	else if (machine == EM_PDP11)
		ft_printf("PDP11 (Digital Equipment Corp. PDP-11)\n"RESET);
	else if (machine == EM_FX66)
		ft_printf("FX66 (Siemens FX66 microcontroller)\n"RESET);
	else if (machine == EM_ST9PLUS)
		ft_printf("ST9PLUS (STMicroelectronics ST9+ 8/16 bit microcontroller)\n"RESET);
	else if (machine == EM_ST7)
		ft_printf("ST7 (STMicroelectronics ST7 8-bit microcontroller)\n"RESET);
	else if (machine == EM_68HC16)
		ft_printf("68HC16 (Motorola MC68HC16 Microcontroller)\n"RESET);
	else if (machine == EM_68HC11)
		ft_printf("68HC11 (Motorola MC68HC11 Microcontroller)\n"RESET);
	else if (machine == EM_68HC08)
		ft_printf("68HC08 (Motorola MC68HC08 Microcontroller)\n"RESET);
	else if (machine == EM_68HC05)
		ft_printf("68HC05 (Motorola MC68HC05 Microcontroller)\n"RESET);
	else if (machine == EM_SVX)
		ft_printf("SVX (Silicon Graphics SVx)\n"RESET);
	else if (machine == EM_ST19)
		ft_printf("ST19 (STMicroelectronics ST19 8-bit microcontroller)\n"RESET);
	else if (machine == EM_VAX)
		ft_printf("VAX (Digital VAX)\n"RESET);
	else if (machine == EM_CRIS)
		ft_printf("CRIS (Axis Communications 32-bit embedded processor)\n"RESET);
	else if (machine == EM_JAVELIN)
		ft_printf("JAVELIN (Infineon Technologies 32-bit embedded processor)\n"RESET);
	else if (machine == EM_FIREPATH)
		ft_printf("FIREPATH (Element 14 64-bit DSP Processor)\n"RESET);
	else if (machine == EM_ZSP)
		ft_printf("ZSP (LSI Logic 16-bit DSP Processor)\n"RESET);
	else if (machine == EM_MMIX)
		ft_printf("MMIX (Donald Knuth's educational 64-bit processor)\n"RESET);
	else if (machine == EM_HUANY)
		ft_printf("HUANY (Harvard University machine-independent object files)\n"RESET);
	else if (machine == EM_PRISM)
		ft_printf("PRISM (SiTera Prism)\n"RESET);
	else if (machine == EM_AVR)
		ft_printf("AVR (Atmel AVR 8-bit microcontroller)\n"RESET);
	else if (machine == EM_FR30)
		ft_printf("FR30 (Fujitsu FR30)\n"RESET);
	else if (machine == EM_D10V)
		ft_printf("D10V (Mitsubishi D10V)\n"RESET);
	else if (machine == EM_D30V)
		ft_printf("D30V (Mitsubishi D30V)\n"RESET);
	else if (machine == EM_V850)
		ft_printf("V850 (NEC v850)\n"RESET);
	else if (machine == EM_M32R)
		ft_printf("M32R (Mitsubishi M32R)\n"RESET);
	else if (machine == EM_MN10300)
		ft_printf("MN10300 (Matsushita MN10300)\n"RESET);
	else if (machine == EM_MN10200)
		ft_printf("MN10200 (Matsushita MN10200)\n"RESET);
	else if (machine == EM_PJ)
		ft_printf("PJ (picoJava)\n"RESET);
	else if (machine == EM_OPENRISC)
		ft_printf("OPENRISC (OpenRISC 32-bit embedded processor)\n"RESET);
	else if (machine == EM_ARC_COMPACT)
		ft_printf("ARC_COMPACT (ARC International ARCompact)\n"RESET);
	else if (machine == EM_XTENSA)
		ft_printf("XTENSA (Tensilica Xtensa Architecture)\n"RESET);
	else if (machine == EM_VIDEOCORE)
		ft_printf("VIDEOCORE (Alphamosaic VideoCore processor)\n"RESET);
	else if (machine == EM_TMM_GPP)
		ft_printf("TMM_GPP (Thompson Multimedia General Purpose Processor)\n"RESET);
	else if (machine == EM_NS32K)
		ft_printf("NS32K (National Semiconductor 32000 series)\n"RESET);
	else if (machine == EM_TPC)
		ft_printf("TPC (Tenor Network TPC processor)\n"RESET);
	else if (machine == EM_SNP1K)
		ft_printf("SNP1K (Trebia SNP 1000 processor)\n"RESET);
	else if (machine == EM_ST200)
		ft_printf("ST200 (STMicroelectronics (www.st.com) ST200 microcontroller)\n"RESET);
	else if (machine == EM_IP2K)
		ft_printf("IP2K (Ubicom IP2xxx microcontroller family)\n"RESET);
	else if (machine == EM_MAX)
		ft_printf("MAX (MAX Processor)\n"RESET);
	else if (machine == EM_CR)
		ft_printf("CR (National Semiconductor CompactRISC microprocessor)\n"RESET);
	else if (machine == EM_F2MC16)
		ft_printf("F2MC16 (Fujitsu F2MC16)\n"RESET);
	else if (machine == EM_MSP430)
		ft_printf("MSP430 (Texas Instruments embedded microcontroller msp430)\n"RESET);
	else if (machine == EM_BLACKFIN)
		ft_printf("BLACKFIN (Analog Devices Blackfin (DSP) processor)\n"RESET);
	else if (machine == EM_SE_C33)
		ft_printf("SE_C33 (S1C33 Family of Seiko Epson processors)\n"RESET);
	else if (machine == EM_SEP)
		ft_printf("SEP (Sharp embedded microprocessor)\n"RESET);
	else if (machine == EM_ARCA)
		ft_printf("ARCA (Arca RISC Microprocessor)\n"RESET);
	else if (machine == EM_UNICORE)
		ft_printf("UNICORE (Microprocessor series from PKU-Unity Ltd. and MPRC of Peking University)\n"RESET);
	else if (machine == EM_EXCESS)
		ft_printf("EXCESS (eXcess: "CYAN"16/32/64-bit configurable embedded CPU)\n"RESET);
	else if (machine == EM_DXP)
		ft_printf("DXP (Icera Semiconductor Inc. Deep Execution Processor)\n"RESET);
	else if (machine == EM_ALTERA_NIOS2)
		ft_printf("ALTERA_NIOS2 (Altera Nios II soft-core processor)\n"RESET);
	else if (machine == EM_CRX)
		ft_printf("CRX (National Semiconductor CRX)\n"RESET);
	else if (machine == EM_XGATE)
		ft_printf("XGATE (Motorola XGATE embedded processor)\n"RESET);
	else if (machine == EM_C166)
		ft_printf("C166 (Infineon C16x/XC16x processor)\n"RESET);
	else if (machine == EM_M16C)
		ft_printf("M16C (Renesas M16C series microprocessors)\n"RESET);
	else if (machine == EM_DSPIC30F)
		ft_printf("DSPIC30F (Microchip Technology dsPIC30F Digital Signal Controller)\n"RESET);
	else if (machine == EM_CE)
		ft_printf("CE (Freescale Communication Engine RISC core)\n"RESET);
	else if (machine == EM_M32C)
		ft_printf("M32C (Renesas M32C series microprocessors)\n"RESET);
	else if (machine == EM_TSK3000)
		ft_printf("TSK3000 (Altium TSK3000 core)\n"RESET);
	else if (machine == EM_RS08)
		ft_printf("RS08 (Freescale RS08 embedded processor)\n"RESET);
	else if (machine == EM_SHARC)
		ft_printf("SHARC (Analog Devices SHARC family of 32-bit DSP processors)\n"RESET);
	else if (machine == EM_ECOG2)
		ft_printf("ECOG2 (Cyan Technology eCOG2 microprocessor)\n"RESET);
	else if (machine == EM_SCORE7)
		ft_printf("SCORE7 (Sunplus S+core7 RISC processor)\n"RESET);
	else if (machine == EM_DSP24)
		ft_printf("DSP24 (New Japan Radio (NJR) 24-bit DSP Processor)\n"RESET);
	else if (machine == EM_VIDEOCORE3)
		ft_printf("VIDEOCORE3 (Broadcom VideoCore III processor)\n"RESET);
	else if (machine == EM_LATTICEMICO32)
		ft_printf("LATTICEMICO32 (RISC processor for Lattice FPGA architecture)\n"RESET);
	else if (machine == EM_SE_C17)
		ft_printf("SE_C17 (Seiko Epson C17 family)\n"RESET);
	else if (machine == EM_TI_C6000)
		ft_printf("TI_C6000 (The Texas Instruments TMS320C6000 DSP family)\n"RESET);
	else if (machine == EM_TI_C2000)
		ft_printf("TI_C2000 (The Texas Instruments TMS320C2000 DSP family)\n"RESET);
	else if (machine == EM_TI_C5500)
		ft_printf("TI_C5500 (The Texas Instruments TMS320C55x DSP family)\n"RESET);
	else if (machine == EM_TI_ARP32)
		ft_printf("TI_ARP32 (Texas Instruments Application Specific RISC Processor, 32bit)\n"RESET);
	else if (machine == EM_TI_PRU)
		ft_printf("TI_PRU (Texas Instruments Programmable Realtime Unit)\n"RESET);
	else if (machine == EM_MMDSP_PLUS)
		ft_printf("MMDSP_PLUS (STMicroelectronics 64bit VLIW Data Signal Processor)\n"RESET);
	else if (machine == EM_CYPRESS_M8C)
		ft_printf("CYPRESS_M8C (Cypress M8C microprocessor)\n"RESET);
	else if (machine == EM_R32C)
		ft_printf("R32C (Renesas R32C series microprocessors)\n"RESET);
	else if (machine == EM_TRIMEDIA)
		ft_printf("TRIMEDIA (NXP Semiconductors TriMedia architecture family)\n"RESET);
	else if (machine == EM_QDSP6)
		ft_printf("QDSP6 (QUALCOMM DSP6 Processor)\n"RESET);
	else if (machine == EM_8051)
		ft_printf("8051 (Intel 8051 and variants)\n"RESET);
	else if (machine == EM_STXP7X)
		ft_printf("STXP7X (STMicroelectronics STxP7x family of configurable and extensible RISC processors)\n"RESET);
	else if (machine == EM_NDS32)
		ft_printf("NDS32 (Andes Technology compact code size embedded RISC processor family)\n"RESET);
	else if (machine == EM_ECOG1X)
		ft_printf("ECOG1X (Cyan Technology eCOG1X family)\n"RESET);
	else if (machine == EM_MAXQ30)
		ft_printf("MAXQ30 (Dallas Semiconductor MAXQ30 Core Micro-controllers)\n"RESET);
	else if (machine == EM_XIMO16)
		ft_printf("XIMO16 (New Japan Radio (NJR) 16-bit DSP Processor)\n"RESET);
	else if (machine == EM_MANIK)
		ft_printf("MANIK (M2000 Reconfigurable RISC Microprocessor)\n"RESET);
	else if (machine == EM_CRAYNV2)
		ft_printf("CRAYNV2 (Cray Inc. NV2 vector architecture)\n"RESET);
	else if (machine == EM_RX)
		ft_printf("RX (Renesas RX family)\n"RESET);
	else if (machine == EM_METAG)
		ft_printf("METAG (Imagination Technologies META processor architecture)\n"RESET);
	else if (machine == EM_MCST_ELBRUS)
		ft_printf("MCST_ELBRUS (MCST Elbrus general purpose hardware architecture)\n"RESET);
	else if (machine == EM_ECOG16)
		ft_printf("ECOG16 (Cyan Technology eCOG16 family)\n"RESET);
	else if (machine == EM_CR16)
		ft_printf("CR16 (National Semiconductor CompactRISC 16-bit processor)\n"RESET);
	else if (machine == EM_ETPU)
		ft_printf("ETPU (Freescale Extended Time Processing Unit)\n"RESET);
	else if (machine == EM_SLE9X)
		ft_printf("SLE9X (Infineon Technologies SLE9X core)\n"RESET);
	else if (machine == EM_L10M)
		ft_printf("L10M (Intel L10M)\n"RESET);
	else if (machine == EM_K10M)
		ft_printf("K10M (Intel K10M)\n"RESET);
	else if (machine == EM_AARCH64)
		ft_printf("AARCH64 (ARM AARCH64)\n"RESET);
	else if (machine == EM_AVR32)
		ft_printf("AVR32 (Atmel Corporation 32-bit microprocessor family)\n"RESET);
	else if (machine == EM_STM8)
		ft_printf("STM8 (STMicroelectronics STM8 8-bit microcontroller)\n"RESET);
	else if (machine == EM_TILE64)
		ft_printf("TILE64 (Tilera TILE64 multicore architecture family)\n"RESET);
	else if (machine == EM_TILEPRO)
		ft_printf("TILEPRO (Tilera TILEPro multicore architecture family)\n"RESET);
	else if (machine == EM_MICROBLAZE)
		ft_printf("MICROBLAZE (Xilinx MicroBlaze 32-bit RISC soft processor core)\n"RESET);
	else if (machine == EM_CUDA)
		ft_printf("CUDA (NVIDIA CUDA architecture)\n"RESET);
	else if (machine == EM_TILEGX)
		ft_printf("TILEGX (Tilera TILE-Gx multicore architecture family)\n"RESET);
	else if (machine == EM_CLOUDSHIELD)
		ft_printf("CLOUDSHIELD (CloudShield architecture family)\n"RESET);
	else if (machine == EM_COREA_1ST)
		ft_printf("COREA_1ST (KIT CoreA 1st generation processor family)\n"RESET);
	else if (machine == EM_COREA_2ND)
		ft_printf("COREA_2ND (KIT CoreA 2nd generation processor family)\n"RESET);
	// else if (machine == EM_ARC_COMPACT2)
	// 	ft_printf("ARC_COMPACT2 (Synopsys ARCompact V2)\n"RESET);
	else if (machine == EM_OPEN8)
		ft_printf("OPEN8 (Open8 8-bit RISC soft processor core)\n"RESET);
	else if (machine == EM_RL78)
		ft_printf("RL78 (Renesas RL78 family)\n"RESET);
	else if (machine == EM_VIDEOCORE5)
		ft_printf("VIDEOCORE5 (Broadcom VideoCore V processor)\n"RESET);
	else if (machine == EM_78KOR)
		ft_printf("78KOR (Renesas 78KOR)\n"RESET);
	else if (machine == EM_56800EX)
		ft_printf("56800EX (Freescale 56800EX Digital Signal Controller (DSC))\n"RESET);
	else if (machine == EM_BA1)
		ft_printf("BA1 (Beyond BA1 CPU architecture)\n"RESET);
	else if (machine == EM_BA2)
		ft_printf("BA2 (Beyond BA2 CPU architecture)\n"RESET);
	else if (machine == EM_XCORE)
		ft_printf("XCORE (XMOS xCORE processor family)\n"RESET);
	else if (machine == EM_MCHP_PIC)
		ft_printf("MCHP_PIC (Microchip 8-bit PIC(r) family)\n"RESET);
	else if (machine == EM_KM32)
		ft_printf("KM32 (KM211 KM32 32-bit processor)\n"RESET);
	else if (machine == EM_KMX32)
		ft_printf("KMX32 (KM211 KMX32 32-bit processor)\n"RESET);
	else if (machine == EM_EMX16)
		ft_printf("KMX16 (KM211 KMX16 16-bit processor)\n"RESET);
	else if (machine == EM_EMX8)
		ft_printf("KMX8 (KM211 KMX8 8-bit processor)\n"RESET);
	else if (machine == EM_KVARC)
		ft_printf("KVARC (KM211 KVARC processor)\n"RESET);
	else if (machine == EM_CDP)
		ft_printf("CDP (Paneve CDP architecture)\n"RESET);
	else if (machine == EM_COGE)
		ft_printf("COGE (Cognitive Smart Memory Processor)\n"RESET);
	else if (machine == EM_COOL)
		ft_printf("COOL (Bluechip Systems CoolEngine)\n"RESET);
	else if (machine == EM_NORC)
		ft_printf("NORC (Nanoradio Optimized RISC)\n"RESET);
	else if (machine == EM_CSR_KALIMBA)
		ft_printf("CSR_KALIMBA (CSR Kalimba architecture family)\n"RESET);
	else if (machine == EM_Z80)
		ft_printf("Z80 (Zilog Z80)\n"RESET);
	else if (machine == EM_VISIUM)
		ft_printf("VISIUM (Controls and Data Services VISIUMcore)\n"RESET);
	else if (machine == EM_FT32)
		ft_printf("FT32 (FTDI Chip FT32 high performance 32-bit RISC)\n"RESET);
	else if (machine == EM_MOXIE)
		ft_printf("MOXIE (Moxie processor family)\n"RESET);
	else if (machine == EM_AMDGPU)
		ft_printf("AMDGPU (AMD GPU architecture)\n"RESET);
	else if (machine == EM_RISCV)
		ft_printf("RISCV (RISC-V)\n"RESET);
	else if (machine == EM_BPF)
		ft_printf("BPF (Linux BPF – in-kernel virtual machine)\n"RESET);
	else if (machine == EM_CSKY)
		ft_printf("CSKY (C-SKY processor family)\n"RESET);
	else
		ft_printf("Unknown machine\n"RESET);
}

void	print_version(uint32_t version)
{
	ft_printf("Version: "CYAN"%d ", version);
	if (version == EV_NONE)
		ft_printf("0x0 (Invalid version)\n"RESET);
	else if (version == EV_CURRENT)
		ft_printf("0x1 (Current version)\n"RESET);
	else
		ft_printf("Unknown version\n"RESET);
}

void	print_entry(uint64_t entry)
{
	ft_printf("Entry point address: "CYAN"%p\n"RESET, entry);
}

void	print_phoff(uint64_t phoff)
{
	ft_printf("Start of program headers: "CYAN"%p (bytes into file)\n"RESET, phoff);
}

void	print_shoff(uint64_t shoff)
{
	ft_printf("Start of section headers: "CYAN"%p (bytes into file)\n"RESET, shoff);
}

void	print_flags(uint32_t flags)
{
	ft_printf("Flags: "CYAN"0x%x\n"RESET, flags);
}

void	print_ehsize(uint16_t ehsz)
{
	ft_printf("Size of this header: "CYAN"%d (bytes)\n"RESET, ehsz);
}

void	print_phentsize(uint16_t phentsz)
{
	ft_printf("Size of program headers: "CYAN"%d (bytes)\n"RESET, phentsz);
}

void	print_phnum(uint16_t phnum)
{
	ft_printf("Number of program headers: "CYAN"%d\n"RESET, phnum);
}

void	print_shentsize(uint16_t shentsz)
{
	ft_printf("Size of section headers: "CYAN"%d (bytes)\n"RESET, shentsz);
}

void	print_shnum(uint16_t shnum)
{
	ft_printf("Number of section headers: "CYAN"%d\n"RESET, shnum);
}

void	print_shstrndx(uint16_t shstrndx)
{
	ft_printf("Section header string table index: "CYAN"%d\n"RESET, shstrndx);
}

void	print_ehdr(void *ehdr, uint8_t class, uint8_t endian)
{
	print_ident(get_e_ident(ehdr));
	print_type(get_e_type(ehdr, endian));
	print_machine(get_e_machine(ehdr, endian));
	print_version(get_e_version(ehdr, endian));
	print_entry(get_e_entry(ehdr, class, endian));
	print_phoff(get_e_phoff(ehdr, class, endian));
	print_shoff(get_e_shoff(ehdr, class, endian));
	print_flags(get_e_flags(ehdr, class, endian));
	print_ehsize(get_e_ehsize(ehdr, class, endian));
	print_phentsize(get_e_phentsize(ehdr, class, endian));
	print_phnum(get_e_phnum(ehdr, class, endian));
	print_shentsize(get_e_shentsize(ehdr, class, endian));
	print_shnum(get_e_shnum(ehdr, class, endian));
	print_shstrndx(get_e_shstrndx(ehdr, class, endian));
}