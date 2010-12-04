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
#include "mglPrimitiveGroup.h"
#include "mgl_util.h"
using namespace std;

mglPrimitiveGroup letter_M,letter_R;
int mouse_X, mouse_Y;
char info[256];

// modes:
// 0 - move
// 1 - scale
// 2 - rotate
int current_mode = 0;


void display( void )
{
    // clear all pixels
    glRenderMode( GL_RENDER );
    glClear( GL_COLOR_BUFFER_BIT );

    PrintText( 20, 50, info );

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

void myReshape( int nWidht, int nHeight )
{
    glViewport( 0, 0, (GLsizei)nWidht, (GLsizei)nHeight );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0, nWidht, 0, nHeight);
    glutPostRedisplay();
}



void myKeyboardFunc (unsigned char key, int x, int y)
{
	switch (key) {

	case 'm':
		current_mode = 0;
		glutPostRedisplay();
		break;
	case 's':
		current_mode = 1;
		glutPostRedisplay();
		break;
	case 'r':
		current_mode = 2;
		glutPostRedisplay();
		break;

	case 27:			// Escape key
		exit(0);
		break;
	}
	sprintf( info, "Current mode: %d\n", current_mode );
}

static void Mouse(int button, int state, int _mouseX, int _mouseY)
{
    _mouseY = glutGet( GLUT_WINDOW_HEIGHT ) - _mouseY;
    
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
	char *dm = new char[10];
	char *dr = new char[10];

        sprintf( x, " Mouse X: %d\n", _mouseX ); 
        sprintf( y, "Mouse Y: %d\n", _mouseY ); 
        sprintf( dm, "Distance to M: %.2f\n",letter_M.min_distance_to( _mouseX, _mouseY )); 

        
	char *rstr = strcat( x, y );
	strcpy( info, rstr );
	strcat( info, dm );

	glutPostRedisplay();
  }
}

GLvoid window_special_key(int key, int x, int y) 
{    
    switch (key) 
    {    
        case GLUT_KEY_RIGHT: 
            if( current_mode == 0 ) letter_R.move( 10,0 );
	    else if( current_mode == 1 ) letter_R.scale( 1.1,1.0 );
	    else if( current_mode == 2 ) letter_R.rotate( 5,0,0 );
	    else current_mode = 0;
            glutPostRedisplay();
            break;

	case GLUT_KEY_LEFT: 
	     if( current_mode == 0 ) letter_R.move( -10,0 );
	     else if( current_mode == 1 ) letter_R.scale( 0.9,1.0 );
	     else if( current_mode == 2 ) letter_R.rotate( -5,0,0 );
	     else current_mode = 0;
             glutPostRedisplay();
             break;
	
        case GLUT_KEY_UP:
	     if( current_mode == 0 ) letter_R.move( 0, 10 );
	     else if( current_mode == 1 ) letter_R.scale( 1.0, 1.1 );
	     else if( current_mode == 2 ) letter_R.rotate( 5,0,0 );
	     else current_mode = 0;
	     glutPostRedisplay();
	     break;
	
	case GLUT_KEY_DOWN:
	     if( current_mode == 0 ) letter_R.move( 0, -10 );
	     else if( current_mode == 1 ) letter_R.scale( 1.0 ,0.9 );
	     else if( current_mode == 2 ) letter_R.rotate( -5,0,0 );
	     else current_mode = 0;
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
    glutKeyboardFunc( myKeyboardFunc );
    glutMouseFunc( Mouse );
    glutReshapeFunc( myReshape );

    glutMainLoop();
    return 0;   // ANSI C requires main to return int.
}
