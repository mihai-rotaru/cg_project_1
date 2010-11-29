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

        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18,  *p );
    }
}
