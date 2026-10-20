#include"Scene_Config.h"
#include"GameManager.h"
#include"Scene_Title.h"

#include"key.h"

//  初期化処理
void SceneConfig::OnEnter(GameManager* manager)
{

}

//  更新処理
void SceneConfig::OnUpdate(GameManager* manager, float deltaTime)
{
    //  バックスペースでタイトル画面へ戻る
    if (PushHitKey(VK_BACK))
    {
        manager->ChangeState(std::make_unique<SceneTitle>());
    }
}

//  終了処理
void SceneConfig::OnExit(GameManager* manager)
{

}

const std::string SceneConfig::GetName()const
{
    return"Config";
}
