#pragma once
#include "Resource.h"
#include <string>
#include <map>
#include <memory>

namespace kiko
{
	class ResourceManager
	{
	public:
		template<typename T, typename ... TArgs>
		res_t<T> Get(const std::string& filename, TArgs ... args);

		ResourceManager() = default;

		void Add(const std::string& id, const std::string& filename);
		std::shared_ptr<Resource> Get(const std::string& id);

	private:
		std::map<std::string, res_t<Resource>> m_resources;
	};

	template<typename T, typename ...TArgs>
	inline res_t<T> ResourceManager::Get(const std::string& filename, TArgs ...args)
	{
		if (m_resources.find(filename) != m_resources.end())
		{
			return std::dynamic_pointer_cast<T>(m_resources(filename));
		}

		res_t<T> resource = std::make_shared<T>();
		resource->Create(filename, args...);
		m_resources[filename] = resource;

		return resource;

	}

	extern ResourceManager g_resources;
}