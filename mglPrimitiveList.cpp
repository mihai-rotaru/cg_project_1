#include "mglPrimitiveList.h"

void mglPrimitiveList::add_front( mglPrimitive* p_prim )
{
    primitives.push_front( p_prim );
}

void mglPrimitiveList::add_back( mglPrimitive* p_prim )
{
    primitives.push_back( p_prim );
}

void mglPrimitiveList::add_line( int x1, int y1, int x2, int y2 )
{
    mglLine* line = new mglLine( x1, y1, x2, y2 );
    primitives.push_front( line );
}

void mglPrimitiveList::draw()
{
    list<mglPrimitive*>::iterator i;

    for( i=primitives.begin(); i != primitives.end(); ++i )
        (*i)->draw();
}

void mglPrimitiveList::scale( float f )
{
}

void mglPrimitiveList::rotate( float f )
{
}

void mglPrimitiveList::move( int x_dist, int y_dist )
{
}
