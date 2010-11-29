//
//   main.cpp
//   The main file of the project
//
#include <GL/glut.h>
#include <GL/glu.h>
#include <string.h>
#include <stdio.h>

#include <iostream>
#include <list>

#include "mglLine.h"
#include "mglPrimitiveList.h"
#include "mgl_util.h"
using namespace std;

mglPrimitiveList letter_M,letter_R;
int mouse_X, mouse_Y;
char info[256];

void display( void )
{
    // clear all pixels
    glClear( GL_COLOR_BUFFER_BIT );

    PrintText( 20, 20, info );

    letter_M.draw();
    letter_R.draw();
    
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
    
    // using the new classes
    letter_M.add_line( 100, 100, 100, 300 );
    letter_M.add_line( 100, 300, 150, 200 );
    letter_M.add_line( 150, 200, 200, 300 );
    letter_M.add_line( 200, 300, 200, 100 );

    letter_R.add_line( 250, 100, 250, 300 );
    letter_R.add_line( 250, 300, 350, 300 );
    letter_R.add_line( 350, 300, 350, 200 );
    letter_R.add_line( 350, 200, 250, 200 );
    letter_R.add_line( 250, 200, 350, 100 );
}

static void Mouse(int button, int state, int _mouseX, int _mouseY)
{
    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            letter_R.line_width+=1;
	}

        else if (button == GLUT_RIGHT_BUTTON) 
        {
	    letter_R.line_width-=1;
	}

	char *x = new char[10];
	char *y = new char[10];

        sprintf( x, "Mouse X: %d\n", _mouseX ); 
        sprintf( y, "Mouse Y: %d", _mouseY ); 

	char *rstr = strcat( x, y );
	strcpy( info, rstr );

	PrintText( 40, 40, rstr );
	glutPostRedisplay();
  }
}

GLvoid window_special_key(int key, int x, int y) 
{    
    switch (key) 
    {    
        case GLUT_KEY_RIGHT: 
            letter_R.move( 10,0 );
            glutPostRedisplay();
            break;

	case GLUT_KEY_LEFT: 
	     letter_R.move( -10,0 );
             glutPostRedisplay();
             break;
    
  default:
    //printf ("Pressing %d doesn't do anything.\n", key);
    break;
  }
}


// Declare initial window size, position, and display mode
//( single buffer and RGBA ).  Open window with "hello"
// in its title bar.  Call initialization routines.
// Register callback function to display graphics.
// Enter main loop and process events.
int main( int argc, char** argv )
{
    // init
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition( 100, 100 );
    glutCreateWindow( "Hello" );
    init();
    
    // callbacks
    glutDisplayFunc( display );
    glutSpecialFunc( window_special_key );
    glutMouseFunc( Mouse );

    glutMainLoop();
    return 0;   // ANSI C requires main to return int.
}
