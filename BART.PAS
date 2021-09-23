(*****************************************************************************
*  Pascal Solution to "Bart Stays After School" from the                     *
*                                                                            *
*       Seventh Annual UCF ACM UPE High School Programming Tournament        *
*                               May 15, 1993                                 *
*                                                                            *
*****************************************************************************)
program bart;

var
    f: text;

    n: integer;

    sentence: string;

    i: integer;


begin
    assign( f, 'bart.in' );
    reset( f );

    while not eof( f ) do
    begin
        readln( f, n );
        readln( f, sentence );

        for i := 1 to n do
        begin
            writeln( sentence );
        end;

        writeln;
    end;

    close( f );
end.
