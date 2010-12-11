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
#include "mglGroupManager.h"
#include "mgl_util.h"
using namespace std;

// version and build numbers
// these two variables will be correctly set just before
// the build in a temp copy of this file, which will be used
// in the compilation process. Therefore, their value shouldn't
// be modified by hand and their values left <unknown>
char VERSION[20] = "<unknown>";
char BUILD_NAME[70] = "<unknown>";

mglGroupManager visibleGroups("visibleGroups");
mglGroupManager selectedGroups("selectedGroups");
mglGroupManager hiddenGroups;
list<mglPrimitiveGroup*>::iterator tab_next;

mglPrimitiveGroup letter_M( "M" ), letter_R( "R" );
char info[256];

// modes:
// 0 - move
// 1 - scale
// 2 - rotate
int current_mode = 0;

void select( list<mglPrimitiveGroup*>::iterator& itB )
{
    dprintf("--> before selection of %s ( %x )\n", (*itB)->name, itB );
    visibleGroups.print();
    selectedGroups.print();
    
    if( selectedGroups.groups.size() != 0 )
    {
        list<mglPrimitiveGroup*>::iterator itS = selectedGroups.groups.begin();
        do
        {
            dprintf("select: *it: %x\n", (*itS));
            if( *itS != *itB ) //
            {
                dprintf("splicing from selected to visible ( de-selecting ) %s\n", (*itS)->name);
                (*itS)->is_selected = false;
                visibleGroups.groups.splice( visibleGroups.groups.begin(), selectedGroups.groups, itS );  
                visibleGroups.print();
                selectedGroups.print();
            }
            if( !selectedGroups.groups.empty()) itS++;
            else break;
        }
        while( itS != selectedGroups.groups.end());
    }
            
    if( !selectedGroups.groups.empty() )
    {
        ++itB;
        printf("%s is already selected\n", (*itB)->name );
        return;
    }
            
    dprintf("splicing from visible to selected: %s\n", (*itB)->name);
    (*itB)->is_selected = true;
    selectedGroups.groups.splice( selectedGroups.groups.begin(),visibleGroups.groups, itB );  

    dprintf("--> after selection\n");
    visibleGroups.print();
    selectedGroups.print();
}

void add_to_selection( mglPrimitiveGroup* prims )
{
    prims->is_selected = true;
    printf("unselect:  visibleGroups size: %d\n", visibleGroups.groups.size());
    printf("unselect:  selectedGroups size: %d\n", selectedGroups.groups.size());
}

void de_select_all()
{
    if( selectedGroups.groups.empty())
    {
        dprintf("cannot deselect - no selection\n");
        return;
    }
    
    list<mglPrimitiveGroup*>::iterator it = selectedGroups.groups.begin();
    if( selectedGroups.groups.size() == 1 )
    {
        (*it)->is_selected = false;
    }
    else
        do
        {
           (*it)->is_selected = false;
           ++it;
        } 
        while( it != selectedGroups.groups.end());
    visibleGroups.groups.splice( visibleGroups.groups.begin(), selectedGroups.groups );
}

void display( void )
{
    // clear all pixels
    glRenderMode( GL_RENDER );
    glClear( GL_COLOR_BUFFER_BIT );

    PrintText( 20, 50, info );
    PrintText( 10, glutGet( GLUT_WINDOW_HEIGHT ) - 15, VERSION );
    PrintText( 10, glutGet( GLUT_WINDOW_HEIGHT ) - 26, BUILD_NAME );

    visibleGroups.draw();
    selectedGroups.draw();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

void init( void )
{
    // select clearing color
    glClearColor( 0.0, 0.0, 0.0, 0.0 );

    // initialize viewing values
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( -500,500,-500,500 );

    glEnable( GLUT_MULTISAMPLE );
    glEnable(GL_LINE_SMOOTH);
    int buf=-100;
    glGetIntegerv(GLUT_WINDOW_NUM_SAMPLES, &buf);
    printf("number of samples is %d\n", buf);
    
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
    
    visibleGroups.add_back( &letter_M );
    visibleGroups.add_back( &letter_R );

    //select( &letter_M ); // will have to overload 'select' to support this
    tab_next = visibleGroups.groups.begin();
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
    case 9: // TAB
        select( tab_next );
        if( !visibleGroups.groups.empty())
            if( visibleGroups.groups.size() == 1 ) tab_next = visibleGroups.groups.begin();
            else tab_next++;
        break;

	}
	sprintf( info, "Current mode: %d\n", current_mode );
}

void Mouse(int button, int state, int _mouseX, int _mouseY)
{
    _mouseY = glutGet( GLUT_WINDOW_HEIGHT ) - _mouseY;
    
    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            dprintf("\n\nON CLICK:\n");
            visibleGroups.print();
            selectedGroups.print();
            dprintf("\n");
            if( ! visibleGroups.groups.empty())
            {
                if( visibleGroups.groups.size() == 1 )
                {
                    list<mglPrimitiveGroup*>::iterator single = visibleGroups.groups.begin();
                    if( (*single)->min_distance_to( _mouseX, _mouseY ) <= 1 + (int)((*single)->line_width))
                        select( single );
                    else de_select_all();
                }
                else // more than 1 groups are visible
                {
                    bool found = false;
                    list<mglPrimitiveGroup*>::iterator it = visibleGroups.groups.begin();
                    dprintf( "about to enter thw WHILE loop; visibleGroups.groups.size() = %d\n", visibleGroups.groups.size());
                    do
                    {
                            dprintf("\nWHILE LOOP: it: %x *it: %x\n", it, *it );
                            dprintf("front():%x\nit:     %x\n*it:    %x\nback(): %x\nend():  %x\n\n",
                                    visibleGroups.groups.front(),
                                    it, (*it),
                                   visibleGroups.groups.back(), visibleGroups.groups.end()); 
                            dprintf("checking distance of %s to %d, %d...\n", (*it)->name, _mouseX, _mouseY );
                            float dist = (*it)->min_distance_to( _mouseX, _mouseY );
                            if( dist <= 1 + (int)((*it)->line_width))
                            {
                                select( it ); // select is responasble for updating 'it'
                                found = true;
                                dprintf("selected ss %s\n", (*it)->name );
                            }
                            dprintf("checked distance of %s to %d, %d: = %.2f\n", (*it)->name, _mouseX, _mouseY, dist );
                            dprintf("iterator: %x, adress: %x\n", it, *it );
                            dprintf("incrementing the iterator...\n");
                            it++;
                            dprintf("iterator: %x, adress: %x\n", it, *it );
                    }
                    while( it != visibleGroups.groups.end() && !found );
                    dprintf("exited the for\n");
                    if( !found ) de_select_all();
                }
            }
                
        }

        else if (button == GLUT_RIGHT_BUTTON) 
        {
            letter_R.line_width+=1;
        }

        char *x = new char[20];
        char *y = new char[20];
        char *dm = new char[20];
        char *dr = new char[20];

        sprintf( x, " Mouse X: %d\n", _mouseX ); 
        sprintf( y, "Mouse Y: %d\n", _mouseY ); 
        sprintf( dm, "Distance: to M: %.2f; to R:%.2f\n",letter_M.min_distance_to( _mouseX, _mouseY ),
                letter_R.min_distance_to( _mouseX, _mouseY )); 

        char *rstr = strcat( x, y );
        strcpy( info, rstr );
        strcat( info, dm );

        glutPostRedisplay();
    }
  
}

GLvoid window_special_key(int key, int x, int y) 
{    
    switch( current_mode )
    {
        case 0: // NORMAL MODE
            switch( key )
            {
                case GLUT_KEY_RIGHT: selectedGroups.move( 10,  0 ); break;
                case GLUT_KEY_LEFT:  selectedGroups.move(-10,  0 ); break;
                case GLUT_KEY_UP:    selectedGroups.move(  0, 10 ); break;
                case GLUT_KEY_DOWN:  selectedGroups.move(  0,-10 ); break;
            }
            break;
        case 1: // SCALE
            switch( key )
            {
                case GLUT_KEY_RIGHT: selectedGroups.scale( 1.1, 1.0 ); break;
                case GLUT_KEY_LEFT:  selectedGroups.scale( 0.9, 1.0 ); break;
                case GLUT_KEY_UP:    selectedGroups.scale( 1.0, 1.1 ); break;
                case GLUT_KEY_DOWN:  selectedGroups.scale( 1.0, 0.9 ); break;
            }
            break;
       case 2: // ROTATE
            switch( key )
            {
                case GLUT_KEY_RIGHT: selectedGroups.rotate(  3, 0, 0 ); break;
                case GLUT_KEY_LEFT:  selectedGroups.rotate( -3, 0, 0 ); break;
            }
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
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE );
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition( 500, 100 );
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
