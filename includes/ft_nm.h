#ifndef FT_NM_H
#define FT_NM_H

#include <libft.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdio.h>
#include <sys/elf.h>


// FLAG's MASKS
#define DEBUG_SYMS		1 << 0 // -a, --debug-syms
#define EXTERN_ONLY		1 << 1 // -g, --extern-only
#define UNDEFINED_ONLY	1 << 2 // -u, --undefined-only
#define REVERSE_SORT	1 << 3 // -r, --reverse-sort
#define NO_SORT			1 << 4 // -p, --no-sort

// flags.c
int	parse_flags(int argc, char *argv[]);

#endif