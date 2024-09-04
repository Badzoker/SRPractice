#include"pch.h"
#include "../Header/Bullet1.h"
#include "Export_Utility.h"

CBullet1::CBullet1(LPDIRECT3DDEVICE9 pGraphicDev)
    :CGameObject(pGraphicDev), m_DeleteTime(GetTickCount64())
{
}

CBullet1::~CBullet1()
{
}

HRESULT CBullet1::Ready_GameObject()
{
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
    
    Engine::CTransform* pPlayerTransform = dynamic_cast<Engine::CTransform*>(Engine::Get_Component(ID_DYNAMIC, L"Layer_GameLogic", L"Player", L"Com_PlayerTransform"));
    NULL_CHECK_RETURN(pPlayerTransform, -1);

    _vec3 vPlayerPos;

    pPlayerTransform->Get_Info(INFO_POS, &vPlayerPos);
    m_pTransformCom->Set_Position(vPlayerPos.x, vPlayerPos.y, vPlayerPos.z);

    return S_OK;
}

_int CBullet1::Update_GameObject(const _float& fTimeDelta)
{
    _vec3 vLook;
    m_pTransformCom->Get_Info(INFO_LOOK, &vLook);
    m_pTransformCom->Move_Position(D3DXVec3Normalize(&vLook, &vLook), fTimeDelta, 10.f);

    Engine::Add_RenderGroup(RENDER_ALPHA, this);


    return  Engine::CGameObject::Update_GameObject(fTimeDelta);
}

void CBullet1::LateUpdate_GameObject()
{
   
    Engine::CGameObject::LateUpdate_GameObject();
}

void CBullet1::Render_GameObject()
{
    m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
    m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    m_pTextureCom->Set_Texture();
    m_pBufferCom->Render_Buffer();
    m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

HRESULT CBullet1::Add_Component()
{
    CComponent* pComponent = NULL;

    pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_Bullet1RcTex"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].insert({ L"Com_Bullet1RcBuffer", pComponent });

    pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_Bullet1Texture"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].insert({ L"Com_Bullet1TextureBuffer", pComponent });

    pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Bullet1Transform", pComponent });
    return S_OK;
}

CBullet1* CBullet1::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CBullet1* pBullet1 = new CBullet1(pGraphicDev);
    if (FAILED(pBullet1->Ready_GameObject()))
    {
        Safe_Release(pBullet1);
        MSG_BOX("Bullet1 Create Failed");
        return nullptr;
    }

    return pBullet1;
}

void CBullet1::Free()
{
    Engine::CGameObject::Free();
}
