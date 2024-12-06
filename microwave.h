#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <thread>

enum MicrowaveState {
    MICROWAVE_ON,
    MICROWAVE_OFF,
    MICROWAVE_BROKEN,
    MICROWAVE_SERVICE,
    MICROWAVE_DOOR_OPENING,
    MICROWAVE_DOOR_CLOSING 
};

class Microwave {
public:
    MicrowaveState State;
    bool Keys[1024];
    unsigned int Width, Height;

    Microwave(unsigned int width, unsigned int height);
    ~Microwave();

    void Init();
    void ProcessInput(float dt);
    void ProcessMouseButtonPressed(double xpos, double ypos);
    void Update(float dt);
    void Render();
    void Restart();
    void TurnOffMicrowave();
    void TurnOnMicrowave();

private:
    unsigned int currentMinutes, currentSeconds;
    std::thread timerThread;
    bool timerRunning;
    void startTimer();
    void runTimer();
    void stopTimer();
};
