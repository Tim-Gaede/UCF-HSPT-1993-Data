(*****************************************************************************
*  Pascal Solution to "How Many Zeroes?" from the                            *
*                                                                            *
*       Seventh Annual UCF ACM UPE High School Programming Tournament        *
*                               May 15, 1993                                 *
*                                                                            *
*  This program computes the number of zeroes at the end of the decimal      *
*  expansion of the factorial of a given number.  Note that a zero occurs    *
*  at the end of a decimal expansion for every factor of 10 of the number,   *
*  or for every factor of 2*5.  Now, there are always more factors of 2 than *
*  of 5 for a number, so the number of fives must be the number of 2*5's     *
*  which are factors of the number.  Therefore, we simply count the number   *
*  of factors of 5 of the factorial, which gives us the number of zeroes at  *
*  the end.                                                                  *
*****************************************************************************)
program Zeroes( input, output );

var
    infile : text;         (* Input file                                   *)
    n,                     (* As defined in problem; we are considering n! *)
    i,                     (* Loop variable                                *)
    k,                     (* Used to determine the number of factors of 5 *)
    num_zeroes : integer;  (* Number of zeroes at the end of n!            *)

begin
    assign( infile, 'zeroes.in' );
    reset( infile );

    while not eof( infile ) do
    begin
        num_zeroes := 0;
        readln( infile, n );

        (* Loop for each number from 1 to n and determine the number of *)
        (* factors of 5 in each one.                                    *)
        for i := 1 to n do
        begin
            k := i;

            (* Count the number of factors of 5 in this integer *)
            while (k mod 5 = 0) and (k>0) do
            begin
                inc( num_zeroes );
                k := k div 5;
            end;
        end;
        if num_zeroes = 1 then
            writeln( 'There is 1 zero at the end of ', n:1, '!.' )
        else
            writeln( 'There are ', num_zeroes:1, ' zeroes at the end of ', n:1, '!.' );
    end;

    close( infile );
end.