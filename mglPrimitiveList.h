#include "mglPrimitive.h"
#include "mglLine.h"
#include <list>
using namespace std;


class mglPrimitiveList
{
public:
    list<mglPrimitive*> primitives;

    void add_front( mglPrimitive* p );
    void add_back(  mglPrimitive* p );

    void add_line( int x1, int y1, int x2, int y2 );     

    void draw();
    void scale( float );
    void rotate( float );
    void move( int, int );
    int min_distance_to( mglPoint p );
    int max_distance_to( mglPoint p );
}; 
