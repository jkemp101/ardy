// Metal detector
// Runs a pulse over the search loop in series with resistor
// Voltage over search loop spikes
// Through a diode this charges a capacitor
// Value of capacitor after series of pulses is read by ADC

// Metal objects near search loop change inductance.
// ADC reading depends on inductance.
// changes wrt long-running mean are indicated by LEDs
// LED1 indicates rise in inductance
// LED2 indicates fall in inductance
// the flash rate indicates how large the difference is

// wiring:
// 220Ohm resistor on D2
// 10-loop D=10cm seach loop between ground and resistor
// diode (-) on pin A0 and (+) on loop-resistor connection
// 10nF capacitor between A0 and ground
// LED1 in series with 220Ohm resistor on pin 8
// LED2 in series with 220Ohm resistor on pin 9

// First time, run with with serial print on and tune value of npulse
// to get capacitor reading between 200 and 300

const byte npulse = 3;
const bool sound = true;
const bool debug = false;

const byte pin_pulse     = 3;
const byte pin_cap       = A1;
const byte pin_cap_drain = 4;

void setup() {
  if (debug) Serial.begin(9600);
  pinMode(pin_pulse, OUTPUT);
  digitalWrite(pin_pulse, LOW);
  pinMode(pin_cap_drain, INPUT);

}

const int nmeas=256;  //measurements to take

void loop() {

  //perform measurement
  long unsigned int sum = 0;
  long unsigned int avg;
  for (int imeas=0; imeas < nmeas; imeas++){
    //reset the capacitor
    pinMode(pin_cap_drain,OUTPUT);
    digitalWrite(pin_cap_drain,LOW);
    delayMicroseconds(20);
    pinMode(pin_cap_drain,INPUT);
    //apply pulses
    for (int ipulse = 0; ipulse < npulse; ipulse++) {
      digitalWrite(pin_pulse,HIGH); //takes 3.5 microseconds
      delayMicroseconds(3);
      digitalWrite(pin_pulse,LOW);  //takes 3.5 microseconds
      delayMicroseconds(3);
    }
    //read the charge on the capacitor
    int val = analogRead(pin_cap); //takes 13x8=104 microseconds
    sum+=val;
  }

  avg = sum / nmeas;

  if (debug){
    Serial.print(avg);
    Serial.println();
  }

}
