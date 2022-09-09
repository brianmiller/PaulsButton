#define RED 11   // pin that red led is connected to    
#define GREEN 10 // pin that green led is connected to     
#define BLUE 9  // pin that blue led is connected to    
#define DELAY 10  // internal delay in ms
int cyclesBeforePaulArrives = 8; // (420 seconds)
int paulStayCycles = 11;
int paulSpeed = 5; //(in ms)
int rainbowSpeed = 80; //(in ms, the higher the number, the slower the unicorn power. 80 = 1 minute for a complete cycle)


void setup() { 
  Serial.begin(9600);
  
  // Assign our pins
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  // Pull all HIGH (common cathode ::facepalm::)
  digitalWrite(RED, HIGH); // pull high (off)
  digitalWrite(GREEN, HIGH); // pull high (off)
  digitalWrite(BLUE, HIGH); // pull high (off)
}


// A small snippet from Paul's original Christmas tree code
void rainbowLoop() {
  // Fade from red to green
  for(int i=0; i<255; i++) {
    analogWrite(RED, i); // red initially ON
    analogWrite(GREEN, 255-i); // green initially OFF
    analogWrite(BLUE, 255); // blue OFF
    delay(rainbowSpeed); // wait before next transition
  }

  // Fade from green to blue
  for(int i=0; i<255; i++) {
    analogWrite(RED, 255); // red OFF
    analogWrite(GREEN, i); // green initially ON
    analogWrite(BLUE, 255-i); // blue initially OFF
    delay(rainbowSpeed);
  }

  // Fade from blue to red
  for(int i=0; i<255; i++) {
    analogWrite(RED, 255-i); // red initially OFF
    analogWrite(GREEN, 255); // green OFF
    analogWrite(BLUE, i); // blue initially ON
    delay(rainbowSpeed);
  }
}


// Paul's loop. He shows up, relaxes then leaves.  He'll be back.
void paulLoop() {
  Serial.println("Paul is here!");

  digitalWrite(RED, HIGH); // pull high (set red to off, Paul only likes green)
  digitalWrite(BLUE, HIGH); // pull high (set blue to off, Paul only likes green)
  
  for(int paulStay=1; paulStay<paulStayCycles; paulStay = paulStay + 1){ // begin Paul's loop
    
    Serial.print("Puff, puff, ");

    // Inhale and hold
    for (int i = 1; i <= 255; i += 5) {
      analogWrite(GREEN, i);
      delay(paulSpeed);
    }

    // Exhale
    for (int i = 255; i >= 0; i -= 5) {
      analogWrite(GREEN, i);
      delay(paulSpeed);
    }
    
    Serial.println("pass..."); 
       
  } // End Paul's loop

  digitalWrite(RED, HIGH); // pull high (off)
  digitalWrite(GREEN, HIGH); // pull high (off)
  digitalWrite(BLUE, HIGH); // pull high (off
  
  Serial.println("Paul says he needs to leave. He'll be back.");  
}


void loop() {

  for(int count=0; count<cyclesBeforePaulArrives; count = count + 1){

    // Start with rainbows.
    //rainbowLoop();

    // Current cycle.
    Serial.print("\rThis is cycle ");
    Serial.print(count);
    Serial.println(".");

    // How much longer until Paul shows up?
    int paulEta = cyclesBeforePaulArrives - count;
    Serial.print("Paul arrives in ");
    Serial.print(paulEta);
    Serial.println(" cycles. Rainbows and unicorns until then!");


    // Watch for Paul.
    if ( count == cyclesBeforePaulArrives - 1) {
      paulLoop();
    }
    else
    {
      rainbowLoop();
    }
    
  } // End watch for Paul loop.
  
} // End main loop.
