#ifndef _MGL_PRIMITIVE
#define _MGL_PRIMITIVE

#include "mgl_structs.h"

class mglPrimitive
{
public:
    virtual void draw()=0;
    virtual float distance_to( mglPoint p )=0;
    virtual void scale( float, float )=0;
    virtual void rotate( float,float,float )=0;
    virtual void move( int x_dist, int y_dist )=0;
};
#endif
