#include "mglPrimitiveList.h"

void mglPrimitiveList::add_front( mglPrimitive prim )
{
    primitives.push_front( prim );
}

void mglPrimitiveList::add_back( mglPrimitive prim )
{
    primitives.push_back( prim );
}

void draw()
{
    list<mglPrimitive>::iterator i;

    for( i=primitives.begin(); i != primitives.end(); ++i )
        *i.draw();
}

void scale( float f )
{
}

void rotate( float f )
{
}

void move( int x_dist, int y_dist )
{
}
