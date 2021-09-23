(*****************************************************************************
*  Pascal Solution to "It Makes No Difference in the End" from the           *
*                                                                            *
*       Seventh Annual UCF ACM UPE High School Programming Tournament        *
*                               May 15, 1993                                 *
*                                                                            *
*****************************************************************************)
program subtract;

var
    f: text;

    num: array[1..5] of integer;


(** This function determines whether **)
(** the four numbers are all zeroes. **)

function all_zeroes: boolean;

var
    zero: boolean;

    i: integer;

begin
    zero := true;

    for i := 1 to 4 do
    begin
        if ( num[i] <> 0 ) then
        begin
            zero := false;
        end;
    end;

    all_zeroes := zero;
end;


(** This procedure writes out the sequence **)
(** and updates it using the differences.  **)

procedure write_and_update;
var
    i: integer;

begin
    num[5] := num[1];     (* This makes finding differences easier *)

    for i := 1 to 4 do
    begin
        write( num[i]:5 );
        num[i] := abs( num[i] - num[i+1] );
    end;

    writeln;
end;


(*** Main program ***)
begin
    assign( f, 'subtract.in' );
    reset( f );

    while not eof( f ) do
    begin
        readln( f, num[1], num[2], num[3], num[4] );

        repeat

            write_and_update;

        until all_zeroes;

        writeln;
    end;

    close( f );
end.
