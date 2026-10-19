#pragma once
#include"SceneBase.h"

class GameManager;

//  —V‚Ñ•û‰æ–Ê
class SceneHowto :public SceneBass
{
public:
    void OnEnter(GameManager* manager);
    void OnUpdate(GameManager* manager, float deltaTime);
    void OnExit(GameManager* manager);
    const std::string GetName()const;
};