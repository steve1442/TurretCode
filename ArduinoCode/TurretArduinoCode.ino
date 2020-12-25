/* Turret Arduino Code
  
*/

#include <Servo.h>

Servo servoX;
Servo servoY;
// creates 2 servo objects to control x and y of turret

void setup() {
  Serial.begin(9600);
  servoX.attach(9);  // attaches the X servo on pin 9 to the servo object
  servoY.attach(8);  // attaches the Y servo on pin 8 to the servo object
  pinMode (7, OUTPUT);
  digitalWrite(7, LOW);
  Serial.println("test");
}

String test = "";
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1; 

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
// "XVAL : YVAL"
int parseX(String serialString){ // parses a string and returns the x cord info for the turret
 return getValue(serialString, ':', 0).toInt();
}

int parseY(String serialString){ // parses a string and returns the y cord info for the turret
  return getValue(serialString, ':', 1).toInt();
}

int parseGun(String serialString){ // parses a string and returns the y cord info for the turret
  return getValue(serialString, ':', 2).toInt();
}

void aim(int x,int y){ // Aims the turret based on x and y cordinate 
  servoX.write(x);
  servoY.write(y);
}
void shoot(int interval){
  if(interval > 0 ){
    digitalWrite(7, HIGH);
    delay(interval);
    digitalWrite(7,LOW);
  }
  else{
    
  }
}
int i = 0;
void serialEvent() {
  String data = Serial.readString();
  aim(parseX(data),parseY(data)); 
  Serial.println(parseY(data));
  shoot(parseGun(data));
  //Serial.println(data);
 // Serial.println("itworked");
}

void loop(){
  //Serial.println("fuck");
  delay(15);
}
