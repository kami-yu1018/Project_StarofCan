#pragma once
#include"SceneBase.h"
#include"SpriteRender.h"

class GameManager;

//  ゲーム画面
class SceneIngame :public SceneBass
{
    //  画像描画クラス呼び出し
    std::unique_ptr<SpriteRender>m_render;
   
    //  座標
    float playerPos_x = 0;      //  プレイヤー
    float playerPos_y = 0;

    float canPos_x = 0;         //  缶
    float canPos_y = 0;

    //  サイズ
    float playerWidth = 0;      //  プレイヤー
    float playerHeight = 0;

    float canWidth = 0;         //  缶
    float canHeight = 0;

public:
    void OnEnter(GameManager* manager);
    void OnUpdate(GameManager* manager, float deltaTime);
    void OnExit(GameManager* manager);
    const std::string GetName()const;
};