#include <ModbusMaster.h>

#define SLAVE_ADDRESS 1        // Modbus slave ID
#define FLOW_RATE_REGISTER 0   // Adjust based on the register map (zero-based)
#define TX_ENABLE_PIN 5        // RS485 driver TX enable pin

// Create ModbusMaster object
ModbusMaster node;

void preTransmission() {
  digitalWrite(TX_ENABLE_PIN, HIGH); // Enable transmission
}

void postTransmission() {
  digitalWrite(TX_ENABLE_PIN, LOW); // Disable transmission
}

void setup() {
  Serial.begin(9600); // Debugging serial monitor
  Serial.println("Reading Flow Rate from Water Flow Meter");

  // Initialize RS485
  pinMode(TX_ENABLE_PIN, OUTPUT);
  digitalWrite(TX_ENABLE_PIN, LOW);

  // Setup Modbus communication
  node.begin(SLAVE_ADDRESS, Serial); // Slave ID and communication port
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

void loop() {
  uint8_t result;          // To store Modbus result
  uint16_t data[2];        // To store register data (two registers for FLOAT32)
  float flowRate = 0.0f;   // Flow rate value

  // Request data from the flow rate register (read two consecutive registers)
  result = node.readHoldingRegisters(FLOW_RATE_REGISTER, 2);

  if (result == node.ku8MBSuccess) {
    // Combine two 16-bit registers into a 32-bit float
   // uint32_t rawData = (node.getResponseBuffer(0) << 16) | node.getResponseBuffer(1);
    
    data[0] = node.getResponseBuffer(0);
    data[1] = node.getResponseBuffer(1);
    
    memcpy(&flowRate, &data, 4); // Interpret as float


    
    // Display the flow rate
    Serial.print("Flow Rate: ");
    Serial.print(flowRate);
    Serial.println(" m3/h"); // Unit based on manual

  } else {
    // Print error code for debugging
    Serial.print("Modbus Error: ");
    Serial.println(result);
  }

  delay(1000); // Wait 1 second before the next read
}
