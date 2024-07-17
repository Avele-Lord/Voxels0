#pragma once
// Refactored 19.06.2021	// Looked Through 15.09.2021
#include "Graphics.h" // need
#include "BufferDataStructs.h" // need


class Voxel
{
public:
	Voxel(Graphics& Graphics, float x, float y, float z, int Color, std::vector<BDS::Instance> InstancesData);
	Voxel() = delete;
	void Draw(Graphics& Graphics) const noexcept(!IS_DEBUG);
	void RebindInstancedBuffer(Graphics& Graphics, std::vector<BDS::Instance> InstancesData);
	~Voxel() = default;
	Voxel(Voxel&&) = delete;
	Voxel& operator=(Voxel&&) = delete;
	Voxel(const Voxel&) = delete;
	Voxel& operator=(const Voxel&) = delete;
	DirectX::XMMATRIX GetTransformXM() const noexcept;
protected:
	static DxgiInfoManager& GetInfoManager(Graphics& Graphics) noexcept(IS_DEBUG);
private:




public:
	
protected:
	
private:
	UINT InstanceCount;
	ID3D11Buffer* VertexBuffersPointers[2];
	static UINT VertexBuffersStrides[2];
	static UINT VertexBuffersOffsets[2];
	Microsoft::WRL::ComPtr<ID3D11Buffer> InstanceBufferPositionP;
	Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBufferP;
	UINT IndexCount;
	Microsoft::WRL::ComPtr<ID3D11Buffer> IndexBufferP;
	//Microsoft::WRL::ComPtr<ID3D11Buffer> ConstantBufferLightingP;
	Microsoft::WRL::ComPtr<ID3D11Buffer> ConstantBufferColorP;
	static Microsoft::WRL::ComPtr<ID3D11Buffer> ConstantBufferViewProjP;
	static UINT ConstantBufferViewProjPSlot;
	static Microsoft::WRL::ComPtr<ID3DBlob> BytecodeBlobP;
	static Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShaderP;
	static Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayoutP;
	static Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShaderP;
	static D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology;
	static bool PrimitiveTopologyIsSet;
	static DirectX::XMFLOAT3X3 MobTransform;
	static bool ChunkTransformIsSet;
	float XCoordinate = 0.0f;
	float YCoordinate = 0.0f;
	float ZCoordinate = 0.0f;
	//float Speed = 0.0f;
};