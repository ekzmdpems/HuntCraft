// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include <assert.h>

#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <functional>

// Base Data Types 헤더
#include "BaseDataTypesNFunctions.h"
#include "cObject.h"
#include "cBoundBox.h"
#include "cMTLnTEX.h"

// Static Manager 헤더
#include "cTimeManager.h"
#include "cKeyInputAssister.h"
#include "cDeviceManager.h"

#include "cTextureManager.h"
#include "cShaderManager.h"
#include "cFontManager.h"

#include "cGameDataManager.h"
#include "cSceneManager.h"
#include "cUIManager.h"

#pragma region 윈도우 관련 상수
extern HWND g_hWnd;
const DWORD WIN_START_POS_X = 0;
const DWORD WIN_START_POS_Y = 0;
const DWORD WIN_SIZE_WIDTH = 1280;
const DWORD WIN_SIZE_HEIGHT = 800;
const DWORD WIN_STYLE = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
#pragma endregion



//맵툴용 헤더
struct SKYBOXVERTEX
{
	D3DXVECTOR3 p;
	DWORD		diffuse;
	D3DXVECTOR2 t;
};

#define RadToDeg( radian ) ((radian) * 57.29577951f)
#define DegToRad( degrees ) ((degrees) * 0.017453293f)
#define D3DFVF_SKYBOXVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)