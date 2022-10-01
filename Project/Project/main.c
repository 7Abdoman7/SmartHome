#include "House.h"

int main(void)
{
	char pass[5] = "0000"; // The initial password
	while(1)
	{
		House_init();
		HouseShutDown();
		Check_Emer(pass); // Check the password
		OpeningMode("Abdo"); // Entering the name of the user
		ShowStatus();
		char active = 1;
		while(1)
		{
			active = ActiveMode();
			if(active == 0) // The user want to show the status of the devices
				break;
			if(active == 2) // The user is leaving
			{
				HouseShutDown();
				ClosingMode();
				Send('\n');
				break;
			}
		}
	}
}

