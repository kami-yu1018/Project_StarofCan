#pragma once

class GameManager;

//  ó‘ÔŠî’êƒNƒ‰ƒX
class SceneBass
{
public:
    virtual ~SceneBass() = default;
    virtual void OnEnter(GameManager* manager) = 0;
    virtual void OnUpdate(GameManager* manager, float deltaTime) = 0;
    virtual void OnExit(GameManager* manager) = 0;
};