#include "Bullet2Tex.h"

CBullet2Tex::CBullet2Tex()
{
}

CBullet2Tex::CBullet2Tex(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{
}

CBullet2Tex::CBullet2Tex(const CBullet2Tex& rhs)
	: CVIBuffer(rhs)
{
}

CBullet2Tex::~CBullet2Tex()
{
}

HRESULT CBullet2Tex::Ready_Buffer()
{
	m_dwTriangleCount = 2;
	m_dwVertexCount = 4;
	m_dwVertexSize = sizeof(VTXTEX);
	m_dwFVF = FVF_TEX;

	m_dwIndexSize = sizeof(INDEX32);
	m_IndexFormat = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	VTXTEX* pVertex = NULL;

	m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPosition = { -1.f, 1.f, 0.f };
	pVertex[0].vTexUV = { 0.f, 0.f };

	pVertex[1].vPosition = { 1.f, 1.f, 0.f };
	pVertex[1].vTexUV = { 1.f, 0.f };

	pVertex[2].vPosition = { 1.f, -1.f, 0.f };
	pVertex[2].vTexUV = { 1.f, 1.f };

	pVertex[3].vPosition = { -1.f, -1.f, 0.f };
	pVertex[3].vTexUV = { 0.f, 1.f };

	m_pVertexBuffer->Unlock();

	INDEX32* pIndex = nullptr;

	m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);

	// 오른쪽 위
	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	// 왼쪽 아래
	pIndex[1]._0 = 0;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 3;

	m_pIndexBuffer->Unlock();
	return S_OK;
}

void CBullet2Tex::Render_Buffer()
{
	CVIBuffer::Render_Buffer();
}

CBullet2Tex* CBullet2Tex::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBullet2Tex* pBullet2Tex = new CBullet2Tex(pGraphicDev);
	if (FAILED(pBullet2Tex->Ready_Buffer()))
	{
		Safe_Release(pBullet2Tex);
		MSG_BOX("Bullet2Tex Create Failed");
		return nullptr;
	}
	return pBullet2Tex;
}

CComponent* CBullet2Tex::Clone()
{
	return new CBullet2Tex(*this);
}

void CBullet2Tex::Free()
{
	CVIBuffer::Free();
}
