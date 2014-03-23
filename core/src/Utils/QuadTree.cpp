#include <Utils/QuadTree.h>

const unsigned int MAX_OBJECTS = 10;
const unsigned int MAX_LEVES = 5;

QuadTree::QuadTree(int level, const sf::FloatRect& bounds)
	: m_level(level)
	, m_bounds(bounds)
{

}

QuadTree::~QuadTree()
{

}

void QuadTree::insert(const entityx::Entity& entity)
{
	if(nodes[0] != nullptr)
	{
		int index = getIndex(entity.component<Transform>());

		if(index != -1)
		{
			nodes[index].insert(entity);

			return;
		}
	}

	m_objects.push_back(pRect);

	if(m_objects.size() > MAX_OBJECTS && level < MAX_LEVELS)
	{
		if(m_nodes[0] == nullptr)
		{
			split();
		}

		int i = 0;
		while(i < m_objects.size())
		{
			//int index = getIndex()
			if(index != -1)
			{
				//m_nodes[index].insert()
			}
		}
	}
}

void QuadTree::clear()
{

}

void QuadTree::split()
{

}

void QuadTree::retrieve(std::std::vector<entityx::Entity>& objects,
	const entityx::Entity& entity)
{

}

int QuadTree::getIndex(float x, float y, float width, float height)
{
	int index = -1;

	double verticalMidpoint = x + (width / 2.0);
	double horizontalMidpoint = y + (height / 2.0);

	// object can completelly fit within the top quadrants
	bool topQuad = (y < horizontalMidpoint && y + height < horizontalMidpoint);
	// object can completelly fit within the bottom quadrants
	bool bottomQuad = (y > horizontalMidpoint);

	// object can fit within the left quadrants
	if(x < verticalMidpoint && x + width < verticalMidpoint)
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