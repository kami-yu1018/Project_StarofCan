#pragma once
#include"SceneBase.h"
#include"SpriteRender.h"

class GameManager;

//  ゲーム画面
class SceneIngame :public SceneBass
{
    //  定数
#define PLAYERSPEEDLR 5.0f

    //  画像描画クラス呼び出し
    std::unique_ptr<SpriteRender>m_render;
  
    //  到達点

    //  座標
    float playerPos_x = 0;      //  プレイヤー
    float playerPos_y = 0;

    float canPos_x = 0;         //  缶
    float canPos_y = 0;

    //  サイズ
    float playerWidth = 0;      //  プレイヤー
    float playerHeight = 0;

    float canWidth = 0;         //  缶
    float canHeight = 0;

    //  ジャンプ関連
    float jumpHeight = 0.0f;            //  ジャンプ中の高さ
    float jumpSpd = 0.0f;               //  ジャンプ速度
    bool isJumping = false;             //  ジャンプ中かどうか

    const float JUMP_POWER = 15.0f;     //  ジャンプ開始時の上向きの力
    const float GRAVITY = 0.5f;         //  重力

    float cameraOffsetY = 0.0f;         //  カメラ移動量

    //  缶の物理情報
    float canVelocityY = 0.0f;          //  上下速度
    float canVelocityX = 0.0f;
    bool canLaunched = false;           //  缶が蹴られたかどうか
    
    const float CAN_KICK_POWER_UD = 20.0f; //  缶を蹴った時の力
    const float CAN_KICK_POWER_LR = 5.0f;
    const float CAN_GRAVITY = 0.5f;     //  缶にかかる重力

public:
    void OnEnter(GameManager* manager);
    void OnUpdate(GameManager* manager, float deltaTime);
    void OnExit(GameManager* manager);
    const std::string GetName()const;

    void Jump(float deltaTime);     //  プレイヤーのジャンプ処理

    enum
    {
        RIGHT,
        LEFT,
    };
    int CheckPlayerCanCollision(); //  プレイヤーと缶の当たり判定

    bool GameOver();
};