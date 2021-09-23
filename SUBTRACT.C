/*****************************************************************************
*  C Solution to "It Makes No Difference in the End" from the                *
*                                                                            *
*       Seventh Annual UCF ACM UPE High School Programming Tournament        *
*                               May 15, 1993                                 *
*                                                                            *
*****************************************************************************/
#include <stdio.h>
#include <math.h>

#define FALSE 0
#define TRUE  1

#define BUFFER_SIZE  80


static int num[5];


int all_zeroes( void )
{
    int i, zero = TRUE;

    for ( i = 0; i < 4; i++ )
    {
        if ( num[i] != 0 )
        {
            zero = FALSE;
        }
    }

    return( zero );
}


void write_and_update( void )
{
    int i;

    num[4] = num[0];

    for ( i = 0; i < 4; i++ )
    {
        printf( "%5d", num[i] );
        num[i] = abs( num[i]-num[i+1] );
    }
    printf( "\n" );
}


void main( void )
{
    FILE *f = fopen( "subtract.in", "r" );

    char line[BUFFER_SIZE];


    while ( !feof( f ) )
    {
        fgets( line, BUFFER_SIZE, f );
        sscanf( line, "%d %d %d %d", num, num+1, num+2, num+3 );

        do
        {
            write_and_update();

        } while ( !all_zeroes() );

        printf( "\n" );
    }

    fclose( f );
}
