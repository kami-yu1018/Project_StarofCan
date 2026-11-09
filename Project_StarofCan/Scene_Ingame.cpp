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

    m_render->LoadTexture("BgImg", L"../data/image/ingame_bg_pre.png");    //  背景（仮）
    //  プレイヤー
    m_render->LoadTexture("PlayerImg", L"../data/image/player.png");      //  待機状態画像
    m_render->LoadTexture("PlayerJumpImg", L"../data/image/player_jump.png");    //  ジャンプ状態画像
    m_render->LoadTexture("PlayerFallImg", L"../data/image/player_fall.png");   // 落下状態画像
    m_render->LoadTexture("PlayerKickImg", L"../data/image/player_kick.png");   //  蹴る状態画像

    m_render->LoadTexture("CanImg", L"../data/image/can.png");          //  缶

    //  ギミック
    m_render->LoadTexture("MeteoImg", L"../data/image/meteo.png");      //  隕石
    m_render->LoadTexture("Debri1Img", L"../data/image/debri1.png");    //  デブリ１
    m_render->LoadTexture("Debri2Img", L"../data/image/debri2.png");    //  デブリ２

    //  その他
    m_render->LoadTexture("StartTextImg", L"../data/image/StartText.png");  //  スタートテキスト

    //  サイズ設定
    //  プレイヤー
    playerWidth = PLAYER_IMAGE_W;
    playerHeight = PLAYER_IMAGE_H;
    //  缶
    canWidth = CAN_IMAGE_W;
    canHeight = CAN_IMAGE_H;

    gameStart = false;

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

    //  累積高度
    totalHeight = 0.0f;
    //  カメラ位置
    cameraOffsetY = 0.0f;

    //  缶の物理情報
    canVelocityX = 0.0f;
    canVelocityY = 0.0f;
    canLaunched = false;

    //  プレイヤーのジャンプ状態
    jumpHeight = 0.0f;
    jumpSpd = 0.f;
    isJumping = false;

    //  プレイヤー状態
    playerState = PLAYER_STATE_IDLE;

}
//  更新処理
void SceneIngame::OnUpdate(GameManager* manager, float deltaTime)
{
    //  キー入力
    if(gameStart)
    {
        //  移動
        if (CheckHitKey(VK_RIGHT))
        {
            playerPos_x += PLAYERSPEEDLR;
        }
        if (CheckHitKey(VK_LEFT))
        {
            playerPos_x -= PLAYERSPEEDLR;
        }

        if (playerPos_x < D3D.m_screenWidth / 3.0f)
        {
            playerPos_x = D3D.m_screenWidth / 3.0f;
        }
        if (playerPos_x + playerWidth > D3D.m_screenWidth / 3.0f + D3D.gameWidth)
        {
            playerPos_x = D3D.m_screenWidth / 3.0f + D3D.gameWidth - playerWidth;
        }
    }

    //  ゲームが始まっている場合にジャンプ、始まっていなければゲーム開始
    if (PushHitKey(VK_SPACE))
    {
        if (!gameStart)
        {
            gameStart = true;
        }
        else
        {
            jumpSpd = JUMP_POWER;
            isJumping = true;
        }
    }

    //  ゲームが始まっている場合
    if(gameStart)
    {
        if (isJumping) Jump(deltaTime);  //  ジャンプ処理

        //  プレイヤーと缶の当たり判定
        int collsionDirection = CheckPlayerCanCollision();
        if (!canLaunched &&
            collsionDirection != -1)
        {
            //  缶を蹴り上げる処理
            float kickPowerUD = GetCanKickPowerUD(totalHeight);
            canVelocityY = kickPowerUD;
            kickAnimaFlame = 10;    //  蹴るアニメーションのフレーム数を設定

            float kickPowerLR = GtetCanKickPowerLR(totalHeight);
            if (collsionDirection == RIGHT)
            {
                canVelocityX = kickPowerLR;
            }
            else if (collsionDirection == LEFT)
            {
                canVelocityX = kickPowerLR * -1.0f;
            }
        }

        //  アニメーションのフレーム数を減少させる
        if (kickAnimaFlame > 0)
        {
            kickAnimaFlame--;
        }

        //  プレイヤーの累積高度に応じた重力を取得
        float canGravity = GetGravity(totalHeight);
        //  重力によって上昇速度を減少させる
        canVelocityY -= canGravity * deltaTime;
        //  上向きの速度が正なら缶は上昇、負なら落下
        canPos_y -= canVelocityY * deltaTime;


        //  正なら右向き、負なら左向きに移動
        canPos_x += canVelocityX * deltaTime;
        //  画面端に行ったら跳ね返る
        if (canPos_x < D3D.m_screenWidth / 3.0f ||
            canPos_x + canWidth> D3D.m_screenWidth / 3.0f + D3D.gameWidth)
        {
            canVelocityX *= -1.0f;
        }

        //  プレイヤーの状態更新（要修正）
        if (!isJumping) //  ジャンプ中でない（地面についている）状態であれば
        {
            playerState = PLAYER_STATE_IDLE;
        }
        else
        {
            if (kickAnimaFlame == 0)
            {
                if (canVelocityY > 0.0f)
                {
                    playerState = PLAYER_STATE_JUMP;
                }
                else
                {
                    playerState = PLAYER_STATE_FALL;
                }
            }
            else
            {
                playerState = PLAYER_STATE_KICK;
            }
        }

        //  缶が画面下へ落ちたらゲームオーバー
        if (GameOver())
        {
            manager->ChangeState(std::make_unique<SceneResult>());
        }
    }

    //  画像の描画
    m_render->Begin();

    //  背景画像の下端ををゲーム画面の下端に合わせる
    float bgPosY = D3D.gameHeight - BG_IMAGE_H + cameraOffsetY;
    m_render->Draw("BgImg", D3D.m_screenWidth / 3.0f, bgPosY, D3D.gameWidth, BG_IMAGE_H);

    //  プレイヤーの状態から描画する画像を切り替える
    switch (playerState)
    {
    case PLAYER_STATE_IDLE:     //  待機状態
        m_render->Draw("PlayerImg", playerPos_x, playerPos_y, playerWidth, playerHeight);
        break;

    case PLAYER_STATE_JUMP:     //  ジャンプ状態
        m_render->Draw("PlayerJumpImg", playerPos_x, playerPos_y, playerWidth, playerHeight);
        break;

    case PLAYER_STATE_FALL:     //  落下状態
        m_render->Draw("PlayerFallImg", playerPos_x, playerPos_y, playerWidth, playerHeight);
        break;

    case PLAYER_STATE_KICK:     //  蹴る状態
        m_render->Draw("PlayerKickImg", playerPos_x, playerPos_y, playerWidth, playerHeight);
        break;
    }

    m_render->Draw("CanImg", canPos_x, canPos_y, canWidth, canHeight);      //  缶の描画

    m_render->Draw("MeteoImg", D3D.m_screenWidth / 3.0f + (D3D.gameWidth * 0.2f), bgPosY + (BG_IMAGE_H * 0.5f), 100, 100);    //  隕石の描画

    if (!gameStart)
    {
        m_render->Draw("StartTextImg", D3D.m_screenWidth / 3.0f, D3D.gameHeight * 0.5, 400, 150);
    }

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
    //  現在のジャンプ高度を葉損
    float previousHeight = jumpHeight;;

    //  累積高度に応じた重力を取得
    float gravity = GetGravity(totalHeight);

    //  重力によってジャンプ速度を減少
    jumpSpd -= gravity * deltaTime;

    //  ジャンプの高さを更新
    jumpHeight += jumpSpd * deltaTime;

    //  上昇分だけ累積高度を増加
    if (jumpHeight > previousHeight)
    {
        totalHeight += jumpHeight - previousHeight;
    }
   
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

//  高度に応じた重力を取得
float SceneIngame::GetGravity(float height)
{
    //  地球から宇宙まで
    if (height < EARTH_TO_SPACE_HEIGHT)
    {
        float t = height / EARTH_TO_SPACE_HEIGHT;

        return EARTH_GRAVITY + (SPACE_GRAVITY - EARTH_GRAVITY) * t;
    }

    //  宇宙から銀河系まで
    if (height < SPACE_TO_GALAXY_HEIGHT)
    {
        float t = (height - EARTH_TO_SPACE_HEIGHT) /
            (SPACE_TO_GALAXY_HEIGHT - EARTH_TO_SPACE_HEIGHT);

        return SPACE_GRAVITY + (GALAXY_GRAVITY - SPACE_GRAVITY) * t;
    }

    //  銀河系以上
    return GALAXY_GRAVITY;
}

//  高度に応じた缶のけり上げる力を取得
float SceneIngame::GetCanKickPowerUD(float height)
{
    //地球から宇宙まで
    if (height < EARTH_TO_SPACE_HEIGHT)
    {
        float t = height / EARTH_TO_SPACE_HEIGHT;

        return EARTH_KICH_POWER_UD + (SPACE_KICK_POWER_UD - EARTH_KICH_POWER_UD) * t;
    }
    //  宇宙から銀河系まで
    if (height < SPACE_TO_GALAXY_HEIGHT)
    {
        float t = (height - EARTH_TO_SPACE_HEIGHT) /
            (SPACE_TO_GALAXY_HEIGHT - EARTH_TO_SPACE_HEIGHT);

        return SPACE_KICK_POWER_UD + (GALAXY_KICK_POWER_UD - SPACE_KICK_POWER_UD) * t;
    }
    //  銀河系以上
    return GALAXY_KICK_POWER_UD;
}
float SceneIngame::GtetCanKickPowerLR(float height)
{
    //  地球から宇宙まで
    if (height < EARTH_TO_SPACE_HEIGHT)
    {
        float t = height / EARTH_TO_SPACE_HEIGHT;
        return EARTH_KICH_POWER_LR + (SPACE_KICK_POWER_LR - EARTH_KICH_POWER_LR) * t;
    }
    //  宇宙から銀河系まで
    if (height < SPACE_TO_GALAXY_HEIGHT)
    {
        float t = (height - EARTH_TO_SPACE_HEIGHT) /
            (SPACE_TO_GALAXY_HEIGHT - EARTH_TO_SPACE_HEIGHT);
        return SPACE_KICK_POWER_LR + (GALAXY_KICK_POWER_LR - SPACE_KICK_POWER_LR) * t;
    }
    //  銀河系以上
    return GALAXY_KICK_POWER_LR;
}

//  ゲームオーバー処理
bool SceneIngame::GameOver()
{
    //  缶が画面下に落ちたらゲームオーバー
    if (canPos_y > D3D.gameHeight)
    {
        return true;
    }
    return false;
}