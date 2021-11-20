#pragma once

#include <engine/graphics/core/shader.hpp>
#include <engine/graphics/camera.hpp>
#include <engine/graphics/core/geometrybuffer.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>

namespace graphics {

	class ParticleRenderer
	{
	public:
		ParticleRenderer();

		void draw(const glm::vec3& _position, const glm::quat& _rotation, float _size);

		void present(const Camera& _camera);
		void clear();
	private:
		struct Vertex
		{
			glm::vec3 position;
			glm::quat rotation;
			float size;
		};
		std::vector<Vertex> m_particles;
		GeometryBuffer m_buffer;
		Program m_program;
	};
}