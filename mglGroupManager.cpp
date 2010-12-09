#include "mglGroupManager.h"
#include <stdio.h>
#include <string.h>

mglGroupManager::mglGroupManager( char* _name )
{
    strcpy( name, _name );
    if( DEBUG ) printf("ctor mglGroupManager: adr: %x, name = %s\n", this, name );
}

mglGroupManager::mglGroupManager()
{
    strcpy( name, "unnamed mglGroupManager" );
    if( DEBUG ) printf("ctor mglGroupManager: adr: %x, name = %s\n", this, name );
}

mglGroupManager::~mglGroupManager()
{
    if( DEBUG ) printf("dtor mglGroupManager: adr: %x, name =%s\n", this, name );
}


void mglGroupManager::print()
{
    //printf("printing...\n");
    printf("mglGroupManager; adr: %x, name = %s, items: %d\n",
            this, name, groups.size());
    for( list<mglPrimitiveGroup*>::iterator i=groups.begin(); i != groups.end(); ++i )
        (*i)->print();
}

void mglGroupManager::add_front( mglPrimitiveGroup* pg )
{
    printf("  adding %s to %s\n", pg->name, name );
    groups.push_front( pg );
    printf("   after addition:\n ");
    print();
}

void mglGroupManager::add_back( mglPrimitiveGroup* pg )
{
    printf("  adding %s to %s\n", pg->name, name );
    groups.push_back( pg );
    printf("   after addition:\n ");
    print();
}

void mglGroupManager::remove( mglPrimitiveGroup* pg )
{
    printf("removing PrimitiveGroup %s ( %x ) from GroupManager %s ( %x )\n", 
            pg->name, pg, this->name, this );
    if( groups.size() == 0 )
    {
        printf("trying to remove %x, but list is empty\n", pg );
        return;
    }
    groups.remove( pg );
    printf("removed PrimitiveGroup %s ( %x ) from GroupManager %s ( %x )\n", 
            pg->name, pg, this->name, this );
    //print();
}

void mglGroupManager::scale( float x_dir, float y_dir )
{
    list<mglPrimitiveGroup*>::iterator i;

    for( i=groups.begin(); i != groups.end(); ++i )
        (*i)->scale( x_dir, y_dir );

    glutPostRedisplay();
}

void mglGroupManager::rotate( float theta, float x_rel, float y_rel )
{
    
    list<mglPrimitiveGroup*>::iterator i;

    for( i=groups.begin(); i != groups.end(); ++i )
        (*i)->rotate( theta, x_rel, y_rel );
    
    glutPostRedisplay();
}

void mglGroupManager::move( float x_dist, float y_dist )
{
    list<mglPrimitiveGroup*>::iterator i;

    for( i=groups.begin(); i != groups.end(); ++i )
        (*i)->move( x_dist, y_dist );
    
    glutPostRedisplay();
}


void mglGroupManager::draw()
{
    if( groups.size() == 0 )
    {
        //printf("trying to draw list %x, but list is empty\n", this );
        return;
    }
    for( list<mglPrimitiveGroup*>::iterator it = groups.begin();
            it != groups.end(); it++ )
        (*it)->draw();
}
