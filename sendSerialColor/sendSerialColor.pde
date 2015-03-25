import processing.serial.*;
// add java color library for HSB to RGB conversion
import java.awt.Color;

Serial myPort;  // Create object from Serial class
int inByte = -1;

void setup() 
{
  colorMode(HSB, 100,100,100);
  size(100, 100);
  String portName = Serial.list()[0];
  myPort = new Serial(this, Serial.list()[0], 9600);
}

void draw() {
//// do cool stuff here:

    int x = int(random(32));
    int y = int(random(16));
    int H = int(random(20,40));
    int S = int(random(100));
    int L = int(random(100));

///// convert color to RGB before sending to arduino  

    color c = Color.HSBtoRGB(H, S, L);
    int R = int(red(c));
    int G = int(green(c));
    int B = int(blue(c));
    //println(B);
    String toard = x + ":" + y + ":" + R + ":" + G + ":" + B + ".";
    
    // send the string to the arduino over serial port
    myPort.write(toard);   
    
    // add some delay
    //delay(40); 

//////////////////////////////////////////////////

    // listen back to the serial data from arduino
    // this is handy for debugging
    while (myPort.available () > 0) {
      inByte = myPort.read();
      println(int(inByte));


    //fill(H,S,B);
    //rect(0,0, width,height);

}
 
}


