//#include "functionline.cpp" //загружается в functionmanyangle2Dfigure.cpp и в functioncircle.cpp
//#include "functionmanyangle2Dfigure.cpp"
#include "functioncircle.cpp"
/*
#include "functionsrays.cpp"

#include <vector>
*/
//#include "functionsfill.cpp"

const int WindowWidthFM = 780;
const int WindowHeightFM = 500;




void CircleBresenhamFilledIn(HDC hdc, int x0, int y0, int radius, COLORREF color)
{
    for(int i = radius; i > 0; i--)
    {
        CircleBresenham(hdc, x0, y0, i, color);
    }
}


void CircleBresenhamFilledOut(HDC hdc, int x0, int y0, int radius, COLORREF color)
{
    for(int i = 0; i < radius; i++)
    {
        CircleBresenham(hdc, x0, y0, i, color);
    }
}



//Упрощенные названия

void Line(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
{
    LineBresenham(hdc, x1, y1, x2, y2, color);
}

void Circle(HDC hdc, int x0, int y0, int radius, COLORREF color)
{
    CircleBresenham(hdc, x0, y0, radius, color);
}

void CircleFilledIn(HDC hdc, int x0, int y0, int radius, COLORREF color)
{
    CircleBresenhamFilledIn(hdc, x0, y0, radius, color);
}

void CircleFilledOut(HDC hdc, int x0, int y0, int radius, COLORREF color)
{
    CircleBresenhamFilledOut(hdc, x0, y0, radius, color);
}



void CircleFilled(HDC hdc, int x0, int y0, int radius, COLORREF color)
{
    CircleBresenham(hdc, x0, y0, radius, color);
}


void WindowClear(HDC hdc, COLORREF color)
{
    GetSysColor(color);
    GetSysColorBrush(color);
    Rectangle(hdc, 0, 0, WindowWidthFM, WindowHeightFM);
/*
 for(int iH = 0; iH < WindowHeightFM; iH++)
    for(int iW = 0; iW < WindowWidthFM; iW++) SetPixel(hdc, iW, iH, color);
*/
}




template <typename OutType,typename InType>
OutType GradToRad (InType grad)  // градусы в радианы
{
  float PI = 3.14159;
  return PI/180*grad;
}

template <typename OutType,typename InType>
OutType RadToGrad (InType rad)  // радианы в градусы
{
  float PI = 3.14159;
  return PI*180/rad;
}

template <typename OutType,typename InType>
OutType GradToAbsolute(InType grad)// градусы в Абсолютный Поворот
{
    float PI = 3.14159;
    return grad/360;
}

template <typename OutType,typename InType>
OutType RadToAbsolute(InType rad)// радианы в Абсолютный Поворот
{
    float PI = 3.14159;
    return (PI*180/rad)/360;
}

template <typename OutType,typename InType>
OutType AbsoluteToGrad(InType AbsGrad)// Абсолютный Поворот в градусы
{
    float PI = 3.14159;
    return AbsGrad*360;
}

template <typename OutType,typename InType>
OutType AbsoluteToRad(InType AbsGrad)// Абсолютный Поворот в радианы
{
    float PI = 3.14159;
    return PI/180*(AbsGrad*360);
}


struct DynamicPoint{
HDC hdc;
int x;
int y;
COLORREF color;
void SetPaintColor()
{
    color = GetPixel(hdc, x, y);
}
};

void RangeFill(HDC hdc, int x0, int y0, COLORREF colorAfter)
{
    COLORREF colorBefore = GetPixel(hdc, x0, y0);

    DynamicPoint DynamicPointActive1 = {/*hdc = */hdc, /*x = */x0, /*y = */y0, /*color = */0};
    DynamicPointActive1.SetPaintColor();

    DynamicPoint DynamicPointActive2 = {/*hdc = */hdc, /*x = */x0, /*y = */y0, /*color = */0};
    DynamicPointActive2.SetPaintColor();


    if(GetPixel(hdc, DynamicPointActive1.x-1, DynamicPointActive1.y-1) == colorBefore &&
       GetPixel(hdc, DynamicPointActive1.x  , DynamicPointActive1.y-1) == colorBefore &&
       GetPixel(hdc, DynamicPointActive1.x+1, DynamicPointActive1.y-1) == colorBefore &&

       GetPixel(hdc, DynamicPointActive1.x-1, DynamicPointActive1.y  ) == colorBefore &&
       GetPixel(hdc, DynamicPointActive1.x-1, DynamicPointActive1.y  ) == colorBefore &&
       GetPixel(hdc, DynamicPointActive1.x+1, DynamicPointActive1.y  ) == colorBefore &&

       GetPixel(hdc, DynamicPointActive1.x-1, DynamicPointActive1.y+1) == colorBefore &&
       GetPixel(hdc, DynamicPointActive1.x  , DynamicPointActive1.y+1) == colorBefore &&
       GetPixel(hdc, DynamicPointActive1.x+1, DynamicPointActive1.y+1) == colorBefore   )

       SetPixel(hdc, DynamicPointActive1.x-1, DynamicPointActive1.y-1, colorAfter);
       SetPixel(hdc, DynamicPointActive1.x  , DynamicPointActive1.y-1, colorAfter);
       SetPixel(hdc, DynamicPointActive1.x+1, DynamicPointActive1.y-1, colorAfter);
       SetPixel(hdc, DynamicPointActive1.x-1, DynamicPointActive1.y  , colorAfter);
       SetPixel(hdc, DynamicPointActive1.x  , DynamicPointActive1.y  , colorAfter);
       SetPixel(hdc, DynamicPointActive1.x+1, DynamicPointActive1.y  , colorAfter);
       SetPixel(hdc, DynamicPointActive1.x-1, DynamicPointActive1.y+1, colorAfter);
       SetPixel(hdc, DynamicPointActive1.x  , DynamicPointActive1.y+1, colorAfter);
       SetPixel(hdc, DynamicPointActive1.x+1, DynamicPointActive1.y+1, colorAfter);
       /*
    DynamicPointActive1.y--;
    i++;
    if(i > 400) break;


*/
/*

    SetPixel(hdc, DynamicPointActive1.x, DynamicPointActive1.y, colorAfter);

    while(DynamicPointActive1.color == colorBefore)
    {
        DynamicPointActive1.y--;
        DynamicPointActive1.SetPaintColor();
    }
*/



/*CoordYStart--;*/
}




void Main1(HDC hdc)
{
        Line(hdc, 20, 20, 70, 20, RGB(255,255,0));
        CircleFilledIn(hdc, 120, 150, 54, RGB(0,255,0));
        CircleFilledOut(hdc, 120, 150, 54, RGB(255,255,0));
        SetPixel(hdc, 10, 10, RGB(255,0,0));	//Вот тут я вывел красный пиксель на экран программы
        //PaintN(hdc, 270, 280, 10, RGB(77,255,0));
}


void Main2(HDC hdc)
{
    CircleFilled(hdc, 520, 450, 74, RGB(0,255,255));
    RangeFill(hdc, 520, 450, RGB(255,255,255));
    Nrectangle(hdc, 300, 200, 500, 370, RGB(255,255,0));
    linesin(hdc,RGB(0,255,0));







}

//Главное подключение функций по темам

void MainFunction(HDC hdc, HWND hwnd)
{
    //SetWindowPos(hwnd,HWND_BOTTOM,0,0,0,0,SWP_NOMOVE || SWP_NOSIZE);
    Main1(hdc);
    Main2(hdc);
}





//Ниже код для проверок

/*



*/



