## Pre-Lab preparation

1. Fill in the following table and enter the number of bits and numeric range for the selected data types defined by C.

   | **Data type** | **Number of bits** | **Range** | **Description** |
   | :-: | :-: | :-: | :-- |
   | `uint8_t`  | 8 | 0, 1, ..., 255 | Unsigned 8-bit integer |
   | `int8_t`   | __8__ | __-128, ..., 127__ | __Signed 8-bit integer__ |
   | `uint16_t` | __16__ | __0, 1, ..., 65536__ | __Unsigned 16-bit integer__ |
   | `int16_t`  | __16__ | __-32768, ..., 32767__ | __Signed 16-bit integer__ |
   | `float`    | __32__ | -3.4e+38, ..., 3.4e+38 | Single-precision floating-point |
   | `void`     | -- | -- | *Incomplete type that cannot be completed* |

2. Any function in C contains a declaration (function prototype), a definition (block of code, body of the function); each declared function can be executed (called). Study [this article](https://www.programiz.com/c-programming/c-user-defined-functions) and complete the missing sections in the following user defined function declaration, definition, and call.

   ```c
   #include <avr/io.h>

   // Function declaration (prototype)
   uint16_t calculate(uint8_t, uint8_t);

   int main(void)
   {
      uint8_t a = 210;
      uint8_t b = 15;
      uint16_t c;

      // Function call
      c = calculate(a, b);

      // Infinite loop
     while (1) ;

      // Will never reach this
      return 0;
   }

   // Function definition (body)
   uint16_t calculate(uint8_t x, uint8_t y)
   {
      uint16_t result;    // result = x^2 + 2xy + y^2

      result = x*x;
      result += 2 * x * y;
      result += y * y;
      return result;
   }
   ```

3. Find the difference between a variable and pointer in C. What mean notations `*variable` and `&variable`?

A `variable` in C is a named space in memory where we can store a data.
Notation `*variable` is called `*pointer` and it can reserves defined space in memory. It contains address of variable not its value.
Notation `&variable` returns address of variable where is stored in memory.
