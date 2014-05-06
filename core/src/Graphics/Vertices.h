#ifndef VERTICES_H
#define VERTICES_H

#include <vector>

typedef std::vector<float>	FloatBuffer;
typedef std::vector<short> ShortBuffer;

class Vertices
{
public:
	Vertices(unsigned int maxVertices, unsigned int maxIndices, bool hasTexCoords, bool hasColor = false);
	~Vertices();

	void setVertices(FloatBuffer& vertices, int offset, int length);
	void setIndices(ShortBuffer& indices, int offset, int lenght);

	void bind();
	void draw(int primitiveType, int offset, int numVertices);
	void unbind();

private:
	bool m_bHasColor;
	bool m_bHasTexCoords;

	int m_vertexSize;

	FloatBuffer m_vertices;
	ShortBuffer m_indices;
};

#endif // VERTICES_H
