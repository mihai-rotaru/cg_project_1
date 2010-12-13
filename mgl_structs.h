#ifndef _MGL_STRUCTS
#define _MGL_STRUCTS
struct mglPoint
{
    int x;
    int y;
};

struct mglColor3f
{
    float Red;
    float Green;
    float Blue;
};

// the following 2 lines work only with C++0x
const struct mglColor3f default_color { 0, 0, 1 };
const struct mglColor3f selected_color { 0, 1, 0};

#endif
