
int rx_byte;

void setup() {
  // start serial port at 115200 bps:
  Serial.begin(115200);
}

void loop() {
  // check if there is data available
  if (Serial.available() > 0) {
    // get incoming byte:
    rx_byte = Serial.read();
    switch(rx_byte) {
      case '1':
        Serial.print("E_1");
        break;
      case '2':
        Serial.print("E_1");
        break;
      case '3':
        Serial.print("E_1");
        break;
      case '4':
        Serial.print("E_1");
        break;
      default:
        if (rx_byte != '\n' && rx_byte != '\r') {
          Serial.print("E_0");
        }
    } // switch
  } // if serial available
} // loop
