#pragma once

//  Refactored start 13.04.2021
class MakeCubeFace
{
public:
	template<class V>
	static IndexedTriangleList<V> Make(VoxelFaces VoxelFaces)
	{
		constexpr float Side = 1.0f / 2.0f;

		std::vector<V> Vertices(4);
	
		switch (VoxelFaces)
		{
		case VoxelFaces::Top:
			Vertices[0].Pos = { -Side,Side,-Side };
			Vertices[1].Pos = { Side,Side,-Side };
			Vertices[2].Pos = { -Side,Side,Side };
			Vertices[3].Pos = { Side,Side,Side };
			return{ std::move(Vertices),{0,2,1, 1,2,3} };
		case VoxelFaces::Left:
			Vertices[0].Pos = { -Side,-Side,-Side };
			Vertices[1].Pos = { -Side,Side,-Side };
			Vertices[2].Pos = { -Side,-Side,Side };
			Vertices[3].Pos = { -Side,Side,Side };
			return{ std::move(Vertices),{0,2,1, 1,2,3} };
		case VoxelFaces::Front:
			Vertices[0].Pos = { -Side,-Side,-Side };
			Vertices[1].Pos = { Side,-Side,-Side };
			Vertices[2].Pos = { -Side,Side,-Side };
			Vertices[3].Pos = { Side,Side,-Side };
			return{ std::move(Vertices),{0,2,1, 2,3,1} };
		case VoxelFaces::Right:
			Vertices[0].Pos = { Side,-Side,-Side };
			Vertices[1].Pos = { Side,Side,-Side };
			Vertices[2].Pos = { Side,-Side,Side };
			Vertices[3].Pos = { Side,Side,Side };
			return{ std::move(Vertices),{0,1,2, 1,3,2} };
		case VoxelFaces::Back:
			Vertices[0].Pos = { -Side,-Side,Side };
			Vertices[1].Pos = { Side,-Side,Side };
			Vertices[2].Pos = { -Side,Side,Side };
			Vertices[3].Pos = { Side,Side,Side };
			return{ std::move(Vertices),{0,1,3, 0,3,2} };
		case VoxelFaces::Bottom:
			Vertices[0].Pos = { -Side,-Side,-Side };
			Vertices[1].Pos = { Side,-Side,-Side };
			Vertices[2].Pos = { -Side,-Side,Side };
			Vertices[3].Pos = { Side,-Side,Side };
			return{ std::move(Vertices),{0,1,2, 1,3,2} };
		default:
			return{ std::move(Vertices),{} };
			break;
		}
	}
};
//  Refactored end 13.04.2021