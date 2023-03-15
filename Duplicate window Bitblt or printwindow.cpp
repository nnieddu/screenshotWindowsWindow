#include <GLFW/glfw3.h>
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include <iostream>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

int main()
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	HWND targetWindow = FindWindow(NULL, "Douwi - Dofus Retro v1.39.8");
	// HWND targetWindow = FindWindow(NULL, "Dofus Retro");

	// Get the dimensions of the target window
	RECT targetRect;
	GetClientRect(targetWindow, &targetRect);
	std::cout << " RIGHT " << targetRect.right << " | BOTTOM " << targetRect.bottom << std::endl;

	GLFWwindow *window = glfwCreateWindow(targetRect.right, targetRect.bottom, "Screenshot", NULL, NULL);
	if (!window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	HWND glfwWindow = glfwGetWin32Window(window);

	glfwMakeContextCurrent(window);

	// while (!glfwWindowShouldClose(window))
	// {
	// 	// Get the device context (DC) of the target window
	// 	HDC hdcTarget = GetDC(targetWindow);
	// 	// Create a compatible DC for the GLFW window
	// 	HDC hdcGLFW = GetDC(glfwWindow);
	// 	// Copy the pixels from the target window to the GLFW window
	// 	BitBlt(hdcGLFW, 0, 0, targetRect.right, targetRect.bottom, hdcTarget, 0, 0, SRCCOPY);
	// 	// Release the DCs
	// 	ReleaseDC(targetWindow, hdcTarget);
	// 	ReleaseDC(glfwWindow, hdcGLFW);

	// 	// Swap buffers and poll events
	// 	glfwSwapBuffers(window);
	// 	glfwPollEvents();
	// }
	// --------------------------------------
	while (!glfwWindowShouldClose(window))
	{
		// Get the device context (DC) of the target window
		HDC hdcTarget = GetDC(targetWindow);
		// Create a compatible DC for the GLFW window
		HDC hdcGLFW = GetDC(glfwWindow);
		// Capture the pixels of the target window using PrintWindow
		PrintWindow(targetWindow, hdcTarget, PW_CLIENTONLY);
		// Copy the captured pixels to the GLFW window
		BitBlt(hdcGLFW, 0, 0, targetRect.right, targetRect.bottom, hdcTarget, 0, 0, SRCCOPY);
		// Release the DCs
		ReleaseDC(targetWindow, hdcTarget);
		ReleaseDC(glfwWindow, hdcGLFW);

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Release GLFW resources
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
