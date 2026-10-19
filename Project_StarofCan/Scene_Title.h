#pragma once
#include"SceneBase.h"

class GameManager;

//  ƒ^ƒCƒgƒ‹‰æ–Ê
class SceneTitle :public SceneBass
{
public:
    void OnEnter(GameManager* manager);
    void OnUpdate(GameManager* manager, float deltaTime);
    void OnExit(GameManager* manager);
    const std::string GetName()const;
};