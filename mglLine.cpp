#include <GL/glu.h>
#include "mglLine.h"
#include <stdlib.h>
#include "mgl_util.h"
#include <math.h>
#include <stdio.h>
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

void mglLine::scale( float x_dir, float y_dir )
{
//    glPushMatrix();
//        glScalef( x_dir, y_dir, 1.0 );
//        draw();
//    glPopMatrix();	
    GLfloat* buff = new GLfloat[5];
    glFeedbackBuffer( 5, GL_2D, buff );
    
    glRenderMode( GL_FEEDBACK );
    glPushMatrix();
       glScalef( x_dir, y_dir, 1 );
       draw();
    glPopMatrix();

    x1 = (int)buff[1];
    y1 = (int)buff[2];
    x2 = (int)buff[3];
    y2 = (int)buff[4];

    delete[] buff;
    
    char mstr[20];
    itoa( x1, mstr, 10 );
    PrintText( 50,50, mstr );
}

void mglLine::rotate( float theta, float x_rel, float y_rel )
{
    printf("theta: %.2f, x_rel: %.2f, y_rel: %.2f\n", theta, x_rel, y_rel );

    GLfloat* buff = new GLfloat[5];
    glFeedbackBuffer( 5, GL_2D, buff );
    
    glRenderMode( GL_FEEDBACK );
    glPushMatrix();
       glRotatef( theta, x_rel, y_rel, 1 );
       draw();
    glPopMatrix();

    x1 = (int)buff[1];
    y1 = (int)buff[2];
    x2 = (int)buff[3];
    y2 = (int)buff[4];

    delete[] buff;
}

void mglLine::move( int x_distance, int y_distance )
{
    GLfloat* buff = new GLfloat[5];
    glFeedbackBuffer( 5, GL_2D, buff );
    
    glRenderMode( GL_FEEDBACK );
    glPushMatrix();
       glTranslatef( (float)x_distance, (float)y_distance, 0 );
       draw();
    glPopMatrix();

    x1 = (int)buff[1];
    y1 = (int)buff[2];
    x2 = (int)buff[3];
    y2 = (int)buff[4];

    delete[] buff;
}

float mglLine::distance_to( int x, int y )
{
    return shortest_distance( (float)x, (float)y, (float)x1, (float)y1, (float)x2, (float)y2 );
}

int mglLine::getMaxX()
{
    return ( x1 > x2 ? x1 : x2 );
}

int mglLine::getMinX()
{
    return ( x1 < x2 ? x1 : x2 );
}

int mglLine::getMaxY()
{
    return ( y1 > y2 ? y1 : y2 );
}

int mglLine::getMinY()
{
    return ( y1 < y2 ? y1 : y2 );
}
