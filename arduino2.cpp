#define RX_PIN 2
unsigned long halfBitTime = 0;
bool syncReceived = false;
unsigned long ultimoTempo = 0;
unsigned long tempoAtual = 0;
String receivedBits = "";

void setup() {
    pinMode(RX_PIN, INPUT);
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(RX_PIN), newBit, CHANGE); 
    Serial.println("Receptor pronto. Aguardando sincronizacao...");
}

void newBit() {
    tempoAtual = millis();
    if (syncReceived) {
        bool currentBitValue = digitalRead(RX_PIN);
        if ((tempoAtual - ultimoTempo) >= halfBitTime) {
            ultimoTempo = tempoAtual;
            if (currentBitValue == HIGH) {
                receivedBits += '1';
            } else {
                receivedBits += '0';
            }
        }
    }
}

void loop() {
    static int lastState = HIGH;
    static unsigned long lastTime = 0;
    static unsigned long interval = 0;
    static int syncEdgeCount = 0;
    
    if (!syncReceived) {
        int currentState = digitalRead(RX_PIN);
        if (currentState != lastState) { 
            unsigned long currentTime = millis();
            unsigned long deltaTime = currentTime - lastTime;
            
            if (lastTime != 0) { 
                interval += deltaTime;
                syncEdgeCount++;
                
                Serial.print("Borda detectada, deltaTime: ");
                Serial.println(deltaTime);
            }
            
            lastTime = currentTime;
            lastState = currentState; 
        }
        
        if (syncEdgeCount >= 2) { 
            halfBitTime = interval / syncEdgeCount;
            syncReceived = true;
            ultimoTempo = millis();
            Serial.print("Sincronizacao recebida, halfBitTime: ");
            Serial.println(halfBitTime);
        }
    }
    else {
        if (receivedBits.length() >= 5) {
            String dataBits = receivedBits.substring(1, 5);
            
            Serial.print("Mensagem recebida: ");
            Serial.println(dataBits);
            
            int decimalValue = 0;
            for (int i = 0; i < 4; i++) {
                if (dataBits.charAt(i) == '1') {
                    decimalValue |= (1 << (3 - i));
                }
            }
            
            Serial.print("Valor decimal: ");
            Serial.println(decimalValue);
            
            receivedBits = "";
        }
    }
}