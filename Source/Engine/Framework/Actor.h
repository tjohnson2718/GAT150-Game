#pragma once
#include "Object.h"
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Components/Component.h"
#include "Core/Json.h"
#include <memory>

namespace kiko
{
	class Actor : public Object
	{
	public:
		CLASS_DECLARATION(Actor)

		Actor() = default;

		Actor(const Transform& transform) : transform{ transform } {}

		virtual bool Initialize() override;
		virtual void OnDestroy() override;

		virtual void Update(float dt);
		virtual void Draw(Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* GetComponent();

		virtual void OnCollisionEnter(Actor* other) {}
		virtual void OnCollisionExit(Actor* other) {}

		class Scene* m_scene = nullptr;
		friend class Scene;

		class Game* m_game = nullptr;

	public:
		Transform transform;
		std::string tag;
		float lifespan = -1.0f;
		bool destroyed = false;
		bool persistent = false;
		bool prototype = false;


	protected:
		std::vector<std::unique_ptr<Component>> components;
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : components)
		{
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}

		return nullptr;
	}
}
