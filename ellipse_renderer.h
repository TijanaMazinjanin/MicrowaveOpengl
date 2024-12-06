#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"

#include <vector>


class EllipseRenderer {
public:
	EllipseRenderer(const Shader& shader, int cres, float positionX, float positionY);
	~EllipseRenderer();
	void Draw(const Texture2D& texture,
		glm::vec2 position,
		float radiusX, float radiusY,
		glm::vec3 color = glm::vec3(1.0f));
private:
	Shader shader;
	unsigned int ellipseVAO;
	void initEllipseData(int cres, float positionX, float positionY);
	std::vector<float> circleVertices;
};
