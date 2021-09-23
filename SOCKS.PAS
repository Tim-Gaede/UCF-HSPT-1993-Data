(*****************************************************************************
*  Pascal Solution to "Dave's Socks" from the                                *
*                                                                            *
*       Seventh Annual UCF ACM UPE High School Programming Tournament        *
*                               May 15, 1993                                 *
*                                                                            *
*****************************************************************************)
(****************************************************************************
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
****************************************************************************)
Program socks;

Const
    (* Maximum number of colors *)
    MAX_N = 15;

    (* Used to signal whether to print pairings while processing *)
    DONT_PRINT = FALSE;
    PRINT = TRUE;
Var
    (* Array of names of colors *)
    colors : Array[ 1..MAX_N ] of String;

    (* Number of Colors in the current set *)
    num_of_colors : Integer;

    (* Array containing number of instances of each color *)
    numbers,

    (* Temporary array containing number of instances of each color. *)
    (* This array is used as a working array in the pairing process  *)
    work_numbers : Array[ 1..MAX_N ] of Integer;

    inf : Text;

    dummy : Boolean;

(****************************************************************************
*  Returns the index of the color that contains the maximum number of socks
*  currently, given by the 'work_numbers' array.
*  It ignores the color that has zero number of socks.
*  If no such color exists, i.e., all the socks are exhausted, it returns -1.
****************************************************************************)
Function FindFirstMax : Integer;
Var
    max_index,
    each_color : Integer;
Begin
    max_index := -1;

    For each_color := 1 To num_of_colors Do Begin
        If( work_numbers[ each_color ] > 0 ) Then Begin
            If( ( max_index = -1 ) OR
                ( work_numbers[ each_color ] > work_numbers[ max_index ] ) ) Then
                max_index := each_color;
        End;
    End;

    FindFirstMax := max_index;
End;

(****************************************************************************
*  Returns the index of the color that has the second maximum socks currently
*  as given in the 'work_numbers' array.
*  It gets the index of the first maximum as an argument, so that it can find
*  the second maximum easily.
*  Again, colors with zero socks are ignored.
****************************************************************************)
Function FindSecondMax( first_max_index : Integer ) : Integer;
Var
    max_index,
    each_color : Integer;
Begin
    max_index := -1;

    For each_color := 1 To num_of_colors Do Begin
        If( ( each_color <> first_max_index ) AND
            ( work_numbers[ each_color ] > 0 ) ) Then Begin
            If( ( max_index = -1 ) OR
                ( work_numbers[ each_color ] > work_numbers[ max_index ] ) ) Then
                max_index := each_color;
        End;
    End;

    FindSecondMax := max_index;
End;

(****************************************************************************
*  Returns TRUE if a solution exists, FALSE otherwise.
*  if the argument 'print_pairings' is TRUE, then the pairings are printed as
*  the matching algorithm proceeds.
****************************************************************************)
Function CanMatch( print_pairings : Boolean ) : Boolean;
Var
    done : Boolean;
    error_found : Boolean;
    first_max_index,
    second_max_index : Integer;
Begin
    done := FALSE;
    error_found := FALSE;

    While( (NOT error_found) AND (NOT done) ) Do Begin
        first_max_index := FindFirstMax;
        If( first_max_index = -1 ) Then Begin
            done := TRUE;
        End Else Begin
            second_max_index := FindSecondMax( first_max_index );
            If( second_max_index = -1 ) Then Begin
                error_found := TRUE;
            End Else Begin
                DEC( work_numbers[ first_max_index ] );
                DEC( work_numbers[ second_max_index ] );
                If( print_pairings ) Then Begin
                    writeln( colors[ first_max_index ], ' ',
                             colors[ second_max_index ] );
                End;
            End;
        End;
    End;

    CanMatch := NOT error_found;
End;

(****************************************************************************
*  Reads in next one set from the input file.
****************************************************************************)
Procedure ReadInColors;
Var
    each_color : Integer;
    dummy_char : char;
Begin
    Read( inf, num_of_colors );
    For each_color := 1 To num_of_colors Do Begin
        Readln( inf, numbers[ each_color ], dummy_char, colors[ each_color ] );
    End;
End;

(****************************************************************************
*  Applies the above described algorithm on several data sets.
****************************************************************************)
Begin (* Main *)
    Assign( inf, 'socks.in' );
    Reset( inf );

    While( NOT EOF(inf) ) Do Begin
        ReadInColors;
        work_numbers := numbers;

        If( NOT CanMatch( DONT_PRINT ) )  Then Begin
            Writeln( 'Dave can''t do it.' );
        End Else Begin
            work_numbers := numbers;
            dummy := CanMatch( PRINT );
        End;

        Writeln;
    End;
End.

(*** End of file ***)
