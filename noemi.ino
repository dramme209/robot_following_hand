class Motor {
public:
  int v; // pin enable
  int a; // pin avanti
  int i; // pin indietro
  Motor(int x, int y, int z) {
    v = x;
    a = y;
    i = z;
    pinMode(v, OUTPUT);
    pinMode(a, OUTPUT);
    pinMode(i, OUTPUT);
    digitalWrite(v, LOW);
    digitalWrite(a, LOW);
    digitalWrite(i, LOW);
  }
  void Speed(int s) {
    if (s < 0) {
      digitalWrite(i, HIGH);
      digitalWrite(a, LOW);
      s *= -1;
    } else {
      digitalWrite(a, HIGH);
      digitalWrite(i, LOW);
    }
    s = map(s, 0, 100, 0, 255);
    analogWrite(v, s);
  }
};

Motor md(11, 12, 13); // motor object 1
Motor ms(6, 7, 8);    // motor object 2

#define tP 4 // trigger pin
#define eP 2 // echo pin

#define ir_L 2 // sensore IR sinistro
#define ir_R 3 // sensore IR destro

int Speed = 27; // Velocità dei motori

void ul_setup() {
  pinMode(tP, OUTPUT);
  pinMode(eP, INPUT);
  pinMode(ir_R, INPUT);
  pinMode(ir_L, INPUT);
  Serial.begin(9600);
}

void ul_loop() {
  digitalWrite(tP, LOW);
  digitalWrite(tP, HIGH);
  delayMicroseconds(100);
  digitalWrite(tP, LOW);
  long duration = pulseIn(eP, HIGH);
  long distance = duration * 0.034 / 2;
  Serial.println(distance);
  
  int L_s = digitalRead(ir_L); // Leggi il sensore sinistro
  int R_s = digitalRead(ir_R); // Leggi il sensore destro

  if (R_s == LOW && L_s == HIGH) { // Se il sensore destro rileva e il sinistro non rileva
    turnLeft(); // Gira a destra
  } else if (L_s == LOW && R_s == HIGH) { // Se il sensore sinistro rileva e il destro non rileva
    turnRight(); // Gira a sinistra
  } else {
        forward();
      }



  
}

void setup() {
  ul_setup(); // Inizializza il sensore ad ultrasuoni e i sensori IR
}

void loop() {
  ul_loop(); // Controllo continuo dei sensori e movimento del robot
}

// Funzioni per i movimenti del robot
void forward() {
  md.Speed(Speed);
  ms.Speed(Speed);
}

void turnRight() {
  md.Speed(Speed);
  ms.Speed(-Speed); // Inverti il motore sinistro per girare a destra
}

void turnLeft() {
  md.Speed(-Speed); // Inverti il motore destro per girare a sinistra
  ms.Speed(Speed);
}

void stop() {
  md.Speed(0);
  ms.Speed(0);
}
