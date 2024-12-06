#include <iostream>
#include <sstream>
#include <iomanip>

#include "microwave.h"
#include "renderer.h"
#include "resource_manager.h"
#include "ellipse_renderer.h"
#include "text_renderer.h"
#include "microwave_object.h"
#include "particle_generator.h"

using namespace std;


Renderer *renderer;
ParticleGenerator* particles;
EllipseRenderer* elipseRenderer;
TextRenderer* textRenderer;
MicrowaveObject* microwaveWindow;
MicrowaveObject* sceneCover;
std::string clockText;

float blinkTime;
float blinkInterval;

float blinkTimeLight;
float blinkIntervalLight;

//number keyboard
float startXKeyboard = 900.0f;
float startYKeyboard = 300.0f;
float keyWidth = 60.0f;
float keyHeight = 60.0f;
float spacing = 10.0f;

int clickCount = 0;
int minute1 = 0;
int minute2 = 0;
int second1 = 0;
int second2 = 0;

glm::vec3 lightOnColor = glm::vec3(1.0f, 0.8f, 0.0f);
glm::vec3 lightOffColor = glm::vec3(0.6f, 0.6f, 0.6f);
glm::vec3 lightColorCurrent = lightOffColor;

float window_opacity = 0.3;

Microwave::Microwave(unsigned int width, unsigned int height) : State(MICROWAVE_OFF), Keys(), Width(width), Height(height), currentMinutes(0), currentSeconds(0), timerRunning(false) {}

Microwave::~Microwave()
{
	delete renderer;
	delete particles;
	delete elipseRenderer;
	delete textRenderer;
	delete microwaveWindow;
	delete sceneCover;
}

void Microwave::Init()
{
	ResourceManager::LoadShader("basic.vert", "basic.frag", NULL, "basic");
	ResourceManager::LoadShader("ellipse.vert", "ellipse.frag", NULL, "ellipse");
	ResourceManager::LoadShader("particles.vert", "particles.frag", nullptr, "particle");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	
	ResourceManager::GetShader("basic").Use().SetInteger("basic", 0);
	ResourceManager::GetShader("basic").SetMatrix4("projection", projection);

	/*ResourceManager::GetShader("ellipse").Use().SetInteger("ellipse", 0);
	ResourceManager::GetShader("ellipse").SetMatrix4("projection", projection);*/

	ResourceManager::GetShader("particle").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("particle").SetMatrix4("projection", projection);

	ResourceManager::LoadTexture("assets/textures/stainlessSteelDark.jpg", true, "stainlessSteelDark");
	ResourceManager::LoadTexture("assets/textures/stainlessSteelLightGray.jpg", true, "stainlessSteelLight");
	ResourceManager::LoadTexture("assets/textures/glass.jpg", true, "glass");
	ResourceManager::LoadTexture("assets/textures/food.png", true, "food");
	ResourceManager::LoadTexture("assets/textures/particle.jpg", true, "particle");

	renderer = new Renderer(ResourceManager::GetShader("basic"));
	elipseRenderer = new EllipseRenderer(ResourceManager::GetShader("ellipse"), 30, 0.0f, 0.0f);
	textRenderer = new TextRenderer(this->Width, this->Height);
	textRenderer->Load("assets/fonts/OpenSans.ttf", 24);
	particles = new ParticleGenerator(ResourceManager::GetShader("particle"), ResourceManager::GetTexture("particle"), 500);

	microwaveWindow = new MicrowaveObject(ResourceManager::GetTexture("glass"), glm::vec2(300.0f, 300.0f), glm::vec2(500.0f, 270.0f), glm::vec4(1.0f, 1.0f, 1.0f, window_opacity), glm::vec2(50.0f, 50.0f));
	sceneCover = new MicrowaveObject(ResourceManager::GetTexture("glass"), glm::vec2(0, 0), glm::vec2(this->Width, this->Height), glm::vec4(0.1f, 0.1f, 0.1f, 0.1f), glm::vec2(100.0f, -350.0f));
	clockText = "00:00";

	blinkTime = 0.0f;
	blinkInterval = 0.5f;

	blinkIntervalLight = 0.0f;
	blinkIntervalLight = 1.0f;
}

void Microwave::Render()
{
	renderer->Draw(ResourceManager::GetTexture("stainlessSteelDark"), glm::vec2(150.0f, 100.0f), glm::vec2(1000, 600), 0.0f);

	float startXClock = 900.0f;
	float startYClock = 150.0f;
	renderer->Draw(Texture2D(), glm::vec2(startXClock, startYClock), glm::vec2(200.0f, 60.0f), 0.0, glm::vec4(1.0f, 1.0f, 1.0f, 0.3f)); //time display
	textRenderer->RenderText(clockText, startXClock +10, startYClock +25, 1.0f);

	float startX = startXKeyboard;
	float startY = startYKeyboard;
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			float x = startX + col * (keyWidth + spacing);
			float y = startY + row * (keyHeight + spacing);

			int number = row * 3 + col + 1;
			std::string text = std::to_string(number);
			renderer->Draw(Texture2D(), glm::vec2(x, y), glm::vec2(keyWidth, keyHeight), 0.0, glm::vec4(1.0f, 1.0f, 1.0f, 0.3f));
			textRenderer->RenderText(text, x+keyWidth/2-12, y+keyHeight/2-12, 1.0f);

		}
	}

	startY += 3 * (keyHeight + spacing);
	renderer->Draw(Texture2D(), glm::vec2(startX, startY), glm::vec2(keyWidth, keyHeight), 0.0, glm::vec4(1.0f, 1.0f, 1.0f, 0.3f)); //zero
	textRenderer->RenderText("0", startX + keyWidth / 2 - 12, startY + keyHeight / 2 - 12, 1.0f);
	renderer->Draw(Texture2D(), glm::vec2(startX+spacing+keyWidth, startY), glm::vec2(keyWidth*2+spacing, keyHeight), 0.0, glm::vec4(1.0f, 1.0f, 1.0f, 0.3f)); //start
	textRenderer->RenderText("START", startX + spacing + keyWidth+spacing, startY + keyHeight / 2 - 12, 1.0f);

	startY += keyHeight + spacing;
	renderer->Draw(Texture2D(), glm::vec2(startX, startY), glm::vec2(keyWidth, keyHeight), 0.0, glm::vec4(1.0f, 1.0f, 1.0f, 0.3f)); //reset
	textRenderer->RenderText("R", startX + spacing, startY + keyHeight / 2 - 12, 1.0f);
	renderer->Draw(Texture2D(), glm::vec2(startX+spacing+keyWidth, startY), glm::vec2(keyWidth*2, keyHeight), 0.0, glm::vec4(1.0f, 1.0f, 1.0f, 0.3f)); //stop
	textRenderer->RenderText("STOP", startX+spacing + spacing + keyWidth, startY + keyHeight / 2 - 12, 1.0f);

	float lightX = this->Width - 200;
	float lightY = startY+3*spacing+keyHeight;
	elipseRenderer->Draw(Texture2D(), glm::vec2((2 * lightX)/this->Width - 1, 1 - (2 * lightY) / this->Height), 0.02f, 0.02, lightColorCurrent); //lampica

	startX = 300;
	startY = 300;
	float windowWidth = 500;
	float windowHeight = keyHeight * 4 + spacing * 3;

	startX = startX + windowWidth / 2;
	startY = startY + windowHeight / 2 + 60;
	elipseRenderer->Draw(Texture2D(), glm::vec2((2 * startX) / this->Width - 1, 1 - (2 * startY) / this->Height), 0.35f, 0.1, glm::vec3(1.0f, 1.0f, 1.0f)); //plate
	renderer->Draw(ResourceManager::GetTexture("food"), glm::vec2(420, 380), glm::vec2(windowWidth / 2, windowHeight / 2), 0.0, glm::vec4(1.0f, 1.0f, 1.0f, 1.0));

	microwaveWindow->Draw(*renderer);
	sceneCover->Draw(*renderer);

	std::string name = "Tijana Mazinjanin SV41/2021";
	textRenderer->RenderText(name, this->Width - 350, this->Height - 30, 1.0f);

	if (this->State == MICROWAVE_BROKEN) {
		particles->Draw();
	}
	
}


void Microwave::startTimer()
{
	this->stopTimer();
	this->timerRunning = true;
	timerThread = std::thread(&Microwave::runTimer, this);
}

void Microwave::runTimer()
{
	while (this->timerRunning) {
		if (currentMinutes == 0 && currentSeconds == 0) {
			this->timerRunning = false;
			lightColorCurrent = lightOnColor;
			break;
		}

		if (currentSeconds == 0) {
			currentSeconds = 59;
			if (currentMinutes > 0) {
				currentMinutes--;
			}
		}
		else {
			currentSeconds--;
		}

		std::ostringstream clockStream;
		clockStream << std::setw(2) << std::setfill('0') << this->currentMinutes
			<< ":"
			<< std::setw(2) << std::setfill('0') << this->currentSeconds;

		clockText = clockStream.str();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void Microwave::stopTimer()
{
	// Stop the timer thread if running
	if (timerRunning) {
		timerRunning = false;
		if (timerThread.joinable()) {
			timerThread.join();
		}
	}
}

void Microwave::ProcessInput(float dt)
{
	if (this->Keys[GLFW_KEY_O])
	{
		this->State = MICROWAVE_DOOR_OPENING;
		this -> stopTimer();
	}

	if (this->Keys[GLFW_KEY_Z])
	{
		this->State = MICROWAVE_DOOR_CLOSING;
	}

	if (this->Keys[GLFW_KEY_X])
	{
		this->State = MICROWAVE_BROKEN;
	}
	if (this->Keys[GLFW_KEY_S])
	{
		this->Restart();
	}
	if (this->Keys[GLFW_KEY_D])
	{
		microwaveWindow->ChangeOpacity(1.0f);
	}
	if (this->Keys[GLFW_KEY_L])
	{
		microwaveWindow->ChangeOpacity(0.3f);
	}
}

void Microwave::Update(float dt)
{

	if (this->State == MICROWAVE_ON && clockText=="00:00") {
		blinkTimeLight += 0.01;
		if (blinkTimeLight >= blinkIntervalLight) {
			blinkTimeLight = 0.0f;
		}
		if (blinkTimeLight >= blinkIntervalLight/2) {
			lightColorCurrent = lightOnColor;
		}
		else {
			lightColorCurrent = lightOffColor;
		}
	}
		
	if (this->State == MICROWAVE_DOOR_OPENING) {
		microwaveWindow->Move(-dt, 100, 300);
		lightColorCurrent = lightOffColor;
	}

	if (this->State == MICROWAVE_DOOR_CLOSING) {
		microwaveWindow->Move(dt, 100, 300);
	}

	if (this->State == MICROWAVE_BROKEN) {
		//particles->Update(dt, glm::vec2(this->Width, this->Height), 2, glm::vec2(-10.0f));
		blinkTime += 0.09;
		if (blinkTime >= blinkInterval) {
			blinkTime = 0.0f;
			clockText = "";
		}
		else {
			clockText = "ERROR";
		}

		sceneCover->DecraseOpacity(0.005f);
		
	}
	if (this->State == MICROWAVE_SERVICE) {
		sceneCover->IncreaseOpacity(0.005f);
	}
}

void Microwave::Restart()
{
	this->TurnOffMicrowave();
	this->State = MICROWAVE_SERVICE;
}

void Microwave::TurnOffMicrowave()
{
	this->currentMinutes = 0;
	this->currentSeconds = 0;
	this->State = MICROWAVE_OFF;
	lightColorCurrent = lightOffColor;
	clockText = "00:00";
	minute1 = 0; minute2 = 0; second1 = 0; second2 = 0;
	stopTimer();
}

void Microwave::TurnOnMicrowave()
{
	if (this->State == MICROWAVE_SERVICE || this->State == MICROWAVE_OFF || this->State == MICROWAVE_DOOR_CLOSING) {
		if (this->currentMinutes == 0 && this->currentSeconds == 0)
			return;

		this->State = MICROWAVE_ON;
		this->startTimer();
	}
	
}

bool IsPointInsideRect(float px, float py, float x, float y, float width, float height) {
	return px >= x && px <= x + width && py >= y && py <= y + height;
}

void UpdateClock(int number) {
	clickCount += 1;

	if (clickCount == 1) minute1 = number;
	
	else if (clickCount == 2) minute2 = number;
	
	else if (clickCount == 3) second1 = number;
	
	else if (clickCount == 4) { second2 = number; clickCount = 0; }
	

	clockText = std::to_string(minute1) + std::to_string(minute2) + ":" +
		std::to_string(second1) + std::to_string(second2);
}

void Microwave::ProcessMouseButtonPressed(double xpos, double ypos)
{
	
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			float x = startXKeyboard + col * (keyWidth + spacing);
			float y = startYKeyboard + row * (keyHeight + spacing);

			if (IsPointInsideRect(xpos, ypos, x, y, keyWidth, keyHeight)) {
				int number = row * 3 + col + 1;
				std::cout << "Rectangle " << number << " clicked!" << std::endl;
				UpdateClock(number);
			}

		}
	}

	float startZeroX = startXKeyboard;
	float startZeroY = startYKeyboard + 3 * (keyHeight + spacing);

	if (IsPointInsideRect(xpos, ypos, startZeroX, startZeroY, keyWidth, keyHeight)) {
		std::cout << "Rectangle " << 0 << " clicked!" << std::endl;
		UpdateClock(0);
	}

	this->currentMinutes = minute1 * 10 + minute2;
	this->currentSeconds = second1 * 10 + second2;

	float startStartX = startXKeyboard + keyWidth + spacing;
	float startStartY = startZeroY;

	if (IsPointInsideRect(xpos, ypos, startStartX, startStartY, keyWidth*2, keyHeight)) {
		std::cout << "Rectangle START clicked!" << std::endl;
		this->TurnOnMicrowave();
	}


	if (IsPointInsideRect(xpos, ypos, startXKeyboard, startStartY + keyHeight + spacing, keyWidth, keyHeight)) {
		std::cout << "Rectangle RESET clicked!" << std::endl;
		this->State = MICROWAVE_OFF;
		this->TurnOffMicrowave();
		/*clockText = "00:00";
		this->currentMinutes = 0;
		this->currentSeconds = 0;
		clickCount = 0;
		minute1 = 0; minute2 = 0; second1 = 0; second2 = 0;
		this->stopTimer();*/
	}

	if (IsPointInsideRect(xpos, ypos, startXKeyboard+spacing+keyWidth, startStartY + keyHeight + spacing, keyWidth * 2, keyHeight)) {
		std::cout << "Rectangle STOP clicked!" << std::endl;
		this->State = MICROWAVE_OFF;
		minute1 = 0; minute2 = 0; second1 = 0; second2 = 0;
		clickCount = 0;
		this->stopTimer();
	}
}


