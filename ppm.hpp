#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "coordinate.hh"
#include <vector>

void pixels_to_ppm (const std::vector<std::vector<Coordinate> >& pixels)
{
  int i, j;
  FILE *fp = fopen("first.ppm", "wb"); /* b - binary mode */
  (void) fprintf(fp, "P6\n%d %d\n255\n", pixels.size(), pixels[0].size());
  for (j = 0; j < pixels.size(); ++j)
    {
      for (i = 0; i < pixels[j].size(); ++i)
	{
	  static unsigned char color[3];
	  color[0] = (char) pixels[j][i].x;  /* red */
	  color[1] = (char) pixels[j][i].y;  /* green */
	  color[2] = (char) pixels[j][i].z;  /* blue */
	  (void) fwrite(color, 1, 3, fp);
	}
    }
  (void) fclose(fp);
}
