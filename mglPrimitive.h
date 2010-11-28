#include "mgl_structs.h"

class mglPrimitive
{
public:
    virtual void draw()=0;
    virtual float distance_to( mglPoint p )=0;
    virtual void scale( float factor )=0;
    virtual void rotate( float angle )=0;
    virtual void move( int x_dist, int y_dist )=0;
};    
