#include "pch.h"

#include "Export_Utility.h"
#include "../Header/Bullet2.h"

CBullet2::CBullet2(LPDIRECT3DDEVICE9 pGraphicDev)
	:Engine::CGameObject(pGraphicDev), m_pBufferCom(nullptr), m_pTextureCom(nullptr),m_pTransformCom(nullptr)
{
}

CBullet2::~CBullet2()
{
}

HRESULT CBullet2::Ready_GameObject()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

_int CBullet2::Update_GameObject(const _float& fTimeDelta)
{

	return  Engine::CGameObject::Update_GameObject(fTimeDelta);

}

void CBullet2::LateUpdate_GameObject()
{
}

void CBullet2::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pTextureCom->Set_Texture();
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

HRESULT CBullet2::Add_Component()
{
	CComponent* pComponent = NULL;

	pComponent = m_pBufferCom = dynamic_cast<CBullet2Tex*>(Engine::Clone_Proto(L"Proto_Bullet2Tex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Bullet2Tex", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_Bullet2Texture"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Bullet2Texture", pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Bullet2Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_Bullet2Transform", pComponent });

	return S_OK;
}

CBullet2* CBullet2::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBullet2* pBullet2 = new CBullet2(pGraphicDev);
	if (FAILED(pBullet2->Ready_GameObject()))
	{
		Safe_Release(pBullet2);
		MSG_BOX("Player Create Failed");
		return nullptr;
	}

	return pBullet2;
}

void CBullet2::Free()
{
	Engine::CGameObject::Free();
}
