#pragma once
#include "Singleton.h"
#include "Core/Logger.h"
#include "Object.h"
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
	class PrototypeCreator : public CreatorBase
	{
	public:
		PrototypeCreator(std::unique_ptr<T> prototype) : m_prototype{ std::move(prototype) } {}
		virtual std::unique_ptr<class Object> Create() override
		{
			return m_prototype->Clone();
		}

	private:
		std::unique_ptr<T> m_prototype;
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
		void RegisterPrototype(const std::string& key, std::unique_ptr<T> prototype);

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
	inline void Factory::RegisterPrototype(const std::string& key, std::unique_ptr<T> prototype)
	{
		INFO_LOG("Prototype Class Registered: " << key);
		m_registry[key] = std::make_unique<PrototypeCreator<T>>(std::move(prototype));
	}

	template<typename T>
	inline std::unique_ptr<T> Factory::Create(const std::string& key)
	{
		auto iter = m_registry.find(key);
		if (iter != m_registry.end())
		{
			return std::unique_ptr<T>(dynamic_cast<T*>(iter->second->Create().release()));
		}

		ERROR_LOG("Class not found in Factory: " << key);

		return std::unique_ptr<T>();
	}
}