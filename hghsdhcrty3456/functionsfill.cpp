#include <stdafx>
/* Arguments:
 *        Pointer to bitmap to fill, (x,y) coordinates of seed point,
 *        color used for solid or masked fills, border color used if area to
 *        be filled is outlined (or CLR_INVALID).
 *
 * Returns:
 *         0 = Success.
 *        -1 = Invalid seed point.
 *        -2 = Memory allocation error.
 *        -3 = Invalid bitmap or unknown error.
 */
int QuickFill(
    CBitmap* pBitmap,int x,int y,
    COLORREF fill_color,COLORREF border_color/*=CLR_INVALID*/)
{
    COLORREF ThisColor;
    int MaxY,MaxX,dy;
    int ChildLeft,ChildRight;
    int ParentLeft,ParentRight;

#ifdef QUICKFILL_SLOW
    HWND hWnd;
    if( m_bSlowMode )
        hWnd = ::GetActiveWindow();
#endif

    // Create dib data object
    if( !m_DibData.CreateDIB(pBitmap) )
        return -3;

    /* Initialize global variables */
#ifdef QUICKFILL_TEST
    SHORT nKeyState;
    m_CurStackSize = m_MaxStackSize = m_VisitSize = 0U;
    m_CurrentLine = 0;
#endif
    m_bXSortOn = m_bMemError = FALSE;
    m_LastY = -1;

    /* Initialize internal info based on fill type */
    if( CLR_INVALID != border_color ) {
        /* Check color at x,y position */
        ThisColor = GetPixel(x,y);
        if( ThisColor == border_color )
            return -1;

        ThisColor = border_color;
        m_bXSortOn = TRUE;
    }
    else {
        /* Check color at x,y position */
        ThisColor = GetPixel(x,y);
        if( ThisColor == fill_color && !m_DibPattern.GetDibPtr() )
            return -1;

        if( m_DibPattern.GetDibPtr() || memcmp(m_FillMask,_SolidMask,8) )
            m_bXSortOn = TRUE;
    }

    /* Using macros because we can not uses pointer to member functions.
     * This makes the code less efficient, but solves the problem.
     */
#define FindLeft(x,y,xmin,color) \
    ((CLR_INVALID != border_color) \
    ? SearchLeft(x,y,xmin,color) : ScanLeft(x,y,xmin,color))
#define FindRight(x,y,xmax,color) \
    ((CLR_INVALID != border_color) \
    ? SearchRight(x,y,xmax,color) : ScanRight(x,y,xmax,color))
#define SkipRight(x,y,xmax,color) \
    ((CLR_INVALID != border_color) \
    ? ScanRight(x,y,xmax,color) : SearchRight(x,y,xmax,color))

    /* Initialize Line list */
    if( MakeList() )
        return -2;

    /* Initialize maximum coords */
    MaxX = m_DibData.GetWidth()-1;
    MaxY = m_DibData.GetHeight()-1;

    /* Push starting point on stack */
    PushLine(x,x,y,+1);        /* Needed in one special case */
    PushLine(x,x,y+1,-1);

    /* Now start flooding */
    while( m_pLineList ) {
        PopLine(&ParentLeft,&ParentRight,&y,&dy);
        y += dy;
        if( y < 0 || MaxY < y )
            continue;
        if( m_bMemError )
            continue;
        if( m_bXSortOn && IsRevisit(ParentLeft,ParentRight,y) )
            continue;

#ifdef QUICKFILL_SLOW
        if( m_bSlowMode ) {
            nKeyState = ::GetAsyncKeyState(VK_ESCAPE);
            if( nKeyState < 0 )
                break;
        }
        m_CurrentLine = y;
#endif

        /* Find ChildLeft end ( ChildLeft>ParentLeft on failure ) */
        ChildLeft = FindLeft(ParentLeft,y,0,ThisColor)+1;
        if( ChildLeft<=ParentLeft ) {
            /* Find ChildRight end ( this should not fail here ) */
            ChildRight = FindRight(ParentLeft,y,MaxX,ThisColor)-1;
            /* Fill line */
            if( ChildLeft == ChildRight )
                SetPixel(ChildRight,y,fill_color);
            else
                DrawHorizontalLine(ChildLeft,ChildRight,y,fill_color);

#ifdef QUICKFILL_SLOW
            if( m_bSlowMode && hWnd ) {
                m_DibData.SetDIBits(pBitmap);
                ::InvalidateRect(hWnd,NULL,FALSE);
                ::UpdateWindow(hWnd);
            }
#endif

            /* Push unvisited lines */
            if( ParentLeft-1<=ChildLeft && ChildRight<=ParentRight+1 ) {
                PushLine(ChildLeft,ChildRight,y,dy);
            }
            else {
                if( m_bXSortOn )
                    PushOpposite(ParentLeft,ParentRight,
                                 ChildLeft,ChildRight,y,dy);
                else
                    PushLine(ChildLeft,ChildRight,y,-dy);
                PushLine(ChildLeft,ChildRight,y,dy);
            }
            /* Advance ChildRight end on to border */
            ++ChildRight;
        }
        else ChildRight = ParentLeft;

        /* Fill between */
        while( ChildRight < ParentRight ) {
            /* Skip to new ChildLeft end
               ( ChildRight>ParentRight on failure ) */
            ChildRight = SkipRight(ChildRight,y,ParentRight,ThisColor);
            /* If new ChildLeft end found */
            if( ChildRight<=ParentRight ) {
                ChildLeft = ChildRight;
                /* Find ChildRight end ( this should not fail here ) */
                ChildRight = FindRight(ChildLeft,y,MaxX,ThisColor)-1;
                /* Fill line */
                if( ChildLeft == ChildRight )
                    SetPixel(ChildRight,y,fill_color);
                else
                    DrawHorizontalLine(ChildLeft,ChildRight,y,fill_color);

#ifdef QUICKFILL_SLOW
                if( m_bSlowMode && hWnd ) {
                    m_DibData.SetDIBits(pBitmap);
                    ::InvalidateRect(hWnd,NULL,FALSE);
                    ::UpdateWindow(hWnd);
                }
#endif

                /* Push unvisited lines */
                if( ChildRight <= ParentRight+1 )
                    PushLine(ChildLeft,ChildRight,y,dy);
                else {
                    if( m_bXSortOn )
                        PushOpposite(ParentLeft,ParentRight,
                                      ChildLeft,ChildRight,y,dy);
                    else
                        PushLine(ChildLeft,ChildRight,y,-dy);
                    PushLine(ChildLeft,ChildRight,y,dy);
                }
                /* Advance ChildRight end onto border */
                ++ChildRight;
            }
        }

        /* Push visited line onto visited stack */
        if( m_bXSortOn )
            PushVisitedLine(ParentLeft,ParentRight,y);
    }
    FreeList();
    m_DibData.SetDIBits(pBitmap);
    m_DibData.DeleteObject();
    return( m_bMemError?-2:0 );
}
