#include "mglPrimitiveList.h"

mglPrimitiveList::mglPrimitiveList()
{
    // initialize visual properties
    color.Red = 0;
    color.Green = 0;
    color.Blue = 1;

    line_width = 1;
}

void mglPrimitiveList::add_line( int x1, int y1, int x2, int y2 )
{
    mglLine* line = new mglLine( x1, y1, x2, y2 );
    primitives.push_front( line );
}

void mglPrimitiveList::draw()
{
    glColor3f( color.Red, color.Green, color.Blue );
    glLineWidth( line_width );

    list<mglPrimitive*>::iterator i;

    for( i=primitives.begin(); i != primitives.end(); ++i )
        (*i)->draw();

    glutPostRedisplay();
}

void mglPrimitiveList::scale( float x_dir, float y_dir )
{
    list<mglPrimitive*>::iterator i;

    for( i=primitives.begin(); i != primitives.end(); ++i )
        (*i)->scale( x_dir, y_dir );

    glutPostRedisplay();
}

void mglPrimitiveList::rotate( float theta, float x_rel, float y_rel )
{
    
    list<mglPrimitive*>::iterator i;

    for( i=primitives.begin(); i != primitives.end(); ++i )
        (*i)->rotate( theta, x_rel, y_rel );
    
    glutPostRedisplay();
}

void mglPrimitiveList::move( int x_dist, int y_dist )
{
    list<mglPrimitive*>::iterator i;

    for( i=primitives.begin(); i != primitives.end(); ++i )
        (*i)->move( x_dist, y_dist );
    
    glutPostRedisplay();
}
