## Project Overview

Custom `scanf()` function in C handling `%c`, `%s`, `%d`, and `%f` format specifiers.

## Functions

| Function           | Description                                           |
|--------------------|-------------------------------------------------------|
| `_scanf(char *str, ...)` | Custom `scanf()` implementation.                   |
| `error(char *str)` | Prints error message and exits.                      |
| `find(const char *str, char c)` | Finds character in string.                          |
| `is_integer(const char *str)` | Checks if string is an integer.                      |
| `custom_string(char *str, char *afterChrcs, char *token)` | Processes strings with format specifiers.             |

## Usage

```bash
gcc main.c scanf.c -o main
./main
```

## Licence

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
