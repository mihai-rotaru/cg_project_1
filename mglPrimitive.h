#include "mgl_structs.h"

class mglPrimitive
{
public:
    virtual void draw();
    virtual float distance_to( mglPoint p );
    virtual void scale( float factor );
    virtual void rotate( float angle );
    virtual void move( int x_dist, int y_dist );
};    
