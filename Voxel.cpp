// Refactored 19.06.2021(NON Refactored)	// Looked Through 15.09.2021
#include "Voxel.h" // need
#include <d3dcompiler.h> // need
#include "GraphicsThrowMacros.h" // need
#include "MakeCube.h" // need


// I need to start Using Triangle Strip to improve performance
Voxel::Voxel(Graphics& Graphics, float x, float y, float z, int Color, std::vector<BDS::Instance> InstancesData)
	:
	XCoordinate(x),
	YCoordinate(y),
	ZCoordinate(z)
{
	namespace dx = DirectX;
	using namespace BDS;
	INFOMAN(Graphics);


	IndexedTriangleList<Vertex> Mob;
	Mob = MakeCube::Make<Vertex>();
	InstanceCount = InstancesData.size();

			
	D3D11_BUFFER_DESC BufferDescIBPos = {};
	BufferDescIBPos.ByteWidth = UINT(sizeof(Instance) * InstanceCount);
	BufferDescIBPos.Usage = D3D11_USAGE_DEFAULT;
	BufferDescIBPos.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDescIBPos.CPUAccessFlags = 0u;
	BufferDescIBPos.MiscFlags = 0u;
	BufferDescIBPos.StructureByteStride = 0u;// = sizeof(Instance);
	D3D11_SUBRESOURCE_DATA SubresourceDataIBInstancePos = {};
	SubresourceDataIBInstancePos.pSysMem = InstancesData.data();
	SubresourceDataIBInstancePos.SysMemPitch = 0u;
	SubresourceDataIBInstancePos.SysMemSlicePitch = 0u;
	Graphics.pDevice->CreateBuffer(&BufferDescIBPos, &SubresourceDataIBInstancePos, &InstanceBufferPositionP);
	VertexBuffersPointers[0] = InstanceBufferPositionP.Get();
	VertexBuffersStrides[0] = sizeof(Instance);
	VertexBuffersOffsets[0] = 0u;
		

	D3D11_BUFFER_DESC BufferDescVB = {};
	BufferDescVB.ByteWidth = UINT(sizeof(Vertex) * Mob.Vertices.size());
	BufferDescVB.Usage = D3D11_USAGE_DEFAULT;
	BufferDescVB.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDescVB.CPUAccessFlags = 0u;
	BufferDescVB.MiscFlags = 0u;
	BufferDescVB.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA SubresourceDataVBRandomColor = {};
	SubresourceDataVBRandomColor.pSysMem = Mob.Vertices.data();
	GFX_THROW_INFO(Graphics.pDevice.Get()->CreateBuffer(&BufferDescVB, &SubresourceDataVBRandomColor, &VertexBufferP));
	VertexBuffersPointers[1] = VertexBufferP.Get();
	VertexBuffersStrides[1] = sizeof(Vertex);
	VertexBuffersOffsets[1] = 0u;


	IndexCount = (UINT)Mob.Indices.size();
	D3D11_BUFFER_DESC BufferDescIB = {};
	BufferDescIB.ByteWidth = UINT(sizeof(unsigned short) * IndexCount);
	BufferDescIB.Usage = D3D11_USAGE_DEFAULT;
	BufferDescIB.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferDescIB.CPUAccessFlags = 0u;
	BufferDescIB.MiscFlags = 0u;
	BufferDescIB.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA SubresourceDataIB = {};
	SubresourceDataIB.pSysMem = Mob.Indices.data();
	GFX_THROW_INFO(Graphics.pDevice.Get()->CreateBuffer(&BufferDescIB, &SubresourceDataIB, &IndexBufferP));


	//Lighting ConstBufferLightingData;
	//D3D11_BUFFER_DESC ConstBufferDescLighting;
	//ConstBufferDescLighting.ByteWidth = sizeof(ConstBufferLightingData);
	//ConstBufferDescLighting.Usage = D3D11_USAGE_DYNAMIC;
	//ConstBufferDescLighting.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//ConstBufferDescLighting.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//ConstBufferDescLighting.MiscFlags = 0u;
	//ConstBufferDescLighting.StructureByteStride = 0u;
	//D3D11_SUBRESOURCE_DATA SubresourceDataConstBufferLighting = {};
	//SubresourceDataConstBufferLighting.pSysMem = &ConstBufferLightingData;
	//GFX_THROW_INFO(Graphics.pDevice.Get()->CreateBuffer(&ConstBufferDescLighting, &SubresourceDataConstBufferLighting, &ConstantBufferLightingP));


	ConstauntBufferVoxelsColor ConstBufferColorData = { {0.7f,0.0f,0.0f} };
	D3D11_BUFFER_DESC ConstBufferDescColor;
	ConstBufferDescColor.ByteWidth = sizeof(ConstBufferColorData);
	ConstBufferDescColor.Usage = D3D11_USAGE_DYNAMIC;
	ConstBufferDescColor.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	ConstBufferDescColor.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ConstBufferDescColor.MiscFlags = 0u;
	ConstBufferDescColor.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA SubresourceDataConstBufferColor = {};
	SubresourceDataConstBufferColor.pSysMem = &ConstBufferColorData;
	GFX_THROW_INFO(Graphics.pDevice.Get()->CreateBuffer(&ConstBufferDescColor, &SubresourceDataConstBufferColor, ConstantBufferColorP.GetAddressOf()));


	if (!ConstantBufferViewProjP)
	{
		D3D11_BUFFER_DESC BufferDescViewProj;
		BufferDescViewProj.ByteWidth = sizeof(Transforms);
		BufferDescViewProj.Usage = D3D11_USAGE_DYNAMIC;
		BufferDescViewProj.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		BufferDescViewProj.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		BufferDescViewProj.MiscFlags = 0u;
		BufferDescViewProj.StructureByteStride = 0u;
		GFX_THROW_INFO(Graphics.pDevice.Get()->CreateBuffer(&BufferDescViewProj, nullptr, &ConstantBufferViewProjP));
		ConstantBufferViewProjPSlot = 0;
	}


	if (!VertexShaderP)
	{

		GFX_THROW_INFO(D3DReadFileToBlob(L"MobVS.cso", &BytecodeBlobP));
		GFX_THROW_INFO(Graphics.pDevice.Get()->CreateVertexShader(BytecodeBlobP->GetBufferPointer(), BytecodeBlobP->GetBufferSize(), nullptr, &VertexShaderP));
	}


	if (!InputLayoutP)
	{
		const std::vector<D3D11_INPUT_ELEMENT_DESC> InputElementDesc =
		{
			{ "InstancePosition",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_INSTANCE_DATA,1 }, // Change
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,1,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		GFX_THROW_INFO(Graphics.pDevice.Get()->CreateInputLayout(InputElementDesc.data(), (UINT)InputElementDesc.size(), BytecodeBlobP->GetBufferPointer(), BytecodeBlobP->GetBufferSize(), &InputLayoutP));
	}


	if (!PixelShaderP)
	{
		GFX_THROW_INFO(D3DReadFileToBlob(L"MobPS.cso", &BytecodeBlobP));
		GFX_THROW_INFO(Graphics.pDevice.Get()->CreatePixelShader(BytecodeBlobP->GetBufferPointer(), BytecodeBlobP->GetBufferSize(), nullptr, &PixelShaderP));
	}


	if (!PrimitiveTopologyIsSet)
	{
		PrimitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		PrimitiveTopologyIsSet = true;
	}


	if (!ChunkTransformIsSet)
	{
		// Model deformation transform (per instance, not stored as bind)
		dx::XMStoreFloat3x3(&MobTransform, dx::XMMatrixScaling(1.0f /*+ Speed*/, 1.0f/*+ Speed*/, 1.0f/*+ Speed*/)); // Put Speed here to move Mobs
		ChunkTransformIsSet = true;
	}
}


void Voxel::Draw(Graphics& Graphics) const noexcept(!IS_DEBUG)
{
	const auto ModelView = this->GetTransformXM() * Graphics.GetCamera();
	const BDS::Transforms Transform = { DirectX::XMMatrixTranspose(ModelView), DirectX::XMMatrixTranspose(ModelView * Graphics.GetProjection()) };
	INFOMAN(Graphics);
	D3D11_MAPPED_SUBRESOURCE MappedSubresource;
	GFX_THROW_INFO(Graphics.pContext.Get()->Map(ConstantBufferViewProjP.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &MappedSubresource));
	memcpy(MappedSubresource.pData, &Transform, sizeof(Transform));
	Graphics.pContext.Get()->Unmap(ConstantBufferViewProjP.Get(), 0u);
	Graphics.pContext.Get()->VSSetConstantBuffers(ConstantBufferViewProjPSlot, 1u, ConstantBufferViewProjP.GetAddressOf());
	Graphics.pContext.Get()->PSSetConstantBuffers(0u, 1u, ConstantBufferColorP.GetAddressOf());
	Graphics.pContext.Get()->VSSetShader(VertexShaderP.Get(), nullptr, 0u);
	Graphics.pContext.Get()->IASetVertexBuffers(0u, 2u, VertexBuffersPointers, VertexBuffersStrides, VertexBuffersOffsets);
	Graphics.pContext.Get()->IASetPrimitiveTopology(PrimitiveTopology);
	Graphics.pContext.Get()->PSSetShader(PixelShaderP.Get(), nullptr, 0u);
	Graphics.pContext.Get()->IASetInputLayout(InputLayoutP.Get());
	Graphics.pContext.Get()->IASetIndexBuffer(IndexBufferP.Get(), DXGI_FORMAT_R16_UINT, 0u);
	Graphics.DrawInstanced(IndexCount, InstanceCount);
}


void Voxel::RebindInstancedBuffer(Graphics& Graphics, std::vector<BDS::Instance> InstancesData)
{
	InstanceCount = InstancesData.size();
	D3D11_BUFFER_DESC BufferDescIBPos = {};
	BufferDescIBPos.ByteWidth = UINT(sizeof(BDS::Instance) * InstanceCount);
	BufferDescIBPos.Usage = D3D11_USAGE_DEFAULT;
	BufferDescIBPos.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDescIBPos.CPUAccessFlags = 0u;
	BufferDescIBPos.MiscFlags = 0u;
	BufferDescIBPos.StructureByteStride = 0u;// = sizeof(Instance);
	D3D11_SUBRESOURCE_DATA SubresourceDataIBInstancePos = {};
	SubresourceDataIBInstancePos.pSysMem = InstancesData.data();
	SubresourceDataIBInstancePos.SysMemPitch = 0u;
	SubresourceDataIBInstancePos.SysMemSlicePitch = 0u;
	Graphics.pDevice->CreateBuffer(&BufferDescIBPos, &SubresourceDataIBInstancePos, &InstanceBufferPositionP);
	VertexBuffersPointers[0] = InstanceBufferPositionP.Get();
	VertexBuffersStrides[0] = sizeof(BDS::Instance);
	VertexBuffersOffsets[0] = 0u;
}


DirectX::XMMATRIX Voxel::GetTransformXM() const noexcept
{
	namespace dx = DirectX;
	return dx::XMLoadFloat3x3(&MobTransform) *  dx::XMMatrixTranslation(XCoordinate, YCoordinate, ZCoordinate);
}


DxgiInfoManager& Voxel::GetInfoManager(Graphics& Graphics) noexcept(IS_DEBUG)
{
#ifndef NDEBUG
	return Graphics.InfoManager;
#else
	throw std::logic_error("You break it! (tried to access gfx.infoManager in Release config)");
#endif
}


UINT Voxel::VertexBuffersStrides[2];
UINT Voxel::VertexBuffersOffsets[2];
Microsoft::WRL::ComPtr<ID3D11Buffer> Voxel::ConstantBufferViewProjP;
UINT Voxel::ConstantBufferViewProjPSlot;
Microsoft::WRL::ComPtr<ID3DBlob> Voxel::BytecodeBlobP;
Microsoft::WRL::ComPtr<ID3D11VertexShader> Voxel::VertexShaderP;
Microsoft::WRL::ComPtr<ID3D11InputLayout> Voxel::InputLayoutP;
Microsoft::WRL::ComPtr<ID3D11PixelShader> Voxel::PixelShaderP;
D3D11_PRIMITIVE_TOPOLOGY Voxel::PrimitiveTopology;
bool Voxel::PrimitiveTopologyIsSet = false;
DirectX::XMFLOAT3X3 Voxel::MobTransform;
bool Voxel::ChunkTransformIsSet = false;