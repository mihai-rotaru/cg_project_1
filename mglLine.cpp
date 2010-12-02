#include <GL/glu.h>
#include "mglLine.h"
#include <stdlib.h>
#include "mgl_util.h"
#include <math.h>
#include <stdio.h>
//#include "mgl_structs.h"

mglLine::mglLine( int _x1, int _y1, int _x2, int _y2 )
{
//    x1 = _x1;
//    x2 = _x2;
//    y1 = _y1;
//    y2 = _y2;
    mline = glGenList( 1 );
    printf( "mline: %d", mline );
    glNewList( mline, GL_COMPILE );
    glVertex2i( x1, y1 );
    glVertex2i( x2, y2 );
    glEndList();    
}

void mglLine::draw()
{
    glBegin( GL_LINES );
        glVertex2i( x1, y1 );
	glVertex2i( x2, y2 );
    glEnd();
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

void mglLine::rotate( float theta, float x_rel, float y_rel )
{
    printf("theta: %.2f, x_rel: %.2f, y_rel: %.2f\n", theta, x_rel, y_rel );
    glPushMatrix();
       glRotatef( theta, x_rel, y_rel, 1 );
       draw();
    glPopMatrix();
    glutPostRedisplay();
//    x1 = ( x1 * cos( theta )) - ( y1 * sin( theta ));
//    y1 = ( x1 * sin( theta )) + ( y1 * cos( theta ));
//    x2 = ( x2 * cos( theta )) - ( y2 * sin( theta ));
//    y2 = ( x2 * sin( theta )) + ( y2 * cos( theta ));
//    printf("cos( %d ) = %d sin( %d ) = %d\n", theta, cos( theta ), theta, sin( theta ));
//    printf("x1 = %d y1 = %d x2 = %d y2 = %d\r\n", x1, y1, x2, y2 );

}

void mglLine::move( int x_distance, int y_distance )
{
//    x1 += x_distance;
//    x2 += x_distance;
//    y1 += y_distance;
//    y2 += y_distance;    
    glPushMatrix();
        glTranslatef( (float)x_distance, (float)y_distance, 0 );
	draw();
    glPopMatrix();
    glutPostRedisplay();
}

float mglLine::distance_to( int x, int y )
{
    return shortest_distance( (float)x, (float)y, (float)x1, (float)y1, (float)x2, (float)y2 );
}
