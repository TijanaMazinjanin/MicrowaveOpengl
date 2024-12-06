#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "renderer.h"

class MicrowaveObject {
public:
    
    glm::vec2   Position, Size, Velocity;
    glm::vec4   Color;
    float       Rotation;
    bool        IsSolid;
    bool        Destroyed;
    
    Texture2D   Texture;
    
    MicrowaveObject();
    MicrowaveObject(Texture2D texture, glm::vec2 pos, glm::vec2 size, glm::vec4 color = glm::vec4(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
   
    void Draw(Renderer& renderer);

    glm::vec2 Move(float dt, unsigned int maxHeight, unsigned int maxWidth);
    void IncreaseOpacity(float step);
    void DecraseOpacity(float step);
    void ChangeOpacity(float opacity);
};