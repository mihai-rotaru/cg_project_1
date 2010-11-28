#include "mglPrimitiveList.h"

void mglPrimitiveList::add_front( const mglPrimitive& prim )
{
    primitives.push_front( prim );
}

void mglPrimitiveList::add_back( const mglPrimitive& prim )
{
    primitives.push_back( prim );
}

void mglPrimitiveList::draw()
{
    list<mglPrimitive>::iterator i;

    for( i=primitives.begin(); i != primitives.end(); ++i )
        (*i).draw();
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
