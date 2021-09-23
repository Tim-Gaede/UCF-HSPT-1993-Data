/*****************************************************************************
*  C Solution to "The 15-Puzzle" from the                                    *
*                                                                            *
*       Seventh Annual UCF ACM UPE High School Programming Tournament        *
*                               May 15, 1993                                 *
*                                                                            *
*****************************************************************************/
/************************************************************************\

   Problem:     The 15-Puzzle

   File Name:   puzzle.c

   Solution By: Gregg Hamilton

\************************************************************************/

#include <stdio.h>


void main( void )
{
   int  puzzle[4][4] ; /* Array to store puzzle          */
   FILE *inFile ;      /* Iput file handle               */
   int  i, j,          /* Used for indexing and counting */
        open_i,        /* Column position of open space  */
        open_j,        /* Row position of open space     */
        done = 0,      /* For control loop               */
        num ;          /* Number of moves                */
   char dir[3] ;       /* Direction character            */

   /* Set up input file. */

   inFile = fopen( "puzzle.in", "r" ) ;

   /* Loop through all input data. */

   while( !done ) {

      /* Read in the puzzle. */

      for( i = 0; i < 4 && !done; i++ ) {
         for( j = 0; j < 4; j++ ) {
            if( fscanf( inFile, "%d", &puzzle[i][j] ) != 1 ) {
               done = 1 ;
               break ;
            }
            if( puzzle[i][j] == 0 ) {
               open_i = i ;
               open_j = j ;
            }
         }
      }

      /* If done is true, we've hit the end of the input file. */

      if( !done ) {

         /* Read in the number of moves. */

         fscanf( inFile, "%d", &num ) ;

         /* Read past the end of line. */

         fgets( dir, 3, inFile ) ;

         /* Loop through the number of moves */

         for( i = 0; i < num; i++ ) {

            /* Read in the move. */

            fgets( dir, 3, inFile ) ;

            /* Based on the direction, copy the contents of the position */
            /* where the blank space is moving to the current position   */
            /* of the space, then set the value at that position to zero */
            /* (marking it as empty, and update the open space indicies. */

            switch( dir[0] ) {

               case 'U' :
                  puzzle[open_i][open_j] = puzzle[open_i - 1][open_j] ;
                  puzzle[open_i - 1][open_j] = 0 ;
                  open_i-- ;
                  break ;

               case 'D' :
                  puzzle[open_i][open_j] = puzzle[open_i + 1][open_j] ;
                  puzzle[open_i + 1][open_j] = 0 ;
                  open_i++ ;
                  break ;

               case 'L' :
                  puzzle[open_i][open_j] = puzzle[open_i][open_j - 1] ;
                  puzzle[open_i][open_j - 1] = 0 ;
                  open_j-- ;
                  break ;

               case 'R' :
                  puzzle[open_i][open_j] = puzzle[open_i][open_j + 1] ;
                  puzzle[open_i][open_j + 1] = 0 ;
                  open_j++ ;
                  break ;
            }
         }

         /* Print out the resulting board. */

         for( i = 0; i < 4; i++ ) {
            for( j = 0; j < 4; j++ ) {
               if( puzzle[i][j] == 0 ) {
                  printf( "   " ) ;
               } else {
                  printf( "%2d ", puzzle[i][j] ) ;
               }
            }
            printf( "\n" ) ;
         }
         printf( "\n" ) ;

      } /* End of if not done */
   } /* End of while not done */
}

