/*
Brainf*ck 解释器（第 1 组供题）

Brainf*ck 是一种只由 8 种运算符构成，但是图灵完全的极简编程语言。

这种语言基于一个简单的机器模型：一个无限大的字符数组和一个指针。初始状态下，字符数组初始化为 0，指针指向数组开头。接下来，机器依次执行程序中的指令。八种指令的效果如下：

- `>` 使指针 + 1；
- `<` 使指针 - 1，若指针已经在开头则不做任何操作；
- `+` 使指针指向的字符 + 1；
- `-` 使指针指向的字符 - 1；
- `.` 输出指针指向的字符；
- `,` 读取一个字符，储存到指针指向的地址；
- `[` 如果指针指向的字符为 0，就向后跳转到对应的 `]` 指令的后一指令；
- `]` 如果指针指向的字符不为 0，就向前跳转到对应的 `[` 指令的后一指令。

提示一：在程序中，无限大的数组可以实现为动态向量。

提示二：“对应的”指的是 `[` 和 `]` 一一配对。

## 输入格式

第一行是需要解释的 Brainf*ck 程序。从第二行开始，都是提供给 Brainf*ck 程序的输入。

本题保证输入的程序是合法的 Brainf*ck 程序，但对程序的长度和输入的长度不作保证。

## 样例一

输入：

```
,.
a
```

输出：

```
a
```

## 样例二

输入：

```
++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.
```

输出：
```
Hello World!

```
*/

#include <cstdio>
#include <vector>

using namespace std;

int main() {
  vector<char> program;
  char tmp;
  while ((tmp = getchar()) != '\n') program.push_back(tmp);

  vector<char> memory(1);
  int ptr = 0;
  for (int prog_ptr = 0; prog_ptr < program.size(); prog_ptr++)
    switch (program[prog_ptr]) {
    case '>':
      ptr++;
      if (ptr >= memory.size()) memory.resize(ptr + 1);
      break;
    case '<':
      if (ptr > 0) ptr--;
      break;
    case '+': memory[ptr]++; break;
    case '-': memory[ptr]--; break;
    case '.': putchar(memory[ptr]); break;
    case ',': memory[ptr] = getchar(); break;
    case '[':
      if (memory[ptr] == 0) {
        prog_ptr++;
        for (int paren = 1; paren > 0; prog_ptr++)
          switch (program[prog_ptr]) {
            case '[': paren++; break;
            case ']': paren--; break;
          }
        prog_ptr--;
      }
      break;
    case ']':
      if (memory[ptr] != 0) {
        prog_ptr--;
        for (int paren = -1; paren < 0; prog_ptr--)
          switch (program[prog_ptr]) {
            case '[': paren++; break;
            case ']': paren--; break;
          }
        prog_ptr++;
      }
      break;
    }

  return 0;
}
