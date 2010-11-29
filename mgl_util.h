#ifndef _MGL_UTIL
#define _MGL_UTIL
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>

void PrintText( int nX, int nY, char* pszText );
float distance( float, float, float, float );
float shortest_distance(float x, float y, float x1, float y1, float x2, float y2);
#endif
