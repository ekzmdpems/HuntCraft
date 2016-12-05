#include "stdafx.h"
#include "cStaticObject.h"

/*
cStaticObject::cStaticObject()
	: m_pMesh(nullptr), m_pShader(nullptr)
{
}


cStaticObject::~cStaticObject()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pShader);
	for each(auto it in m_mapMtlTex)
	{
		SAFE_RELEASE(it.second);
	}
	m_mapMtlTex.clear();
}
cStaticObject::cStaticObject(LPSTR szObjPath, LPSTR szSurface, D3DXMATRIXA16* matWorld)
{
	
	LoadSurface(szSurface, matWorld);		// 한객체만 부르게 만들어야함
}

void cStaticObject::Render()
{

}
bool cStaticObject::GetHeight(IN float x, OUT float& y, IN float z)
{
	// boundbox 안에있는지 확인해야함
	D3DXVECTOR3 vRayPos(x, 1000, z);
	D3DXVECTOR3 vRayDir(0, -1, 0);
	float u, v, d;
	for (size_t i = 0; i < m_vecSurface.size(); i += 3)
	{
		D3DXVECTOR3 v0 = m_vecSurface[i];
		D3DXVECTOR3 v1 = m_vecSurface[i + 1];
		D3DXVECTOR3 v2 = m_vecSurface[i + 2];
		if (D3DXIntersectTri(&v0, &v1, &v2, &vRayPos, &vRayDir, &u, &v, &d))
		{
			y = 1000 - d;
			return true;
		}
	}
	y = 0;
	return false;
}

void cStaticObject::LoadObject(std::string szPath, IN D3DXMATRIXA16* pmat)
{
	std::vector<D3DXVECTOR3>	vecV;
	std::vector<D3DXVECTOR3>	vecVN;
	std::vector<D3DXVECTOR2>	vecVT;
	std::vector<ST_PNT_VERTEX>	vecVertex;
	std::vector<DWORD>			vecAttr;

	std::string					sMtlName;

	FILE* fp = NULL;

	fopen_s(&fp, szPath.c_str(), "r");

	while (!feof(fp))
	{
		char szBuf[1024] = { '\0', };
		fgets(szBuf, 1024, fp);
		if (strlen(szBuf) == 0) continue;

		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'm')
		{
			char szMtlPath[1024];
			sscanf_s(szBuf, "%*s %s", szMtlPath, 1024);
			LoadMtlLib(szMtlPath);
		}
		else if (szBuf[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);
		}
		else if (szBuf[0] == 'g')
		{
		}
		else if (szBuf[0] == 'v')
		{
			if (szBuf[1] == 't')
			{
				float u, v;
				sscanf_s(szBuf, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if (szBuf[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
			else
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szBuf[0] == 'f')
		{
			int aIndex[3][3];
			sscanf_s(szBuf, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);

			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[aIndex[i][0] - 1];
				v.t = vecVT[aIndex[i][1] - 1];
				v.n = vecVN[aIndex[i][2] - 1];
				if (pmat)
				{
					D3DXVec3TransformCoord(&v.p, &v.p, pmat);
					D3DXVec3TransformNormal(&v.n, &v.n, pmat);
				}
				vecVertex.push_back(v);
			}

			vecAttr.push_back(m_mapMtlTex[sMtlName]->GetAttrID());
		}
	}

	fclose(fp);

	SAFE_RELEASE(m_pMesh);

	D3DXCreateMeshFVF(vecVertex.size() / 3,
		vecVertex.size(),
		D3DXMESH_MANAGED,
		ST_PNT_VERTEX::FVF,
		DEVICE,
		&m_pMesh);

	ST_PNT_VERTEX* pV = NULL;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy_s(pV, vecVertex.size() * sizeof(ST_PNT_VERTEX),&vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	for (size_t i = 0; i < vecVertex.size(); ++i)
	{
		pI[i] = i;
	}
	m_pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	m_pMesh->LockAttributeBuffer(0, &pA);
	memcpy_s(pA, vecAttr.size() * sizeof(DWORD), &vecAttr[0], vecAttr.size() * sizeof(DWORD));
	m_pMesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdj(m_pMesh->GetNumFaces() * 3);
	m_pMesh->OptimizeInplace(
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0],
		NULL,
		NULL,
		NULL);
}
void cStaticObject::LoadSurface(std::string szPath, IN D3DXMATRIXA16* pmat)
{
	std::vector<D3DXVECTOR3>	vecV;

	FILE* fp = NULL;
	fopen_s(&fp, szPath.c_str(), "r");

	while (!feof(fp))
	{
		char szBuf[1024] = { '\0', };
		fgets(szBuf, 1024, fp);
		if (strlen(szBuf) == 0) continue;

		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'v')
		{
			if (szBuf[1] == 't' || szBuf[1] == 'n');
			else
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szBuf[0] == 'f')
		{
			int aIndex[3];
			sscanf_s(szBuf, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&aIndex[0], &aIndex[1], &aIndex[2]);

			for (int i = 0; i < 3; ++i)
			{
				D3DXVECTOR3 p = vecV[aIndex[i] - 1];
				if (pmat)
				{
					D3DXVec3TransformCoord(&p, &p, pmat);
				}
				m_vecSurface.push_back(p);
			}
		}
	}

	fclose(fp);
}
void cStaticObject::LoadMtlLib(std::string szPath)
{
	m_mapMtlTex.clear();
	std::string sMtlName;
	auto nAttID = 0;
	
	D3DMATERIAL9* tempMTL = nullptr;
	float fAlpha = 0.0f;
	D3DXCOLOR cAmbient, cDiffuse, cSpecular;
	cAmbient = cDiffuse = cSpecular = { 0,0,0,0 };
	int illum = 0;

	FILE* fp = NULL;
	fopen_s(&fp, szPath.c_str(), "r");

	while (!feof(fp))
	{
		char szBuf[1024] = { '\0', };
		fgets(szBuf, 1024, fp);
		if (strlen(szBuf) == 0) continue;

		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'n')
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);

			m_mapMtlTex[sMtlName] = new cMTLnTEX;
			m_mapMtlTex[sMtlName]->SetAttrID(nAttID);
			nAttID++;
			tempMTL = &m_mapMtlTex[sMtlName]->GetMtl();
		}
		else if (szBuf[0] == 'K')
		{
			if (szBuf[1] == 'a')
			{
				sscanf_s(szBuf, "%*s %f %f %f", &cAmbient.r, &cAmbient.g, &cAmbient.b);
			}
			else if (szBuf[1] == 'd')
			{
				sscanf_s(szBuf, "%*s %f %f %f", &cDiffuse.r, &cDiffuse.g, &cDiffuse.b);
			}
			else if (szBuf[1] == 's')
			{
				sscanf_s(szBuf, "%*s %f %f %f", &cSpecular.r, &cSpecular.g, &cSpecular.b);
			}
		}
		else if (szBuf[0] == 'd')
		{
			sscanf_s(szBuf, "%*s %f", &fAlpha);	// 알파 값
		}
		else if (szBuf[0] == 'N')
		{
			sscanf_s(szBuf, "%*s %f", &tempMTL->Power);	// 스페큘러 거리
		}
		else if (szBuf[0] == 'i')
		{
			sscanf_s(szBuf, "%*s %n", &illum);	// 알파 값
		}
		else if (szBuf[0] == 'm')
		{
			tempMTL->Ambient = { cAmbient.r, cAmbient.g, cAmbient.b ,fAlpha };
			tempMTL->Diffuse = { cDiffuse.r, cDiffuse.g, cDiffuse.b ,fAlpha };
			tempMTL->Specular = { cSpecular.r, cSpecular.g, cSpecular.b ,fAlpha };
			cAmbient = cDiffuse = cSpecular = { 0,0,0,0 }; fAlpha = 0.0f;

			char szPath[1024];
			sscanf_s(szBuf, "%*s %s", szPath, 1024);
			m_mapMtlTex[sMtlName]->SetTexture(TEXTURE_MANAGER->GetTexture(szPath));
		}
	}
	fclose(fp);
}








*/
