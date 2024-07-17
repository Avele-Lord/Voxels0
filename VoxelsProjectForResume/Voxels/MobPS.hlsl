// Refactored ??.??.2021	// Looked Through 15.09.2021


cbuffer CBuf
{
	float4 Color;
};  

float4 main( /*uint TID : SV_PrimitiveID*/ ) : SV_Target
{
	return Color;
}	