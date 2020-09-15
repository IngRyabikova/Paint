//https://habr.com/ru/post/185086/
#include "functionmanyangle2Dfigure.cpp"

void CircleBresenham(HDC hdc, int x0, int y0, int radius, COLORREF color)
{
    int x = radius;
    int y = 0;
    int radiusError = 1 - x;
    while (x >= y)
    {
        SetPixel(hdc, x + x0, y + y0, color);
        SetPixel(hdc, y + x0, x + y0, color);
        SetPixel(hdc, -x + x0, y + y0, color);
        SetPixel(hdc, -y + x0, x + y0, color);
        SetPixel(hdc, -x + x0, -y + y0, color);
        SetPixel(hdc, -y + x0, -x + y0, color);
        SetPixel(hdc, x + x0, -y + y0, color);
        SetPixel(hdc, y + x0, -x + y0, color);
        y++;
        if (radiusError < 0)
        {
            radiusError += 2 * y + 1;
        }
        else
        {
            x--;
            radiusError += 2 * (y - x + 1);
        }
    }
}
