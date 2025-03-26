#define TX_PIN 3
unsigned long TX_HALF_BIT = 150;             
unsigned long TX_SYNC_TIME = TX_HALF_BIT * 2;  

void setup() {
  pinMode(TX_PIN, OUTPUT);
  Serial.begin(9600);
  sendConfirmationBit();
  Serial.println("Digite um numero binario de 4 bits (ex: 1010):");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    
    if (input.length() == 4 && isValidBinary(input)) {
      int binaryMessage[4];
      for (int i = 0; i < 4; i++) {
        binaryMessage[i] = (input.charAt(i) == '1') ? 1 : 0;
      }
      
      Serial.print("Bits: ");
      for (int i = 0; i < 4; i++){
        Serial.print(binaryMessage[i]);
      }
      Serial.println();
      
      sendNibble(binaryMessage);
      
      Serial.println("Transmissao completa!");
      Serial.println("Digite outro numero binario de 4 bits:");
    } 
    else {
      Serial.println("Entrada invalida! Digite exatamente 4 digitos binarios (0 ou 1)");
    }
  }
}

bool isValidBinary(String str) {
  for (int i = 0; i < str.length(); i++) {
    if (str.charAt(i) != '0' && str.charAt(i) != '1') {
      return false;
    }
  }
  return true;
}

void sendConfirmationBit() {
  digitalWrite(TX_PIN, HIGH);
  Serial.println("Sync HIGH");
  delay(TX_SYNC_TIME);
  digitalWrite(TX_PIN, LOW);
  Serial.println("Sync LOW");
  delay(TX_SYNC_TIME);
  digitalWrite(TX_PIN, HIGH);
  Serial.println("Sync HIGH");
  delay(TX_SYNC_TIME);
  digitalWrite(TX_PIN, LOW);
  Serial.println("Sync LOW");
  delay(TX_SYNC_TIME);
}

void sendNibble(int binary[4]) {
  digitalWrite(TX_PIN, LOW);
  delay(TX_HALF_BIT);
  digitalWrite(TX_PIN, HIGH);
  delay(TX_HALF_BIT);
  
  for (int i = 0; i < 4; i++) {
    Serial.print("Enviando bit ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(binary[i]);
    
    if (binary[i] == 1) {
      digitalWrite(TX_PIN, LOW);
      delay(TX_HALF_BIT);
      digitalWrite(TX_PIN, HIGH);
      delay(TX_HALF_BIT);
    } else {
      digitalWrite(TX_PIN, HIGH);
      delay(TX_HALF_BIT);
      digitalWrite(TX_PIN, LOW);
      delay(TX_HALF_BIT);
    }
  }
}