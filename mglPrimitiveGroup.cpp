#include "mglPrimitiveGroup.h"
#include <stdio.h>
#include <string.h>


mglPrimitiveGroup::mglPrimitiveGroup()
{
    strcpy( name, "unnamed PrimitiveGroup" );

    dprintf("ctor mglPrimitiveGroup: adr: %x, name = %s\n", this, name );
    // initialize visual properties
    color.Red = 0;
    color.Green = 0;
    color.Blue = 1;

    line_width = 1;
    is_selected = false;
}

mglPrimitiveGroup::mglPrimitiveGroup( char* _name )
{
    strcpy( name, _name );
    if( DEBUG ) printf("ctor mglPrimitiveGroup: adr: %x, name = %s\n", this, name );

    color.Red = 0;
    color.Green = 0;
    color.Blue = 1;

    line_width = 1;
    is_selected = false;
}

mglPrimitiveGroup::~mglPrimitiveGroup()
{
    if( DEBUG ) printf("dtor mglPrimitiveGroup: adr: %x, name = %s\n", this, name );
    list<mglPrimitive*>::iterator i;

    for( i=primitives.begin(); i != primitives.end(); ++i )
	    delete (*i);
}

void mglPrimitiveGroup::print()
{
    printf("mglPrimitiveGroup; adr: %x, name = %s, items: %d\n",
            this, name, primitives.size());
    for( list<mglPrimitive*>::iterator it = primitives.begin(); it != primitives.end(); ++it )
        (*it)->print();
        
}

void mglPrimitiveGroup::add_line( int x1, int y1, int x2, int y2 )
{
    mglLine* line = new mglLine( x1, y1, x2, y2 );
    primitives.push_front( line );
}

void mglPrimitiveGroup::draw()
{
    is_selected ?
        glColor3f( selected_colour.Red, selected_colour.Green, selected_colour.Blue ):
        glColor3f( default_colour.Red, default_colour.Green, default_colour.Blue );
    
    glLineWidth( line_width );

    list<mglPrimitive*>::iterator i;

    for( i=primitives.begin(); i != primitives.end(); ++i )
        (*i)->draw();

    glutPostRedisplay();
}

void mglPrimitiveGroup::scale( float x_dir, float y_dir )
{
    list<mglPrimitive*>::iterator i;

    for( i=primitives.begin(); i != primitives.end(); ++i )
        (*i)->scale( x_dir, y_dir );

    glutPostRedisplay();
}

void mglPrimitiveGroup::rotate( float theta, float x_rel, float y_rel )
{
    
    list<mglPrimitive*>::iterator i;

    for( i=primitives.begin(); i != primitives.end(); ++i )
        (*i)->rotate( theta, x_rel, y_rel );
    
    glutPostRedisplay();
}

void mglPrimitiveGroup::move( int x_dist, int y_dist )
{
    list<mglPrimitive*>::iterator i;

    for( i=primitives.begin(); i != primitives.end(); ++i )
        (*i)->move( x_dist, y_dist );
    
    glutPostRedisplay();
}

float mglPrimitiveGroup::min_distance_to( int x, int y )
{
    float min_distance = 999999;

    list<mglPrimitive*>::iterator i;

    for( i=primitives.begin(); i != primitives.end(); ++i )
    {
        float this_prim_dist = (*i)->distance_to( x, y );
	if( this_prim_dist < min_distance ) min_distance = this_prim_dist;
    }

    return min_distance;
}

float mglPrimitiveGroup::max_distance_to( int x, int y )
{
    float max_distance = 0;
    
    list<mglPrimitive*>::iterator i;

    for( i=primitives.begin(); i != primitives.end(); ++i )
    {
        float this_prim_dist = (*i)->distance_to( x, y );
	if( this_prim_dist > max_distance ) max_distance = this_prim_dist;
    }

    return max_distance;
}

