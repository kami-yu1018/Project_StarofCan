#pragma once
#include"SceneBase.h"
#include"SpriteRender.h"

class GameManager;

//  結果画面
class SceneResult :public SceneBass
{
    std::unique_ptr<SpriteRender>m_render;  //  画像描画クラスの呼び出し

    enum
    {
        MODE_RETRY,
        MODE_BACKTITLE
    };
    int choseMode = MODE_RETRY; //  選択中のモード

public:
    void OnEnter(GameManager* manager);
    void OnUpdate(GameManager* manager, float deltaTime);
    void OnExit(GameManager* manager);
    const std::string GetName()const;
};