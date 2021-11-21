#include "physics.hpp"
#include "../components/collider.hpp"
#include <engine/game/operations/applyVelocity.hpp>
#include <spdlog/spdlog.h>

namespace game {
namespace systems {

	using namespace glm;
	using namespace math;

	void Physics::update(Components _comps, float _deltaTime, SceneGraph& _sceneGraph)
	{
		namespace comps = components;
		// dampening proportional to current speed
		_comps.execute([&](components::Velocity& vel)
			{
				constexpr float dampCoef = 0.1f;
				vel.value *= 1.f - dampCoef * _deltaTime * glm::dot(vel.value, vel.value);
			});

		// orientation according to velocity
		// todo: move into extra system?
		_comps.execute([&](components::AngularVelocity& angVel
			, const components::Velocity& vel
			, const components::Rotation& rot)
			{
				mat3 rotMat = static_cast<mat3>(rot.value);
				const vec3 forward = rotMat * vec3(0.f, 1.f, 0.f);
				const float speed = length(vel.value);
				spdlog::info("{}", angVel.speed);
				if (speed > 0.001f)
				{
					const vec3 dir = vel.value / speed;
					if (const float angle = std::acos(dot(forward, dir)); angle > 0.001f)
					{
						const vec3 axis = normalize(cross(forward, dir));
						angVel.axis = axis;
						angVel.speed = angle * angle * 3.f + angle * 1.f + 2.f;
						if (angVel.speed * _deltaTime >= angle)
						{
							angVel.speed = angle / _deltaTime * 0.5f;
						}
					}
					else
						angVel.speed = 0.f;
				}
				else
					angVel.speed = 0.f;
			});

		_comps.execute(operations::ApplyVelocity(_deltaTime));
		_comps.execute(operations::ApplyAngularVelocity(_deltaTime));
		_comps.execute([&](Entity ent, const components::Velocity&)
			{
				getComp<components::TransformNeedsUpdate>(_comps).add(ent);
			});

		// rebuild scene graph
		_sceneGraph.objects.clear();
		_comps.execute([&](Entity _ent, const comps::SphereCollider& _collider, const comps::Position& _position)
			{
				_sceneGraph.objects.insert(math::AABB3D(vec3(-_collider.radius) + _position.value,
					vec3(_collider.radius) + _position.value), { _collider.type, _ent });
			});

		_comps.execute([&](Entity _ent
			, const comps::SphereCollider& _collider
			, comps::Position& _position
			, comps::Velocity& _velocity)
			{
				const float r = _collider.radius;
				math::AABB3D aabb(vec3(-r) + _position.value, vec3(r) + _position.value);
				// prevent match with current element and double checks
				if (!_sceneGraph.objects.remove(aabb, { _collider.type, _ent }))
					spdlog::debug("Current collider not found in the intersection structure.");

				auto resolveCollisions = [&](const AABB3D& key, CollisionEntity el)
				{
					const Entity oth = el.entity;
					// do not test colliders of the same entity
					if (_ent == oth || _collider.type == el.type)
						return;

					//	HitInfo info;
					bool collide = false;

					if (auto collider = getComp<comps::SphereCollider>(_comps).get(oth))
					{
						const float rOth = collider->radius;
						auto& posOth = getComp<comps::Position>(_comps).getUnsafe(oth);
						auto& velOth = getComp<comps::Velocity>(_comps).getUnsafe(oth);

						const glm::vec3 diff = posOth.value - _position.value;
						const float distSq = glm::dot(diff, diff);
						const float minDist = _collider.radius + collider->radius;
						if (distSq < minDist)
						{
							const glm::vec3 normal = glm::normalize(diff);
							const float d = glm::dot(_velocity.value - velOth.value, normal);
							if (d >= 0.f)
							{
								constexpr float c = 0.5f;
								const float J = 1.f * 1.f / (1.f + 1.f)
									* (1.f + c) * d;
								_velocity.value -= J / 1.f * normal;
								velOth.value += J / 1.f * normal;
							}
						}
						//	collide |= sphereSphereCollision(_position, r, posOth, rOth);
					}

					if (collide)
					{
						getComp<comps::TransformNeedsUpdate>(_comps).add(_ent);
						getComp<comps::TransformNeedsUpdate>(_comps).add(oth);
					}
				};
				SceneGraph::QueryStructure::IntersectQuery<decltype(resolveCollisions)> query(aabb, resolveCollisions);
				_sceneGraph.traverse(query);
			});
	}

}
}