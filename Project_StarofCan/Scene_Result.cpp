#include"Scene_Result.h"
#include"GameManager.h"
#include"Scene_Title.h"
#include"key.h"

#include"DirectX.h"

//  初期化画面
void SceneResult::OnEnter(GameManager* manager)
{
    //  画像の読み込み
    m_render = std::make_unique<SpriteRender>();
    if (!m_render->Initialize())
        return;

    //  背景画像仮置き（後で変更）
    m_render->LoadTexture("BgImg", L"../data/image/title_bg.png");

}

//  更新処理
void SceneResult::OnUpdate(GameManager* manager, float deltaTime)
{
    //  画像の描画
    m_render->Begin();

    m_render->Draw("BgImg",D3D.m_screenWidth / 3.0f, 0, D3D.gameWidth, D3D.gameHeight);

    m_render->End();
}

//  終了処理
void SceneResult::OnExit(GameManager* manager)
{
    m_render->Release();
}

const std::string SceneResult::GetName()const
{
    return "Result";
}