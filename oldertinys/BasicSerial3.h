/* Optimized half-duplex serial uart implementation
 * timing within 2% using at 230.4kbps @ 8Mhz 
 * @author: Ralph Doncaster
 * @version: $Id$
 */

#define BAUD_RATE 115200

#ifdef F_CPU
  /* account for integer truncation by adding 3/2 = 1.5 */
  #define TXDELAY (((F_CPU/BAUD_RATE)-7 +1.5)/3)
#else
  #error CPU frequency F_CPU undefined
#endif

extern void TxTimedByte(char, char);