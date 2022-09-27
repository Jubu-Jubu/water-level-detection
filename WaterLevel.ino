#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>



// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "Etv8_sSlZXE3PFkoHJ72nYo3Pzjc1BQ5";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Infinix Smart 3 Plus";
char pass[] = "Oyedotun12";


int TRIGGER = D3;
int ECHO   = D2;
int PUMP = D5;

int upperlimit = 0;
int lowerlimit = 99;
int data;
int control;
int emma;

BLYNK_WRITE(V0)
{
  control = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
}

BLYNK_WRITE(V1)
{
  upperlimit = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
}

BLYNK_WRITE(V2)
{
  lowerlimit = param.asInt(); // assigning incoming value from pin V2 to a variable

  // process received value
}

BLYNK_WRITE(V3)
{
  emma = param.asInt(); // assigning incoming value from pin V2 to a variable

  // process received value
}

void setup()
{
  // Debug console
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(PUMP, OUTPUT);
  delay(1000);

  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  Serial.println("Operation Started");
}

void loop()
{
  Blynk.run();
  ultrasonic();
  if(control == 1)
  {
    //Automatic Mode
    automate();
  }
  else if (control == 0)
  {
    //Manual mode
    digitalWrite(PUMP, emma);
    return;
  }
}


void ultrasonic()
{
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  long duration = pulseIn(ECHO, HIGH);
  data = (duration / 2) / 29.09;
  Serial.println(data);
  Blynk.virtualWrite(V8, data);
}

void automate()
{
  if(data <= upperlimit)
  {
    digitalWrite(PUMP, LOW);
  }
  if(data >= lowerlimit)
  {
    digitalWrite(PUMP, HIGH);
  }
}
