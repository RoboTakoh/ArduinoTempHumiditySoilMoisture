#include <Adafruit_Sensor.h>
#include <DHT.h>

int solenoidPin = 4;                                    //This is the output pin on the Arduino we are using
int drynessLevel = 6000;                                //Dryness Level Variable
//float h = 0;                                            //Humidity from Sensor
//float t = 0;                                            //Temperature from Sensor
//String sensorReading = "";

#define DHTPIN 2                                        // Digital pin connected to the DHT sensor
#define DHTTYPE    DHT11                                //The type of temperature sensor in use: DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

float readDHTTemperature() {
  float t = dht.readTemperature();                    // Function: Read temperature as Celsius from sensor  
  if (isnan(t)) {                                     // Check if any reads failed and exit early (to try again).    
    Serial.println("Failed to read from DHT sensor!");
    return 0;
  }
  else {
    //Serial.println(t);
    //return String(t);
    return t;
  }
}

float readDHTHumidity() {                           // Function: read humidity from sensor
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return 0;
  }
  else {
    //Serial.println(h);
    //return String(h);
    return h;
  }
}


void outputTempHumidy() {

  float h = readDHTTemperature();                       // Read temperature as Celsius (the default) and Humidity
  float t = readDHTHumidity();  
  float hic = dht.computeHeatIndex(t, h, false);        // Compute heat index in Celsius (isFahreheit = false)

  Serial.print("Humidity: ");
  Serial.print(int(h));
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(int(t));
  Serial.print("C \t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print("C \t");
}

void setup() {
  // put your setup code here, to run once:
  pinMode(solenoidPin, OUTPUT);                         //Sets the pin as an output
  Serial.begin(9600);
  Serial.println("Valve test!");
  dht.begin();
}
 
void loop() {
  outputTempHumidy();                                   //Read and output Temperature and Humidity from Sensor. 
  
  drynessLevel = analogRead(A2);                        //Read from moisture sensor
  Serial.print("Dryness Level "); 
  Serial.print(drynessLevel);

  if (drynessLevel >= 400) {                            //Dry soil. Switch Water Valve Solenoid ON
    Serial.println(" (Dry Soil)");
    digitalWrite(solenoidPin, HIGH);    
  }
  else if (drynessLevel < 400){                          //Moist Soil. Switch Water Valve Solenoid OFF
    Serial.println(" (Moisture OK)");
    digitalWrite(solenoidPin, LOW);     
  }   
  else   {                                              //Something went wrong.
    Serial.println("Moisture sensor error.");
  }
  delay(4000);                                          //Wait 4 Second
}
