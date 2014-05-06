#ifndef _RESOURCEHOLDER_H
#define _RESOURCEHOLDER_H

#include <unordered_map>
#include <memory>
#include <cassert>

template <class Identifier, class Resource>
class ResourceHolder
{
public:
    virtual ~ResourceHolder() { clear(); }

	void load(Identifier id, const std::string& filename)
	{
		// Create and load resource
		ResourcePtr resource(new Resource());
		if(!resource->loadFromFile(filename))
			throw std::runtime_error("ResourceHolder::load - Failed to load: " + filename);

		// If loading successful, insert resource to map
        insertResource(id, resource);
	}

	template <typename Parameter>
	void load(Identifier id, const std::string& filename, const Parameter& secondParam)
	{
		// Create and load resource
		ResourcePtr resource(new Resource());
		if(!resource->loadFromFile(filename, secondParam))
			throw std::runtime_error("ResourceHolder::load - Failed to load: " + filename);

		// Insert to resource map
		insertResource(id, resource);
	}

    const Resource&	get(Identifier id) const
	{
		auto found = m_resourceMap.find(id);
		// If at end, then not found
		assert(found != m_resourceMap.end());

		return *(found->second);
	}

    Resource& get(Identifier id)
    {
        // Calling the const version of get reduces duplication.
        // Calling it provides no risk

        // Cast away const on return type
        return const_cast<Resource&>(
                // Add const to *this type and call const version of method
                static_cast<const ResourceHolder&>(*this).get(id)
        );
    }


	void remove(Identifier id)
	{
		auto found = m_resourceMap.find(id);
		assert(found != m_resourceMap.end());

		m_resourceMap.erase(found);
	}

	void clear() { m_resourceMap.clear(); }

	bool empty() const { return m_resourceMap.empty(); }

private:
	typedef std::unique_ptr<Resource> ResourcePtr;

    void insertResource(Identifier id, const ResourcePtr& resource)
	{
		// Insert and check success
		auto inserted = m_resourceMap.insert(std::make_pair(id, std::move(resource)));
		assert(inserted.second);
	}

	std::unordered_map<Identifier, ResourcePtr>	m_resourceMap;
};

#endif // _RESOURCEHOLDER_H
