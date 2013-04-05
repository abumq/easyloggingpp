#ifndef LIB1_GLOBAL_HH
#define LIB1_GLOBAL_HH

#include <QtCore/qglobal.h>

#if defined(LIB1_LIBRARY)
#  define LIB1SHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIB1SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIB1_GLOBAL_HH
