#pragma once
#include"SceneBase.h"
#include"SpriteRender.h"

class GameManager;

//  ゲーム画面
class SceneIngame :public SceneBass
{
    //  定数
#define PLAYERSPEEDLR 5.0f  //  プレイヤーの左右移動速度

#define PLAYER_IMAGE_W 75   //  プレイヤー画像の幅
#define PLAYER_IMAGE_H 75   //  プレイヤー画像の高さ

#define CAN_IMAGE_W 75      //   缶画像の幅
#define CAN_IMAGE_H 75      //  缶画像の高さ

    const float BG_IMAGE_H = 20000.0f;  //  背景画像の描画サイズ

    //  画像描画クラス呼び出し
    std::unique_ptr<SpriteRender>m_render;
  
    //  座標
    float playerPos_x = 0;      //  プレイヤー
    float playerPos_y = 0;

    //  プレイヤーの状態
    enum
    {
        PLAYER_STATE_IDLE,
        PLAYER_STATE_JUMP,
        PLAYER_STATE_FALL,
        PLAYER_STATE_KICK,
    };
    int playerState = PLAYER_STATE_IDLE;

    int kickAnimaFlame = 0;     //  蹴るアニメーションのフレーム数

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

    //  累積高度
    float totalHeight = 0.0f;

    //  エリアごとの目標高度
    const float EARTH_TO_SPACE_HEIGHT = 10000.0f;    //  地球から宇宙までの高度
    const float SPACE_TO_GALAXY_HEIGHT = 20000.0f;   //  宇宙から銀河までの高度

    //  重力
    const float EARTH_GRAVITY = 0.5f;    //  地球の重力
    const float SPACE_GRAVITY = 0.1f;    //  宇宙の重力
    const float GALAXY_GRAVITY = 0.01f;   //  銀河の重力
    float GetGravity(float height);   //  高度に応じた重力を取得
    

    float cameraOffsetY = 0.0f;         //  カメラ移動量

    //  缶の物理情報
    float canVelocityY = 0.0f;          //  上下速度
    float canVelocityX = 0.0f;
    bool canLaunched = false;           //  缶が蹴られたかどうか
    
    //  缶の蹴る力
    const float EARTH_KICH_POWER = 15.0f;
    const float SPACE_KICK_POWER = 6.0f;
    const float GALAXY_KICK_POWER = 2.0f;

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

    float GetCanKichPower(float height);   //  高度に応じた缶の蹴る力を取得

    bool GameOver();
};