#ifndef _MGL_PRIMITIVE
#define _MGL_PRIMITIVE

#include "mgl_structs.h"

class mglPrimitive
{
public:
    virtual void draw()=0;
    virtual float distance_to( int, int )=0;
    virtual void scale( int ref_x, int ref_y, float, float )=0;
    virtual void scale( float, float )=0;
    virtual void rotate( float,float,float )=0;
    virtual void move( int x_dist, int y_dist )=0;
    virtual void print()=0;
    virtual int getMaxX( )=0;
    virtual int getMinX( )=0;
    virtual int getMaxY( )=0;
    virtual int getMinY( )=0;
    char name[30];
};
#endif
