#pragma once
#include"SceneBase.h"
#include"SpriteRender.h"

class GameManager;

//  タイトル画面
class SceneTitle :public SceneBass
{
    // 画像描画クラスの呼び出し
    std::unique_ptr<SpriteRender>m_render;

    enum
    {
        MODE_PLAY,
        MODE_HOWTO,
        MODE_CONFIG
    };

    int choseMode = MODE_PLAY;

public:
    void OnEnter(GameManager* manager);
    void OnUpdate(GameManager* manager, float deltaTime);
    void OnExit(GameManager* manager);
    const std::string GetName()const;
};