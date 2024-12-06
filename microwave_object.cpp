#include "microwave_object.h"

MicrowaveObject::MicrowaveObject() : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Texture(), IsSolid(false), Destroyed(false) {}

MicrowaveObject::MicrowaveObject(Texture2D texture, glm::vec2 pos, glm::vec2 size, glm::vec4 color, glm::vec2 velocity) : Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Texture(texture), IsSolid(false), Destroyed(false) {}

void MicrowaveObject::Draw(Renderer& renderer)
{
	renderer.Draw(this->Texture, this->Position, this->Size, this->Rotation, this->Color);
}

glm::vec2 MicrowaveObject::Move(float dt, unsigned int minHeight, unsigned int maxHeight)
{
	this->Position.y += this->Velocity.y*dt;
	if (this->Position.y <= minHeight) {
		this->Position.y = minHeight;
	}
	else if (this->Position.y >= maxHeight) {
		this->Position.y = maxHeight;
	}
	return this->Position;
}

void MicrowaveObject::DecraseOpacity(float step)
{
	this->Color.a += step;
	if (this->Color.a > 0.8f)
		this->Color.a = 1.0f;
}

void MicrowaveObject::IncreaseOpacity(float step)
{
	this->Color.a -= step;
	if (this->Color.a < 0.0f)
		this->Color.a = 0.0f;
}


