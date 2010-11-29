//
//   main.cpp
//   The main file of the project
//
#include <GL/glut.h>
#include <GL/glu.h>

#include <iostream>
#include <list>

#include "mglLine.h"
#include "mglPrimitiveList.h"
using namespace std;

void PrintText( int nX, int nY, char* pszText )
{
    int lines;
    char *p;

    glColor3ub( 150, 150, 150 );
    glRasterPos2i( nX, nY );

    for( p=pszText, lines=0; *p; p++ )
    {
        if( *p == '\n' )
        {
            lines++;
            glRasterPos2i( nX, nY-(lines*18) );
        }

        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18,  *p );
    }
}

void display( void )
{
    // clear all pixels
    glClear( GL_COLOR_BUFFER_BIT );

    // set line colour red( r=1, g=0,b=0 ).
    glColor3f( 1.0, 0.0, 0.0 );

    // using the new classes
    mglPrimitiveList letter_M;
    letter_M.add_line( 100, 100, 100, 300 );
    letter_M.add_line( 100, 300, 150, 200 );
    letter_M.add_line( 150, 200, 200, 300 );
    letter_M.add_line( 200, 300, 200, 100 );
    letter_M.draw();

    PrintText( 20, 20, "TEST" );
    

    glFlush();
    glutPostRedisplay();
}

void init( void )
{
    // select clearing color
    glClearColor( 0.0, 0.0, 0.0, 0.0 );

    // initialize viewing values
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0,500,0,500 );
}

// Declare initial window size, position, and display mode
//( single buffer and RGBA ).  Open window with "hello"
// in its title bar.  Call initialization routines.
// Register callback function to display graphics.
// Enter main loop and process events.
int main( int argc, char** argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition( 100, 100 );
    glutCreateWindow( "Hello" );
    init();
    glutDisplayFunc( display );
    glutMainLoop();
    return 0;   // ANSI C requires main to return int.
}
