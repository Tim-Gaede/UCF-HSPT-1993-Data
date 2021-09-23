(*****************************************************************************
*  Pascal Solution to "Orthogonal Latin Squares" from the                    *
*                                                                            *
*       Seventh Annual UCF ACM UPE High School Programming Tournament        *
*                               May 15, 1993                                 *
*                                                                            *
*****************************************************************************)
program latin;

var
  n, index1, index2 : integer;
  square : array[1..15, 1..15, 1..2] of integer;
  infile : text;
  orthogonal : string[4];

begin
  assign(infile, 'latin.in');
  reset(infile);
  while not eof(infile) do
  begin
    orthogonal := '';
    readln(infile, n);
    if n > 0 then
    begin
      for index1 := 1 to 2 do
        for index2 := 1 to n * n do
          read(infile, square[index2 mod n + 1, index2 div n, index1]);
      for index1 := 1 to n * n do
        for index2 := 1 to index1 - 1 do
          if (square[index1 mod n + 1, index1 div n, 1] =
              square[index2 mod n + 1, index2 div n, 1]) and
             (square[index1 mod n + 1, index1 div n, 2] =
              square[index2 mod n + 1, index2 div n, 2]) then
             orthogonal := 'NOT ';
      writeln('The Latin Squares are ', orthogonal, 'orthogonal.');
    end;
  end;
end.




