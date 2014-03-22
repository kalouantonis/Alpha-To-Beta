#ifndef QuadTree_h__
#define QuadTree_h__

#include <array>
#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <entityx/Entity.h>

class QuadTree
{
public:
	QuadTree(int level, sf::FloatRect bounds);
	~QuadTree();

	// Note: May use shared_ptrs. Not sure of the implementation yet
	void insert(const Entity& entity);

	void clear();
	void split();

	void retrieve(std::vector<Entity>& objects, const Entity& entity);

private:
	unsigned int m_level;

	int getIndex(void);

	sf::FloatRect m_bounds;
	std::array<QuadTree, 4> m_nodes;
};

#endif // QuadTree_h__
