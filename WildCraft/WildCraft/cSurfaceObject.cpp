#include "stdafx.h"
#include "cSurfaceObject.h"


cSurfaceObject::cSurfaceObject()
	:m_pMesh(nullptr), m_pEffect(nullptr)
{
}


cSurfaceObject::~cSurfaceObject()
{
	SAFE_RELEASE(m_pMesh);
}

cSurfaceObject::cSurfaceObject(LPSTR szTexturePath, LPSTR szHeightMapPath
	, int numVertsPerRow, int numVertsPerCol, int cellSpacing)
{
	auto _numCellsPerRow = numVertsPerRow -1;
	auto _numCellsPerCol = numVertsPerCol -1;
	auto _width = _numCellsPerRow * cellSpacing;
	auto startX = -_width / 2;		
	auto endX = _width / 2;

	auto _depth = _numCellsPerCol * cellSpacing;
	auto startZ = _depth / 2;		
	auto endZ = -_depth / 2;

	auto _numVertices = numVertsPerRow * numVertsPerCol;
	auto _numTriangles = _numCellsPerRow * _numCellsPerCol * 2;

	auto uCoordIncrementSize = 1.0f / static_cast<float>(_numCellsPerRow);
	auto vCoordIncrementSize = 1.0f / static_cast<float>(_numCellsPerCol);
	
	
	std::vector<BYTE> vecHeight(_numVertices);
	FILE* _fp = nullptr;
	fopen_s(&_fp, szHeightMapPath, "rb");
	fread_s(&vecHeight[0], sizeof(BYTE) * _numVertices, sizeof(BYTE), _numVertices, _fp);
	fclose(_fp);

	D3DXCreateMeshFVF(_numTriangles, _numVertices,
		D3DUSAGE_WRITEONLY, ST_PNT_VERTEX::FVF, DEVICE, &m_pMesh);

	ST_PNT_VERTEX* pV = nullptr;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	int i = 0;
	for (int z = startZ; z >= endZ; z -= cellSpacing)
	{
		int j = 0;
		for (int x = startX; x <= endX; x += cellSpacing)
		{
			int index = i * numVertsPerRow + j;
			pV[index] = ST_PNT_VERTEX(
				D3DXVECTOR3(x, vecHeight[index], z),
				D3DXVECTOR3(0,1,0), D3DXVECTOR2(j * uCoordIncrementSize, i * vCoordIncrementSize));
			j++;
		}
		i++;
	}
	m_pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	int baseIndex = 0;
	for (auto i = 0; i < _numCellsPerCol; ++i)
	{
		for (int j = 0; j < _numCellsPerRow; ++j)
		{
			pI[baseIndex] = i * numVertsPerRow + j;
			pI[baseIndex + 1] = i * numVertsPerRow + j + 1;
			pI[baseIndex + 2] = (i+1) * numVertsPerRow + j;
			pI[baseIndex + 3] = (i+1) * numVertsPerRow + j;
			pI[baseIndex + 4] = i * numVertsPerRow + j + 1;
			pI[baseIndex + 5] = (i+1) * numVertsPerRow + j + 1;
			baseIndex += 6;
		}
	}
	m_pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	m_pMesh->LockAttributeBuffer(0, &pA);
	pA[0] = 0;
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
void cSurfaceObject::Render()
{
	//m_pEffect->Begin()
}
bool cSurfaceObject::GetHeight(IN float x, OUT float& y, IN float z)
{
	return false;
}