#ifndef CLASS_H
#define CLASS_H

#include "ft_nm.h"

#define SYM_INFO(sym, class) (class == ELFCLASS32 ? ((Elf32_Sym *) sym)->st_info : ((Elf64_Sym *) sym)->st_info)
#define SYM_NAME(sym, class, endian) read_uint32(class == ELFCLASS32 ? ((Elf32_Sym *) sym)->st_name : ((Elf64_Sym *) sym)->st_name, endian)
#define SYM_VALUE(sym, class, endian) (class == ELFCLASS32 ? read_uint32(((Elf32_Sym *) sym)->st_value, endian) : read_uint64(((Elf64_Sym *) sym)->st_value, endian))
#define SYM_VALUE_SIZE(class) (class == ELFCLASS32 ? sizeof(uint32_t) : sizeof(uint64_t))
#define SYM_SIZE(class) (class == ELFCLASS32 ? sizeof(Elf32_Sym) : sizeof(Elf64_Sym))
#define SYM_SHNDX(sym, class, endian) read_uint16(class == ELFCLASS32 ? ((Elf32_Sym *) sym)->st_shndx : ((Elf64_Sym *) sym)->st_shndx, endian)
#define SYM_BIND(sym, class) (class == ELFCLASS32 ? ELF32_ST_BIND(((Elf32_Sym *) sym)->st_info) : ELF64_ST_BIND(((Elf64_Sym *) sym)->st_info))
#define SYM_TYPE(sym, class) (class == ELFCLASS32 ? ELF32_ST_TYPE(((Elf32_Sym *) sym)->st_info) : ELF64_ST_TYPE(((Elf64_Sym *) sym)->st_info))
#define SYM_VISIBILITY(sym, class) (class == ELFCLASS32 ? ELF32_ST_VISIBILITY(((Elf32_Sym *) sym)->st_other) : ELF64_ST_VISIBILITY(((Elf64_Sym *) sym)->st_other))
#define NEXT_SYM(sym, class) (class == ELFCLASS32 ? (void *) (((Elf32_Sym *) sym) + 1) : (void *) (((Elf64_Sym *) sym) + 1))

#define EH_SHOFF(ehdr, class, endian) (class == ELFCLASS32 ? read_uint32(((Elf32_Ehdr *) ehdr)->e_shoff, endian) : read_uint64(((Elf64_Ehdr *) ehdr)->e_shoff, endian))
#define EH_SHNUM(ehdr, class, endian) read_uint16(class == ELFCLASS32 ? ((Elf32_Ehdr *) ehdr)->e_shnum : ((Elf64_Ehdr *) ehdr)->e_shnum, endian)
#define EH_SHSTRNDX(ehdr, class, endian) read_uint16(class == ELFCLASS32 ? ((Elf32_Ehdr *) ehdr)->e_shstrndx : ((Elf64_Ehdr *) ehdr)->e_shstrndx, endian)

#define SH_INDEX(addr, i, class) (class == ELFCLASS32 ? ((void *) ((Elf32_Shdr *) addr + i)) : ((void *) ((Elf64_Shdr *) addr + i)))
#define SH_OFFSET(shdr, class, endian) (class == ELFCLASS32 ? read_uint32(((Elf32_Shdr *) shdr)->sh_offset, endian) : read_uint64(((Elf64_Shdr *) shdr)->sh_offset, endian))
#define SH_SIZE(shdr, class, endian) (class == ELFCLASS32 ? read_uint32(((Elf32_Shdr *) shdr)->sh_size, endian) : read_uint64(((Elf64_Shdr *) shdr)->sh_size, endian))
#define SH_TYPE(shdr, class, endian) read_uint32(class == ELFCLASS32 ? ((Elf32_Shdr *) shdr)->sh_type : ((Elf64_Shdr *) shdr)->sh_type, endian)
#define SH_NAME(shdr, class, endian) read_uint32(class == ELFCLASS32 ? ((Elf32_Shdr *) shdr)->sh_name : ((Elf64_Shdr *) shdr)->sh_name, endian)
#define SH_FLAGS(shdr, class, endian) (class == ELFCLASS32 ? read_uint32(((Elf32_Shdr *) shdr)->sh_flags, endian) : read_uint64(((Elf64_Shdr *) shdr)->sh_flags, endian))

#endif