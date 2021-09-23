(*****************************************************************************
*  Pascal Solution to "Found in the Shuffle" from the                        *
*                                                                            *
*       Seventh Annual UCF ACM UPE High School Programming Tournament        *
*                               May 15, 1993                                 *
*                                                                            *
*****************************************************************************)
(************************************************************************

   Problem:     Found in the Shuffle

   File Name:   deck.pas

   Solution By: Gregg Hamilton

 ************************************************************************)

Const

(* This string is used in determining if two cards are in sequence. *)
     sequence = 'A23456789TJQK' ;

Var

   deck     : string[104] ; (* Stores the list of cards              *)
   temp     : string[52] ;  (* Temporary string for reading in cards *)
   inFile   : text ;        (* Input file handle                     *)
   count,                   (* Sequence counter                      *)
   index,                   (* Position in deck                      *)
   best,                    (* Longest Sequence so far               *)
   cur_pos  : integer ;     (* Current position in sequence string   *)
   cur_suit : char ;        (* Current Same-Suit                     *)


Begin

   (* Set up input file. *)

   assign( inFile, 'deck.in' ) ;
   reset( inFile ) ;

   (* Loop through all input data. *)

   while not eof( inFile ) do
   Begin

      (* There should not be any blank lines at the bottom of the input    *)
      (* file, but it's better to be safe than sorry!  The following check *)
      (* will take care of them.                                           *)

      if eoln( inFile ) then
         readln( inFile )

      else
      Begin

         (* Read in an input deck and merge it into one line (this will *)
         (* eliminate a lot of code to deal with special cases later).  *)

         readln( inFile, deck ) ;
         readln( inFile, temp ) ;
         deck := deck + temp ;

         (* Initialization for longest Same-Suit Sequence search.  Start *)
         (* index at second suit character, and consider the first suit  *)
         (* character to be a Same-Suit Sequence of length one.          *)

         index := 4 ;
         cur_suit := deck[2] ;
         count := 1 ;
         best := 0 ;

         (* Loop through the suit characters in the deck *)

         while index <= 104 do
         Begin

            (* If the suit matches the current suit, increment the count. *)

            if deck[index] = cur_suit then
               inc( count )

            else
            Begin

               (* Start of a new Same-Suit Sequence, save the last count if *)
               (* it's the best so far, and reinitialize the current suit   *)
               (* and count.                                                *)

               if count > best then
                  best := count ;
               cur_suit := deck[index] ;
               count := 1 ;
            End ;

            (* Increment to the next suit character. *)

            index := index + 2 ;
         End ;

         (* Check to see if the final count was the best. *)

         if count > best then
            best := count ;

         (* Print the longest Same-Suit Sequence. *)

         writeln( 'Longest same-suit sequence: ', best:0 ) ;

         (* Initialization for longest Ascending Sequence search.      *)
         (* Start index at the second "value" character, and consider  *)
         (* the first "value" to be a Sequence of length one.          *)

         index := 3 ;
         cur_pos := pos( deck[1], sequence ) ;
         count := 1 ;
         best := 0 ;

         (* Loop through the "value" characters in the deck *)

         while index <= 103 do
         Begin

            (* If the position of the "value" in the sequence string is *)
            (* one past the position of the last "value", increment the *)
            (* current sequence position and the Sequence count.        *)

            if ( pos( deck[index], sequence ) - 1 ) = cur_pos then
            Begin
               inc( cur_pos ) ;
               inc( count ) ;
            End

            else
            Begin

               (* This take care of the special case of a King to Ace *)
               (* sequence continuation.                              *)

               if ( cur_pos = 13 ) and ( deck[index] = 'A' ) then
               Begin
                  cur_pos := 1 ;
                  inc( count ) ;
               End

               else
               Begin

                  (* Start of a new Ascending Sequence, save the last count *)
                  (* if it's the best so far, and reinitialize the current  *)
                  (* "value" position and count.                            *)

                  if count > best then
                     best := count ;
                  count := 1 ;
                  cur_pos := pos( deck[index], sequence ) ;
               End ;
            End ;

            (* Increment to the next "value" character. *)

            index := index + 2 ;
         End ;

         (* Check to see if the final count was the best. *)

         if count > best then
            best := count ;

         (* Print the longest Ascending Sequence. *)

         writeln( 'Longest ascending sequence: ', best:0 ) ;
         writeln ;

      End ; (* End of else not eoln *)
   End ; (* End of while not eof *)
End.

