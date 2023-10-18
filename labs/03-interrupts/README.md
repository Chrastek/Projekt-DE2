## Pre-Lab preparation

Consider an *n*-bit number that we increment based on the clock signal. If we reach its maximum value and try to increase it, the value will be reset. We call this state an **overflow**. The overflow time depends on the frequency of the clock signal, the number of bits, and on the prescaler value:

![Timer overflow](images/timer_overflow.png)

> **Note:** The equation was generated by [Online LaTeX Equation Editor](https://www.codecogs.com/latex/eqneditor.php) using the following code.
>
> ```LaTeX
> t_{OVF} = \frac{1}{f_{CPU}}\cdot 2^{nbit}\cdot prescaler
> ```

1. Calculate the overflow times for three Timer/Counter modules that contain ATmega328P if CPU clock frequency is 16&nbsp;MHz. Complete the following table for given prescaler values. Note that, Timer/Counter2 is able to set 7 prescaler values, including 32 and 128 and other timers have only 5 prescaler values.

   | **Module** | **Number of bits** | **1** | **8** | **32** | **64** | **128** | **256** | **1024** |
   | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
   | Timer/Counter0 | 8  | 16u | 128u | -- | 1ms | -- | 4ms | 16ms |
   | Timer/Counter1 | 16 |  4ms | 32ms | -- | 262ms | -- | 1s | 4s |
   | Timer/Counter2 | 8  | 16u | 128u | 512u | 1ms | 2ms | 4ms | 16ms |

<a name="part1"></a>