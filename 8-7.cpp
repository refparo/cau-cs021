#include <cstdio>

int main() {
  int bracket = 0;
  char c;
  while ((c = getchar()) != -1)
    switch (c) {
    case '(': bracket++; break;
    case ')':
      bracket--;
      if (bracket < 0) goto exit;
    }
exit:
  if (bracket != 0) printf("false");
  else printf("true");
  return 0;
}
