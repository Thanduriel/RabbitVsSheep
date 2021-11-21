#include "particledrawing.hpp"

namespace game {
namespace systems{

	void ParticleDrawing::update(Components _comps, const graphics::Camera& _camera)
	{
		m_renderer.clear();

		_comps.execute([&](const components::Position& pos, const components::Rotation& rot)
			{
				m_renderer.draw(pos.value, rot.value, 1.f);
			});

		m_renderer.present(_camera);
	}

	void LineDrawing::update(Components _comps, const graphics::Camera& _camera)
	{
		m_renderer.clear();

		_comps.execute([&](const components::Ray& ray, const components::Position& pos)
			{
				m_renderer.draw(pos.value, ray.target, ray.color, ray.thickness);
			});

		m_renderer.present(_camera);
	}
}
}