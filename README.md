This is a repository of miscellaneous small C programs which are too small
to make a full-blown repo for each one.

# bin2hex

Convert a binary file in to a hexadecimal representation of the file.

# hex2bin

Convert a hex file (e.g. the output of bin2hex) in to a binary file.

# entropy

Generate 160 bits of entropy as 32 ASCII bytes.  Use -DMINGW when
compiling as a native Windows binay

# Makefile

This Makefile will compile `bin2hex`, `hex2bin`, and `entropy`.  It will
also clean up build artifacts with `make clean`.  `make install` is not
supported (just copy the files to `/usr/local/bin` by hand).

