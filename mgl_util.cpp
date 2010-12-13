#include "mgl_util.h"

void PrintText( int nX, int nY, char* pszText )
{
    int lines;
    char *p;

    glColor3ub( 150, 150, 150 );
    glRasterPos2i( nX, nY );

    for( p=pszText, lines=0; *p; p++ )
    {
        if( *p == '\n' )
        {
            lines++;
            glRasterPos2i( nX, nY-(lines*18) );
        }

        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_10,  *p );
    }
}

// distance between two points
float distance( float x1, float y1, float x2, float y2 )
{
    return sqrt( ((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)) ) ;
}

float shortest_distance(float x, float y, float x1, float y1, float x2, float y2)
{
    float A = x - x1;
    float B = y - y1;
    float C = x2 - x1;
    float D = y2 - y1;

    float dot = (A * C) + (B * D);
    float len_sq = (C * C) + (D * D);
    float param = dot / len_sq;

    float xx,yy;

    if(param < 0)
    {
        xx = x1;
        yy = y1;
    }
    else if(param > 1)
    {
        xx = x2;
        yy = y2;
    }
    else
    {
        xx = x1 + ( param * C );
        yy = y1 + ( param * D );
    }

    return distance( x, y, xx, yy );//your distance function

}

int dprintf( char const * __restrict fmt, ... )
{
    if( DEBUG )
    {
        int ret;
        va_list ap;

        va_start( ap, fmt );
        ret = vfprintf( stdout, fmt, ap );
        va_end( ap );

        return ret;
    }
    return -1;
}

// approximate
mglColor3f brighter( int percentage, float& R, float& G, float& B )
{
    float max;
    mglColor3f retval;
    max = R > G ? R : G;
    max = max < B ? B: max;

    float r_ratio = (float)(R/max);
    float g_ratio = (float)(G/max);
    float b_ratio = (float)(B/max);

    retval.Red   = R + r_ratio * R;
    retval.Green = G + g_ratio * G;
    retval.Blue  = B + b_ratio * B;

    return retval;
}

void cycle_frame( int& current_frame, int max_frames )
{
    current_frame == max_frames ?
        current_frame = 1 :
        current_frame++;
}
