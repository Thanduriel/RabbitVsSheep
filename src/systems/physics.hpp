#pragma once

#include "../components/collider.hpp"
#include <engine/game/core/componentaccess.hpp>
#include <engine/game/components/simpleComponents.hpp>
#include <engine/math/geometrictypes.hpp>
#include <engine/utils/containers/octree.hpp>

namespace game {

	struct CollisionEntity
	{
		CollisionType type;
		Entity entity;

		// entity is already unique
		constexpr bool operator==(const CollisionEntity& _oth) const
		{
			return entity == _oth.entity;
		}
	};

	class SceneGraph
	{
	public:
		SceneGraph()
			: objects(2048.f)
		{}

		// Only checks the AABBs currently.
	//	std::vector<Entity> sphereQuery(const math::Sphere& _circle) const;
		// The ray direction is expected to be normalized
	//	std::vector<Entity> rayQuery(const math::Ray& _ray, float _maxLength = 0.f) const;
		template<class Processor>
		void traverse(Processor& _proc) const
		{
			objects.traverse(_proc);
		}

		using QueryStructure = utils::SparseOctree<CollisionEntity, 3, float>;
		QueryStructure objects;
	};

namespace systems {

	class Physics
	{
	public:
		using Components = ComponentTuple<
			WriteAccess<components::Position>
			, WriteAccess<components::Velocity>
			, ReadAccess<components::SphereCollider>
			, WriteAccess<components::TransformNeedsUpdate>>;

		void update(Components _comps, float _deltaTime, SceneGraph& _sceneGraph);
	};
}
}