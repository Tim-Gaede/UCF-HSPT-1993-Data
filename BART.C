/*****************************************************************************
*  C Solution to "Bart Stays After School" from the                          *
*                                                                            *
*       Seventh Annual UCF ACM UPE High School Programming Tournament        *
*                               May 15, 1993                                 *
*                                                                            *
*****************************************************************************/
#include <stdio.h>

#define SENTENCE_LENGTH 100

void main( void )
{
    FILE *f = fopen( "bart.in", "r" );

    int n, i;

    char sentence[SENTENCE_LENGTH];

    while ( !feof( f ) )
    {
        /* Temporarily put number in string */
        fgets( sentence, SENTENCE_LENGTH, f );
        sscanf( sentence, "%d", &n );

        /* This one is the real sentence */
        fgets( sentence, SENTENCE_LENGTH, f );
        if ( sentence[strlen( sentence ) - 1] == '\n' )
        {
            sentence[strlen( sentence ) - 1] = '\0';
        }

        for ( i = 0; i < n; i++ )
        {
            printf( "%s\n", sentence );
        }

        printf( "\n" );
    }

    fclose( f );
}
