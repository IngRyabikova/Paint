




void Nrectangle(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
{
    if(x1<x2)
    for(int x = x1; x < x1+(x2-x1); x++)
    for(int y = y1; y < y1+(y2-y1); y++)
    {
        SetPixel(hdc, x, y, color);
    }
/*
    else if(x1>x2)
    for(int x = 270; x > 271; x++)
    {
        SetPixel(hdc, x, 75, color);
    }*/
}

void linesin(HDC hdc, COLORREF color)
{



    int y = 0;
    for(int x = 0; x < 500; x++)
    {
        y = tan(x);
        SetPixel(hdc, 400+x, 150+y, color);
        //x+=5; y+=5;
    }

}

