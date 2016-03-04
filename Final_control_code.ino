/*  PSX Controller Decoder Library (Psx.pde)
	Written by: Kevin Ahrendt June 22nd, 2008
	
	Controller protocol implemented using Andrew J McCubbin's analysis.
	http://www.gamesx.com/controldata/psxcont/psxcont.htm
	
	Shift command is based on tutorial examples for ShiftIn and ShiftOut
	functions both written by Carlyn Maw and Tom Igoe
	http://www.arduino.cc/en/Tutorial/ShiftIn
	http://www.arduino.cc/en/Tutorial/ShiftOut

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
    /*
psxLeft 0x0001 
psxDown 0x0002 
psxRight  0x0004 
psxUp 0x0008 
psxStrt 0x0010 
psxSlct 0x0080 
psxSqu  0x0100 
psxX  0x0200 
psxO  0x0400 
psxTri  0x0800 
psxR1 0x1000 
psxL1 0x2000 
psxR2 0x4000 
psxL2 0x8000 
    */

#include <Psx.h>                                          // Includes the Psx Library 
                                                          // Any pins can be used since it is done in software
#define dataPin 8
#define cmndPin 9
#define attPin 11
#define clockPin 10
// motor pins in arduino for moveing  
int m_right1 = 2 ; 
int m_right2 = 3 ; 
int m_left1 = 4 ; 
int m_left2 = 5 ; 
// motor pins for grapping and lifting 
int m_grap1 = 6 ; 
int m_grap2 = 7 ; 
int m_lift1 = 12 ; 
int m_lift2 = 13 ;


unsigned int data = 0;                                     // data stores the controller response
Psx Psx;                                                  // Initializes the library

                                   

void setup()
{
  Psx.setupPins(dataPin, cmndPin, attPin, clockPin, 10);  // Defines what each pin is used
                                                          // (Data Pin #, Cmnd Pin #, Att Pin #, Clk Pin #, Delay)
                                                          // Delay measures how long the clock remains at each state,
                                                          // measured in microseconds.
                                                          // too small delay may not work (under 5)
  // directions 
  pinMode(m_right1, OUTPUT); 
  pinMode(m_right2, OUTPUT);
  pinMode(m_left1, OUTPUT);
  pinMode(m_left2, OUTPUT);


  // grapping and lifting 
  pinMode(m_grap1, OUTPUT);
  pinMode(m_grap2, OUTPUT);                               
  pinMode(m_lift1, OUTPUT);
  pinMode(m_lift2, OUTPUT);
 

  Serial.begin(9600);
}

void loop()
{

  data = Psx.read();  

  if(data & psxUp ){
  pinMode(m_right1, HIGH); 
  pinMode(m_right2, LOW);
  pinMode(m_left1, HIGH);
  pinMode(m_left2, LOW);                                 
  Serial.println("Forward"); 
delay(750);
  
  }


  else if(data & psxDown ){
  pinMode(m_right1, LOW); 
  pinMode(m_right2, HIGH);
  pinMode(m_left1, LOW);
  pinMode(m_left2, HIGH);
  Serial.println("Backward");
  delay(500);


  }

  else if(data & psxRight ){
  pinMode(m_right1, HIGH); 
  pinMode(m_right2, LOW);
  pinMode(m_left1, LOW);
  pinMode(m_left2, HIGH);
  Serial.println("RIGHT");
  delay(500);


  }


  else if(data & psxLeft ){
  pinMode(m_right1, HIGH); 
  pinMode(m_right2, LOW);
  pinMode(m_left1, LOW);
  pinMode(m_left2, HIGH);
  Serial.println("Left");
  delay(750);

  }




//**************************** Grapping **************************

 else if(data & psxTri ){
  pinMode(m_right1, HIGH); 
  pinMode(m_right2, LOW);
  pinMode(m_left1, HIGH);
  pinMode(m_left2, LOW);                                 
  Serial.println("UP"); 
delay(500);
  
  }


  else if(data & psxX ){
  pinMode(m_right1, LOW); 
  pinMode(m_right2, HIGH);
  pinMode(m_left1, LOW);
  pinMode(m_left2, HIGH);
  Serial.println("Down");
  delay(500);


  }

  else if(data & psxO ){
  pinMode(m_right1, HIGH); 
  pinMode(m_right2, LOW);
  pinMode(m_left1, LOW);
  pinMode(m_left2, HIGH);
  Serial.println("RIGHT");
  delay(500);


  }


  else if(data & psxSqu ){
  pinMode(m_right1, HIGH); 
  pinMode(m_right2, LOW);
  pinMode(m_left1, LOW);
  pinMode(m_left2, HIGH);
  Serial.println("Left");
  delay(500);

  }
else {
 pinMode(m_right1, LOW); 
  pinMode(m_right2, LOW);
  pinMode(m_left1, LOW);
  pinMode(m_left2, LOW);
    Serial.println("brake");
delay(500);
}
}


