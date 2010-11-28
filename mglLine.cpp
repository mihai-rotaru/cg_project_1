#include "mglLine.h"
#include "mgl_structs.h"

mglLine::mglLine( int _x1, int _y1, int _x2, int _y2 )
{
    x1 = _x1;
    x2 = _x2;
    y1 = _y1;
    y2 = _y2;
}

void mglLine::draw()
{
    glBegin( GL_LINES );
        glVertex2i( x1, y1 );
	glVertex2i( x2, y2 );
    glEnd();
}

float mglLine::distance_to( mglPoint p )
{
    return 0;
}

void mglLine::scale( float factor )
{
}

void mglLine::rotate( float angle )
{
}

void mglLine::move( int x_distance, int y_distance )
{
}
