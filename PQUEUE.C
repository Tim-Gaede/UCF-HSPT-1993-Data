/*****************************************************************************
*  C Solution to "Mind Your PQs" from the                                    *
*                                                                            *
*       Seventh Annual UCF ACM UPE High School Programming Tournament        *
*                               May 15, 1993                                 *
*                                                                            *
*  This program implements a PQ, with operations INSERT and REMOVE, as       *
*  defined in the problem statement.  A PQ is implemented as an unordered    *
*  list.  To insert a value, we add the value to the end of the list.  To    *
*  remove the smallest value, we scan for the smallest value, remove it, and *
*  then compress the list to fill in the hole created by removing the value. *
*****************************************************************************/
#include <stdio.h>
#include <string.h>

#define MAX_IN_PQ    100   /* Maximum number of elements in the PQ */
#define MAX_STRING    10   /* Maximum size of an input command     */
#define MAXINT     32767   /* Maximum integer in the PQ            */

void main( void )
{
    int the_pq[MAX_IN_PQ],    /* The PQ structure                          */
        num_in_pq,            /* Number of elements currently in the PQ    */
        i,                    /* Looping variable                          */
        min,                  /* Minimum element in the PQ                 */
        index,                /* Location of the minimum element in the PQ */
        end_of_file=0;        /* BOOLEAN:  At the end of the input file?   */
    char command[MAX_STRING]; /* Input command                             */
    FILE *infile;             /* Input file                                */

    infile = fopen( "pqueue.in", "r" );

    while( !end_of_file )
    {
        command[0] = '\0';

        /* Start each data set with an empty PQ */
        num_in_pq = 0;
        while( !end_of_file && strcmp( command, "END" ) != 0 )
        {
            end_of_file = fscanf( infile, "%s", command ) == EOF;
            if( !end_of_file )
            {
                if( strcmp( command, "INSERT" ) == 0 )
                {
                    /* Insert a value into the PQ */
                    fscanf( infile, "%d", &the_pq[num_in_pq] );
                    num_in_pq++;
                }
                else if( strcmp( command, "REMOVE" ) == 0 )
                {
                    /* Find the smallest element in the PQ */
                    min = MAXINT;
                    for( i=0; i<num_in_pq; i++ )
                    {
                        if( the_pq[i] < min )
                        {
                            min = the_pq[i];
                            index = i;
                        }
                    }

                    /* Remove the smallest element from the PQ */
                    num_in_pq--;
                    for( i=index; i<num_in_pq; i++ )
                        the_pq[i] = the_pq[i+1];

                    /* Output the removed element */
                    printf( "%d\n", min );
                }
            }
        }
        printf( "\n" );
    }

    fclose( infile );
}