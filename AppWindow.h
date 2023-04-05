#ifndef APPWINDOW_H
#define APPWINDOW_H

#include "Window.h"


class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

public:
	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;

};

#endif

