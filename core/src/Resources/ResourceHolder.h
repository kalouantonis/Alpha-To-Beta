#ifndef _RESOURCEHOLDER_H
#define _RESOURCEHOLDER_H

#include <unordered_map>
#include <memory>
#include <Utils/Logger.h>

/**
 * @brief Holder of various long lived resources
 * 
 * @tparam Identifier Identifier type to use
 * @tparam Resource Resource type used
 */
template <class Identifier, class Resource>
class ResourceHolder
{
public:
    virtual ~ResourceHolder() { clear(); }

    /**
     * @brief Load item from file and give it an ID
     * 
     * @param id ID to assign to object
     * @param filename File to load from
     */
	void load(Identifier id, const std::string& filename)
	{
		// Create and load resource
		ResourcePtr resource(new Resource());
		if(!resource->loadFromFile(filename))
			throw std::runtime_error("Failed to load: " + filename);

		// If loading successful, insert resource to map
        insertResource(id, resource);
	}

    /**
     * @brief Load item from file and give it an ID, along with passing it 
     * an extra parameter
     * 
     * @param id ID to assign to object
     * @param filename File to load from
     * @param secondParam Second parameter to use
     * @tparam Parameter Extra parameter type
     */
	template <typename Parameter>
	void load(Identifier id, const std::string& filename, const Parameter& secondParam)
	{
		// Create and load resource
		ResourcePtr resource(new Resource());
		if(!resource->loadFromFile(filename, secondParam))
			throw std::runtime_error("Failed to load: " + filename);

		// Insert to resource map
		insertResource(id, resource);
	}

    /**
     * @brief Get resource under given ID
     * 
     * @param id ID of resource 
     * @return Constant reference to resource
     */
    const Resource&	get(Identifier id) const
	{
		auto found = m_resourceMap.find(id);
		// If at end, then not found
		CORE_ASSERT(found != m_resourceMap.end());

		return *(found->second);
	}

    /**
     * @brief Get resource under given ID
     * 
     * @param id ID of resource
     * @return reference to resource
     */
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

    /**
     * @brief Remove resource from holder under the given ID
     * 
     * @param id ID of resource
     */
	void remove(Identifier id)
	{
		auto found = m_resourceMap.find(id);
		CORE_ASSERT(found != m_resourceMap.end());

		m_resourceMap.erase(found);
	}
    /**
     * @brief Clear all resource
     */
	void clear() { m_resourceMap.clear(); }

    /**
     * @brief Is resource holder empty
     */
	bool empty() const { return m_resourceMap.empty(); }

private:
	typedef std::unique_ptr<Resource> ResourcePtr;

    /**
     * @brief Insert a new resource in to the map
     * @details Transfers ownership to this holder
     */
    void insertResource(Identifier id, const ResourcePtr& resource)
	{
		// Insert and check success
		auto inserted = m_resourceMap.insert(std::make_pair(id, std::move(resource)));
		CORE_ASSERT(inserted.second);
	}

	std::unordered_map<Identifier, ResourcePtr>	m_resourceMap;
};

#endif // _RESOURCEHOLDER_H
