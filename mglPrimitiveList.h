#include "mglPrimitive.h"
#include "mgl_structs.h"
#include <list>


class mglPrimitiveList
{
    list<mglPrimitive> primitives;
public:
    void add_front( mglPrimitive );
    void add_back(  mglPrimitive );
    
    void draw();
    void scale( float );
    void rotate( float );
    void move( int, int );
    int min_distance_to( mglPoint p );
    int max_distance_to( mglPoint p );
} 
