#pragma once
#include"SceneBase.h"
#include"SpriteRender.h"

class GameManager;

//  Œ‹‰Ê‰æ–Ê
class SceneResult :public SceneBass
{
    std::unique_ptr<SpriteRender>m_render;

public:
    void OnEnter(GameManager* manager);
    void OnUpdate(GameManager* manager, float deltaTime);
    void OnExit(GameManager* manager);
    const std::string GetName()const;
};