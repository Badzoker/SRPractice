#pragma once

#include "GameObject.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;

class CBullet3 
	: public Engine::CGameObject
{
	enum class BULLETDIR { DIR_FORWARD, DIR_BACKWARD, DIR_LEFT, DIR_RIGHT };

private :
	explicit CBullet3(LPDIRECT3DDEVICE9 _pGraphicDev);
	virtual ~CBullet3();

public :
	static int Get_Count() { return m_iCount; }

	void Set_Pos(const _vec3* _pPos);

public :
	static CBullet3* Create(LPDIRECT3DDEVICE9 _pGraphicDev);

public :
	virtual HRESULT Ready_GameObject();
	virtual _int Update_GameObject(const _float& _fTimeDelta);
	virtual void LateUpdate_GameObject();
	virtual void Render_GameObject();

public :
	static void Add_Count() { m_iCount++; }

private :
	HRESULT Add_Component();

private :
	virtual void Free();

private :
	Engine::CRcTex* m_pBufferCom;
	Engine::CTexture* m_pTextureCom;
	Engine::CTransform* m_pTransformCom;

	float m_fSpeed;
	_float m_fLifeTime;
	_ulong m_ulLastTime;

	BULLETDIR m_eBulletDir;

	static int m_iCount;
};

END