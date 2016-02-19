#ifndef GLOBAL
#define GLOBAL

#include <QtGlobal>

#if defined(SPIDER_LIBRARY)
#  define SPIDER_EXPORT Q_DECL_EXPORT
#else
#  define SPIDER_EXPORT Q_DECL_IMPORT
#endif

#endif // GLOBAL

