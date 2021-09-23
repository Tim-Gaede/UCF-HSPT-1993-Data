(*****************************************************************************
*  Pascal Solution to "Mind Your PQs" from the                               *
*                                                                            *
*       Seventh Annual UCF ACM UPE High School Programming Tournament        *
*                               May 15, 1993                                 *
*                                                                            *
*  This program implements a PQ, with operations INSERT and REMOVE, as       *
*  defined in the problem statement.  A PQ is implemented as an unordered    *
*  list.  To insert a value, we add the value to the end of the list.  To    *
*  remove the smallest value, we scan for the smallest value, remove it, and *
*  then compress the list to fill in the hole created by removing the value. *
*****************************************************************************)
program PQ(input, output);

const MAX_IN_PQ = 100;  (* Maximum number of elements in the PQ *)

var
    the_pq : array[1..MAX_IN_PQ] of integer; (* The PQ structure      *)
    num_in_pq,           (* Number of elements currently in the PQ    *)
    i,                   (* Looping variable                          *)
    min,                 (* Minimum element in the PQ                 *)
    index : integer;     (* Location of the minimum element in the PQ *)
    ch : char;           (* Used for input                            *)
    infile : text;       (* Input file                                *)

begin
    assign( infile, 'pqueue.in' );
    reset( infile );

    while not eof( infile ) do
    begin
        ch := ' ';

        (* Start each data set with an empty PQ *)
        num_in_pq := 0;
        while ch <> 'E' do
        begin
            read( infile, ch );
            if ch = 'I' then
            begin
                (* Remove the INSERT command from the input line *)
                while ch <> ' ' do
                    read( infile, ch );

                (* Insert a value into the PQ *)
                inc( num_in_pq );
                read( infile, the_pq[num_in_pq] );
            end
            else if ch = 'R' then
            begin
                (* Find the smallest element in the PQ *)
                min := MAXINT;
                for i := 1 to num_in_pq do
                begin
                    if the_pq[i] < min then
                    begin
                        min := the_pq[i];
                        index := i;
                    end;
                end;

                (* Remove the smallest element from the PQ *)
                dec( num_in_pq );
                for i := index to num_in_pq do
                    the_pq[i] := the_pq[i+1];

                (* Output the removed element *)
                writeln( min );
            end;
            readln( infile );
        end;
        writeln;
    end;

    close( infile );
end.
