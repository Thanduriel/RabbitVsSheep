#include "particlerenderer.hpp"
#include <engine/graphics/resources.hpp>
#include <engine/graphics/core/device.hpp>
#include <array>

namespace graphics {

	constexpr std::array<VertexAttribute, 3> vertexAttributes = { {
		{PrimitiveFormat::FLOAT, 3, false, false},
		{PrimitiveFormat::FLOAT, 4, false, false},
		{PrimitiveFormat::FLOAT, 1, false, false}
	} };

	ParticleRenderer::ParticleRenderer()
		: m_buffer(GLPrimitiveType::POINTS, vertexAttributes.data(), static_cast<int>(vertexAttributes.size()), 0)
	{
		m_program.attach(ShaderManager::get("shader/particle.vert", ShaderType::VERTEX));
		m_program.attach(ShaderManager::get("shader/particlecube.geom", ShaderType::GEOMETRY));
		m_program.attach(ShaderManager::get("shader/particle.frag", ShaderType::FRAGMENT));
		m_program.link();
	}

	void ParticleRenderer::draw(const glm::vec3& _position, const glm::quat& _rotation, float _size)
	{
		m_particles.emplace_back(_position, _rotation, _size);
	}

	void ParticleRenderer::clear()
	{
		m_particles.clear();
	}

	void ParticleRenderer::present(const Camera& _camera)
	{
		Device::setZFunc(ComparisonFunc::LESS);
		Device::setZWrite(false);
		Device::enableBlending(true);
		Device::setBlendOp(BlendOp::ADD);
		Device::setBlendFactor(BlendFactor::SRC_ALPHA, BlendFactor::ONE);

		m_program.use();
		m_program.setUniform(0, _camera.getViewProjection());

		m_buffer.setData(m_particles.data(), static_cast<unsigned>(m_particles.size() * sizeof(Vertex)));
		m_buffer.draw();

		Device::setZWrite(true);
	}
}