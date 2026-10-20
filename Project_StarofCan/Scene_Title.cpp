#include"Scene_Title.h"
#include"GameManager.h"
#include"Scene_Config.h"
#include"Scene_Howto.h"
#include"Scene_Ingame.h"

#include"DirectX.h"

//  初期化処
void SceneTitle::OnEnter(GameManager* manager)
{
    //  画像読み込み
    m_render = std::make_unique<SpriteRender>();

    if (!m_render->Initialize())
        return;

    m_render->LoadTexture("TitleBg", L"../data/image/title_bg.png");    //  ゲーム背景
    m_render->LoadTexture("TitleRogo", L"../data/image/title_rogo.png");    //  タイトルロゴ
    m_render->LoadTexture("PlayButton", L"../data//image/button_gameplay.png"); //  ゲームプレイ
    m_render->LoadTexture("HowtoButton", L"../data/image/button_howto.png");    //  遊び方
    m_render->LoadTexture("ConfigButton", L"../data/image/button_config.png");  //  設定
}

//  更新処理
void SceneTitle::OnUpdate(GameManager* manager, float deltaTime)
{


    //  ウィンドウサイズ取得
    float screenW = static_cast<float>(D3D.m_screenWidth);
    float screenH = static_cast<float>(D3D.m_screenHeight);

    //  ボタンの座標とサイズを取得
    float buttonW = screenW * 0.3f;
    float buttonH = screenH * 0.1;

    float buttonX = (screenW - buttonW) * 0.5f;
    float buttonY[3] = { screenH * 0.6f,screenH * 0.7f,screenH * 0.8f };

    //  画像の描画
    m_render->Begin();

    float titleBg_W = screenW * 0.33f;
    float titleBg_H = screenH;
    float titleBg_X = (screenW - titleBg_W) * 0.5f;
    float titleBg_Y = 0;

    float rogo_W = screenW * 0.30f;
    float rogo_H = screenH * 0.30f;
    float rogo_X = (screenW - rogo_W) * 0.5f;
    float rogo_Y = screenH * 0.10f;

    m_render->Draw("TitleBg", titleBg_X, titleBg_Y, titleBg_W, titleBg_H);
    m_render->Draw("TitleRogo", rogo_X, rogo_Y, rogo_W, rogo_H);
    m_render->Draw("PlayButton", buttonX, buttonY[0], buttonW, buttonH);
    m_render->Draw("HowtoButton", buttonX, buttonY[1], buttonW, buttonH);
    m_render->Draw("ConfigButton", buttonX, buttonY[2], buttonW, buttonH);

    m_render->End();


}

//  終了処理
void SceneTitle::OnExit(GameManager* manager)
{
    //  解放
    m_render->Release();
}

const std::string SceneTitle::GetName()const
{
    return"Title";
}