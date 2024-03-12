/**
 * @file format_string.c
 * Simple program that is vulnerable to a format-string attack.
 *
 * @author Mathias Payer <mathias.payer@nebelwelt.net>
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void foo(char *prn) {
  char text[512];
  bzero(text, 512);
  strcpy(text, prn);
  printf(text);
#if !defined(MAKEITEASY)
  printf("nice redirect possible\n");
#endif
}

#if defined(MAKEITEASY)
void not_called() {
  printf("\nwe are now behind enemy lines...\n");
  system("/bin/sh");
  exit(1);
}
#else
void not_called() {
  system("echo hi there");
}
#endif

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Not enough arguments\n");
    exit(1);
  }

  printf("main: %p foo: %p, argv[1]: %p not_called: %p rip: %p\n", &main, &foo,
         argv[1], &not_called, ((unsigned long*)__builtin_frame_address(0)+1) );

  foo(argv[1]);
  printf("\nReturned safely\n");
  return 0;
}
