#include"Scene_Ingame.h"
#include"GameManager.h"
#include"Scene_Result.h"
#include"key.h"

#include"DirectX.h"


//  初期化処理
void SceneIngame::OnEnter(GameManager* manager)
{
    //  画像読み込み
    m_render = std::make_unique<SpriteRender>();
    if (!m_render->Initialize())
        return;

    m_render->LoadTexture("BgImg", L"../data/image/title_bg.png");    //  背景（仮）
    m_render->LoadTexture("PlayerImg", L"../data/image/player.png");    //  プレイヤー
    m_render->LoadTexture("CanImg", L"../data/image/can.png");          //  缶

    //  サイズ設定
    //  プレイヤー
    playerWidth = D3D.gameWidth * 0.12f;
    playerHeight = D3D.gameHeight * 0.12f;
    //  缶
    canWidth = D3D.gameWidth * 0.08;
    canHeight = D3D.gameHeight * 0.08;

    //  初期座標設定
    playerPos_x = D3D.m_screenWidth / 3.0f + (D3D.gameWidth * 0.5f);
    playerPos_y = D3D.gameHeight * 0.8;

    canPos_x = D3D.m_screenWidth / 3.0f + (D3D.gameWidth * 0.6f);
    canPos_y = D3D.gameHeight * 0.8;

    //  ジャンプ関連
    jumpHeight = 0.0f;
    jumpSpd = 0.0f;
    isJumping = false;
    cameraOffsetY = 0.0f;

}
//  更新処理
void SceneIngame::OnUpdate(GameManager* manager, float deltaTime)
{
    //  キー入力
    //  移動
    if (CheckHitKey(VK_RIGHT))   
    {
        playerPos_x += PLAYERSPEEDLR;
    }
    if (CheckHitKey(VK_LEFT))
    {
        playerPos_x -= PLAYERSPEEDLR;
    }

    //  ジャンプ
    if (PushHitKey(VK_SPACE))
    {
        jumpSpd += JUMP_POWER;
        isJumping = true;
    }
    if(isJumping) Jump(deltaTime);  //  ジャンプ処理

    //  カメラを反映した缶の画面座標
    float canScreenY = canPos_y + cameraOffsetY;
    //  プレイヤーと缶の当たり判定
    if (!canLaunched &&
        CheckPlayerCanCollision(canScreenY))
    {
        //  缶を蹴り上げる処理
        canVelocityY = CAN_KICK_POWER;
        
    }
    //  重力によって上昇速度を減少させる
    canVelocityY -= CAN_GRAVITY * deltaTime;

    //  上向きの速度が正なら缶は上昇、負なら落下
    canPos_y -= canVelocityY * deltaTime;
    


    //  画像の描画
    m_render->Begin();

    m_render->Draw("BgImg", D3D.m_screenWidth / 3.0f, cameraOffsetY, D3D.gameWidth, D3D.gameHeight);
    m_render->Draw("PlayerImg", playerPos_x, playerPos_y, playerWidth, playerHeight);
    m_render->Draw("CanImg", canPos_x, canPos_y, canWidth, canHeight);

    m_render->End();
}
//  終了処理
void SceneIngame::OnExit(GameManager* manager)
{

}

const std::string SceneIngame::GetName()const
{
    return"Ingame";
}

//  ジャンプの処理
void SceneIngame::Jump(float deltaTime)
{
    //  重力によってジャンプ速度を減少
    jumpSpd -= GRAVITY * deltaTime;

    //  ジャンプの高さを更新
    jumpHeight += jumpSpd * deltaTime;
   
    //  プレイヤーが上へ移動する
    playerPos_y -= jumpHeight;
    //  中央で止めてその後は背景を動かすようにする
    if (playerPos_y < D3D.gameHeight * 0.5f)
    {
        playerPos_y = D3D.gameHeight * 0.5f;
        //  カメラ移動量をジャンプの高さに合わせる
        cameraOffsetY = jumpHeight;
    }
    //  プレイヤーが地面があった場所についたらそのまま下にいかないように止める
        //  要修正（着いた後、ジャンプができない）
    else if (playerPos_y > D3D.gameHeight * 0.8)
    {
        playerPos_y = D3D.gameHeight * 0.8f;
    }

    
}
//  プレイヤーと缶の当たり判定
bool SceneIngame::CheckPlayerCanCollision(float canScreenY)
{
    //  プレイヤーの矩形
    float playerLeft = playerPos_x;
    float playerRight = playerPos_x + playerWidth;
    float playerTop = playerPos_y;
    float playerBottom = playerPos_y + playerHeight;
    //  缶の矩形
    float canLeft = canPos_x;
    float canRight = canPos_x + canWidth;
    float canTop = canScreenY;
    float canBottom = canScreenY + canHeight;

    //  プレイヤーと缶の矩形が重なっているか判定
    if (playerRight > canLeft &&
        playerLeft<canRight &&
        playerBottom>canTop &&
        playerTop < canBottom)
    {
        return true;
    }
    return false;
}