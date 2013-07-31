#ifndef LIB2_GLOBAL_HH
#define LIB2_GLOBAL_HH

#include <QtCore/qglobal.h>

#if defined(LIB2_LIBRARY)
#  define LIB2SHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIB2SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIB2_GLOBAL_HH
