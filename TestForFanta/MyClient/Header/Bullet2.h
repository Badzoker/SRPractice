#pragma once

#include "GameObject.h"
BEGIN(Engine)

class CBullet2Tex;
class CTexture;
class CTransform;

END

class CBullet2 : public CGameObject
{
private:
	explicit CBullet2(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBullet2();


public:
	virtual HRESULT Ready_GameObject();
	virtual _int	Update_GameObject(const _float& fTimeDelta);
	virtual void	LateUpdate_GameObject();
	virtual void	Render_GameObject();


private:
	HRESULT Add_Component();

private:
	Engine::CBullet2Tex* m_pBufferCom;
	Engine::CTexture* m_pTextureCom;
	Engine::CTransform* m_pTransformCom;


public:
	static CBullet2* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free();
};



