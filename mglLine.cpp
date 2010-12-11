#include <GL/glu.h>
#include "mglLine.h"
#include <stdlib.h>
#include "mgl_util.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
//#include "mgl_structs.h"

mglLine::mglLine( char* _name, int _x1, int _y1, int _x2, int _y2 )
{
    x1 = _x1;
    x2 = _x2;
    y1 = _y1;
    y2 = _y2;
    strcpy( name, _name );
    if( DEBUG ) 
        printf("ctor mglLine: adr: %x, name = %s\n", this, name );
}

mglLine::mglLine( int _x1, int _y1, int _x2, int _y2 )
{
    x1 = _x1;
    x2 = _x2;
    y1 = _y1;
    y2 = _y2;
    strcpy( name, "unnamed Line" );
    if( DEBUG ) 
        printf("ctor mglLine: adr: %x, name = %s\n", this, name );
}

mglLine::~mglLine()
{
    if( DEBUG ) 
        printf("dtor mglLine: adr: %x, name = %s\n", this, name );
}

void mglLine::draw()
{
    glBegin( GL_LINES );
        glVertex2i( x1, y1 );
        glVertex2i( x2, y2 );
    glEnd();
}

void mglLine::print()
{
    printf("        mglLine; name = %s, adr = %x ", name, this );
    printf("            x1 = %3d, y1 = %3d, x2 = %3d, y2 = %3d\n", x1, y1, x2, y2 );
}

void mglLine::scale( int rel_x, int rel_y, float x_dir, float y_dir )
{
    GLfloat* buff = new GLfloat[5];
    glFeedbackBuffer( 5, GL_2D, buff );
    dprintf("before scaling: x1=%d, y1=%d, x2=%d, y2=%d\n", x1, y1, x2, y2 ); 
    
    glRenderMode( GL_FEEDBACK );
    glPushMatrix();
       glScalef( x_dir, y_dir, 1 );
       draw();
    glPopMatrix();

    //int xdiff = (int)buff[1] - x1;
    //int ydiff = (int)buff[2] - y1;
    x1 = ((int)buff[1] );
    y1 = ((int)buff[2] );
    x2 = ((int)buff[3] );
    y2 = ((int)buff[4] );

    delete[] buff;
    dprintf("after scaling:  x1=%d, y1=%d, x2=%d, y2=%d\n", x1, y1, x2, y2 ); 
    
    char mstr[20];
    itoa( x1, mstr, 10 );
    PrintText( 50,50, mstr );
}

void mglLine::scale( float x_dir, float y_dir )
{
    //dprintf("before scaling: x1=%d, y1=%d, x2=%d, y2=%d\n", x1, y1, x2, y2 ); 
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
    
    //dprintf("after scaling:  x1=%d, y1=%d, x2=%d, y2=%d\n", x1, y1, x2, y2 ); 
    char mstr[20];
    itoa( x1, mstr, 10 );
    PrintText( 50,50, mstr );
}

void mglLine::rotate( float theta, float x_rel, float y_rel )
{
    dprintf("theta: %.2f, x_rel: %.2f, y_rel: %.2f\n", theta, x_rel, y_rel );

    GLfloat* buff = new GLfloat[5];
    glFeedbackBuffer( 5, GL_2D, buff );
    
    glRenderMode( GL_FEEDBACK );
    glPushMatrix();
        glTranslatef( -x_rel, -y_rel, 0 );
        glRotatef( theta, 0, 0, 1 );
        glTranslatef( x_rel, y_rel, 0 );
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
