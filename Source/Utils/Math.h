#pragma once
#include <vector>

#ifdef WIN32 || _WINDOWS
    #ifdef _EXPORTING
        #define MATH_API    __declspec(dllexport)
    #elif _IMPORTING
        #define MATH_API    __declspec(dllimport)
    #else
        #define MATH_API
    #endif
#else
    #define MATH_API __attribute__ ((visibility ("default")))
#endif

namespace LifeExe {
    MATH_API int max(int x, int y);
    MATH_API int factorial(int n);
    MATH_API int sum(int n);
    MATH_API int random(int min, int max);
}

