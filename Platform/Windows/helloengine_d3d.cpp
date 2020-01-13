#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <stdint.h>

// #include <d2d1.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>

// ID2D1Factory                 *pFactory = nullptr;
// ID2D1HwndRenderTarget		 *pRenderTarget = nullptr;
// ID2D1SolidColorBrush         *pLightSlateGrayBrush = nullptr;
// ID2D1SolidColorBrush         *pCornflowerBlueBrush = nullptr;
using namespace DirectX;
using namespace DirectX::PackedVector;

const uint32_t SCREEN_WIDTH  = 960;
const uint32_t SCREEN_HEIGHT = 480;

// global declarations
IDXGISwapChain			*g_pSwapchain	= nullptr;	// the pointer to the swap chain interface 
ID3D11Device			*g_pDev			= nullptr;	// the pointer to our Direct3D device interface 
ID3D11DeviceContext		*g_pDevcon		= nullptr;	// the pointer to our Direct3D device context 

ID3D11RenderTargetView	*g_pRTView		= nullptr;

ID3D11InputLayout		*g_pLayout		= nullptr;	// the pointer to the input layour
ID3D11VertexShader		*g_pVS			= nullptr;	// the pointer to the vertex shader 
ID3D11PixelShader		*g_pPS			= nullptr;	// the pointer to the pixel shader 

ID3D11Buffer			*g_pVBuffer		= nullptr;	// Vertex Buffer 

// vertex buffer structure
struct VERTEX {
	XMLFLOAT3	Position;
	XMLFLOAT4	Color;
};

template<class T>
inline void SafeRelease(T **ppInterfaceToRelease) {
	if (*ppInterfaceToRelease != nullptr) {
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = nullptr;
	}
}

void CreateRenderTarget() {
	HRESULT hr;
	ID3D11Texture2D *pBackBuffer;

	// Get a pointer to the back buffer
	g_pSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// Create a render-target view 
	g_pDev->CreateRenderTargetView(pBackBuffer, NULL, &g_pRTView); 

	pBackBuffer->Release(); 

	// Bind the view 
	g_pDevcon->OMSetRenderTargets(1, &g_pRTView, NULL);
}

void SetViewPort() {
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = SCREEN_WIDTH;
	viewport.Height = SCREEN_HEIGHT;

	g_pDevcon->RSSetViewports(1, &viewport);
}

// this is the function that loads and prepares the shaders
void InitPipline() {
	// load and compile the two shaders
	ID3DBlob *VS, *PS;

	D3DReadFileToBlob(L"copy.vso", &VS);
	D3DReadFileToBlob(L"copy.pso", &PS);

	// encapsulate both shaders into shader objects
	g_pDev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &g_pVS);
	g_pDev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &g_pPS);

	// set the shader objects
	g_pDevcon->VSSetShader(g_pVS, 0, 0);
	g_pDevcon->PSSetShader(g_pPS, 0, 0);

	// create the input layout object 
	D3D11_INPUT_ELEMENT_DESC ied[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	}; 

	g_pDev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &g_pLayout);
	g_pDevcon->IASetInputLayout(g_pLayout);

	VS->Release();
	PS->Release();
}

// this is the function that creates the shape to render 

