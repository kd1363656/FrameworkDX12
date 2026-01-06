#pragma once
//=============================================
// プリコンパイル済みヘッダー
//  ここに書いた者は初回のみ解析されるため、コンパイル時間が高速になる。
//  全てのcppからインクルードされる必要がある。
//=============================================

//=============================================
// 基本
//=============================================
#pragma comment(lib , "winmm.lib")

#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include <cassert>

#include <wrl/client.h>

//=============================================
// STL
//=============================================
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <array>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <memory>
#include <random>
#include <sstream>
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#include <filesystem>
#include <chrono>

#define _USE_MATH_DEFINES
#include <math.h>