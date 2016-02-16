/*
file: LoadCell_INA125p.ino
The Creative commons License (CC)
Copyright (c) 2016 Abhay Shankar Bharadwaj
abhaysbharadwaj@gmail.com
Load Cell Calibration & weight value output
*/

#define loadCell  A0 // Arduino analog pin to read
#define LoadSamples 20 //define the samples to average readings
int samples[LoadSamples];


// LOAD CELL CALIBRATION
static long loadLow = 0; // measured low end load in grammes from good scales
static int analogLow = 74; // [82] analog reading from load cell for low end test load

// High end of the test load values
static long loadHigh = 1000; // [5091] measured high end load in grammes from good scales
static int analogHigh = 242; // [1022] analog reading from load cell for high end test load

void setup()
{
    Serial.begin(9600);  // Set a slower boadrate for calibration
}

void loop() 
{
  int i;
  float LoadAverage;
  for(i=0;i<LoadSamples;i++)
  {
    samples[i] = analogRead(loadCell);
  }
  LoadAverage=0;
  for(i=0;i<LoadSamples;i++)
  {
    LoadAverage += samples[i];
  }
  LoadAverage/=LoadSamples;
  // Convert analog value to load in grams
  int loadGrams = map(LoadAverage, analogLow, analogHigh, loadLow, loadHigh);
  int xy = loadGrams;//-(loadGrams*0.5/100);
  /*
  //debug option
  Serial.print("Analog pin value: ");
  Serial.println(analogValue);
  Serial.print("Smoothed analog value: ");
  Serial.println(analogSamplesLoadAverage);*/
  Serial.print("Scale load: ");
  Serial.print(xy);
  Serial.println(" grammes ");
  delay(500);
}
