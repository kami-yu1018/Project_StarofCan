#pragma once
#include"SceneBase.h"
#include"DirectX.h"

class GameManager;

//  ゲーム画面
class SceneIngame :public SceneBass
{
    //  プレイヤーサイズ
    float playerWidth = 0;
    float playerHeight = 0;

    //  缶サイズ
    float canWidth = 0;
    float canHeight = 0;

public:
    void OnEnter(GameManager* manager);
    void OnUpdate(GameManager* manager, float deltaTime);
    void OnExit(GameManager* manager);
    const std::string GetName()const;
};