(*****************************************************************************
*  Pascal Solution to "Rot13 Encryption" from the                            *
*                                                                            *
*       Seventh Annual UCF ACM UPE High School Programming Tournament        *
*                               May 15, 1993                                 *
*                                                                            *
*****************************************************************************)
program thirteen;

var
    f: text;

    c: char;

begin
    assign( f, 'thirteen.in' );
    reset( f );

    while not eof( f ) do
    begin
        while not eoln( f ) do
        begin
            read( f, c );

            if ( upcase( c ) in ['A'..'M'] ) then
            begin
                write( chr( ord( c ) + 13 ) );
            end
            else if ( upcase( c ) in ['N'..'Z'] ) then
            begin
                write( chr( ord( c ) - 13 ) );
            end
            else
            begin
                write( c );
            end;
        end;

        readln( f );
        writeln;
    end;

    close( f );
end.
