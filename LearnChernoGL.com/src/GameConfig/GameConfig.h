#pragma once

#include <iostream>

/* LOG Macro */
#ifdef _DEBUG
#define LOG(x) std::cout << x
#else
#define LOG(x)
#endif