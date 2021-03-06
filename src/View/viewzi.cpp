#include <QPen>

#include "viewzi.h"
#include "graphicsview.h"
#include "../Handle/zi.h"

ViewZI::ViewZI(ZI *zi, const QRectF &rect)
    : QGraphicsRectItem(rect),
      m_zi(zi)
{
}


ViewZI::~ViewZI(void)
{
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC-----------------------------------------------
---------------------------------------------------------------------------------------------------*/

void ViewZI::changeColor( const QColor & color )
{
    QPen p( color );
    m_color = color;
    setPen(p);
}


void ViewZI::resize( int direction, int x, int y )
{
    if( direction & GraphicsView::TOP )
        m_zi->resize(ZI::Y , y);
    else if( direction & GraphicsView::BOTTOM )
        m_zi->resize(ZI::HEIGHT , y );

    if( direction & GraphicsView::LEFT )
        m_zi->resize(ZI::X , x);
    else if( direction & GraphicsView::RIGHT )
        m_zi->resize(ZI::WIDTH , x );
}



void ViewZI::select(void)
{
    QPen p( QColor(0,255,100) );
    setPen(p);
}


int ViewZI::type(void) const
{
    return ID_VIEWZI;
}


void ViewZI::unselect(void)
{
    QPen p( m_color );
    setPen(p);
}

/*---------------------------------------------------------------------------------------------------
------------------------------------------------PUBLIC SLOT------------------------------------------
---------------------------------------------------------------------------------------------------*/

void ViewZI::finelize(void)
{
    m_zi->showParameters();
}
