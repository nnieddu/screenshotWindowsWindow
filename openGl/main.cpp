#pragma once
#include <iostream>
#include <windows.h>
#include <GL/glcorearb.h>
#include <GL/glext.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <opencv2/opencv.hpp>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

void captureOpenGLWindow(HWND windowHandle, cv::Mat &capturedImage)
{
	// Get the device context for the window
	HDC deviceContext = GetDC(windowHandle);

	// Get the dimensions of the window
	RECT windowRect;
	GetClientRect(windowHandle, &windowRect);
	int windowWidth = windowRect.right - windowRect.left;
	int windowHeight = windowRect.bottom - windowRect.top;

	// Create a buffer to hold the pixel data
	int pixelBufferSize = windowWidth * windowHeight * 3;
	BYTE *pixelBuffer = new BYTE[pixelBufferSize];

	// Set the pixel storage mode
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Create a texture
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	// -------- Capture the OpenGL window -> FRONT BUFFER --------
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, windowWidth, windowHeight, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, pixelBuffer);

	// -------- Capture the OpenGL window -> BACK BUFFER  --------
	// glReadBuffer(GL_BACK);
	// glReadPixels(0, 0, windowWidth, windowHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixelBuffer);

	// Bind the texture and upload the pixel data to it
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowWidth, windowHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixelBuffer);

	// Create a matrix to hold the image data
	capturedImage.create(windowHeight, windowWidth, CV_8UC3);

	// Download the texture data and store it in the matrix
	glGetTexImage(GL_TEXTURE_2D, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, capturedImage.data);

	// Free the memory used by the pixel buffer and delete the texture
	delete[] pixelBuffer;
	glDeleteTextures(1, &textureId);

	// Release the device context
	ReleaseDC(windowHandle, deviceContext);
}

int main(int ac, char **av)
{
	HWND targetWindow;

	// Find the handle of the window to capture
	if (ac == 3)
	{
		std::cout << av[2] << std::endl;
		targetWindow = FindWindow(NULL, av[2]);
		// Put the window title raw here or use arg.
	}
	if (targetWindow == NULL)
	{
		std::cout << "No window title found, capturing main screen instead." << std::endl;
		targetWindow = GetDesktopWindow();
	}

	// Make the window's device context current
	HDC deviceContext = GetDC(targetWindow);
	wglMakeCurrent(deviceContext, wglCreateContext(deviceContext));

	// Capture the window
	cv::Mat capturedImage;
	captureOpenGLWindow(targetWindow, capturedImage);

	// Release the device context and destroy the OpenGL context
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(wglGetCurrentContext());
	ReleaseDC(targetWindow, deviceContext);

	// Display the captured image using openCV
	cv::namedWindow("Captured Image", cv::WINDOW_NORMAL);
	cv::imshow("Captured Image", capturedImage);
	cv::waitKey(0);

	return 0;
}
