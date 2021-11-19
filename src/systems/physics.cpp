#include "physics.hpp"
#include <engine/game/operations/applyVelocity.hpp>

namespace game {
namespace systems {

	void Physics::update(Components _comps, float _deltaTime)
	{
		_comps.execute(operations::ApplyVelocity(_deltaTime));
		_comps.execute([&](Entity ent, const components::Velocity&)
			{
				getComp<components::TransformNeedsUpdate>(_comps).add(ent);
			});
	}

}
}