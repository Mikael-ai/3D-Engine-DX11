#include "Window.h"

Window *window = NULL;

LRESULT CALLBACK windowProcedure(HWND hwnd, 
								 UINT message,
								 WPARAM wparam,
								 LPARAM lparam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		window->onCreate();
		break;
	}
	case WM_DESTROY:
	{
		window->onDestroy();
		PostQuitMessage(0);
		break;
	}

	default:
	{
		return DefWindowProc(hwnd,
							 message,
							 wparam,
							 lparam);
	}

	}
	return NULL;
}

Window::Window()
{
}

Window::~Window()
{
	release();
}

bool Window::init()
{
	constexpr const wchar_t* const windowClassName= L"WindowClass";
	constexpr const wchar_t* const engineWindowName = L"Engine";

	m_isRun = true;
	if (!window)
		window = this;

	// Setup window class
	WNDCLASSEX windowClass;
	windowClass.lpszClassName = windowClassName;
	windowClass.lpszMenuName = L"";

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.cbClsExtra = NULL;
	windowClass.cbWndExtra = NULL;

	windowClass.hInstance = NULL;
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hIcon   = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	windowClass.style = NULL;

	windowClass.lpfnWndProc = &windowProcedure;

	// Register created window class
	if (!RegisterClassEx(&windowClass))
		return false;

	m_engineWindow = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, // dwStyle ?
									windowClassName, // lpClassName
									engineWindowName, // lpWindowName
									WS_EX_OVERLAPPEDWINDOW, // dwStyle
									CW_USEDEFAULT, CW_USEDEFAULT, // x, y
									m_engineWindowWidth, m_engineWindowHeight, // nWidth, nHeight
									NULL, // hWndParent
									NULL, // hMenu
									NULL, // hInstance
									NULL); // lpParam
	if (!m_engineWindow)
		return false;

	ShowWindow(m_engineWindow, SW_SHOW);
	UpdateWindow(m_engineWindow);

	return true;
}

bool Window::broadcast()
{
	MSG message;

	while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	window->onUpdate();

	Sleep(0);

	return true;
}

bool Window::isRun()
{
	return m_isRun;
}

bool Window::release()
{
	return (!DestroyWindow(m_engineWindow)) ? false : true;
}

void Window::onDestroy()
{
	m_isRun = false;
}
