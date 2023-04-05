#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>

class Window
{
private:
	unsigned int m_engineWindowWidth = 1152;
	unsigned int m_engineWindowHeight = 768;

	bool m_isRun;

protected:
	HWND m_engineWindow;

public:
	Window();
	~Window();
	// Init the window
	// return - operation result
	bool init();
	bool broadcast();
	bool isRun();
	// Release the window
	// return - operation result
	bool release();

public:
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy();
};

#endif