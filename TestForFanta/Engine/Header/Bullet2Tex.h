#pragma once
#include "VIBuffer.h"
BEGIN(Engine)
class ENGINE_DLL CBullet2Tex : public CVIBuffer
{
private:
	explicit CBullet2Tex();
	explicit CBullet2Tex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBullet2Tex(const CBullet2Tex& rhs);
	virtual ~CBullet2Tex();

public:
	virtual HRESULT Ready_Buffer();
	virtual void Render_Buffer();

public:
	static CBullet2Tex* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent* Clone();

private:
	virtual void Free();
};
END
