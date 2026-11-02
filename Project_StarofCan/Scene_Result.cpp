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

   
    m_render->LoadTexture("BgImg", L"../data/image/title_bg.png");              //  背景画像仮置き（後で変更）
    m_render->LoadTexture("RetryButton", L"../data/image/button_retry.png");            //   リトライ
    m_render->LoadTexture("BackTitleButton",L"../data/image/button_backtitle.png");     //  タイトルに戻る
}

//  更新処理
void SceneResult::OnUpdate(GameManager* manager, float deltaTime)
{
    //  ウィンドウサイズを取得
    float screenW = static_cast<float>(D3D.m_screenWidth);
    float screenH = static_cast<float>(D3D.m_screenHeight);
    //  ボタン座標とサイズを取得
    float buttonW = screenW * 0.3f;
    float buttonH = screenH * 0.1f;

    float buttonX = (screenW - buttonW) * 0.5f;
    float buttonY[2] = { screenH * 0.6f,screenH * 0.73f };

    //  画像の描画
    m_render->Begin();

    m_render->Draw("BgImg",D3D.m_screenWidth / 3.0f, 0, D3D.gameWidth, D3D.gameHeight);     //  背景画像
    m_render->Draw("RetryButton", buttonX, buttonY[0], buttonW, buttonH);                   //  リトライボタン
    m_render->Draw("BackTitleButton", buttonX, buttonY[1], buttonW, buttonH);               //  タイトルに戻るボタン

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