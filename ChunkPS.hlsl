// Refactored 11.06.2021	// Looked Through 15.09.2021


cbuffer ConstBufferColor
{
	float4 Colors[12];
};

struct ColorData
{
	int Color : Color;
	float3 RandomColor : RandomColor;
	unsigned int ColorGradient : ColorGradient;
};


float4 main( ColorData ColorData ) : SV_Target
{
	float4 Color = Colors[ColorData.Color - 1]; //  [ColorData.Color - 1] ( -1 ) Minus one cos 0 indicates for empty voxel so in chunk generator start count of colors is 1
	// Make RandomColor only one variable so that color isn't different color but just the gradient of one color ( befor there was just .x .x .x not .x .y .z
	Color.x += ColorData.RandomColor.x;
	Color.y += ColorData.RandomColor.y;
	Color.z += ColorData.RandomColor.z;

	float ColorGradient = (float)ColorData.ColorGradient / 40.0f;
	if (ColorGradient <= 0.5f)
	{
		ColorGradient += 0.2f;
	}

	Color.x *= ColorGradient;
	Color.y *= ColorGradient;
	Color.z *= ColorGradient;

	return Color;
}