#pragma once
#include <windows.h>
#include <list>
#include <iostream>
namespace Input
{

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
			34

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
	};

}