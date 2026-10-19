#include"SpriteRender.h"
#include<Windows.h>

using namespace DirectX;

//  初期化処理
bool SpriteRender::Initialize()
{
    if (!D3D.m_deviceContext)      //   何もなかったらfalseを返す
        return false;

    m_spriteBatch = std::make_unique<SpriteBatch>(D3D.m_deviceContext.Get());   //  SpriteBatchを生成、描画に必要なDirect3Dデバイスコンテキストを渡す

    return true;
}

//  画像の読み込み
bool SpriteRender::LoadTexture(
    const std::string& name,
    const wchar_t* filePath)
{
    if (!D3D.m_device || !filePath)     //  何もなかったらfalseを返す
        return false;

    //  同じ名前の画像があれば2重読み込みしない
    if (m_texture.find(name) != m_texture.end())
        return true;

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>texture;

    HRESULT hr = CreateWICTextureFromFile(
        D3D.m_device.Get(),
        filePath,
        nullptr,
        texture.GetAddressOf()
    );

    //  画像読み込みに失敗したらテキストを返す
    if (FAILED(hr))
    {
        OutputDebugStringW(
            L"SpriteRender : 画像の読み込みに失敗しました\n"
        );
        return false;
    }

    m_texture.emplace(name, std::move(texture));
    return true;
}

//  描画開始
void SpriteRender::Begin()
{
    if (m_spriteBatch)
        m_spriteBatch->Begin();
}

//  描画処理
void SpriteRender::Draw(
    const std::string& name,
    float x,
    float y,
    float width,
    float height)
{
    //  m_spriteBatchが空であれば描画しない
    if (!m_spriteBatch)
        return;

    auto it = m_texture.find(name);

    //  二重の場合は描画しない
    if (it == m_texture.end())
        return;

    auto* texture = it->second.Get();   //  it->second：事象に登録したシェーダーリソースビュー

    //  テクスチャの元サイズを取得
    Microsoft::WRL::ComPtr<ID3D11Resource>resource;
    texture->GetResource(resource.GetAddressOf());  //  参照しているリソースを取得

    Microsoft::WRL::ComPtr<ID3D11Texture2D>texture2D;
    if (FAILED(resource.As(&texture2D)))        //  As(&texture2D)：取得したリソースをID3D11Texture2Dとして扱えるか確認、対応するインタフェースを取得
        return;

    D3D11_TEXTURE2D_DESC desc{};
    texture2D->GetDesc(&desc);

    if (desc.Width == 0 || desc.Height == 0)
        return;

    //  指定された描画サイズに合わせる
    XMFLOAT2 scale(
        width / static_cast<float>(desc.Width),
        height / static_cast<float>(desc.Height)
    );

    m_spriteBatch->Draw(
        texture,                //  描画する画像
        XMFLOAT2(x, y),         //  描画位置
        nullptr,                //  画像全体を描画する指定
        Colors::White,          //  色を白に指定、元画像の色を変えない
        0.0f,                   //  回転角度（今回は回転しない）
        XMFLOAT2(0.0f, 0.0f),   //  回転、拡大縮小の基準点を左上にする
        scale                   //  横と縦の拡大縮小率
    );
}

//  終了
void SpriteRender::End()
{
    if (m_spriteBatch)
        m_spriteBatch->End();
}

//  解放
void SpriteRender::Release()
{
    m_spriteBatch.reset();
    m_texture.clear();
}