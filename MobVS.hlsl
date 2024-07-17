// Refactored ??.??.2021	// Looked Through 15.09.2021


cbuffer CBuf
{
	matrix ModelView;
	matrix ModelViewProj;
};


struct VertexInstanceData
{
	float3 Pos : Position;
	float3 InstancePosition : InstancePosition;
	//uint Instance : SV_InstanceID;
};


float4 main(VertexInstanceData VertexInstanceData) : SV_Position
{
	VertexInstanceData.Pos.x += VertexInstanceData.InstancePosition.x;
	VertexInstanceData.Pos.y += VertexInstanceData.InstancePosition.y;
	VertexInstanceData.Pos.z += VertexInstanceData.InstancePosition.z;
	return mul(float4(VertexInstanceData.Pos,1.0f),ModelViewProj);
}