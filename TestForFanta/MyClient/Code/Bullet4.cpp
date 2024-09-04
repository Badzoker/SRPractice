#include "pch.h"
#include "../Header/Bullet4.h"
#include "Export_Utility.h"
#include "Export_System.h"

CBullet4::CBullet4(LPDIRECT3DDEVICE9 pGraphicDev) : CGameObject(pGraphicDev), m_bIsRender(false), m_fTimer(0.f)
{
}

CBullet4::~CBullet4()
{
}

HRESULT CBullet4::Ready_GameObject()
{
    FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

    return S_OK;
}

_int CBullet4::Update_GameObject(const _float& fTimeDelta)
{
    _int iExit = Engine::CGameObject::Update_GameObject(fTimeDelta);

    Engine::Add_RenderGroup(RENDER_PRIORITY, this);

    Bullet_Launch(fTimeDelta);

    return iExit;
}

void CBullet4::LateUpdate_GameObject()
{
    Engine::CGameObject::LateUpdate_GameObject();
}

void CBullet4::Render_GameObject()
{
    if (m_bIsRender)
    {
        m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
        m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
        m_pTextureCom->Set_Texture();
        m_pBufferCom->Render_Buffer();
        m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    }
}

HRESULT CBullet4::Add_Component()
{
    CComponent* pComponent = NULL;

    pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_Bullet4RcTex"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].insert({ L"Com_Bullet4RcTexBuffer", pComponent });

    pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_Bullet4Texture"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_STATIC].insert({ L"Com_Bullet4TextureBuffer", pComponent });

    pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
    NULL_CHECK_RETURN(pComponent, E_FAIL);
    m_mapComponent[ID_DYNAMIC].insert({ L"Com_Bullet4Transform", pComponent });

    return S_OK;
}

HRESULT CBullet4::Bullet_Launch(const _float& fTimeDelta)
{
    //���� Bullet4 Key �Է� by InputDev
    if (Engine::Get_DIKeyState(DIK_SPACE) & 0x80)
    {
        //�ǳ��� �ʿ��ҵ�
        Set_Render_True();
    }
    if (m_bIsRender)
    {
        m_fTimer += fTimeDelta;
        if (m_fTimer > 5.f)
        {
            m_fTimer = 0.f;
            m_bIsRender = false;
        }
        _vec3 vLook;
        m_pTransformCom->Get_Info(INFO_LOOK, &vLook);
        m_pTransformCom->Move_Position(&vLook, fTimeDelta, -10.f);
    }
    else
    {
        Engine::CTransform* pPlayerTransform = dynamic_cast<Engine::CTransform*>(Engine::Get_Component(ID_DYNAMIC, L"Layer_GameLogic", L"Player", L"Com_PlayerTransform"));
        NULL_CHECK_RETURN(pPlayerTransform, -1);

        _vec3 vPlayerPos;

        pPlayerTransform->Get_Info(INFO_POS, &vPlayerPos);
        m_pTransformCom->Set_Position(vPlayerPos.x, vPlayerPos.y, vPlayerPos.z);
    }
    return S_OK;
}

CBullet4* CBullet4::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CBullet4* pBullet = new CBullet4(pGraphicDev);

    if (FAILED(pBullet->Ready_GameObject()))
    {
        Safe_Release(pBullet);
        MSG_BOX("Bullet4 Created Failed");
        return nullptr;
    }
    return pBullet;
}

void CBullet4::Free()
{
    Engine::CGameObject::Free();
}
