/*****************************************************************************
*  C Solution to "How Many Zeroes?" from the                                 *
*                                                                            *
*       Seventh Annual UCF ACM UPE High School Programming Tournament        *
*                               May 15, 1993                                 *
*                                                                            *
*  This program computes the number of zeroes at the end of the decimal      *
*  expansion of the factorial of a given number.  Note that a zero occurs    *
*  at the end of a decimal expansion for every factor of 10 of the number,   *
*  or for every factor of 2*5.  Now, there are always more factors of 2 than *
*  of 5 for a number, so the number of fives must be the number of 2*5's     *
*  which are factors of the number.  Therefore, we simply count the number   *
*  of factors of 5 of the factorial, which gives us the number of zeroes at  *
*  the end.                                                                  *
*****************************************************************************/
#include <stdio.h>

void main( void )
{
    FILE *infile;    /* Input file                                   */
    int n,           /* As defined in problem; we are considering n! */
        i,           /* Loop variable                                */
        k,           /* Used to determine the number of factors of 5 */
        num_zeroes;  /* Number of zeroes at the end of n!            */

    infile = fopen( "zeroes.in", "r" );

    while( fscanf( infile, "%d", &n ) != EOF )
    {
        num_zeroes = 0;

        /* Loop for each number from 1 to n and determine the number of */
        /* factors of 5 in each one.  There is a subtlety here:  the    */
        /* loop indices are 0 to n-1, but k is always set to i+1 at the */
        /* beginning of the loop, so k goes from 1 to n.  The reason    */
        /* for this is to avoid overflowing the integer variable i.     */
        /* If the loop were coded from 1 to n, then on the last         */
        /* iteration when n is 32767 (maxint), the increment of i will  */
        /* overflow and i will be set to a negative value.  This will   */
        /* be done before the exit condition is tested, and hence the   */
        /* loop will never terminate.                                   */
        for( i=0; i<n; i++ )
        {
            k = i+1;

            /* Count the number of factors of 5 in this integer */
            while( (k % 5 == 0) && (k>0) )
            {
                num_zeroes++;
                k = k / 5;
            }
        }
        if( num_zeroes == 1 )
            printf( "There is 1 zero at the end of %d!.\n", n );
        else
            printf( "There are %d zeroes at the end of %d!.\n", num_zeroes, n );
    }

    fclose( infile );
}