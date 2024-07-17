#pragma once
// Refactored 10.06.2021	// Looked Through 15.09.2021
#include "Graphics.h" // need
#include "BufferDataStructs.h" // need


class Chunk
{
public:
	Chunk(Graphics& Graphics, float x, float y, float z, const std::vector<BDS::Vertex>& Vertices, const std::vector<unsigned short>& Indices, const std::vector<BDS::Color>& Colors, const std::vector<BDS::ColorGradient>& ColorGradients);
	Chunk() = delete;
	void Draw(Graphics& Graphics) const noexcept(!IS_DEBUG);
	~Chunk() = default;
	Chunk(Chunk&&) = delete;
	Chunk& operator=(Chunk&&) = delete;
	Chunk(const Chunk&) = delete;
	Chunk& operator=(const Chunk&) = delete;
	DirectX::XMMATRIX GetTransformXM() const noexcept;
protected:
	static DxgiInfoManager& GetInfoManager(Graphics& Graphics) noexcept(IS_DEBUG);
private:




public:

protected:

private:
	ID3D11Buffer* VertexBuffersPointers[4]; // Cannot be static cos unique for every Chunk
	static UINT VertexBuffersStrides[4];
	static UINT VertexBuffersOffsets[4];
	Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBufferP; // Cannot be static cos unique for every Chunk
	Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBufferColorP; // Cannot be static cos unique for every Chunk
	Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBufferColorGradientsP;  // Cannot be static cos unique for every Chunk
	Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBufferRandomColorP; // Cannot be static cos unique for every Chunk
	UINT IndexCount; // Cannot be static cos unique for every Chunk
	Microsoft::WRL::ComPtr<ID3D11Buffer> IndexBufferP; // Cannot be static cos unique for every Chunk
	//Microsoft::WRL::ComPtr<ID3D11Buffer> ConstantBufferLightingP;
	static Microsoft::WRL::ComPtr<ID3D11Buffer> ConstantBufferColorsP;
	static Microsoft::WRL::ComPtr<ID3D11Buffer> ConstantBufferViewProjP; 
	static UINT ConstantBufferViewProjPSlot;
	static Microsoft::WRL::ComPtr<ID3DBlob> BytecodeBlobP;
	static Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShaderP; 
	static Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayoutP;
	static Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShaderP;
	static D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology;
	static bool PrimitiveTopologyIsSet;
	static DirectX::XMFLOAT3X3 ChunkTransform;
	static bool ChunkTransformIsSet;
	float XCoordinate = 0.0f; // Cannot be static cos unique for every Chunk
	float YCoordinate = 0.0f; // Cannot be static cos unique for every Chunk
	float ZCoordinate = 0.0f; // Cannot be static cos unique for every Chunk
};