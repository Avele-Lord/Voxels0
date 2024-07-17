// Refactored 11.06.2021	// Looked Through 15.09.2021


cbuffer ConstBufferView
{
	matrix ModelView;
	matrix ModelViewProj;
};

struct ColorData
{
	int Color : Color;
	float3 RandomColor : RandomColor;
	unsigned int ColorGradient : ColorGradient;
};

struct VertexBufferInput
{
	float3 Pos : Position;
	ColorData ColorData; 
};

struct VertexBufferOutput
{
	ColorData ColorData;
	float4 Pos : SV_Position;
};


VertexBufferOutput main( VertexBufferInput VertexBufferInput )
{
	VertexBufferOutput VertexBufferOutput;
	VertexBufferOutput.ColorData = VertexBufferInput.ColorData;
	VertexBufferOutput.Pos = mul(float4(VertexBufferInput.Pos, 1.0f), ModelViewProj);
	return VertexBufferOutput;
}