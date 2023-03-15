# screenshotWindowsWindow
differents way to capture a window in windows in C++


--------------------------------
CODE SNIPPET WINDOWS GET HDWND BY PID
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	auto windowData = reinterpret_cast<std::vector<std::pair<HWND, DWORD>> *>(lParam);
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	windowData->push_back(std::make_pair(hwnd, pid));
	return TRUE;
}

HWND GetWindowHandleFromProcessId(DWORD pid)
{
	std::vector<std::pair<HWND, DWORD>> windowData;
	EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&windowData));
	for (const auto &data : windowData)
	{
		if (data.second == pid)
		{
			return data.first;
		}
	}
	return nullptr;
}
--------------------------------
CODE SNIPPET WINDOWS GET ALL HDWND
#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    vector<HWND>* pHandles = reinterpret_cast<vector<HWND>*>(lParam);
    pHandles->push_back(hwnd);
    return TRUE;
}

int main()
{
    vector<HWND> handles;
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&handles));
    for (auto hwnd : handles)
    {
        char buffer[256];
        GetWindowTextA(hwnd, buffer, sizeof(buffer));
        string title(buffer);
        if (!title.empty())
        {
            cout << "Window handle: " << hwnd << " Title: " << title << endl;
        }
    }
    return 0;
}

This code uses a callback function EnumWindowsProc to add each window handle to a vector of HWNDs. After the enumeration is complete, it loops through the vector and retrieves the window title using the GetWindowTextA function.

Note that this code only lists top-level windows, which are windows that have no parent window. If you also want to list child windows, you can use the EnumChildWindows function instead.
======================================================
======================================================
