/*

  MODE 1: TRANSMIT (Default, Switch OFF)
   - Type in Serial Monitor -> LED Flashes & Buzzer Beeps
   
  MODE 2: RECEIVE (Switch ON)
   - Flash Light at LDR -> Decodes to Text
*/


const int PIN_LED = 2;
const int PIN_BUZZER = 4;
const int PIN_BUTTON = 18; 
const int PIN_POT = 34;
const int PIN_LDR = 35;


const int DOT_DURATION = 800; 
const int CHARACTER_TIMEOUT = 4000; 


int threshold = 0;
bool signalActive = false;
unsigned long signalStartTime = 0;
unsigned long lastSignalTime = 0;
String currentPattern = ""; 


bool lastModeWasReceive = false; 

const char* morseLetters[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--",
  "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};
const char* morseNumbers[] = {
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
};

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  
  Serial.println("--- System Ready ---");
  Serial.println("[MODE: TRANSMIT] Switch is Released. Type in Serial.");
}

void loop() {

  bool isReceiveMode = (digitalRead(PIN_BUTTON) == LOW);

  if (isReceiveMode && !lastModeWasReceive) {
      Serial.println("\n--- SWITCHED TO RECEIVE MODE (LDR Input) ---");
      Serial.println("Waiting for light signals...");
      lastModeWasReceive = true;
  } 
  else if (!isReceiveMode && lastModeWasReceive) {
      Serial.println("\n--- SWITCHED TO TRANSMIT MODE (Serial Input) ---");
      Serial.println("Type a message to send...");
      lastModeWasReceive = false;
  }

  if (isReceiveMode) {
      runReceiveLogic();
  } else {
      runTransmitLogic();
  }
}


void runReceiveLogic() {

  int potValue = analogRead(PIN_POT); 
  threshold = map(potValue, 0, 4095, 0, 4000); 

  int ldrValue = analogRead(PIN_LDR);
  
  bool isLightDetected = (ldrValue > threshold);

  if (isLightDetected) {
    if (!signalActive) {
      signalActive = true;
      signalStartTime = millis();
      digitalWrite(PIN_LED, HIGH); 
      tone(PIN_BUZZER, 1000);      
    }
  } else {
    if (signalActive) {
      signalActive = false;
      unsigned long duration = millis() - signalStartTime;
      digitalWrite(PIN_LED, LOW);
      noTone(PIN_BUZZER);
      
      if (duration > 50) { 
        if (duration < (DOT_DURATION * 2)) {
           currentPattern += ".";
           Serial.print(".");
        } else {
           currentPattern += "-";
           Serial.print("-");
        }
      }
      lastSignalTime = millis();
    }
  }

  if (currentPattern != "" && (millis() - lastSignalTime > CHARACTER_TIMEOUT)) {
    char letter = decodeMorse(currentPattern);
    Serial.print(" -> ");
    Serial.println(letter);
    currentPattern = ""; 
  }
}

void runTransmitLogic() {
  if (Serial.available()) {
    char c = Serial.read();
    Serial.print("TX: "); Serial.println(c); 
    transmitChar(c);
  }
  delay(10);
}

char decodeMorse(String pattern) {
  for (int i = 0; i < 26; i++) {
    if (pattern == morseLetters[i]) return (char)('A' + i);
  }
  for (int i = 0; i < 10; i++) {
    if (pattern == morseNumbers[i]) return (char)('0' + i);
  }
  return '?';
}


void transmitChar(char c) {
  c = toupper(c);
  String code = "";
  
  if (c >= 'A' && c <= 'Z') code = morseLetters[c - 'A'];
  else if (c >= '0' && c <= '9') code = morseNumbers[c - '0'];
  else if (c == ' ') { delay(DOT_DURATION * 4); return; }
  else return; 

  for (int i = 0; i < code.length(); i++) {
    int duration = (code[i] == '.') ? DOT_DURATION : (DOT_DURATION * 3);
    
    digitalWrite(PIN_LED, HIGH);
    tone(PIN_BUZZER, 1000);
    delay(duration);
    
    digitalWrite(PIN_LED, LOW);
    noTone(PIN_BUZZER);
    delay(DOT_DURATION); 
  }
  delay(DOT_DURATION * 3); 
}