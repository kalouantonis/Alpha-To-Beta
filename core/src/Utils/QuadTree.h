#ifndef QuadTree_h__
#define QuadTree_h__

#include <array>
#include <unordered_map>

#include <SFML/Graphics/Rect.hpp>
#include <Artemis/Entity.h>

class QuadTree
{
public:
	QuadTree(int level, const sf::FloatRect& bounds);
	~QuadTree();

	// Note: May use shared_ptrs. Not sure of the implementation yet
	void insert(const artemis::Entity& entity);

	void clear();

	void retrieve(std::unordered_map<int, const Transform* transform>& objects, 
		const artemis::Entity& entity);

private:
	unsigned int m_level;

	/**
	 * @brief Splits the node in to 4 subnodes
	 */
	void split();

	int getIndex(float x, float y, float width, float height);

	sf::FloatRect m_bounds;

	typedef std::pair<int, const Transform*> TransformPair;
	typedef std::vector<TransformPair> TransformVector;

	TransformVector m_objects;
	std::array<QuadTree, 4> m_nodes;
};

#endif // QuadTree_h__
