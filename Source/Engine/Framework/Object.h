#pragma once
#include <string>

#define CLASS_DECLARATION(classname) \
	virtual const char* GetClassName() { return #classname; } \
		class Register \
		{ \
		public: \
			Register() \
			{ \
				Factory::Instance().Register<classname>(#classname); \
			} \
		}; 

#define CLASS_DEFINITION(classname) \
	classname::Register register_class;

namespace kiko
{
	class Object
	{
	public:
		Object() = default;
		Object(const std::string name) : m_name{ name } {}
		virtual ~Object() { OnDestroy(); }

		CLASS_DECLARATION(Object)

		virtual bool Initialize() { return true; }
		virtual void OnDestroy() {}

	protected:
		std::string m_name;
	};
}