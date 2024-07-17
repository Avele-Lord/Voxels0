#pragma once
// Refactored 13.04.2021	// Looked Through 15.09.2021


template<class T>
class IndexedTriangleList
{
public:
	IndexedTriangleList() = default;
	IndexedTriangleList(std::vector<T> Verts_In, std::vector<unsigned short> Indices_In)
		:
		Vertices(std::move(Verts_In)),
		Indices(std::move(Indices_In))
	{
		assert(Vertices.size() > 2);
		assert(Indices.size() % 3 == 0);
	}


public:
	std::vector<T> Vertices;
	std::vector<unsigned short> Indices;
};