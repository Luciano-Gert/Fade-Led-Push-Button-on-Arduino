// Declarações
int led = 10; // Led no pino 10 pwm
int button = 2; // Botão no pino digital 2
bool fade = false; // Variavel boleana para ativar e desativar o programa
int buttonState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  // Define a função de interrupção a ser chamada 
  // toda vez que o bottão muda de HIGH para LOW
  attachInterrupt(0, interrupt_toogle, FALLING);
  loop();
}

void loop() {
  int startFadeValue = 0;
  // Quando receber valor serial, set startFadeValue
  while (Serial.available() > 0) {
    startFadeValue = Serial.parseInt();
    if(startFadeValue < 255){
      delay(30);  
    }else{
      Serial.println("Valor fora da escala, precisa ser < 255!");
    }
  };

  // Ativa somente quando o botão for acionado
  if(fade){
    Serial.println("Fade In");
    // Incrementa o brilho do led em 20%
    for (int fadeValue = startFadeValue ; fadeValue <= 255; fadeValue += 51) {
      analogWrite(led, fadeValue);
      print_voltage();
      // Espera 1segundo
      delay(1000);
    }
  
    Serial.println("Fade Out");
    // Decrementa o brilho do led em 20%
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 51) {
      analogWrite(led, fadeValue);
      print_voltage();
      // Espera 1 segundo
      delay(1000);
    }
  }
}

// Ativa ou desativa o fade do led
void interrupt_toogle() {
  buttonState = digitalRead(button); // Muda o estado do botão qdo precionado
  fade = !fade; // Inverte o valor do fade 
  Serial.println("Voce apertou o botao!");
}

void print_voltage(){
  // Lê o valor do pino analogico
  int sensorValue = analogRead(A0);
  // Converte a leitura analogica em voltagem
  float voltage = sensorValue * (5.0 / 1023.0);
  Serial.println(voltage);
}

