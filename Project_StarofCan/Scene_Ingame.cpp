#include"Scene_Ingame.h"
#include"GameManager.h"
#include"Scene_Result.h"

#include"DirectX.h"


//  初期化処理
void SceneIngame::OnEnter(GameManager* manager)
{
    //  画像読み込み
    m_render = std::make_unique<SpriteRender>();
    if (!m_render->Initialize())
        return;

    m_render->LoadTexture("PlayerImg", L"../data/image/player.png");
    m_render->LoadTexture("CanImg", L"../data/image/can.png");

    //  サイズ設定
    //  プレイヤー
    playerWidth = D3D.gameWidth * 0.12f;
    playerHeight = D3D.gameHeight * 0.12f;
    //  缶
    canWidth = D3D.gameWidth * 0.08;
    canHeight = D3D.gameHeight * 0.08;

}
//  更新処理
void SceneIngame::OnUpdate(GameManager* manager, float deltaTime)
{




    //  画像の描画
    m_render->Begin();

    m_render->Draw("PlayerImg", playerPos_x, playerPos_y, playerWidth, playerHeight);
    m_render->Draw("CanImg", canPos_x, canPos_y, canWidth, canHeight);

    m_render->End();
}
//  終了処理
void SceneIngame::OnExit(GameManager* manager)
{

}

const std::string SceneIngame::GetName()const
{
    return"Ingame";
}