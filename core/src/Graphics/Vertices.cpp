#include <Graphics/Vertices.h>

#include <SFML/OpenGL.hpp>

Vertices::Vertices(unsigned int maxVertices, unsigned int maxIndices, 
	bool hasTexCoords, bool hasColor)
{
	m_bHasTexCoords = hasTexCoords;
	m_bHasColor = hasColor;

	m_vertexSize = (2 + (m_bHasColor ? 4 : 0) + (m_bHasTexCoords ? 2 : 0) * sizeof(float));

	// reserve space, remove un-necessary allocations
	m_vertices.reserve(m_vertexSize * maxVertices);

	if(maxIndices > 0)
	{
		m_indices.reserve(m_vertexSize * maxVertices);
	}
}

Vertices::~Vertices()
{
}

void Vertices::setVertices(FloatBuffer& vertices, int offset, int length)
{
	//m_vertices.clear();
	//m_vertices.insert(offset, vertices.data(), vertice.data() + length);
	// m_vertices.assign(vertices.begin(), vertices.end());
	m_vertices.swap(vertices);
}

void Vertices::setIndices(ShortBuffer &indices, int offset, int lenght)	
{
	m_indices.swap(indices);
}

void Vertices::bind()
{
	// Allow VBA's
	glEnableClientState(GL_VERTEX_ARRAY);

	// Draw primitives
	glVertexPointer(2, GL_FLOAT, m_vertexSize, m_vertices.data());

	if(m_bHasColor)
	{
		// Enable coloring
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4, GL_FLOAT, m_vertexSize, m_vertices.data() + 2);
	}

	if(m_bHasTexCoords)
	{
		// Enable texturing
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, m_vertexSize, m_vertices.data() + (m_bHasColor ? 6 : 2));
	}
}

void Vertices::draw(int primitiveType, int offset, int numVertices)
{
	if(!m_indices.empty())
	{
		glDrawElements(primitiveType, numVertices, GL_UNSIGNED_SHORT, m_indices.data());
	}
	else
	{
		glDrawArrays(primitiveType, offset, numVertices);
	}
}

void Vertices::unbind()
{
	if(m_bHasTexCoords)
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	if(m_bHasColor)
		glDisableClientState(GL_COLOR_ARRAY);
}