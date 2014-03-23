#ifndef QuadTree_h__
#define QuadTree_h__

#include <array>
#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <entityx/Entity.h>

class QuadTree
{
public:
	QuadTree(int level, const sf::FloatRect& bounds);
	~QuadTree();

	// Note: May use shared_ptrs. Not sure of the implementation yet
	void insert(const entityx::Entity& entity);

	void clear();
	void split();

	void retrieve(std::vector<entityx::Entity>& objects, 
		const entityx::Entity& entity);

private:
	unsigned int m_level;

	int getIndex(float x, float y, float width, float height);

	sf::FloatRect m_bounds;
	std::vector<entityx::Entity> m_objects;
	std::array<QuadTree, 4> m_nodes;
};

#endif // QuadTree_h__
