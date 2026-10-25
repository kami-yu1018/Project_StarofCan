#include"Scene_Ingame.h"
#include"GameManager.h"
#include"Scene_Result.h"

//  初期化処理
void SceneIngame::OnEnter(GameManager* manager)
{
    //  サイズ設定
    //  プレイヤー
    playerWidth = D3D.gameWidth * 0.12f;
    playerHeight = D3D.gameHeight * 1.5f;
    //  缶
    canWidth = D3D.gameWidth * 0.08;
    canHeight = D3D.gameHeight * 1.5;

}
//  更新処理
void SceneIngame::OnUpdate(GameManager* manager, float deltaTime)
{

}
//  終了処理
void SceneIngame::OnExit(GameManager* manager)
{

}

const std::string SceneIngame::GetName()const
{
    return"Ingame";
}