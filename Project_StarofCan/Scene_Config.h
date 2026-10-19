#pragma once
#include"SceneBase.h"

class GameManager;

//  İ’è‰æ–Ê
class SceneConfig :public SceneBass
{
public:
    void OnEnter(GameManager* manager);
    void OnUpdate(GameManager* manager, float deltaTime);
    void OnExit(GameManager* manager);
    const std::string GetName()const;
};