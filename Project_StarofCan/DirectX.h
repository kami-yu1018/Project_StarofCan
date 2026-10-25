#pragma once

//	DirectXの実装
//	ライブラリ読み込み
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")
//	インクルード
#include<d3d11.h>
#include<dxgi.h>
#include<DirectXMath.h>
//	ComPtrを使用できるように
#include<wrl/client.h>
using Microsoft::WRL::ComPtr;

///	Direct3Dクラス
class Direct3D
{
public:

    //  スクリーンサイズ
    int m_screenWidth = 0;
    int m_screenHeight = 0;

    //  ゲーム画面サイズ
    float gameWidth = 0;
    float gameHeight = 0;

	ComPtr<ID3D11Device>			m_device;			//	デバイス
	ComPtr<ID3D11DeviceContext>		m_deviceContext;	//	デバイスコンテキスト
	ComPtr<IDXGISwapChain>			m_swapChain;		//	スワップチェイン
	ComPtr<ID3D11RenderTargetView>	m_backBufferView;	//	RTビュー

	//--------------------------------------------------------------
	//	Direct3Dを初期化し、使用できるようにする関数
	//	hWnd	：ウィンドウハンドル
	//	width	：画面の幅
	//	height	：　　　高さ
	//--------------------------------------------------------------
	bool Initalize(HWND hWnd, int width, int height);

	
	//	シングルトンパターン
private:
	static inline Direct3D* s_instance;		//	インスタンス用ポインタ
	Direct3D() {};							//	コンストラクタ
public:
	static void CreateInstance()	//	インスタンス作成
	{
		DeleteInstance();

		s_instance = new Direct3D();
	}

	static void DeleteInstance()	//	インスタンス削除
	{
		if (s_instance != nullptr)
		{
			delete s_instance;
			s_instance = nullptr;
		}
	}

	static Direct3D& GetInstance()	//	唯一のインスタンスを取得
	{
		return *s_instance;
	}
};

//	インスタンス取得用マクロ
#define D3D Direct3D::GetInstance()