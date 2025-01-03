#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"


class Renderer {
public:
	Renderer(const Shader& shader);
	~Renderer();
	void Draw(const Texture2D& texture,
		glm::vec2 position, 
		glm::vec2 size = glm::vec2(10.0f, 10.0f), 
		float rotate = 0.0f, 
		glm::vec4 color = glm::vec4(1.0f));
	
private:
	Shader shader;
	unsigned int quadVAO;
	void initRenderData();
};
