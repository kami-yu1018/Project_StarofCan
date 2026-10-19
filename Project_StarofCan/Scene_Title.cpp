#include"Scene_Title.h"
#include"GameManager.h"
#include"Scene_Config.h"
#include"Scene_Howto.h"
#include"Scene_Ingame.h"

#include"DirectX.h"

//  ‰Šú‰»ˆ
void SceneTitle::OnEnter(GameManager* manager)
{
    //  ‰æ‘œ“Ç‚İ‚İ
    m_render = std::make_unique<SpriteRender>();

    if (!m_render->Initialize())
        return;

    m_render->LoadTexture("TitleBg", L"../data/image/title_bg.png");    //  ƒQ[ƒ€”wŒi
}

//  XVˆ—
void SceneTitle::OnUpdate(GameManager* manager, float deltaTime)
{


    //  ‰æ‘œ‚Ì•`‰æ
    m_render->Begin();
    m_render->Draw("TitleBg", 0, 0, 900, 1300);
    m_render->End();


}

//  I—¹ˆ—
void SceneTitle::OnExit(GameManager* manager)
{
    //  ‰ğ•ú
    m_render->Release();
}

const std::string SceneTitle::GetName()const
{
    return"Title";
}