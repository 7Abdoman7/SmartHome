#include "House.h"

void Reset_init()
{
	ClearBit(Reset_DDR ,PD2);
	SetBit(Reset_PORT ,PD2);
}

void Shutdown_init()
{
	SetBit(Shutdown_DDR ,PD6);
	SetBit(Shutdown_PORT ,PD6);
}

void House_init()
{
	// Initialize all the components
	LCD_init();
	Keypad_init();
	Motor_init();
	Sensor_init();
	Servo_init(0);
	Leds_init();
	Dimmer_init();
	Bluetooth_init();
	Reset_init();
	Buzzer_init();
	Shutdown_init();	
}

void HouseShutDown()
{
	AC_TurnOff();
	Leds_TurnOffAll();
	Dimmmer_input(0);
	DoorClose();
	Buzzer_Off();
}

unsigned char SecMode(char* pass)
{
	HouseShutDown();
	char Pass[5]; // The initial password
	unsigned char alert = '3';
	while(alert != '0') // Check the number of trials trying entering the password
	{
		LCD_cmd(0x01);
		LCD_Sec();
		for(int i = 0 ; i < 4 ; i++) // Getting the password from the keypad
		{
			Pass[i] = Keypad_read();
			LCD_sendchar('*');
		}
		Pass[4] = '\0';
		if(strcmp(Pass ,pass) != 0) // Checking if the password entered is the initial password
		{
			alert--;
			if(alert != '0') // Telling the number of trials left before the alert going
			{
				LCD_cmd(0x90);
				LCD_sendchar(alert);
				LCD_sendstring(" attempts");
				LCD_cmd(0xD0);
				LCD_sendstring("remaining");
				_delay_ms(2000);
			}
		}
		else
		{
			LCD_cmd(0x01);
			break;
		}
	}
	return alert; // Return the number of trials
}

unsigned char EmerMode(unsigned char alert)
{
	if(alert == '0') // Check no trials left
	{
		LCD_cmd(0x01);
		LCD_sendstring("   >>ERROR<<");
		LCD_cmd(0xC0);
		LCD_sendstring("Reset");
		LCD_cmd(0x90);
		LCD_sendstring("Manually");
		return '1';
	}
	return '0';
}

void Check_Emer(char* pass)
{
	unsigned char alert;
	alert = EmerMode(SecMode(pass)); // Check if there an emergency
	if(alert == '1')
		Send_String("Warning!!\nReset the system manually");
	Send('\n');
	while(alert == '1') // If the reset button wasn't pushed the buzzer is still on 
	{
		Buzzer_On();
		if(GetBit(Reset_PIN ,PD2) == 0) // The reset button is pushed
		{
			Buzzer_Off();
			break;
		}
	}
}

void ShowStatus()
{
	char AC_state;
	char data = 'n';
	AC_state = AC_Auto(GetTemp()); // Gets the stste of the AC
	LCD_cmd(0x01);
	if(AC_state == 0)
	{
		LCD_sendstring("AC: OFF");
		Send_String("AC: OFF");
	}
	else
	{
		LCD_sendstring("AC: ON");
		Send_String("AC: ON");
	}
	Send('\n');
	LCD_cmd(0xC0);
	LCD_sendstring("Temp: ");
	LCD_sendint(GetTemp());
	Send_String("Temp: ");
	Send_int(GetTemp());
	Send('\n');
	LCD_cmd(0x90);
	if(GetBit(Dimmer_PORT ,PD7) == 0) // Check the state of the dimmer
	{
		LCD_sendstring("Dimmer: OFF");
		Send_String("Dimmer: OFF");
	}
	else
	{
		LCD_sendstring("Dimmer: ON");
		Send_String("Dimmer: ON");
	}
	Send('\n');
	LCD_cmd(0xD0);
	LCD_sendstring("* for Settings");
	Show_Leds();
	while(1)
	{
		if(Data_avail())
			data = Receive();
		if(Keypad_Get() == '*' || data == '*')
		{
			Send_String("Settings mode activated");
			Send('\n');
			break;
		}
	}
	LCD_cmd(0x01);
	LCD_sendstring("1- AC Toggle");
	LCD_cmd(0xC0);
	LCD_sendstring("2- Dimmer Toggle");
	LCD_cmd(0x90);
	LCD_sendstring("3- Door Open");
	LCD_cmd(0xD0);
	LCD_sendstring("4- Status");
}

char ActiveMode()
{
	char data = 'n';
	char keyClicked = Keypad_Get();
	if(Data_avail())
		data = Receive();
	if(keyClicked == '1' || data == 'a') // If one the AC tog.
	{
		AC_TGL();
		if(GetBit(Motor_PORT ,PD3) == 0)
			Send_String("AC has been turned off.");
		if(GetBit(Motor_PORT ,PD3) == 1)
			Send_String("AC has been turned on.");
		Send('\n');	
	}
	if(keyClicked == '2') // If 2 the dimmer tog.
	{
		data = Dimmer_TGL();
		if(data == 0)
			Send_String("Dimmer has been turned off.");
		else
			Send_String("Dimmer has been turned on.");
		Send('\n');	
	}
	if(data == 'd') 
	{
		int dataDimmer;
		Send('\n');
		Send_String("Dimmer power: ");
		Send_int(Dimmer_Power());
		Send('\n');
		Send_String("Enter the power: "); 
		do{
			dataDimmer = Receive_int(); // Getting the power that the user wants the dimmer 
		}while(dataDimmer < 0 || dataDimmer > 100);
		Send_int(dataDimmer);
		Dimmmer_input(dataDimmer);	
		Send('\n');
		Send_String("Dimmer power has changed to ");
		Send_int(Dimmer_Power());
		Send('\n');
	}
	if(keyClicked == '3' || data == 'D') // If 3 the door opens then closes
	{
		Send('\n');
		DoorOpen();
		Send_String("Door opens.");
		_delay_ms(2000);
		DoorClose();
		Send('\n');
		Send_String("Door closes");
		Send('\n');
	}
	// Checking the lamps setting sent by thr user
	if(data == 'l')
	{
		Send('\n');
		Leds_TGL(1);
		Send_String("Living room lamp: ");
		if(GetBit(LivingRoomLed_PORT ,PC2) == 1)
			Send_String("on");
		else
			Send_String("off");
		Send('\n');	
	}
	if(data == 'b')
	{
		Send('\n');
		Leds_TGL(2);
		Send_String("Bedroom lamp: ");
		if(GetBit(Leds_PORT ,PA4) == 1)
			Send_String("on");
		else
			Send_String("off");
		Send('\n');
	}
	if(data == 'k')
	{
		Send('\n');
		Leds_TGL(3);
		Send_String("Kitchen lamp: ");
		if(GetBit(Leds_PORT ,PA5) == 1)
			Send_String("on");
		else
			Send_String("off");
		Send('\n');
	}
	if(data == 'B')
	{
		Send('\n');
		Leds_TGL(4);
		Send_String("Bathroom lamp: ");
		if(GetBit(Leds_PORT ,PA6) == 1)
			Send_String("on");
		else
			Send_String("off");
		Send('\n');
	}
	if(data == 'K')
	{
		Send('\n');
		Leds_TGL(5);
		Send_String("Kidsroom lamp: ");
		if(GetBit(Leds_PORT ,PA7) == 1)
			Send_String("on");
		else
			Send_String("off");
		Send('\n');
	}
	if(data == 't')
	{
		Send('\n');
		Send_String("The temperature: ");
		Send_int(GetTemp());
		Send('\n');
	}
	if(keyClicked == '4' || data == 's') // if 4 show the status on the LCD and the phone
	{
		Send('\n');
		Send_String("The status: ");
		Send('\n');
		ShowStatus();
		return 0;
	}
	if(GetBit(Shutdown_PORT ,PD6) == 0 || data == 'S') // If the shutdown butten is pushed, shutdown everything and return to secmode
	{
		Send('\n');
		Send_String("Shutdown");
		_delay_ms(500);
		Send('.');
		_delay_ms(500);
		Send('.');
		_delay_ms(500);
		Send('.');
		Send('\n');
		return 2;
	}
	return 1;
}

void OpeningMode(char* name)
{
	LCD_cmd(0x01);
	LCD_sendstring("  Hello, ");
	LCD_sendstring(name); // Entering the user name
	Send_String("Hello, ");
	Send_String(name);
	Send('\n');
	DoorOpen();
	_delay_ms(2000);
	DoorClose();
}

void ClosingMode()
{
	LCD_cmd(0x01);
	LCD_sendstring("   Bye,");
	LCD_sendstring("Abdo");
	Send_String("Bye, ");
	Send_String("Abdo");
	_delay_ms(2000);
	LCD_cmd(0x01);
}