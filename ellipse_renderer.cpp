#include "ellipse_renderer.h"


EllipseRenderer::EllipseRenderer(const Shader& shader, int cres, float positionX, float positionY)
{
    this->shader = shader;
    this->initEllipseData(cres, positionX, positionY);
}

EllipseRenderer::~EllipseRenderer()
{
    glDeleteVertexArrays(1, &this->ellipseVAO);
}

void EllipseRenderer::Draw(const Texture2D& texture, glm::vec2 position, float radiusX, float radiusY, glm::vec3 color)
{
    this->shader.Use();
    unsigned int uRxLoc = glGetUniformLocation(this->shader.ID, "uRx");
    unsigned int uRyLoc = glGetUniformLocation(this->shader.ID, "uRy");
    unsigned int uColLoc = glGetUniformLocation(this->shader.ID, "uCol");
    unsigned int uTranslateLoc = glGetUniformLocation(this->shader.ID, "uTranslate"); //ovo mora da se poklopi sa uTranslate u shader-u
    glUniform1f(uRxLoc, radiusX); //precnik po X osi
    glUniform1f(uRyLoc, radiusY); //precnik po Y osi
    glUniform3f(uColLoc, color.x, color.y, color.z);
    glUniform2f(uTranslateLoc, position.x, position.y); //pozicija centra kruga

    glBindVertexArray(this->ellipseVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, this->circleVertices.size());
    glBindVertexArray(0);
}

void EllipseRenderer::initEllipseData(int cres, float positionX, float positionY)
{
    
    circleVertices.reserve((cres + 2) * 2);

    // Center of the ellipse
    circleVertices.push_back(positionX);
    circleVertices.push_back(positionY);

    // Ellipse points
    for (unsigned int i = 0; i <= cres; ++i)
    {
        float angle = glm::radians(i * 360.0f / cres);
        circleVertices.push_back(cos(angle));
        circleVertices.push_back(sin(angle));
    }

    unsigned int VBO;
    glGenVertexArrays(1, &this->ellipseVAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(this->ellipseVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, circleVertices.size() * sizeof(float), circleVertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); //meni je ovde bila greska. Mora da bude *sizeof(float)

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &VBO);
}
