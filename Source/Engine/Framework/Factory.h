#pragma once
#include "Singleton.h"
#include "Core/Logger.h"
#include <string>
#include <memory>
#include <map>

#define CREATE_CLASS(classname) kiko::Factory::Instance().Create<kiko::classname>(#classname)
#define CREATE_CLASS_BASE(classbase, classname) kiko::Factory::Instance().Create<kiko::classbase>(classname)
#define INSTANTIATE(classbase, classname) kiko::Factory::Instance().Create<kiko::classbase>(classname)

namespace kiko
{
	class CreatorBase
	{
	public:
		virtual ~CreatorBase() = default;

		virtual std::unique_ptr<class Object> Create() = 0;
	};

	template<typename T>
	class Creator : public CreatorBase
	{
	public:
		virtual std::unique_ptr<class Object> Create() override
		{
			return std::make_unique<T>();
		}
	};

	class Factory :public Singleton<Factory>
	{
	public:
		template<typename T>
		void Register(const std::string& key);

		template<typename T>
		std::unique_ptr<T> Create(const std::string& key);

		friend class Singleton;

	protected:
		Factory() = default;

	private:
		std::map<std::string, std::unique_ptr<CreatorBase>> m_registry;
	};

	template<typename T>
	inline void Factory::Register(const std::string& key)
	{
		INFO_LOG("Class Registered: " << key);
		m_registry[key] = std::make_unique<Creator<T>>();
	}

	template<typename T>
	inline std::unique_ptr<T> Factory::Create(const std::string& key)
	{
		auto iter = m_registry.find(key);
		if (iter != m_registry.end())
		{
			return std::unique_ptr<T>(dynamic_cast<T*>(iter->second->Create().release()));
		}

		return std::unique_ptr<T>();
	}
}