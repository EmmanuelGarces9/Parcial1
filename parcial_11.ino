int LATCH = 6;
int inputy = 5;
int inputx = 10;
int CLKY = 7;
int CLKX = 13;
char opcion = 0;
bool mostrarMenu = true;
unsigned long tiempoInicial;
unsigned long duracionDeseada = 1000;


unsigned char LED[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };

void pulse(int pin) {
  digitalWrite(pin, LOW);
  digitalWrite(pin, HIGH);
}

void writeY(unsigned char byte) {  //que leds de la columna encienden
  for (int i=0; i<8; i++) {
   	digitalWrite(inputy, (byte & (128 >> i)));
    pulse(CLKY);
  }
}

void writeX(unsigned char byte) {  //que columna enciende
  for (int i=0; i<8; i++) {
    digitalWrite(inputx, ((~byte) & (128 >> i)));
    pulse(CLKX);
  }
}

void publik(char opcion) {
    switch (opcion) {
      case '1':
      	verificacion();
        break;
      case '2':
        //Imagen();
        break;
      case '3':
      	patron1();
      	delay(500);
      	patron2();
        break;
      default:
        break;
    }
}

void verificacion() {
  Serial.println("iniciando verificacion:");
  if (opcion=='1'){
    int temp=0;
    while(temp<7){
      for (int f = 0; f < 8; f++) {
      digitalWrite(LATCH, LOW);
      writeX(LED[f]);  
      writeY(255);  
      digitalWrite(LATCH, HIGH);
    }
      for(int o=0;o<8;o++){
        digitalWrite(LATCH, LOW);
        writeX(0);
        writeY(0);
		digitalWrite(LATCH, HIGH);
        delay(100);
      }
      temp++;
  }
  Serial.println("finalizando verificacion:");
  }
}


void setup() {
  pinMode(inputy, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLKY, OUTPUT);
  pinMode(inputx, OUTPUT);
  pinMode(CLKX, OUTPUT);

  digitalWrite(inputy, 0);
  digitalWrite(LATCH, LOW);
  digitalWrite(CLKY, LOW);
  digitalWrite(inputx, 1);
  digitalWrite(CLKX, LOW);
  
  Serial.begin(9600);
  }

void loop() {
  if (mostrarMenu) {
    Serial.println("Elija una opcion:");
    Serial.println("1. Opcion 1");
    Serial.println("2. Opcion 2");
    Serial.println("3. Opcion 3");
    mostrarMenu = false; // Desactiva la visualización del menú hasta que se elija una opción
  }

  if (Serial.available() > 0) {
    opcion = Serial.read(); // Lee un carácter del puerto serial
	
    if (opcion >= '1' && opcion <= '3') {
      publik(opcion);
      mostrarMenu = true;// Activa la visualización del menú nuevamente
      opcion = 0; // Reinicia la opción seleccionada
    } else {
      Serial.println("Opción no válida. Elija una opción del 1 al 3.");
    }
  }
}
void patron1(){
 	tiempoInicial = millis();
    while (true){
       unsigned long tiempoActual = millis();
    	unsigned long tiempoTranscurrido = tiempoActual - tiempoInicial;
        if (tiempoTranscurrido<duracionDeseada){
            int n=0;
            unsigned char filas1[8] = {};
            unsigned char fila = 255;
            for(int i = 6; i >= 0; i-=2, fila = 255) {
                fila = (fila >> i) << (i/2);
                filas1[n++]=fila;
            }
            for(int i = 0; i <= 6; i+=2, fila = 255) {
                fila = (fila >> i) << (i/2);
                filas1[n++]=fila;
            }
            for (int x = 0; x < 8; x++) {
                digitalWrite(LATCH, LOW);
                writeX(LED[x]);
                writeY(filas1[x]);
                digitalWrite(LATCH, HIGH);
            }
        }else{
          		digitalWrite(LATCH, LOW);
                writeX(0);
                writeY(0);
                digitalWrite(LATCH, HIGH);
          		break;
        }
    }
    digitalWrite(LATCH, LOW);
    writeX(0);
    writeY(0);
    digitalWrite(LATCH, HIGH);
}

void patron2(){
  tiempoInicial = millis();
  digitalWrite(LATCH, LOW);
  writeX(0);
  writeY(0);
  digitalWrite(LATCH, HIGH);
  while (true){
      unsigned long tiempoActual = millis();
      unsigned long tiempoTranscurrido = tiempoActual - tiempoInicial;
      if (tiempoTranscurrido<duracionDeseada){
        int n = 0;
        unsigned char Filas[8] = {};
        for (int i = 0; i < 8; i++) {
          unsigned char fila = 0;
          fila = (1 << i) | (1 << (7 - i));
          Filas[n++] = fila;
        }
        for (int x = 0; x < 8; x++) {
          digitalWrite(LATCH, LOW);
          writeX(LED[x]);
          writeY(Filas[x]);
          digitalWrite(LATCH, HIGH);
        }
      }else{
        digitalWrite(LATCH, LOW);
        writeX(0);
        writeY(0);
        digitalWrite(LATCH, HIGH);
        break;
      	}
     }
}
