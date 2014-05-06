#include <DataStructures/QuadTree.h>

#include <Components/Transform.h>

const unsigned int MAX_OBJECTS = 10;
const unsigned int MAX_LEVES = 5;

QuadTree::QuadTree(int level, const sf::FloatRect& bounds)
	: m_level(level)
	, m_bounds(bounds)
{

}

QuadTree::~QuadTree()
{
	if(!m_objects.empty() || !m_nodes.empty())
	{
		clear();
	}
}

void QuadTree::insert(int id, const Transform* transform)
{
	if(nodes[0] != nullptr)
	{
		int index = getIndex(transform);

		if(index != -1)
		{
			nodes[index].insert(id, transform);

			return;
		}
	}

	m_objects.push_back(TransformPair(id, transform));

	if(m_objects.size() > MAX_OBJECTS && level < MAX_LEVELS)
	{
		if(m_nodes[0] == nullptr)
		{
			split();
		}

		TransformVector::const_iterator it = m_objects.begin();
		while(it != m_objects.end())
		{
			const TransformPair& pair = (*it);

			// Re-insert in to child nodes
			int index = getIndex(pair.second); 
			if(index != -1)
			{
				// Insert in to child node
				m_nodes[index].insert(pair.first, pair.second)
				// Remove from this node
				it = m_objects.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

void QuadTree::clear()
{
	m_objects.clear();

	for(QuadTree& quadTree : m_nodes)
	{
		if(quadTree != nullptr)	
		{
			quadTree.clear();
		}
	}

	m_nodes.clear();
}

void QuadTree::split()
{
	int subWidth = (int)(m_bounds.width / 2.f);
	int subHeight = (int)(m_bounds.height / 2.f);
	int x = (int) m_bounds.x;
	int y = (int) m_bounds.y;

	// Top right
	m_nodes[0] = QuadTree(
		// Lets take it to the next level...
		level + 1, 
		sf::FloatRect(x + subWidth, y, subWidth, subHeight)
	);
	// Top left
	m_nodes[1] = QuadTree(
		level + 1, 
		sf::FloatRect(x, y, subWidth, subHeight)
	);
	// Bottom left
	m_nodes[2] = QuadTree(
		level + 1, 
		sf::FloatRect(x, y + subHeight, subWidth, subHeight)
	);
	// Bottom right
	m_nodes[3] = QuadTree(
		level + 1, 
		sf::FloatRect(x + subWidth, y + subHeight, subWidth, subHeight)
	);
}

void QuadTree::retrieve(std::vector<artemis::Entity>& objects,
	const artemis::Entity& entity)
{
	int index = getIndex(transform);
	if(index != -1 && nodes[0] != nullptr)
	{
		nodes[index].retrieve(returnObjects, transform);
	}

	returnObjects.insert(
		// Insert on the the back of the list
		returnObjects.back(), 
		// All of the object map
		m_objects.begin(),
		m_objects.end()
	)
}

int QuadTree::getIndex(const Transform* transform)
{
	int index = -1;

	const sf::Vector2f& position = transform->position;
	const sf::Vector2f& bounds = transform->bounds;

	double verticalMidpoint = position.x + (bounds.x / 2.0);
	double horizontalMidpoint = position.y + (bounds.y / 2.0);

	// object can completelly fit within the top quadrants
	bool topQuad = (position.y < horizontalMidpoint && 
		position.y + bounds.y < horizontalMidpoint);
	// object can completelly fit within the bottom quadrants
	bool bottomQuad = (position.y > horizontalMidpoint);

	// object can fit within the left quadrants
	if(position.x < verticalMidpoint && 
		position.x + bounds.x < verticalMidpoint)
	{
		if(topQuad)
			index = 1;
		else if(bottomQuad)
			index = 2;
	}
	// Right quads
	else if(x > verticalMidpoint)
	{
		if(topQuad)
			index = 0;
		else if(bottomQuad)
			index = 3;
	}

	return index;
}