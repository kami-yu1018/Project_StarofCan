#pragma once
#include"SceneBase.h"

class GameManager;

//  Œ‹‰Ê‰æ–Ê
class SceneResult :public SceneBass
{
public:
    void OnEnter(GameManager* manager);
    void OnUpdate(GameManager* manager, float deltaTime);
    void OnExit(GameManager* manager);
    const std::string GetName()const;
};