#include "stdafx.h"
#include "cFontManager.h"


cFontManager::cFontManager()
{
}


cFontManager::~cFontManager()
{
}

LPD3DXFONT cFontManager::GetFont(eFontType e)
{
	if (m_mapFont.find(e) != m_mapFont.end())
		return m_mapFont[e];
	
	switch (e)
	{
	case eFontType::FT_NORMAL:
	{
		D3DXFONT_DESC fd;
		ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
		fd.Height = 25;
		fd.Width = 12;
		fd.Weight = FW_NORMAL;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
		//AddFontResource("umberto.ttf");	// 폰트 추가시 
		lstrcpy(fd.FaceName, L"궁서체");
		D3DXCreateFontIndirect(DEVICE, &fd, &m_mapFont[e]);
	}
		break;
	default:
		break;
	}
	return m_mapFont[e];
}

void cFontManager::Destroy()
{
	for each(auto it in m_mapFont)
	{
		SAFE_RELEASE(it.second);
	}
}


