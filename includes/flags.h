#ifndef FLAGS_H
#define FLAGS_H

// Flags
#define FLAGS_NB 6
#define FLAGS "agurph"
#define LONG_FLAGS (char *[]) { "debug-syms", "extern-only", "undefined-only", "reverse-sort", "no-sort", "help" }

// Flags Mask
#define DEBUG_SYMS		1 << 0
#define EXTERN_ONLY		1 << 1
#define UNDEFINED_ONLY	1 << 2
#define REVERSE_SORT	1 << 3
#define NO_SORT			1 << 4
#define HELP			1 << 5

#define USAGE "\
Usage: nm [option(s)] [file(s)]\n\
 List symbols in [file(s)] (a.out by default).\n\
 The options are:\n\
  -a, --debug-syms       Display debugger-only symbols\n\
  -g, --extern-only      Display only external symbols\n\
  -p, --no-sort          Do not sort the symbols\n\
  -r, --reverse-sort     Reverse the sense of the sort\n\
  -u, --undefined-only   Display only undefined symbols\n\
  -h, --help             Display this information\n\
"

#endif