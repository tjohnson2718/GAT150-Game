#pragma once
#include "Resource.h"
#include "Framework/Singleton.h"
#include <string>
#include <map>
#include <memory>

#define GET_RESOURCE(type, filename, ...) kiko::ResourceManager::Instance().Get<type>(filename, __VA_ARGS__)

namespace kiko
{
	class ResourceManager : public Singleton<ResourceManager>
	{
	public:
		template<typename T, typename ... TArgs>
		res_t<T> Get(const std::string& filename, TArgs ... args);

		ResourceManager() = default;

	private:
		std::map<std::string, res_t<Resource>> m_resources;
	};

	template<typename T, typename ...TArgs>
	inline res_t<T> ResourceManager::Get(const std::string& filename, TArgs ...args)
	{
		if (m_resources.find(filename) != m_resources.end())
		{
			return std::dynamic_pointer_cast<T>(m_resources[filename]);
		}


		res_t<T> resource = std::make_shared<T>();
		if (!resource->Create(filename, args...))
		{
			WARNING_LOG("Could not create resource: " << filename);
			return res_t<T>();
		}
	
		m_resources[filename] = resource;
		return resource;

	}
}