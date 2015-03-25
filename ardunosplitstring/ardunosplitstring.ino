/// the clever bits of this all come from:
// www.esologic.com/?p=1157

const char EOPmarker = '.'; //This is the end of packet marker
char serialbuf[32]; //This gives the incoming serial some room. Change it if you want a longer incoming.
 
//#include <SoftwareSerial.h>
#include <string.h> // we'll need this for subString
#define MAX_STRING_LEN 20 // like 3 lines above, change as needed.
 
//SoftwareSerial SoftSer(11, 10); // RX, TX
 
void setup(){
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}
 
void loop() {
  
    if (Serial.available() > 0) { //makes sure something is ready to be read
      static int bufpos = 0; //starts the buffer back at the first position in the incoming serial.read
      char inchar = Serial.read(); //assigns one byte (as serial.read()'s only input one byte at a time
      if (inchar != EOPmarker) { //if the incoming character is not the byte that is the incoming package ender
        serialbuf[bufpos] = inchar; //the buffer position in the array get assigned to the current read
        bufpos++; //once that has happend the buffer advances, doing this over and over again until the end of package marker is read.
      }
      else { //once the end of package marker has been read
        serialbuf[bufpos] = 0; //restart the buff
        bufpos = 0; //restart the position of the buff
        
 //////////////////////////////////////////////////////////////////////////////////////////////
 // this is where we grab the x y HSB values and do whatever we thing is nice :) //////////////
        
         int x = atoi(subStr(serialbuf, ":", 1));
         int y = atoi(subStr(serialbuf, ":", 2));
         int R = atoi(subStr(serialbuf, ":", 3));
         int G = atoi(subStr(serialbuf, ":", 4));
         int B = atoi(subStr(serialbuf, ":", 5));

         // send back to processing for debugging 
        
         Serial.write(B);
          // quick and dirty LED tester
          if(B >= 50){
            digitalWrite(13,HIGH);
          } else digitalWrite(13,LOW);
          
          
          
          
          
          
          
          
      // all our stuff goes above here /////////////////////////////////////////////////
      }
    }
}


// this is the function that allows us to easily grab an item from the string by index

char* subStr (char* input_string, char *separator, int segment_number) {
  char *act, *sub, *ptr;
  static char copy[MAX_STRING_LEN];
  int i;
  strcpy(copy, input_string);
  for (i = 1, act = copy; i <= segment_number; i++, act = NULL) {
    sub = strtok_r(act, separator, &ptr);
    if (sub == NULL) break;
  }
 return sub;
}
