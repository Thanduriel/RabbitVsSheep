#include "mapboundary.hpp"

namespace game {
namespace systems{

	MapBoundary::MapBoundary(std::vector<math::AABB3D> _areas)
		: m_areas(std::move(_areas))
	{
	}

	void MapBoundary::update(Components _comps) const
	{
		_comps.execute([&](const components::AreaRestriction& restriction
			, const components::Position& position
			, components::Velocity& velocity)
			{
				const math::AABB3D& area = m_areas[static_cast<size_t>(restriction.area)];
				if (!area.isIn(position.value))
					velocity.value = glm::vec3(0.f);
			});
	}
}
}