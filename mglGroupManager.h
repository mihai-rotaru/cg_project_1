#ifndef _MGL_GROUP_MANAGER_
#define _MGL_GROUP_MANAGER_

#include <list>
#include "mglPrimitiveGroup.h"
#include "mgl_util.h"

class mglGroupManager
{
public:
   list<mglPrimitiveGroup*> groups;
   char name[20];

   mglGroupManager();
   mglGroupManager( char* );
   ~mglGroupManager();
   void print();
   void add_front( mglPrimitiveGroup* ); 
   void add_back( mglPrimitiveGroup* );
   void remove( mglPrimitiveGroup* );

   void move( float, float );
   void rotate( float, float, float );
   void scale( float, float );

   void draw();
};

#endif
