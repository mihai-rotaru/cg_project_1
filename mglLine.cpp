#include <GL/glu.h>
#include "mglLine.h"
#include <stdlib.h>
#include "mgl_util.h"
//#include "mgl_structs.h"

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

void mglLine::scale( float x_dir, float y_dir )
{
//    glPushMatrix();
//        glScalef( x_dir, y_dir, 1.0 );
//        draw();
//    glPopMatrix();	
    x1 = (int)(x1 * x_dir);
    y1 = (int)(y1 * y_dir);
    x2 = (int)(x2 * x_dir);
    y2 = (int)(y2 * y_dir);
    
    char mstr[20];
    itoa( x1, mstr, 10 );
    PrintText( 50,50, mstr );
}

void mglLine::rotate( float angle )
{
}

void mglLine::move( int x_distance, int y_distance )
{
    x1 += x_distance;
    x2 += x_distance;
    y1 += y_distance;
    y2 += y_distance;    
}
