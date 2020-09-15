//http://compgraphics.info/2D/Brezenham.php

#include <windows.h>
#include "math.h"

#define roundf(x) floor(x + 0.5f)

void LineBresenham(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
{
      int dx = (x2 - x1 >= 0 ? 1 : -1);
      int dy = (y2 - y1 >= 0 ? 1 : -1);

      int lengthX = abs(x2 - x1);
      int lengthY = abs(y2 - y1);

      int length = max(lengthX, lengthY);

      if (length == 0)
      {
            SetPixel(hdc, x1, y1, color);
      }

      if (lengthY <= lengthX)
      {
            // Начальные значения
            int x = x1;
            int y = y1;
            int d = -lengthX;

            // Основной цикл
            length++;
            while(length--)
            {
                  SetPixel(hdc, x, y, color);
                  x += dx;
                  d += 2 * lengthY;
                  if (d > 0) {
                        d -= 2 * lengthX;
                        y += dy;
                  }
            }
      }
      else
      {
            // Начальные значения
            int x = x1;
            int y = y1;
            int d = - lengthY;

            // Основной цикл
            length++;
            while(length--)
            {
                  SetPixel(hdc, x, y, 0);
                  y += dy;
                  d += 2 * lengthX;
                  if (d > 0) {
                        d -= 2 * lengthY;
                        x += dx;
                  }
            }
      }
}
