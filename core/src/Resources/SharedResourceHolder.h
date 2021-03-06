#ifndef SharedResourceHolder_h__
#define SharedResourceHolder_h__

#include <unordered_map>
#include <memory>
#include <Utils/Logger.h>

/**
 * @brief Works like ResourceHolder, apart from all items are stored as 
 * shared_ptr's rather than unique_ptr's
 */
template <class Identifier, class Resource>
class SharedResourceHolder
{
public:
	typedef std::shared_ptr<Resource> Ptr;
    typedef const std::shared_ptr<const Resource> ConstPtr;

    virtual ~SharedResourceHolder() { clear(); }

	void load(Identifier id, const std::string& filename)
	{
		// Create and load resource
		Ptr resource(new Resource());
		if(!resource->loadFromFile(filename))
			throw std::runtime_error("Failed to load: " + filename);

		// If loading successful, insert resource to map
		// Transfer ownership to map, as it will have a longer lifetime than all others 
		insertResource(id, resource);
	}

	template <typename Parameter>
	void load(Identifier id, const std::string& filename, const Parameter& secondParam)
	{
		// Create and load resource
		Ptr resource(new Resource());
		if(!resource->loadFromFile(filename, secondParam))
			throw std::runtime_error("Failed to load: " + filename);

		// Insert to resource map
		insertResource(id, std::move(resource));
	}

    // Return pointer, not reference. Thus we declare another owner of the object
    Ptr get(Identifier id)
    {
        // Duplication exists, but its better than using const_cast in this
        // case due to the forced removal of const ptr<const T> to ptr<const T>
        // and then to ptr<T>

        auto found = m_resourceMap.find(id);
        // If at end, then not found
        //assert(found != m_resourceMap.end());
        if(found != m_resourceMap.end())
	        return found->second;

	    return nullptr;
    }

    ConstPtr get(Identifier id) const
	{
		auto found = m_resourceMap.find(id);
		// If at end, then not found
		// assert(found != m_resourceMap.end());
		if(found != m_resourceMap.end())
			return found->second;

		return nullptr;
    }

	void remove(Identifier id)
	{
		auto found = m_resourceMap.find(id);
		CORE_ASSERT(found != m_resourceMap.end());

		m_resourceMap.erase(found);
	}

	void clear() 
	{ 
		if(!m_resourceMap.empty())
			m_resourceMap.clear();
	}
	
	bool empty() const { return m_resourceMap.empty(); }

private:
	void insertResource(Identifier id, const Ptr& resource)
	{
		// Insert and check success
		/*auto inserted = */m_resourceMap.insert(std::make_pair(id, std::move(resource)));
		//assert(inserted.second);
	}

	std::unordered_map<Identifier, Ptr> m_resourceMap;
};

template <class T>
std::shared_ptr<T> make_holder(T* resouceHolder);

#endif // SharedResourceHolder_h__
