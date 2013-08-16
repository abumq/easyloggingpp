// A very simple sample demonstrating an app and shared-lib usage that both uses
// easylogging++ as their logging library.
//
// @since v9.01
// @author mkhan3189

#ifndef MYLIB_HH
#define MYLIB_HH

#include "mylib_global.hh"

class MYLIBSHARED_EXPORT Mylib
{
    
public:
    Mylib(void);
    virtual ~Mylib(void);
    float add(float x, float y) const;
    float sub(float x, float y) const;
    float mul(float x, float y) const;
    float div(float x, float y) const;
};

#endif // MYLIB_HH
