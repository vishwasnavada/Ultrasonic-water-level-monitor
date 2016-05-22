#include <LiquidCrystal.h> //Load Liquid Crystal Library
LiquidCrystal LCD(12, 11, 5, 4, 3, 2);  //Create Liquid Crystal Object called LCD

#define trigPin 10 //Sensor Trip pin connected to Arduino pin 10
#define echoPin 9  //Sensor Echo pin connected to Arduino pin 9
#define trigPin1 8 //Sensor Trip pin connected to Arduino pin 8
#define echoPin1 7  //Sensor Echo pin connected to Arduino pin 7
#define pump 13  //pump value
#define reset 6//Reset the monthly usage
float pingTime;
float pingTime1;//time for ping to travel from sensor to target and return
float h=0;
float h1=0;//Distance to Target in cms
int v=0;// volume of the water
long int T=0;// Total volume of water used per month
int i=0;
int l=0,m=0;
float speedOfSound=776.5; //Speed of sound in miles per hour when temp is 77 degrees.

void setup() {

  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pump, OUTPUT);
  pinMode(reset, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);


  LCD.begin(16,2); //Tell Arduino to start your 16 column 2 row LCD
  LCD.setCursor(0,0);  //Set LCD cursor to upper left corner, column 0, row 0
  LCD.print("Vol=");
  LCD.setCursor(0,1);
  LCD.print("Totl="); //Print Message on First Row
  LCD.setCursor(13,0);
  LCD.print("ON");

}

void loop()
{

  digitalWrite(trigPin1, LOW); //Set trigger pin low
  delayMicroseconds(2000); //Let signal settle
  digitalWrite(trigPin1, HIGH); //Set trigPin high
  delayMicroseconds(15); //Delay in high state
  digitalWrite(trigPin1, LOW); //ping has now been sent
  delayMicroseconds(10); //Delay in high state


  pingTime1=pulseIn(echoPin1, HIGH);  //pingTime is presented in microceconds
  pingTime1=pingTime1/1000000; //convert pingTime to seconds by dividing by 1000000 (microseconds in a second)
  pingTime1=pingTime1/3600; //convert pingtime to hours by dividing by 3600 (seconds in an hour)
  h1=speedOfSound * pingTime1;  //This will be in miles, since speed of sound was miles per hour
  h1=h1/2; //Remember ping travels to target and back from target, so you must divide by 2 for actual target distance.
  h1=h1*160934.4;    //Convert miles to cms by multipling by 160934.4 (cms per mile)
  Serial.println(h1);
  Serial.println("height1= \n");


  digitalWrite(trigPin, LOW); //Set trigger pin low
  delayMicroseconds(2000); //Let signal settle
  digitalWrite(trigPin, HIGH); //Set trigPin high
  delayMicroseconds(15); //Delay in high state
  digitalWrite(trigPin, LOW); //ping has now been sent
  delayMicroseconds(10); //Delay in high state

  pingTime =pulseIn(echoPin, HIGH);  //pingTime is presented in microceconds
  pingTime=pingTime/1000000; //convert pingTime to seconds by dividing by 1000000 (microseconds in a second)
  pingTime=pingTime/3600; //convert pingtime to hourse by dividing by 3600 (seconds in an hour)
  h=speedOfSound * pingTime;  //This will be in miles, since speed of sound was miles per hour
  h=h/2; //Remember ping travels to target and back from target, so you must divide by 2 for actual target distance.
  h=h*160934.4;    //Convert miles to cms by multipling by 160934.4 (cms per mile)

  Serial.println(h);
  Serial.println("height=\n");

  v=22/7*51*51*(128.25-h)/1000;



  LCD.setCursor(4,0);  //Set cursor to first column of second row


  LCD.print(v); //Print measured volume
  LCD.print("Ltr");  //Print your units.
  delay(250); //pause to let things settle

  LCD.setCursor(5,1);  //Set cursor to first column of second row


  LCD.print(T); //Print measured total volume
  LCD.print("Ltr");  //Print your units.
  delay(250); //pause to let things settle
  if(h1<10)
  {
    if(100<h)
    {
      l=1;
      digitalWrite(pump, HIGH);
      LCD.setCursor(14,0);
      LCD.print("ON");  //Set cursor to first column of second row
      delay(250);
    }

  }
  if(h<10)
  {
    m=1;
    digitalWrite(pump, LOW);
    LCD.setCursor(13,0);
    LCD.print("OFF");  //Set cursor to first column of second row
    delay(250);
  }
  if(l && m)
  {
    T=T+991;
    l=0;
    m=0;
  }
  if(reset==HIGH)
  {
    T=00;
  }
}





