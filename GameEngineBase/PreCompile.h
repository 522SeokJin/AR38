#pragma once

// 이안에 들어있고 중복이 되는 헤더는 다시 빌드하지 않는다.

#include <Windows.h>

// Debug
#include <assert.h>
#include <crtdbg.h>

// data struct
#include <vector>
#include <list>
#include <map>

// std::
#include <string>
#include <functional>

// Math
#include <math.h>
#include <random>

// DirectX 마소에서 제공하는 simd 연산용 함수들을 사용할수있다.
#include <DirectXPackedVector.h>

// io
#include <io.h>
#include <filesystem>