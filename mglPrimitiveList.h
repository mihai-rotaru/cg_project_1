#include "mglPrimitive.h"
//#include "mgl_structs.h"
#include <list>
using namespace std;


class mglPrimitiveList
{
public:
    list<mglPrimitive*> primitives;

    void add_front( mglPrimitive* p );
    void add_back(  mglPrimitive* p );
    
    void draw();
    void scale( float );
    void rotate( float );
    void move( int, int );
    int min_distance_to( mglPoint p );
    int max_distance_to( mglPoint p );
}; 
