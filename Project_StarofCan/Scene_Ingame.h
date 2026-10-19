#pragma once
#include"SceneBase.h"

class GameManager;

//  ƒQ[ƒ€‰æ–Ê
class SceneIngame :public SceneBass
{
public:
    void OnEnter(GameManager* manager);
    void OnUpdate(GameManager* manager, float deltaTime);
    void OnExit(GameManager* manager);
    const std::string GetName()const;
};