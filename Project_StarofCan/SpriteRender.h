#pragma once

#include"DirectX.h"

#include<SpriteBatch.h>
#include<WICTextureLoader.h>

#include<string>
#include<unordered_map>

//  ２Ｄ描画スプライトクラス
class SpriteRender
{
    //  
    std::unique_ptr<DirectX::SpriteBatch>m_spriteBatch; //  画像描画用の仕組みを保持

    std::unordered_map<
        std::string,
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>
    >m_texture;     //  読み込んだ画像を名前で管理するための辞書
                    //  例： m_texture["名前"] = 読み込んだ画像;

public:
    bool Initialize();              //  初期化
    bool LoadTexture(               //  画像を読み込んで名前をつける
        const std::string& name,        //  名前
        const wchar_t* filePath         //  ファイルのパス
    );
    void Begin();                   //  描画開始
    void Draw(                      //  描画
        const std::string& name,        //  名前
        float x,                        //  ｘ座標
        float y,                        //  ｙ座標
        float width,                    //  幅
        float height,                    //  高さ
        float alpha = 1.0f
    );
    void End();                     //  描画終了
    void Release();                 //  読み込んだ画像を解放
};