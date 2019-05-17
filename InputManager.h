#pragma once
#include <windows.h>
#include <list>
#include <iostream>
#include "Camera.h"

namespace Input
{
	//TODOS
	//The Static keyword in a namespace has a completely different meaning than the one in a class
	//It means that all files that include this one have their own instances of the static variables/functions
	//This stops the linker from complaining, but it means that you have to do all of your accessing in one file
	//the static variables here are NOT global. Look into the extern keyword.

	enum class KEY
	{
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		ENTER,
		SPACE,
		DOWN,
		UP,
		LEFT,
		RIGHT,
		BACKSPACE,
		MOUSEWHEEL,
		MOUSELEFT,
		MOUSERIGHT,
		NUM_ITEMS
	};

	//Gross, but I dont know how to reach namespace variables by index
	static unsigned int keyValues[] = {
			0x41,
			0x42,
			0x43,
			0x44,
			0x45,
			0x46,
			0x47,
			0x48,
			0x49,
			0x4A,
			0x4B,
			0x4C,
			0x4D,
			0x4E,
			0x4F,
			0x50,
			0x51,
			0x52,
			0x53,
			0x54,
			0x55,
			0x56,
			0x57,
			0x58,
			0x59,
			0x5A,
			VK_RETURN,
			VK_SPACE,
			VK_DOWN,
			VK_UP,
			VK_LEFT,
			VK_RIGHT,
			VK_BACK,
			VK_MBUTTON,
			VK_LBUTTON,
			VK_RBUTTON,
			37

	};

	static bool* KeyPress=(bool*)calloc(sizeof(keyValues)/sizeof(unsigned int),sizeof(bool));
	static bool* KeyHold=(bool*) calloc(sizeof(keyValues) / sizeof(unsigned int),sizeof(bool));
	static bool* KeyRelease=(bool*)calloc(sizeof(keyValues) / sizeof(unsigned int),sizeof(bool));

	static bool KeyPressed(KEY keyCode)
	{
		int keyIndex = static_cast<int>(keyCode);
		return KeyPress[keyIndex];
	};
	static bool KeyHeld(KEY keyCode)
	{
		int keyIndex = static_cast<int>(keyCode);
		return KeyHold[keyIndex];
	};
	static bool KeyReleased(KEY keyCode)
	{
		int keyIndex = static_cast<int>(keyCode);
		return KeyRelease[keyIndex];
	};


	//Mouse variables
	//ScreenMouse variables show where the mouse is on the screen (in pixels)
	static int ScreenMouseX=-1;
	static int ScreenMouseY=-1;
	static int WorldMouseX = -1;
	static int WorldMouseY = -1;

	//Needs to be called on and implemented by the game engine
	static void UpdateMousePosition(int x,int y, Camera* camera)
	{
		ScreenMouseX = x;
		ScreenMouseY = y;
		WorldMouseX = x+camera->GetPosition().x;
		WorldMouseY = y+camera->GetPosition().y;
	}

	static void UpdateKeys()
	{

		for (int i =0; i< sizeof(keyValues) / sizeof(int);i++)
		{
			bool keyInput = GetAsyncKeyState(keyValues[i]);

			//Reset all key releases
			KeyRelease[i] =false;


			if (keyInput)
			{
				//If the key was pressed the last frame, it's currently being held
				if (KeyPress[i])
				{
					KeyHold[i] = true;
					KeyPress[i] = false;
				}
				//If the key wasn't pressed the last frame
				if (!KeyPress[i] && !KeyHold[i])
				{
				
					KeyPress[i] = true;
				}
			}
			

			if (!keyInput)
			{

				//If the key was held or pressed the last frame, and it hasnt been released yet, it should be released
				if ((KeyHold[i] || KeyPress[i]) && !KeyRelease[i])
				{
					KeyHold[i] = false;
					KeyPress[i] = false;
					KeyRelease[i] = true;
				}
			}

		}
	}

}