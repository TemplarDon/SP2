
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);

    // Variables for mouse controls
    static double mouseX;
    static double mouseY;
private:

	//Declare a window object
	StopWatch m_timer;

};

#endif