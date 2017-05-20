#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "coordinate.hh"
#include <vector>

void pixels_to_ppm (const std::vector<std::vector<Coordinate> >& pixels)
{
  int i, j;
  FILE *fp = fopen("first.ppm", "wb"); /* b - binary mode */
  (void) fprintf(fp, "P3 %d %d 255\n", pixels[0].size(), pixels.size());
  for (j = 0; j < pixels.size(); ++j)
    {
      for (i = 0; i < pixels[j].size(); ++i)
	{
	  fprintf(fp, "%.0f %.0f %.0f ",pixels[j][i].x,pixels[j][i].y,pixels[j][i].z);
	}
  fprintf(fp,"\n");
    }
  (void) fclose(fp);
}
