#include "stdafx.h"
#include "cUIManager.h"
#include "cUIObject.h"

cUIManager::cUIManager() : m_pSprite(NULL), m_pTexture(NULL),
m_pSprite2(NULL), m_pTexture2(NULL)
{
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
}


cUIManager::~cUIManager()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pSprite2);
	SAFE_RELEASE(m_pTexture2);
	for each(auto p in v_mChild)
	{
		SAFE_DELETE(p);
	}
}
cUIObject* cUIManager::GetUI(eUIType e)
{
	return nullptr;
}
void cUIManager::Destroy()
{
	for each(auto it in m_mapUIObject)
	{
		SAFE_RELEASE(it.second);
	}
}

void cUIManager::Init(cUIManager* root, Element element , const char* name, const char* name2, POINT pos)
{
	isAble = false;

	isClicked = false;

	isSelected = 0;

	e_type = element;

	pos_x = pos.x;
	pos_y = pos.y;
	m_Parent = root;

	isActive = false;

	D3DXCreateTextureFromFileEx(
		DEVICE,
		name,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_stImageInfo,
		NULL,
		&m_pTexture);
	D3DXCreateSprite(DEVICE, &m_pSprite);

	D3DXCreateTextureFromFileEx(
		DEVICE,
		name2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_stImageInfo2,
		NULL,
		&m_pTexture2);

	D3DXCreateSprite(DEVICE, &m_pSprite2);

	for each(auto p in v_mChild)
	{
		p->SetMoveX(m_MoveX);
		p->SetMoveY(m_MoveY);
		p->SetDragAble(isMove);
	}
	SetRect(&UI, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);
}

void cUIManager::Update()
{
	if (m_Parent != NULL)
	{
		m_MoveX = m_Parent->GetMoveX();
		m_MoveY = m_Parent->GetMoveY();
		switch (e_type)
		{
		case EX:
			isActive = m_Parent->GetActived();
			break;
		case BUTTON:
			if (m_Parent->GetSelected() == 0)
			{
				isActive = m_Parent->GetActived();
			}
			else
			{
				isActive = false;
			}
			break;
		}
	}

	for each(auto p in v_mChild)
	{
		p->SetMoveX(m_MoveX);
		p->SetMoveY(m_MoveY);
		p->SetDragAble(isMove);
	}
}

void cUIManager::render()
{
	D3DXMATRIXA16 matT;

	if (m_Parent == NULL)
	{
		D3DXMatrixTranslation(&matT, m_MoveX, m_MoveY, 0);
	}
	else
	{
		D3DXMatrixTranslation(&matT, m_Parent->GetMoveX(), m_Parent->GetMoveY(), 0);
	}
	if (e_type != BUTTON)
	{
		if (isClicked)
		{
			m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
			m_pSprite->SetTransform(&matT);
			m_pSprite->Draw(m_pTexture2,
				&UI,
				&D3DXVECTOR3(0, 0, 0),
				&D3DXVECTOR3(pos_x, pos_y, 0),
				D3DCOLOR_XRGB(255, 255, 255));
			m_pSprite->End();
		}
		else
		{
				m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
				m_pSprite->SetTransform(&matT);
				m_pSprite->Draw(m_pTexture,
					&UI,
					&D3DXVECTOR3(0, 0, 0),
					&D3DXVECTOR3(pos_x, pos_y, 0),
					D3DCOLOR_XRGB(255, 255, 255));
				m_pSprite->End();
		}
	}

	for each(auto p in v_mChild)
	{
		p->SetMoveX(m_MoveX);
		p->SetMoveY(m_MoveY);
		p->SetDragAble(isMove);
	}
}

void cUIManager::setChild(cUIManager *_child)
{
	v_mChild.push_back(_child);
}

void cUIManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	POINT pt_Mouse;

	pt_Mouse.x = LOWORD(lParam);
	pt_Mouse.y = HIWORD(lParam);

	if (isActive)
	{
		switch (message)
		{
		case WM_LBUTTONDOWN:
			m_ptPrevMouse.x = LOWORD(lParam);
			m_ptPrevMouse.y = HIWORD(lParam);

			if (isMove)
				m_isLButtonDown = true;

			if (isAble)
				isClicked = true;

			break;
		case WM_LBUTTONUP:
			m_isLButtonDown = false;
			isClicked = false;
			if (m_Parent != NULL)
			{
				if (isAble)
				{
					switch (e_type)
					{
					case EX:
						m_Parent->SetActived(false);
						m_Parent->SetSelected(0);
						break;
					case BUTTON:
						m_Parent->SetSelected(1);
						break;
					}
				}
			}
			break;
		case WM_MOUSEMOVE:
		{
			if (m_isLButtonDown)
			{
				if (isMove)
				{
					POINT ptCurrMouse;
					ptCurrMouse.x = LOWORD(lParam);
					ptCurrMouse.y = HIWORD(lParam);

					int nDeltaX = ptCurrMouse.x - m_ptPrevMouse.x;
					int nDeltaY = ptCurrMouse.y - m_ptPrevMouse.y;


					m_MoveX += nDeltaX * 1.0f;
					m_MoveY += nDeltaY * 1.0f;

					m_ptPrevMouse = ptCurrMouse;

				}

			}

			if ((UI.left + m_MoveX + pos_x <= pt_Mouse.x && (UI.right - 27) + m_MoveX + pos_x >= pt_Mouse.x)
				&& (UI.top + m_MoveY + pos_y <= pt_Mouse.y && (UI.bottom / 3) + m_MoveY + pos_y >= pt_Mouse.y))
			{
				isMove = true;
			}
			else { isMove = false; }

			if ((UI.left + m_MoveX + pos_x <= pt_Mouse.x && UI.right + m_MoveX + pos_x >= pt_Mouse.x)
				&& (UI.top + m_MoveY + pos_y <= pt_Mouse.y && UI.bottom + m_MoveY + pos_y >= pt_Mouse.y))
			{
				isAble = true;
			}
			else { isAble = false; }
		}
		break;
		}
	}
}
