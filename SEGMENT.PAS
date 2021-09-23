(*****************************************************************************
*  Pascal Solution to "Interesting Intersections" from the                   *
*                                                                            *
*       Seventh Annual UCF ACM UPE High School Programming Tournament        *
*                               May 15, 1993                                 *
*                                                                            *
*  This program determines whether a given line segment intersects a given   *
*  circle.                                                                   *
*****************************************************************************)
program Segment( input, output );

var
    infile : text;        (* Input data file                         *)
    cx, cy, cr,           (* Center and radius of the circle         *)
    a, b, c, d : real;    (* (a,b) and (c,d) define the line segment *)

(******************************************************************************
*  Exchanges the values of a and b.                                           *
******************************************************************************)
procedure Swap( var a, b : real );
var temp : real;
begin
    temp := a;
    a := b;
    b := temp;
end;


(******************************************************************************
*  Determines whether the line segment with endpoints (a,b) and (c,d)         *
*  intersects the circle with center (0,0) and radius cr.                     *
*                                                                             *
*  Method:                                                                    *
*      The equation of the circle is x^2 + y^2 = r^2.  The equation of the    *
*  line containing the line segment is y = mx + B, where m = (b-d)/(a-c) and  *
*  B = a(b-d)/(a-c)+b.  Substituting the equation of the line into the        *
*  equation of the circle, we get                                             *
*                    x^2 + (mx+B)^2 = r^2, or                                 *
*                    x^2 + (mx)^2 + 2mxB + B^2 = r^2, or                      *
*                    (1+m^2)x^2 + (2mB)x + (B^2 - r^2) = 0                    *
*  which is a quadratic in x.  Therefore, there are 0, 1, or 2 real solutions *
*  for x.  If there are 0 solutions (i.e., 2 complex roots of the equation)   *
*  then the line segment does not intersect the circle.  If there is at least *
*  1 solution, compute the corresponding y for each x using the equation for  *
*  the line given above, and check whether that point is in between the       *
*  endpoints of the line segment.  We only need one point to be in between    *
*  the two endpoints for the line segment to intersect the circle.            *
*                                                                             *
*  Special case:  If the line segment is vertical, the equation of the line   *
*                 becomes x = a.  This is substituted into the equation for   *
*                 the circle, obtaining                                       *
*                     a^2 + y^2 = r^2, or                                     *
*                     y^2 = r^2 - a^2                                         *
*                 As before, there are 0, 1, or 2 real solutions of this      *
*                 equation.  Note that if there is a real solution for y, we  *
*                 already know the x coordinate (since x = a) and hence we    *
*                 only need to check that the point (a,y) is between the two  *
*                 endpoints of the line segment.                              *
*                                                                             *
*  Returns                                                                    *
*      Boolean:  Does the line segment intersect the circle?                  *
******************************************************************************)
function Intersects : boolean;
var m,                  (* Slope of the line segment                      *)
    k,                  (* Temp variable                                  *)
    discr,              (* Discriminant of quadratic formula              *)
    x, y : real;        (* Possible intersection point                    *)
    result : boolean;   (* Whether the line segment intersects the circle *)
begin
    result := false;
    if abs( a-c ) < 0.001 then
    begin
        (* The line segment is vertical *)
        if d < b then
            Swap( b, d );
        discr := cr*cr-a*a;
        if discr >= 0 then
        begin
            k := sqrt(discr);
            result := ((b <= k) and (k <= d)) or ((b <= -k) and (-k <= d));
        end;
    end
    else
    begin
        (* The line segment is not vertical *)
        m := (b-d)/(a-c);
        k := b-m*a;
        discr := m*m*k*k-(1+m*m)*(k*k-cr*cr);
        if c < a then Swap( a, c );
        if d < b then Swap( b, d );
        if discr >= 0 then
        begin
            x := (-m*k+sqrt(discr))/(1+m*m);
            y := m*x+k;
            result := (a<=x) and (x<=c) and (b<=y) and (y<=d);
            if not result then
            begin
                x := (-m*k-sqrt(discr))/(1+m*m);
                y := m*x+k;
                result := (a<=x) and (x<=c) and (b<=y) and (y<=d);
            end;
        end;
    end;
    Intersects := result;
end;

begin
    assign( infile, 'segment.in' );
    reset( infile );

    while not eof( infile ) do
    begin
        readln( infile, cx, cy, cr );
        readln( infile, a, b, c, d );

        (* Center the coordinate system at (cx,cy) for simplicity *)
        a := a - cx;
        b := b - cy;
        c := c - cx;
        d := d - cy;

        if Intersects then
            writeln( 'The line segment intersects the circle.' )
        else
            writeln( 'The line segment does not intersect the circle.' );
    end;

    close( infile );
end.
