#pragma once
// Refactored 13.06.2021	// Looked Through 15.09.2021
#include "IndexedTriangleList.h" // need


class MakeCube
{
public:
	template<class V>
	static IndexedTriangleList<V> Make()
	{
		constexpr float Side = 1.0f / 2.0f;
		std::vector<V> Vertices(8);
		Vertices[0].Pos = { -Side,-Side,-Side };
		Vertices[1].Pos = { Side,-Side,-Side };
		Vertices[2].Pos = { -Side,Side,-Side };
		Vertices[3].Pos = { Side,Side,-Side };
		Vertices[4].Pos = { -Side,-Side,Side };
		Vertices[5].Pos = { Side,-Side,Side };
		Vertices[6].Pos = { -Side,Side,Side };
		Vertices[7].Pos = { Side,Side,Side };

		return{
			std::move(Vertices),{
				0,2,1, 2,3,1,
				1,3,5, 3,7,5,
				2,6,3, 3,6,7,
				4,5,7, 4,7,6,
				0,4,2, 2,4,6,
				0,1,4, 1,5,4
			}
		};
	}
};