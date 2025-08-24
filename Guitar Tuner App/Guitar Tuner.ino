#include "arduinoFFT.h"
 
#define SAMPLES 64             //SAMPLES-pt FFT. Must be a base 2 number. Max 128 for Arduino Uno.
#define SAMPLING_FREQUENCY 1024 //Ts = Based on Nyquist, must be 2 times the highest expected frequency.

arduinoFFT FFT = arduinoFFT();
 
// Arduino pin bağlantıları
const int analogPin = A0;     // Sinüs sinyalinin okunacağı analog pin
const int digitalPin = 8;    // GPIO pin bağlantısı
bool button;
int state=0;

// Değişkenler
double Cfreq=0;
int sensorValue;             // Okunan analog değer
int thresholdh = 520;         // Eşik değeri (yüksek/düşük sinyal için)
int thresholdl = 500;
int counter;
unsigned long starttime;
double vReal[SAMPLES]; //create vector of size SAMPLES to hold real values
double vImag[SAMPLES]; //create vector of size SAMPLES to hold imaginary values
 unsigned long samplingPeriod; //= round(1000000*(1.0/SAMPLING_FREQUENCY)); //Period in microseconds 
unsigned long microSeconds;
unsigned long tut=0,tut2=0;  
void setup() {
  Serial.begin(9600);
  pinMode(digitalPin, OUTPUT);   // GPIO pinini çıkış olarak ayarla
  samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY)); //Period in microseconds
}

void loop() {

      //Sample SAMPLES times/
    for(int i=0; i<SAMPLES; i++)
    {
        microSeconds = micros();    //Returns the number of microseconds since the Arduino board began running the current script. 
     
        vReal[i] = analogRead(A0); //Reads the value from analog pin 0 (A0), quantize it and save it as a real term.
        vImag[i] = 0; //Makes imaginary term 0 always
          if (micros() - tut >= 500000/Cfreq){
            digitalWrite(8,!digitalRead(8));
            tut=micros();    
          }

        //remaining wait time between samples if necessary/
        while(micros() < (microSeconds + samplingPeriod))
        {
          if (micros() - tut >= 500000/Cfreq){
            digitalWrite(8,!digitalRead(8));
            tut=micros();    
          }
          //do nothing
        }
    }
    //Perform FFT on samples/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

    //Find peak frequency and print peak/
    
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
 //   Serial.println(peak);     //Print out the most dominant frequency.
    

    if(digitalRead(4)== !button)
    {
        button = !button;
        state++;
        if(state==6)
          state=0;
    }

     switch (state) {
      case 5:
        if(abs(peak -83) < abs(Cfreq-83))
          Cfreq=peak;
      break;
      case 4:
        if(abs(peak -110) < abs(Cfreq-110))
          Cfreq=peak;
      break;
      case 3:
        if(abs(peak -147) < abs(Cfreq-147))
          Cfreq=peak;
      break;
      case 2:
        if(abs(peak -196) < abs(Cfreq-196))
          Cfreq=peak;
      break;
      case 1:
        if(abs(peak -247) < abs(Cfreq-247))
          Cfreq=peak;
      break;
      case 0:
        if(abs(peak -330) < abs(Cfreq-330))
          Cfreq=peak;
      break;
    }
    Serial.println(Cfreq);
    Serial.println(state+1);

   
    if(micros()-tut2>=10000000)
    {
      tut2=micros();
      Cfreq=0;
    }

    if (micros() - tut >= 500000/Cfreq){
       digitalWrite(8,!digitalRead(8));
       tut=micros();    
    }

}
