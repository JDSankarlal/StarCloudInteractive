#include "controller.h"
#include <Windows.h>
#include <iostream>

int main()
{
	Input::XBoxInput XBoxController;

	// Our game loop
	while (true)
	{
		// Do this at the BEGINNING of your game loop, and if you have more than one controller,
		// use the number of controllers as the first parameter (1 - 4)
		XBoxController.DownloadPackets(1);

		// If the first controller is connected
		if (XBoxController.GetConnected(0))
		{
			// Check if any of the 14 buttons were pressed
			for (int i = 0; i < 14; i++)
			{
				if (XBoxController.GetButton(0, (Input::Button)i))
				{
					std::cout << "Button #" << i << " was pressed!" << std::endl;
				}

				// You can also check using the enum
				XBoxController.GetButton(0, Input::Button::DPadRight);
			}
			
			// Get the two trigger values (from 0 to 1)
			float lTrig, rTrig;
			XBoxController.GetTriggers(0, lTrig, rTrig);

			if (lTrig > 0 || rTrig > 0)
				std::cout << "Left Trigger: " << lTrig << std::endl << "Right Trigger: " << rTrig << std::endl;

			// Get the two sticks. They are stored in a Stick struct, which has two floats, (from 0 to 1) for xAxis and yAxis
			Input::Stick lStick, rStick;
			XBoxController.GetSticks(0, lStick, rStick);

			if (lStick.xAxis > 0 || lStick.yAxis > 0)
				std::cout << "Left Stick : " << lStick.xAxis << " " << lStick.yAxis << std::endl;
			if (rStick.xAxis > 0 || rStick.yAxis > 0)
				std::cout << "Right Stick : " << rStick.xAxis << " " << rStick.yAxis << std::endl;
		}
	}
}