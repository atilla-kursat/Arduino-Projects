#include <arduinoFFT.h> // Include FFT library

// Constants
#define SAMPLES 128      // Number of samples for FFT (power of 2)
#define SAMPLING_FREQUENCY 100000 // Sampling frequency in Hz (100 kHz)
#define IR_WAVELENGTH 850e-9  // Wavelength of IR light in meters
#define PIPE_RADIUS 0.05      // Radius of pipe in meters
#define SOUND_SPEED 3e8       // Speed of light in vacuum (m/s)

// Arrays for FFT
double vReal[SAMPLES];        // Real part of FFT
double vImag[SAMPLES];        // Imaginary part of FFT

arduinoFFT FFT = arduinoFFT(vReal, vImag, SAMPLES, SAMPLING_FREQUENCY);

void setup() {
  Serial.begin(115200);
  Serial.println("Doppler Water Flow Measurement Started");
}

void loop() {
  // Step 1: Collect ADC samples
  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] = analogRead(A0); // Replace A0 with the pin connected to photodiode
    vImag[i] = 0; // Imaginary part is zero
    delayMicroseconds(1000000 / SAMPLING_FREQUENCY); // Sampling interval
  }

  // Step 2: Perform FFT
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD); // Apply Hamming window
  FFT.Compute(FFT_FORWARD); // Perform FFT
  FFT.ComplexToMagnitude(); // Compute magnitude

  // Step 3: Find peak frequency
  double peakFrequency = FFT.MajorPeak(); // Get the dominant frequency in Hz
  Serial.print("Peak Frequency (Hz): ");
  Serial.println(peakFrequency);

  // Step 4: Calculate water velocity
  double velocity = (peakFrequency * IR_WAVELENGTH) / 2;
  Serial.print("Water Velocity (m/s): ");
  Serial.println(velocity);

  // Step 5: Calculate flow rate
  double area = PI * pow(PIPE_RADIUS, 2);
  double flowRate = velocity * area; // Flow rate in cubic meters per second
  Serial.print("Flow Rate (L/s): ");
  Serial.println(flowRate * 1000); // Convert to liters per second

  delay(1000); // Delay before next reading
}
