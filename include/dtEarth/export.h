#pragma once


#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
#   ifdef DT_EARTH_LIBRARY
#      define DT_EARTH_EXPORT __declspec(dllexport)
#   else
#      define DT_EARTH_EXPORT __declspec(dllimport)
#   endif 
#else
#   ifdef DT_EARTH_LIBRARY
#      define DT_EARTH_EXPORT __attribute__ ((visibility("default")))
#   else
#      define DT_EARTH_EXPORT
#   endif 
#endif
