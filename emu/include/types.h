#ifndef _H_TYPES_
#define _H_TYPES_

#include <vector3d.h>

typedef irr::core::vector3df vector3;

struct py_v3
{
    double x()
    {
        return x_;
    }
    double y()
    {
        return y_;
    }
    double z()
    {
         return z_;
    }
    py_v3()
    {
    }
    py_v3(vector3 const & v)
    {
        float c[4];
        v.getAs4Values(c);
        x_ = c[0];
        y_ = c[1];
        z_ = c[2];
    }
    double x_, y_, z_;
};

#endif //_H_TYPES_