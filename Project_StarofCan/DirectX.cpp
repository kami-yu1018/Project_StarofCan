#include"DirectX.h"
#include<Windows.h>

bool Direct3D::Initalize(HWND hWnd, int width, int height)
{
    m_screenWidth = width;
    m_screenHeight = height;

    //  ゲーム画面サイズ変更（縦はスクリーンと同じ、横はスクリーンの３分の１）
    gameWidth = D3D.m_screenWidth / 3.0f;
    gameHeight = static_cast<float>(D3D.m_screenHeight);

	///---------------------------------------------------------------------------
	///	ファクトリー作成
	///---------------------------------------------------------------------------
	ComPtr<IDXGIFactory> factory;

	if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory))))
	{
		return false;
	}

	///---------------------------------------------------------------------------
	///	デバイス生成
	///---------------------------------------------------------------------------
	UINT creationFlags = 0;

#ifdef DEBUG
	//	DEBUGビルド時はDirect3Dデバッグを有効にする
	creationFlags != D3D11_CREATE_DEVICE_DEBUG;
#endif // DEBUG
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	//	デバイスとデバイスコンテキストを作成
	D3D_FEATURE_LEVEL futureLevel;
	if (FAILED(D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		creationFlags,
		featureLevels,
		_countof(featureLevels),
		D3D11_SDK_VERSION,
		&m_device,
		&futureLevel,
		&m_deviceContext)))
	{
		return false;
	}

	///---------------------------------------------------------------------------
	///	スワップチェイン作成
	///---------------------------------------------------------------------------
	DXGI_SWAP_CHAIN_DESC scDesc = {};
	scDesc.BufferDesc.Width = width;
	scDesc.BufferDesc.Height = height;
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scDesc.BufferDesc.RefreshRate.Numerator = 0;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;
	scDesc.SampleDesc.Count = 1;
	scDesc.SampleDesc.Quality = 0;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.BufferCount = 2;
	scDesc.OutputWindow = hWnd;
	scDesc.Windowed = TRUE;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//	スワップチェインの作成
	if (FAILED(factory->CreateSwapChain(m_device.Get(),&scDesc,&m_swapChain)))
	{
		return false;
	}
	//	スワップチェインからバックバッファリソース取得
	ComPtr<ID3D11Texture2D> pBackBuffer;
	if (FAILED(m_swapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer))))
	{
		return false;
	}
	//	バックバッファリソース用のRTVを作成
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = scDesc.BufferDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	if (FAILED(m_device->CreateRenderTargetView(pBackBuffer.Get(), &rtvDesc, &m_backBufferView)))
	{
		return false;
	}

	///---------------------------------------------------------------------------
	///	デバイスコンテキストに描画に関する設定
	///---------------------------------------------------------------------------
	//	バックバッファをRTとしてセット
	m_deviceContext->OMSetRenderTargets(1, m_backBufferView.GetAddressOf(), nullptr);
	//	ビューポートの設定
	D3D11_VIEWPORT vp = { 0.0f,0.0f,(float)width,(float)height,0.0f,1.0f };
	m_deviceContext->RSSetViewports(1, &vp);

	return true;
}