/*****************************************************************************
*  C Solution to "Found in the Shuffle" from the                             *
*                                                                            *
*       Seventh Annual UCF ACM UPE High School Programming Tournament        *
*                               May 15, 1993                                 *
*                                                                            *
*****************************************************************************/
/************************************************************************\

   Problem:     Found in the Shuffle

   File Name:   deck.c

   Solution By: Gregg Hamilton

\************************************************************************/

#include <stdio.h>
#include <string.h>

/* This string is used in determining if two cards are in sequence. */
const char sequence[14] = "A23456789TJQK" ;

void main( void )
{
   char deck[106] ; /* Stores the list of cards                       */
   FILE *inFile ;   /* Input file handle                              */
   char *p,         /* Temporary pointer for reading in cards         */
        cur_suit,   /* Current same-suit sequence suit                */
        *cur_pos ;  /* Current position in sequence string            */
   int  count,      /* Same-suit and Ascending sequence count         */
        index,      /* Position in deck                               */
        best ;      /* Longest Same-Suit or Ascending sequence so far */

   /* Set up input file. */

   inFile = fopen( "deck.in", "r" ) ;

   /* Loop through all input data. */

   while( fgets( deck, 54, inFile ) != NULL ) {

      /* There should not be any blank lines at the bottom of the input    */
      /* file, but it's better to be safe than sorry!  The following check */
      /* will take care of them.                                           */

      if( strlen( deck ) < 53 ) {
         continue ;
      }

      /* Read in the rest of the input deck and merge it into one line */
      /* (this will eliminate a lot of code to deal with special cases */
      /* later).                                                       */

      p = deck + 52 ;
      fgets( p, 54, inFile ) ;

      /* Initialization for longest same-suit search.  Start index at */
      /* second suit character, and consider the first suit character */
      /* to be a same-suit sequence of length one.                    */

      index = 3 ;
      cur_suit = deck[1] ;
      count = 1 ;
      best = 0 ;

      /* Loop through the suit characters in the deck */

      while( index <= 103 ) {

         /* If the suit matches the current suit, increment the count. */

         if( deck[index] == cur_suit ) {
            count++ ;

         } else {

            /* Start of a new same-suit sequence, save the last count if it's the     */
            /* best so far, and reinitialize the current suit and count. */

            if( count > best ) {
               best = count ;
            }
            cur_suit = deck[index] ;
            count = 1 ;
         }

         /* Increment to the next suit character. */

         index += 2 ;
      }

      /* Check to see if the final count was the best. */

      if( count > best ) {
          best = count ;
      }

      /* Print the longest same-suit sequence. */

      printf( "Longest same-suit sequence: %d\n", best ) ;

      /* Initialization for longest ascending sequence search.  Start index at the  */
      /* second "value" character, and consider the first "value" to                */
      /* be a longest ascending sequence of length one.                             */

      index = 2 ;
      cur_pos = strchr( sequence, deck[0] ) ;
      count = 1 ;
      best = 0 ;

      /* Loop through the "value" characters in the deck */

      while( index <= 102 ) {

         /* If the position of the "value" in the sequence string is    */
         /* one past the position of the last "value", increment the    */
         /* current sequence position and the ascending sequence count. */

         if( strchr( sequence, deck[index] ) - 1 == cur_pos ) {
            cur_pos++ ;
            count++ ;

         /* This take care of the special case of a King to Ace */
         /* sequence continuation.                              */

         } else if( *cur_pos == 'K' && deck[index] == 'A' ) {
            cur_pos = sequence ;
            count++ ;

         /* Start of a new ascending sequence, save the last count if it's the */
         /* best so far, and reinitialize the current "value"                  */
         /* position and count.                                                */

         } else {
            if( count > best ) {
               best = count ;
            }
            count = 1 ;
            cur_pos = strchr( sequence, deck[index] ) ;
         }

         /* Increment to the next "value" character. */

         index += 2 ;
      }

      /* Check to see if the final count was the best. */

      if( count > best ) {
          best = count ;
      }

      /* Print the longest ascending sequence. */

      printf( "Longest ascending sequence: %d\n\n", best ) ;

   } /* End of while fgets != NULL */
}

