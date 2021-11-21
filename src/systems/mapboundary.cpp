#include "mapboundary.hpp"

namespace game {
namespace systems{

	void MapBoundary::update(Components _comps, float _deltaTime, const MapBoundaries& _boundaries) const
	{
		const float maxOver = 2.f * _boundaries.size;
		_comps.execute([&](const components::AreaRestriction& restriction
			, const components::Position& position
			, components::Velocity& velocity)
			{
				const math::AABB3D& area = _boundaries.areas[static_cast<size_t>(restriction.area)];
				for (int i = 0; i < 3; ++i)
				{
					const float under = area.min[i] + _boundaries.size - position.value[i];
					if (under > 0.f)
					{
						velocity.value[i] += 132.f * std::min(under, maxOver) * _deltaTime;
					}

					const float over = position.value[i] - area.max[i] + _boundaries.size;
					if (over > 0.f)
					{
						velocity.value[i] -= 132.f * std::min(over, maxOver) * _deltaTime;
					}
				}
			});
	}

	void BoundaryGrid::update(Components _comps, EntityCreator& _creator, const MapBoundaries& _boundaries) const
	{
		static bool init = false;
		if (!init)
		{
			init = true;

			constexpr float targetRayLen = 2.5f;
			for (const math::AABB3D& area : _boundaries.areas)
			{
				glm::vec3 direction = area.size();
				glm::ivec2 numRays(std::ceil(direction.x / targetRayLen), std::ceil(direction.y / targetRayLen));
				const glm::vec3 offset(direction.x / (numRays.x-1), direction.y / (numRays.y-1), 0.f);
				const glm::vec3 pos = glm::vec3(area.min.x, area.min.y, 0.f);
				for (int i = 0; i < numRays.x; ++i)
				{
					glm::vec3 cur(pos.x + i * offset.x, pos.y, 0.f);
					glm::vec3 target(cur.x, cur.y + direction.y, 0.f);

					CreateComponents(_comps, _creator.create())
						.add<components::Position>(cur)
						.add<components::Ray>(target, glm::vec4(0.f, 1.f, 0.f, 0.5f), 0.5f);
				}

				for(int i = 0; i < numRays.y; ++i)
				{
					glm::vec3 cur(pos.x, pos.y + i * offset.y, 0.f);
					glm::vec3 target(cur.x + direction.x, cur.y, 0.f);

					CreateComponents(_comps, _creator.create())
						.add<components::Position>(cur)
						.add<components::Ray>(target, glm::vec4(0.f,1.f,0.f, 0.5f), 0.5f);
				}
			}
		}
	}
}
}