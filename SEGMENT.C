/*****************************************************************************
*  C Solution to "Interesting Intersections" from the                        *
*                                                                            *
*       Seventh Annual UCF ACM UPE High School Programming Tournament        *
*                               May 15, 1993                                 *
*                                                                            *
*  This program determines whether a given line segment intersects a given   *
*  circle.                                                                   *
*****************************************************************************/
#include <stdio.h>
#include <math.h>

float cx, cy, cr,     /* Center and radius of the circle         */
      a, b, c, d;     /* (a,b) and (c,d) define the line segment */

/*****************************************************************************
*  Exchanges the values of a and b.                                          *
*****************************************************************************/
void Swap( float *a, float *b )
{
    float temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

/******************************************************************************
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
******************************************************************************/
int Intersects( void )
{
    float m,        /* Slope of the line segment                      */
          k,        /* Temp variable                                  */
          discr,    /* Discriminant of quadratic formula              */
          x,y;      /* Possible intersection point                    */
    int result;     /* Whether the line segment intersects the circle */

    result = 0;
    if( fabs( a-c ) < 0.001 )
    {
        /* The line segment is vertical */
        if( d < b )
            Swap( &b, &d );
        discr = cr*cr-a*a;
        if( discr >= 0 )
        {
            k = sqrt( discr );
            result = ((b<=k) && (k<=d)) || ((b<=-k) && (-k<=d));
        }
    }
    else
    {
        /* The line segment is not vertical */
        m = (b-d)/(a-c);
        k = b-m*a;
        discr = m*m*k*k-(1+m*m)*(k*k-cr*cr);
        if( c<a ) Swap( &a, &c );
        if( d<b ) Swap( &b, &d );
        if( discr >= 0 )
        {
            /* Try one intersection point */
            x = (-m*k+sqrt(discr))/(1+m*m);
            y = m*x+k;
            result = (a<=x) && (x<=c) && (b<=y) && (y<=d);
            if( !result )
            {
                /* Try the other intersection point.  Notice that if */
                /* discr == 0, then this point is really the same as */
                /* the one we tested above (but this doesn't hurt    */
                /* anything).                                        */
                x = (-m*k-sqrt(discr))/(1+m*m);
                y = m*x+k;
                result = (a<=x) && (x<=c) && (b<=y) && (y<=d);
            }
        }
    }
    return( result );
}

void main( void )
{
    FILE *infile;     /* Input data file */

    infile = fopen( "segment.in", "r" );

    while( fscanf( infile, "%f %f %f %f %f %f %f",
                   &cx, &cy, &cr, &a, &b, &c, &d ) != EOF )
    {
        /* Center the coordinate system at (cx,cy) for simplicity */
        a = a - cx;
        b = b - cy;
        c = c - cx;
        d = d - cy;

        if( Intersects() )
            printf( "The line segment intersects the circle.\n" );
        else
            printf( "The line segment does not intersect the circle.\n" );
    }

    fclose( infile );
}