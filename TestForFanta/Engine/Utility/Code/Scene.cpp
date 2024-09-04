#include "../../Header/Scene.h"

CScene::CScene(LPDIRECT3DDEVICE9 pGraphicDev) : m_pGraphicDev(pGraphicDev)
{
    m_pGraphicDev->AddRef();
}

CScene::~CScene()
{
}

CComponent* CScene::Get_Component(COMPONENTID eID, const _tchar* pLayerTag, const _tchar* pGameObjectTag, const _tchar* pComponentTag)
{
    auto iter = find_if(m_mapLayer.begin(), m_mapLayer.end(), CTag_Finder(pLayerTag));

    if (iter == m_mapLayer.end())
        return nullptr;

    return iter->second->Get_Component(eID, pGameObjectTag, pComponentTag);
}

HRESULT CScene::Ready_Scene()
{
    return S_OK;
}

_int CScene::Update_Scene(const _float& fTimeDelta)
{
    _int iResult(0);

    for (auto& pLayer : m_mapLayer)
    {
        iResult = pLayer.second->Update_Layer(fTimeDelta);

        if (iResult & 0x80000000)
            return iResult;

    }
    return iResult;
}

void CScene::LateUpdate_Scene()
{
    for (auto& pLayer : m_mapLayer)
        pLayer.second->LateUpdate_Layer();
}

void CScene::Render_Scene()
{
    for (auto& pLayer : m_mapLayer)
        pLayer.second->Render_Layer();
}

void CScene::Add_GameObject(CGameObject* _pGameObject)
{
    CGameObject::GAMEOBJECTID eObjectType = _pGameObject->Get_ObjectType();

    switch (eObjectType)
    {
    case CGameObject::GAMEOBJECTID::OBJECT_BULLET :
    {
        const _tchar* pLayerTag = L"Layer_GameLogic";
        auto iter = find_if(m_mapLayer.begin(), m_mapLayer.end(), CTag_Finder(pLayerTag));

        if (iter == m_mapLayer.end())
            return;
        
        const _tchar* pObjTag = L"Bullet";

        iter->second->Add_GameObject(L"Bullet", _pGameObject);

        break;
    }

    case CGameObject::GAMEOBJECTID::OBJECT_END:
        break;
    default :
        break;
    }

}

void CScene::Free()
{
    for_each(m_mapLayer.begin(), m_mapLayer.end(), CDeleteMap());
    m_mapLayer.clear();

    Safe_Release(m_pGraphicDev);
}
