#include"GameManager.h"
#include"SceneBase.h"

//  コンストラクタ作動時にcurrentStateを初期化
GameManager::GameManager(std::unique_ptr<SceneBass>initialState)
    :isRunning(true),gameTime(0.0f),currentState(std::move(initialState))
{
    currentState->OnEnter(this);
}

//  次のステートに移行する時に使用する
void GameManager::ChangeState(std::unique_ptr<SceneBass>newState)
{
    currentState->OnExit(this);
    currentState = std::move(newState);
    currentState->OnEnter(this);
}

//  更新
void GameManager::Update(float deltaTime)
{
    gameTime += deltaTime;
    if (currentState)
    {
        currentState->OnUpdate(this, deltaTime);
    }
}