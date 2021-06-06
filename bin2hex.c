// Public domain 2021 Sam Trenholme
// Given a binary stream on standard input, output the hex representation
// of that stream on standard output

#include <stdio.h>
#include <stdint.h>

int main() {
  int a, b;
  b = 0;
  while(!feof(stdin)) {
    a = getc(stdin);
    if(feof(stdin)) {
      puts("");
      return 0;
      }
    printf("%02x ",a);
    if(b++ > 16) {
      puts("");
      b = 0;
      }
   }
 puts("");
 return 0;
 }
