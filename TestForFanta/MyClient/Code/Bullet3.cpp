#include "pch.h"
#include "../Header/Bullet3.h"
#include "Export_System.h"
#include "Export_Utility.h"

int CBullet3::m_iCount = 0;

CBullet3::CBullet3(LPDIRECT3DDEVICE9 _pGraphicDev)
	: Engine::CGameObject(_pGraphicDev)
	, m_pBufferCom(nullptr)
	, m_pTextureCom(nullptr)
	, m_pTransformCom(nullptr)
	, m_fSpeed(100.f)
	, m_fLifeTime(1.f)
	, m_ulLastTime(0)
	, m_eBulletDir(BULLETDIR::DIR_LEFT)
{
	m_eGameObjectType = GAMEOBJECTID::OBJECT_BULLET;
}

CBullet3::~CBullet3()
{
}

void CBullet3::Set_Pos(const _vec3* _pPos)
{
	m_pTransformCom->Set_Position(_pPos->x, _pPos->y, _pPos->z);
}

CBullet3* CBullet3::Create(LPDIRECT3DDEVICE9 _pGraphicDev)
{
	CBullet3* pBullet = new CBullet3(_pGraphicDev);

	if (FAILED(pBullet->Ready_GameObject()))
	{
		Safe_Release(pBullet);
		MSG_BOX("Player Create Failed");
		return nullptr;
	}

	return pBullet;
}

HRESULT CBullet3::Ready_GameObject()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_ulLastTime = GetTickCount64();

	return S_OK;
}

_int CBullet3::Update_GameObject(const _float& _fTimeDelta)
{
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	_vec3 vDir{ 0.f, 0.f, 0.f };

	switch (m_eBulletDir)
	{
	case BULLETDIR::DIR_FORWARD:
		m_pTransformCom->Get_Info(INFO::INFO_LOOK, &vDir);
		break;
	case BULLETDIR::DIR_BACKWARD:
		m_pTransformCom->Get_Info(INFO::INFO_LOOK, &vDir);
		vDir -= vDir;
		break;
	case BULLETDIR::DIR_LEFT:
		m_pTransformCom->Get_Info(INFO::INFO_RIGHT, &vDir);
		vDir -= vDir;
		break;
	case BULLETDIR::DIR_RIGHT:
		m_pTransformCom->Get_Info(INFO::INFO_RIGHT, &vDir);
		break;
	default:
		break;
	}

	vDir = { -1.f, 0.f, 0.f };

	m_pTransformCom->Move_Position(&vDir, _fTimeDelta, m_fSpeed);

	return  Engine::CGameObject::Update_GameObject(_fTimeDelta);
}

void CBullet3::LateUpdate_GameObject()
{
	if ((float)(GetTickCount64() - m_ulLastTime) >= m_fLifeTime * 1000.f)
		m_bDead = true;

	Engine::CGameObject::LateUpdate_GameObject();
}

void CBullet3::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pTextureCom->Set_Texture();
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

HRESULT CBullet3::Add_Component()
{
	CComponent* pComponent = NULL;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_BulletRcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_BulletRcBuffer", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_BulletTexture"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Com_BulletTextureBuffer", pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_BulletTransform", pComponent });

	return S_OK;
}

void CBullet3::Free()
{
	m_iCount--;

	Engine::CGameObject::Free();
}