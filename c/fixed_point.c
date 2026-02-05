#include <stdio.h>

/* 
   This program is to demonstrate how to do fixed point math
   using 32bit integers 16:16.
   Fixed point math is basically made up of two sides of a double word.

   A double word is made up of 4 bytes.    
   example:
   32bit integer, 2 words or 4 bytes (each byte cotains 8 bits, 
      so 4 bytes * 8bits = 32bits).
         1 bytes = 8 bits
         0000 0000 0000 0000 0000 0000 0000 0100 
         --------- high word:low word  _________ 
         high byte                     low byte  

   The high part is the whole/integer value, the low part is the
   fractional/decimal value.
   
   Why bother with fixed point math, is it a waste of time?
   
   case 1:
   There are some processors that do not support a floating point unit,
   an FPU.  The Intel StrongARM 206mhz doesn't have a FPU, so this is one
   case it is useful.
   
   case 2:
   A computer's CPU can do binary shifts very fast, so for optimization
   you can use fixed point math where applicable.  Don't just use fixed 
   pointed math, use it where necessary.  Compilers can do very good
   optimization and in some cases it's not too useful to use fixed point
   math. 
   
   --------------------------------------------------------
   Change log | date |
   --------------------------------------------------------
   Paul Cardwell | 04-21-2002 | Original code
 */

/*
 * x and y are fixed 16:16 integers - fixed math
 * 65536 = 16bit.
 * 32767.65535 = max int : max frac
 */
#define fm_add(x,y)	(x + y)  	// add
#define fm_sub(x,y)	(x - y)  	// substract
#define fm_frac(x)	(x & 0xffff) 	// set 16bit fractional part, where x is whole number
#define fm_mul(x,y)	((x * y) >> 16) // multiply
#define fm_div(x,y)	((x << 16) / y) // divide
#define fm_setint(x)	(x << 16)	// multiply x by 65536 or x << 16 (same) to convert into 16 point fixed
#define fm_getint(x)	(x >> 16) 	// get the 16bit integer part
#define fm_setfrac(x)	(x & 0xffff) 	// set 16bit fractional part, where x is whole number
#define fm_getfrac(x)	(fm_frac(x)) 	// get the 16bit fractional part

int main(void)
{
  unsigned long x, y, speed;
  unsigned long answer;
  
  x = fm_setint(25);
  y = fm_setint(2);
  
  speed = 5;
  
  /*
   * 16:16 fixed point math has
   * a max high byte of 32767 : and low byte 65535..thus
   *                    32767.65535 in float (x.y)
   *
   */
  
  // lets do some addition
  //
  // answer = x + y + fm_frac(speed);  // should end up 27.5
  answer = fm_add(x,y) + fm_frac(speed);  // should end up 27.5

  // first, print out whole number, followed by the fractional part
  printf("%ld + %ld = %ld.%ld\n",
                               fm_getint(x),
                               fm_getint(y),
                               fm_getint(answer),
                               fm_getfrac(answer));

  // lets do some multiplication
  //
  answer = fm_mul(x,y) + fm_frac(speed);  // should end up 50.5

  // first, print out whole number, followed by the fractional part
  printf("%ld * %ld = %ld.%ld\n",
                               fm_getint(x),
                               fm_getint(y),
                               fm_getint(answer),
                               fm_getfrac(answer));
  return 1;
}