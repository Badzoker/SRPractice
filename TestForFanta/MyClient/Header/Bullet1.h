#pragma once
#include "GameObject.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;

END

class CBullet1 : public CGameObject
{
private:
	explicit CBullet1(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBullet1();
public:
	virtual HRESULT Ready_GameObject();
	virtual _int Update_GameObject(const _float& fTimeDelta);
	virtual void LateUpdate_GameObject();
	virtual void Render_GameObject();
private:
	HRESULT Add_Component();
private:
	Engine::CRcTex* m_pBufferCom;
	Engine::CTexture* m_pTextureCom;
	Engine::CTransform* m_pTransformCom;
public:
	static CBullet1* Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	DWORD m_DeleteTime;

private:
	virtual void Free();

};

