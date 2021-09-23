(*****************************************************************************
*  Pascal Solution to "The 15-Puzzle" from the                               *
*                                                                            *
*       Seventh Annual UCF ACM UPE High School Programming Tournament        *
*                               May 15, 1993                                 *
*                                                                            *
*****************************************************************************)
(************************************************************************

   Problem:     The 15-Puzzle

   File Name:   puzzle.pas

   Solution By: Gregg Hamilton

 ************************************************************************)

Var

   puzzle  : array[1..4, 1..4] of integer ; (* Array to store puzzle *)

   inFile  : text ;    (* Iput file handle               *)
   i, j,               (* Used for indexing and counting *)
   open_i,             (* Column position of open space  *)
   open_j,             (* Row position of open space     *)
   num     : integer ; (* Number of moves                *)
   dir     : char ;    (* Direction character            *)

Begin

   (* Set up input file. *)

   assign( inFile, 'puzzle.in' ) ;
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

         (* Read in the puzzle. *)

         for i := 1 to 4 do
         Begin
            for j := 1 to 4 do
            Begin
               read( inFile, puzzle[i][j] ) ;
               if puzzle[i][j] = 0 then
               Begin
                  open_i := i ;
                  open_j := j ;
               End ;
            End ;
            readln( inFile ) ;
         End ;

         (* Read in the number of moves. *)

         readln( inFile, num ) ;

         (* Loop through the number of moves *)

         for i := 1 to num do
         Begin

            (* Read in the move. *)

            read( inFile, dir ) ;
            readln( inFile ) ;

            (* Based on the direction, copy the contents of the position *)
            (* where the blank space is moving to the current position   *)
            (* of the space, then set the value at that position to zero *)
            (* (marking it as empty, and update the open space indicies. *)

            case dir of

               'U' : Begin
                        puzzle[open_i][open_j] := puzzle[open_i - 1][open_j] ;
                        puzzle[open_i - 1][open_j] := 0 ;
                        open_i := open_i - 1 ;
                     End ;

               'D' : Begin
                        puzzle[open_i][open_j] := puzzle[open_i + 1][open_j] ;
                        puzzle[open_i + 1][open_j] := 0 ;
                        open_i := open_i + 1 ;
                     End ;

               'L' : Begin
                        puzzle[open_i][open_j] := puzzle[open_i][open_j - 1] ;
                        puzzle[open_i][open_j - 1] := 0 ;
                        open_j := open_j - 1 ;
                     End ;

               'R' : Begin
                        puzzle[open_i][open_j] := puzzle[open_i][open_j + 1] ;
                        puzzle[open_i][open_j + 1] := 0 ;
                        open_j := open_j + 1 ;
                     End ;
            End ;
         End ;

         (* Print out the resulting board. *)

         for i := 1 to 4 do
         Begin
            for j := 1 to 4 do
            Begin
               if puzzle[i][j] = 0 then
                  write( '   ' )
               else
                  write( puzzle[i][j]:2, ' ' ) ;
            End ;
            writeln ;
         End ;
         writeln ;

      End ; (* End of else not eoln *)
   End ; (* End of while not eof *)
End.

