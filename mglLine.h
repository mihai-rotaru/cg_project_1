#ifndef _MGL_LINE
#define _MGL_LINE
#include "mglPrimitive.h"

class mglLine : virtual public mglPrimitive
{
public:
    // getters and setters
    int get_x1() { return x1; }
    int get_y1() { return y1; }
    int get_x2() { return x2; }
    int get_y2() { return y2; }
    void set_x1( int _x1 ) { x1 = _x1; }
    void set_y1( int _y1 ) { y1 = _y1; }
    void set_x2( int _x2 ) { x2 = _x2; }
    void set_y2( int _y2 ) { y2 = _y2; }

    mglLine( int, int, int, int );
    virtual void draw();
    virtual float distance_to( mglPoint );
    virtual void scale( float, float );
    virtual void rotate( float );
    virtual void move( int, int );
private:
    int x1,y1,x2,y2;
};
#endif
