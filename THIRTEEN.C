/*****************************************************************************
*  C Solution to "Rot13 Encryption" from the                                 *
*                                                                            *
*       Seventh Annual UCF ACM UPE High School Programming Tournament        *
*                               May 15, 1993                                 *
*                                                                            *
*****************************************************************************/
#include <stdio.h>
#include <ctype.h>

void main( void )
{
    int c;

    FILE *f = fopen( "thirteen.in", "r" );

    while( !feof( f ) ) 
    {
        c = fgetc( f );

        if ( toupper( c ) >= 'A' && toupper( c ) <= 'M' )
        {
            putchar( c + 13 );
        }
        else if ( toupper( c ) >= 'N' && toupper( c ) <= 'Z' )
        {
            putchar( c - 13 );
        }
        else
        {
            putchar( c );
        }

    }

    fclose( f );
}
