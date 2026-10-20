#include"Scene_Howto.h"
#include"GameManager.h"
#include"Scene_Title.h"

#include"key.h"

//  ‰Šú‰»ˆ—
void SceneHowto::OnEnter(GameManager* manager)
{

}

//  XVˆ—
void SceneHowto::OnUpdate(GameManager* manager, float deltaTime)
{
    if (PushHitKey(VK_BACK))
    {
        manager->ChangeState(std::make_unique<SceneTitle>());
    }
}

//  I—¹ˆ—
void SceneHowto::OnExit(GameManager* manager)
{

}

const std::string SceneHowto::GetName()const
{
    return"Howto";
}
