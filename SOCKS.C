/*****************************************************************************
*  C Solution to "Dave's Socks" from the                                     *
*                                                                            *
*       Seventh Annual UCF ACM UPE High School Programming Tournament        *
*                               May 15, 1993                                 *
*                                                                            *
*****************************************************************************/
/****************************************************************************
*  The solution is as follows:
*    Find the color, say C1, that has the maximum instances (socks).
*    Find the color, say C2, that has the next maximum (second maximum) of
*    instances (socks).
*    Pair one sock of color C1 with one sock of C2.
*    Repeat the above for the remaining socks.
*    Iff all the socks CANNOT be paired as described above, then there exists
*    no solution, i.e., Dave can't do it!
*
*    Note that using the above algorithm, we need to carry out the above
*    process ONCE WITHOUT printing the pairings in order to find out if
*    at all a solution exists, and if one exists, then carry out the process
*    AGAIN, this time printing the pairings.
****************************************************************************/

#include <stdio.h>

/* Maximum number of colors */
#define MAX_N 15

/* Maximum color name length, plus one for the null character */
#define MAX_STR_LEN (20+1)

/* Boolean constants for readability */
#define TRUE  (1)
#define FALSE (0)

/* Used to signal whether to print pairings while processing */
#define DONT_PRINT 0
#define PRINT 1

/* Define a String type since C has none */
typedef char STRING[ MAX_STR_LEN ];

/* Array of names of colors */
STRING colors[ MAX_N ];

/* Number of Colors in the current set */
int num_of_colors;

/* Array containing number of instances of each color */
int numbers[ MAX_N ];

/* Temporary array containing number of instances of each color. */
/* This array is used as a working array in the pairing process  */
int work_numbers[ MAX_N ];

/****************************************************************************
*  Returns the index of the color that contains the maximum number of socks
*  currently, given by the 'work_numbers' array.
*  It ignores the color that has zero number of socks.
*  If no such color exists, i.e., all the socks are exhausted, it returns -1.
****************************************************************************/
int FindFirstMax( void )
{
    int max_index = -1;
    int each_color;

    for( each_color = 0; each_color < num_of_colors; each_color++ )
    {
        if( work_numbers[ each_color ] > 0 )
        {
            if( max_index == -1 ||
                work_numbers[ each_color ] > work_numbers[ max_index ] )
                max_index = each_color;
        }
    }

    return max_index;
}

/****************************************************************************
*  Returns the index of the color that has the second maximum socks currently
*  as given in the 'work_numbers' array.
*  It gets the index of the first maximum as an argument, so that it can find
*  the second maximum easily.
*  Again, colors with zero socks are ignored.
****************************************************************************/
int FindSecondMax( int first_max_index )
{
    int max_index = -1;
    int each_color;

    for( each_color = 0; each_color < num_of_colors; each_color++ )
    {
        if( each_color != first_max_index &&
            work_numbers[ each_color ] > 0 )
        {
            if( max_index == -1 ||
                work_numbers[ each_color ] > work_numbers[ max_index ] )
                max_index = each_color;
        }
    }

    return max_index;
}

/****************************************************************************
*  Returns TRUE if a solution exists, FALSE otherwise.
*  if the argument 'print_pairings' is TRUE, then the pairings are printed as
*  the matching algorithm proceeds.
****************************************************************************/
int CanMatch( int print_pairings )
{
    int done = FALSE;
    int error_found = FALSE;

    while( !error_found && !done )
    {
        int first_max_index, second_max_index;

        first_max_index = FindFirstMax();
        if( first_max_index == -1 )
            done = TRUE;
        else
        {
            second_max_index = FindSecondMax( first_max_index );
            if( second_max_index == -1 )
                error_found = TRUE;
            else
            {
                work_numbers[ first_max_index ]--;
                work_numbers[ second_max_index ]--;
                if( print_pairings )
                {
                    printf( "%s %s\n",
                            colors[ first_max_index ],
                            colors[ second_max_index ] );
                }
            }
        }
    }

    return !error_found;
}

/****************************************************************************
*  Applies the above described algorithm on several data sets.
****************************************************************************/
main( void )
{
    FILE *inf = fopen( "socks.in", "r" );

    while( fscanf( inf, "%d", &num_of_colors ) == 1 )
    {
        int each_color;

        for( each_color = 0; each_color < num_of_colors; each_color++ )
        {
            fscanf( inf, "%d%s",
                    &numbers[ each_color ],
                    colors[ each_color ] );
            work_numbers[ each_color ] = numbers[ each_color ];
        }

        if( !CanMatch( DONT_PRINT ) )
            printf( "Dave can't do it.\n" );
        else
        {
            for( each_color = 0; each_color < num_of_colors; each_color++ )
                work_numbers[ each_color ] = numbers[ each_color ];

            CanMatch( PRINT );
        }

        printf("\n");
    }

    return 0;
}

/*** End of file ***/
