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
        jumpSpd = JUMP_POWER;
        isJumping = true;
    }
    if(isJumping) Jump(deltaTime);  //  ジャンプ処理

    //  プレイヤーと缶の当たり判定
    int collsionDirection = CheckPlayerCanCollision();
    if (!canLaunched &&
        collsionDirection != -1)
    {
        //  缶を蹴り上げる処理
        canVelocityY = CAN_KICK_POWER_UD;

        if(collsionDirection == RIGHT)
        {
            canVelocityX = CAN_KICK_POWER_LR;
        }
        else if (collsionDirection == LEFT)
        {
            canVelocityX = CAN_KICK_POWER_LR * -1.0f;
        }
    }
    //  重力によって上昇速度を減少させる
    canVelocityY -= CAN_GRAVITY * deltaTime;
    //  上向きの速度が正なら缶は上昇、負なら落下
    canPos_y -= canVelocityY * deltaTime;
    
    //  時間によって左右移動速度を減少させる
    canVelocityX /= deltaTime;
    //  正なら右向き、負なら左向きに移動
    canPos_x += canVelocityX;
    //  画面端に行ったら跳ね返る
    if (canPos_x < D3D.m_screenWidth / 3.0f || 
        canPos_x+canWidth> D3D.m_screenWidth / 3.0f+D3D.gameWidth)
    {
        canVelocityX *= -1.0f;
    }

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
    m_render->Release();
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
   
    //  プレイヤーが地面があった場所についたらそのまま下にいかないように止める
    if (jumpHeight <= 0.0f && jumpSpd <= 0.0f)
    {
        jumpHeight = 0.0f;
        jumpSpd = 0.0f;

        isJumping = false;

        playerPos_y = D3D.gameHeight * 0.8f;

        cameraOffsetY = 0.0f;
        
        return;
    }

    //  プレイヤーの初期座標を基準に画面上の座標を計算する
    float groundY = D3D.gameHeight * 0.8f;
    float centerY = D3D.gameHeight * 0.7f;

    //  プレイヤーが上昇する
    playerPos_y = groundY - jumpHeight;
  
    //  中央で止めてその後は背景を動かすようにする
    if (playerPos_y < centerY)
    {
        playerPos_y = centerY;
        //  カメラ移動量をジャンプの高さに合わせる
        cameraOffsetY = jumpHeight ;
    }
    else
    {
        cameraOffsetY = 0.0f;
    }
    
}
//  プレイヤーと缶の当たり判定
int SceneIngame::CheckPlayerCanCollision()
{
    //  プレイヤーの矩形
    float playerLeft = playerPos_x;
    float playerRight = playerPos_x + playerWidth;
    float playerTop = playerPos_y;
    float playerBottom = playerPos_y + playerHeight;
    //  缶の矩形
    float canLeft = canPos_x;
    float canRight = canPos_x + canWidth;
    float canTop = canPos_y;
    float canBottom = canPos_y + canHeight;

    //  プレイヤーと缶の矩形が重なっているか判定
    bool isColliding = 
        playerRight > canLeft &&
        playerLeft < canRight &&
        playerBottom > canTop &&
        playerTop < canBottom;
    
    //  重なっていなければ当たり判定なし
    if (!isColliding)
    {
        return -1;
    }

    //  プレイヤーと缶の中央座標
    float playerCenterX = playerPos_x + playerWidth / 2.0f;
    float canCenterX = canPos_x + canWidth / 2.0f;

    //  プレイヤーが缶の右側にいれば左へ飛ばす
    if (playerCenterX > canCenterX)
    {
        return RIGHT;
    }
    //  プレイヤーが缶の左側にいれば右へ飛ばす
    else
    {
        return LEFT;
    }
}