// Placed in the public domain 2021 by Sam Trenholme
// This is a simple program which, given the hex code of a program
// (e.g. the output of bin2hex), convert it in to a binary file.
// Input is standard input; output is standard output
// # can be used to put comments in the hex code
// Anything besides [0-9a-fA-F] is ignored by the parser

#include <stdio.h>
int main() {
  int a, b, c;
  c = 0;
  b = 0;
  while(!feof(stdin)) {
    a = getc(stdin);
    if(feof(stdin)) {
      return 0;
    }
    if(a >= '0' && a <= '9') {
       b <<= 4;
       b = b | (a - '0');
       c++;
       if(c > 1) { c = 0; printf("%c",b); }
    } else if(a >= 'a' && a <= 'f') {
       b <<= 4;
       b = b | (10 + a - 'a');
       c++;
       if(c > 1) { c = 0; printf("%c",b); }
    } else if(a >= 'A' && a <= 'F') {
       b <<= 4;
       b = b | (10 + a - 'A');
       c++;
       if(c > 1) { c = 0; printf("%c",b); }
    } else if(a == '#') { // Simple comments
      while(a != 10 && a != 13) {
        a = getc(stdin);
        if(feof(stdin)) {
          return 0;
        }
      }
    }
  }
  return 0;
}
