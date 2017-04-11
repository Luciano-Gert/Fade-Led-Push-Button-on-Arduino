
int led = 10; // Led in pino 10 pwm
int button = 2; // Button in pino digital 2
bool fade = false; // bool variable to activate and deactivate the fade
int buttonState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  // Define the function to be called when an interruption (push button) 
  // It happens everytime the button changes from high to low
  attachInterrupt(0, interrupt_toogle, FALLING);
  loop();
}

void loop() {
  int startFadeValue = 0;
  while (Serial.available() > 0) {
    startFadeValue = Serial.parseInt();
    if(startFadeValue < 255){
      delay(30);  
    }else{
      Serial.println("Value out of range, it needs to be < 255!");
    }
  };

  // When the button is pressed
  if(fade){
    Serial.println("Fade In");
    // Brights up the led in 20%
    for (int fadeValue = startFadeValue ; fadeValue <= 255; fadeValue += 51) {
      analogWrite(led, fadeValue);
      print_voltage();
      // Wait 1 second
      delay(1000);
    }
  
    Serial.println("Fade Out");
    // Brights down the led in 20%
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 51) {
      analogWrite(led, fadeValue);
      print_voltage();
      // Wait 1 seconde
      delay(1000);
    }
  }
}

// Function to activate or deactivate the fadding
void interrupt_toogle() {
  buttonState = digitalRead(button); // Changes the button state
  fade = !fade;  
  Serial.println("You pressed the button!");
}

void print_voltage(){
  // Reads the value of the analog pin
  int sensorValue = analogRead(A0);
  // Converts the value to voltage
  float voltage = sensorValue * (5.0 / 1023.0);
  Serial.println(voltage);
}

