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

    float screenW = static_cast<float>(D3D.m_screenWidth);
    float screenH = static_cast<float>(D3D.m_screenHeight);

    //  ‰æ‘œ‚Ì•`‰æ
    m_render->Begin();

    float titleBg_W = screenW * 0.33f;
    float titleBg_H = screenH;

    float titleBg_X = (screenW - titleBg_W) * 0.5f;
    float titleBg_Y = 0;

    m_render->Draw("TitleBg", titleBg_X, titleBg_Y, titleBg_W, titleBg_H);
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