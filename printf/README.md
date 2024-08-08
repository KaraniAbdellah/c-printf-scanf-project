# c-printf-scanf-project

A project to learn and implement `printf()` and `scanf()` functions in C.

## Project Overview

This project provides a custom implementation of the `printf()` function in C. It supports various format specifiers and demonstrates handling of integer, character, float, and string outputs.

## Functions

| Function Name      | Description                                                                                              |
|--------------------|----------------------------------------------------------------------------------------------------------|
| `_printf`          | Main function to format and print output based on format specifiers.                                     |
| `calculate_digits` | Calculates the number of digits in an integer.                                                           |
| `to_string`        | Converts an integer to a string with a specified length.                                                |
| `to_number`        | Converts a string representing a number to an integer.                                                   |
| `add_zeros`        | Adds leading zeros to a string based on the number of digits required.                                   |
| `_print_d`         | Prints an integer, handling leading zeros based on format specifiers.                                    |
| `_print_c`         | Prints a single character.                                                                             |
| `concatenate`      | Concatenates two strings with an optional decimal point in between.                                      |
| `truncation_float` | Truncates the fractional part of a float to a specified number of digits.                                |
| `get_fractional_part` | Gets the fractional part of a float as an integer.                                                        |
| `_print_f`         | Prints a float, including handling decimal places based on format specifiers.                            |
| `truncation_string`| Truncates a string to a specified number of characters.                                                   |
| `_printf_s`        | Prints a string, including truncation based on format specifiers.                                        |

## Usage

To compile and run the project:

1. Compile the code:
    ```bash
    gcc main.c printf.c -o main
    ```

2. Execute the compiled program:
    ```bash
    ./main
    ```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
