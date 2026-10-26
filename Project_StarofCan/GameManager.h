#pragma once
#include<memory>

class SceneBass;

//  ƒQ[ƒ€ŠÇ—ƒNƒ‰ƒX
class GameManager
{
    std::unique_ptr<SceneBass>currentState;
    std::unique_ptr<SceneBass>nextState;

    bool isRunning;
    float deltaTime;
public:
    GameManager(std::unique_ptr<SceneBass>initialState);

    void ChangeState(std::unique_ptr<SceneBass>newState);
    void Update(float deltaTime);
};