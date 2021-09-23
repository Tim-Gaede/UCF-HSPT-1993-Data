/*****************************************************************************
*  C Solution to "Orthogonal Latin Squares" from the                         *
*                                                                            *
*       Seventh Annual UCF ACM UPE High School Programming Tournament        *
*                               May 15, 1993                                 *
*                                                                            *
*****************************************************************************/
#include <stdio.h>

void main()
{
  FILE *infile;
  int n, index1, index2, index3, square[16][16][3];
  char *orthogonal;

  infile = fopen("latin.in", "rt");
  if (infile)
  {
    while (!feof(infile))
    {
      orthogonal = "";
      fscanf(infile, "%d ", &n);
      for (index1 = 1; index1 <= 2; index1++)
        for (index2 = 1; index2 <= n * n; index2++)
          fscanf(infile, "%d ", &square[index2 % n + 1][index2 / n][index1]);
      for (index1 = 1; index1 <= n * n; index1++)
        for (index2 = 1; index2 <= index1 - 1; index2++)
          if (square[index1 % n + 1][index1 / n][1] ==
              square[index2 % n + 1][index2 / n][1] &&
              square[index1 % n + 1][index1 / n][2] ==
              square[index2 % n + 1][index2 / n][2])
            orthogonal = "NOT ";
      printf("The Latin Squares are %sorthogonal.\n", orthogonal);
    }
  }
}