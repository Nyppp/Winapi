#pragma once

//미리 컴파일된 헤더
//모든 cpp파일들은 미리 컴파일 된 헤더를 참조해야 함

#include <Windows.h>
#include <wchar.h>

#include <vector>
using std::vector;

#include<string>
using std::string;
using std::wstring;

#include <map>
using std::map;
using std::make_pair;

#include <assert.h>
#include <numbers>

//라이브러리 추가 시에는 이와 같이 선언
#pragma comment(lib, "Msimg32.lib")

#include "Define.h"
#include "Struct.h"