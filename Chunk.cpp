// Refactored 10.06.2021	// Looked Through 15.09.2021
#include "Chunk.h" // need
#include <d3dcompiler.h> // need
#include "GraphicsThrowMacros.h" // need
#include <random> // need


// Learn what is faster for Chunk drawing  DrawInstanced or DrawIndexed // may be instancing faster???
// I need to start Using Triangle Strip to improve performance
// If I destroy all of the blocks in the chunk and pass 0 vertex buffer it's a CRASH!
Chunk::Chunk(Graphics& Graphics, float x, float y, float z, const std::vector<BDS::Vertex>& Vertices, const std::vector<unsigned short>& Indices, const std::vector<BDS::Color>& Colors, const std::vector<BDS::ColorGradient>& ColorGradients)
	:
	XCoordinate(x),
	YCoordinate(y),
	ZCoordinate(z)
{
	namespace dx = DirectX;
	using namespace BDS;

	INFOMAN(Graphics);

	assert((Vertices.size() == Colors.size() && Vertices.size() == ColorGradients.size()));
	const int VertexBuffersSize = Vertices.size();

	float RandomColorRange = 0.05f; // 0.02f  0.1f
	std::uniform_real_distribution<float> Range(0.0f, RandomColorRange);

	std::random_device SeedR;
	std::random_device SeedG;
	std::random_device SeedB;
	std::mt19937 RandomNumberGeneratorR(SeedR());
	std::mt19937 RandomNumberGeneratorG(SeedG());
	std::mt19937 RandomNumberGeneratorB(SeedB());
	std::vector<RandomColor> RandomColorBufferData;

	RandomColorBufferData.resize(VertexBuffersSize);
	for (int i = 0; i < VertexBuffersSize; i++)
	{
		RandomColorBufferData[i].RandomColor.x = Range(RandomNumberGeneratorR);
		RandomColorBufferData[i].RandomColor.y = Range(RandomNumberGeneratorG);
		RandomColorBufferData[i].RandomColor.z = Range(RandomNumberGeneratorB);
	}


	D3D11_BUFFER_DESC BufferDescVB = {};
	BufferDescVB.ByteWidth = UINT(sizeof(Vertex) * VertexBuffersSize);
	BufferDescVB.Usage = D3D11_USAGE_DEFAULT;
	BufferDescVB.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDescVB.CPUAccessFlags = 0u;
	BufferDescVB.MiscFlags = 0u;
	BufferDescVB.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA SubresourceDataVB = {};
	SubresourceDataVB.pSysMem = Vertices.data();
	GFX_THROW_INFO(Graphics.pDevice.Get()->CreateBuffer(&BufferDescVB, &SubresourceDataVB, &VertexBufferP));
	VertexBuffersPointers[0] = VertexBufferP.Get();
	VertexBuffersStrides[0] = sizeof(Vertex);
	VertexBuffersOffsets[0] = 0u;


	D3D11_BUFFER_DESC BufferDescVBColor = {};
	BufferDescVBColor.ByteWidth = UINT(sizeof(BDS::Color) * VertexBuffersSize);
	BufferDescVBColor.Usage = D3D11_USAGE_DEFAULT;
	BufferDescVBColor.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDescVBColor.CPUAccessFlags = 0u;
	BufferDescVBColor.MiscFlags = 0u;
	BufferDescVBColor.StructureByteStride = sizeof(BDS::Color);
	D3D11_SUBRESOURCE_DATA SubresourceDataVBColor = {};
	SubresourceDataVBColor.pSysMem = Colors.data();
	GFX_THROW_INFO(Graphics.pDevice.Get()->CreateBuffer(&BufferDescVBColor, &SubresourceDataVBColor, &VertexBufferColorP));
	VertexBuffersPointers[1] = VertexBufferColorP.Get();
	VertexBuffersStrides[1] = sizeof(BDS::Color);
	VertexBuffersOffsets[1] = 0u;


	D3D11_BUFFER_DESC BufferDescVBColorGradient = {};
	BufferDescVBColorGradient.ByteWidth = UINT(sizeof(ColorGradient) * VertexBuffersSize);
	BufferDescVBColorGradient.Usage = D3D11_USAGE_DEFAULT;
	BufferDescVBColorGradient.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDescVBColorGradient.CPUAccessFlags = 0u;
	BufferDescVBColorGradient.MiscFlags = 0u;
	BufferDescVBColorGradient.StructureByteStride = sizeof(ColorGradient);
	D3D11_SUBRESOURCE_DATA SubresourceDataVBColorGradient = {};
	SubresourceDataVBColorGradient.pSysMem = ColorGradients.data();
	GFX_THROW_INFO(Graphics.pDevice.Get()->CreateBuffer(&BufferDescVBColorGradient, &SubresourceDataVBColorGradient, &VertexBufferColorGradientsP));
	VertexBuffersPointers[2] = VertexBufferColorGradientsP.Get();
	VertexBuffersStrides[2] = sizeof(ColorGradient);
	VertexBuffersOffsets[2] = 0u;


	// Somehow make it const so Vertex Shader would not interpolate it
	D3D11_BUFFER_DESC BufferDescVBRandomColor = {};
	BufferDescVBRandomColor.ByteWidth = UINT(sizeof(RandomColor) * VertexBuffersSize);
	BufferDescVBRandomColor.Usage = D3D11_USAGE_DEFAULT;
	BufferDescVBRandomColor.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDescVBRandomColor.CPUAccessFlags = 0u;
	BufferDescVBRandomColor.MiscFlags = 0u;
	BufferDescVBRandomColor.StructureByteStride = sizeof(RandomColor);
	D3D11_SUBRESOURCE_DATA SubresourceDataVBRandomColor = {};
	SubresourceDataVBRandomColor.pSysMem = RandomColorBufferData.data();
	GFX_THROW_INFO(Graphics.pDevice.Get()->CreateBuffer(&BufferDescVBRandomColor, &SubresourceDataVBRandomColor, &VertexBufferRandomColorP));
	VertexBuffersPointers[3] = VertexBufferRandomColorP.Get();
	VertexBuffersStrides[3] = sizeof(RandomColor);
	VertexBuffersOffsets[3] = 0u;


	IndexCount = (UINT)Indices.size();
	D3D11_BUFFER_DESC BufferDescIB = {};
	BufferDescIB.ByteWidth = UINT(sizeof(unsigned short) * IndexCount);
	BufferDescIB.Usage = D3D11_USAGE_DEFAULT;
	BufferDescIB.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferDescIB.CPUAccessFlags = 0u;
	BufferDescIB.MiscFlags = 0u;
	BufferDescIB.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA SubresourceDataIB = {};
	SubresourceDataIB.pSysMem = Indices.data();
	GFX_THROW_INFO(Graphics.pDevice.Get()->CreateBuffer(&BufferDescIB, &SubresourceDataIB, &IndexBufferP));

	 
	//const Lighting ConstBufferLightingData;
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


	if (!ConstantBufferColorsP)
	{
		const ConstauntBufferVoxelsColors ConstBufferColorsData =
		{
			{
				/// Do not forget that in PS you moved colors array by -1  //[Color - 1](-1) Minus one cos 0 indicates for empty voxel so in chunk generator start count of colors is 1
				{(float)228 / (float)255, (float)228 / (float)255, (float)228 / (float)255}, // White // Snow // 1
				{(float)77 / (float)255, (float)77 / (float)255, (float)77 / (float)255}, // Grey // Stone // 2
				{(float)204 / (float)255, (float)0 / (float)255, (float)0 / (float)255}, // Red // HotStone //HotRock // 3
				{(float)64 / (float)255, (float)0 / (float)255, (float)128 / (float)255}, // Purple // EvilStone // 4
				{(float)0 / (float)255, (float)64 / (float)255, (float)0 / (float)255}, // Green // Grass // 5
				{(float)128 / (float)255, (float)64 / (float)255, (float)0 / (float)255}, // Brown // Dirt // 6

				//{(float)110 / (float)255, (float)250 / (float)255, (float)40  / (float)255}, // My Light Green // Grass // 5 
				//{(float)53  / (float)255, (float)150 / (float)255, (float)48  / (float)255}, // My Green // Grass // 5 
				//{(float)110 / (float)255, (float)70  / (float)255, (float)40  / (float)255}, // My Brown // Dirt // 6
				//{(float)100 / (float)255, (float)50  / (float)255, (float)150 / (float)255}, // My Purple // EvilStone // 4
				//{(float)130 / (float)255, (float)130 / (float)255, (float)130 / (float)255}, // My Grey // Stone // 2
				//{(float)220 / (float)255, (float)30  / (float)255, (float)25  / (float)255}, // My  Red // HotStone //HotRock // 3
				//{(float)10  / (float)255, (float)10  / (float)255 ,(float)10  / (float)255}, // My Black // Coal
				//{(float)300 / (float)255, (float)300 / (float)255, (float)300 / (float)255}  // My White // Snow // 1
			}
		};
		D3D11_BUFFER_DESC ConstBufferDescColors;
		ConstBufferDescColors.ByteWidth = sizeof(ConstBufferColorsData);
		ConstBufferDescColors.Usage = D3D11_USAGE_DYNAMIC;
		ConstBufferDescColors.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		ConstBufferDescColors.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		ConstBufferDescColors.MiscFlags = 0u;
		ConstBufferDescColors.StructureByteStride = 0u;
		D3D11_SUBRESOURCE_DATA SubresourceDataConstBufferColors = {};
		SubresourceDataConstBufferColors.pSysMem = &ConstBufferColorsData;
		GFX_THROW_INFO(Graphics.pDevice.Get()->CreateBuffer(&ConstBufferDescColors, &SubresourceDataConstBufferColors, ConstantBufferColorsP.GetAddressOf()));
	}


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
		GFX_THROW_INFO(D3DReadFileToBlob(L"ChunkVS.cso", &BytecodeBlobP));
		GFX_THROW_INFO(Graphics.pDevice.Get()->CreateVertexShader(BytecodeBlobP->GetBufferPointer(), BytecodeBlobP->GetBufferSize(), nullptr, &VertexShaderP));
	}


	if (!InputLayoutP)
	{
		const std::vector<D3D11_INPUT_ELEMENT_DESC> InputElementDesc =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "Color",0,DXGI_FORMAT_R16_SINT,1,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "ColorGradient",0,DXGI_FORMAT_R8_UINT,2,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "RandomColor",0,DXGI_FORMAT_R32G32B32_FLOAT,3,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		GFX_THROW_INFO(Graphics.pDevice.Get()->CreateInputLayout(InputElementDesc.data(), (UINT)InputElementDesc.size(), BytecodeBlobP->GetBufferPointer(), BytecodeBlobP->GetBufferSize(), &InputLayoutP));
	}


	if (!PixelShaderP)
	{
		GFX_THROW_INFO(D3DReadFileToBlob(L"ChunkPS.cso", &BytecodeBlobP));
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
		dx::XMStoreFloat3x3(&ChunkTransform, dx::XMMatrixScaling(1.0f, 1.0f, 1.0f));
		ChunkTransformIsSet = true;
	}
}


void Chunk::Draw(Graphics& Graphics) const noexcept(!IS_DEBUG)
{
	INFOMAN(Graphics); // Dosn't work if called only once when creating
	const DirectX::XMMATRIX ModelView = this->GetTransformXM() * Graphics.GetCamera(); // Dosn't work if called only once when creating
	const BDS::Transforms Transform = { DirectX::XMMatrixTranspose(ModelView), DirectX::XMMatrixTranspose(ModelView * Graphics.GetProjection()) }; // Dosn't work if called only once when creating
	D3D11_MAPPED_SUBRESOURCE MappedSubresource; // Dosn't work if called only once when creating
	GFX_THROW_INFO(Graphics.pContext.Get()->Map(ConstantBufferViewProjP.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &MappedSubresource));// Dosn't work if called only once when creating
	memcpy(MappedSubresource.pData, &Transform, sizeof(Transform)); // Dosn't work if called only once when creating
	Graphics.pContext.Get()->Unmap(ConstantBufferViewProjP.Get(), 0u); // Works if called only once when creating
	Graphics.pContext.Get()->VSSetConstantBuffers(ConstantBufferViewProjPSlot, 1u, ConstantBufferViewProjP.GetAddressOf()); // Dosn't work if called only once when creating
	Graphics.pContext.Get()->PSSetConstantBuffers(0u, 1u, ConstantBufferColorsP.GetAddressOf()); // Correct // Dosn't work if called only once when creating
	//Graphics.pContext.Get()->PSSetConstantBuffers(0u, 1u, ConstantBufferLightingP.GetAddressOf()); // For Test // Don't know if it work if called only once when creating
	Graphics.pContext.Get()->VSSetShader(VertexShaderP.Get(), nullptr, 0u); // Dosn't work if called only once when creating
	Graphics.pContext.Get()->IASetVertexBuffers(0u, 4u, VertexBuffersPointers, VertexBuffersStrides, VertexBuffersOffsets); // Dosn't work if called only once when creating
	Graphics.pContext.Get()->IASetPrimitiveTopology(PrimitiveTopology); // Works if called only once when creating
	Graphics.pContext.Get()->PSSetShader(PixelShaderP.Get(), nullptr, 0u); // Dosn't work if called only once when creating
	Graphics.pContext.Get()->IASetInputLayout(InputLayoutP.Get()); // Dosn't work if called only once when creating
	Graphics.pContext.Get()->IASetIndexBuffer(IndexBufferP.Get(), DXGI_FORMAT_R16_UINT, 0u); // Dosn't work if called only once when creating
	Graphics.DrawIndexed(IndexCount); // Dosn't work if called only once when creating
}


DirectX::XMMATRIX Chunk::GetTransformXM() const noexcept
{
	return DirectX::XMLoadFloat3x3(&ChunkTransform) *  DirectX::XMMatrixTranslation(XCoordinate, YCoordinate, ZCoordinate);
}


DxgiInfoManager& Chunk::GetInfoManager(Graphics& Graphics) noexcept(IS_DEBUG)
{
#ifndef NDEBUG
	return Graphics.InfoManager;
#else
	throw std::logic_error("You break it! (tried to access gfx.infoManager in Release config)");
#endif
}


UINT Chunk::VertexBuffersStrides[4];
UINT Chunk::VertexBuffersOffsets[4];
Microsoft::WRL::ComPtr<ID3D11Buffer> Chunk::ConstantBufferColorsP;
Microsoft::WRL::ComPtr<ID3D11Buffer> Chunk::ConstantBufferViewProjP;
UINT Chunk::ConstantBufferViewProjPSlot;
Microsoft::WRL::ComPtr<ID3DBlob> Chunk::BytecodeBlobP;
Microsoft::WRL::ComPtr<ID3D11VertexShader> Chunk::VertexShaderP;
Microsoft::WRL::ComPtr<ID3D11InputLayout> Chunk::InputLayoutP;
Microsoft::WRL::ComPtr<ID3D11PixelShader> Chunk::PixelShaderP;
D3D11_PRIMITIVE_TOPOLOGY Chunk::PrimitiveTopology;
bool Chunk::PrimitiveTopologyIsSet = false;
DirectX::XMFLOAT3X3 Chunk::ChunkTransform;
bool Chunk::ChunkTransformIsSet = false;