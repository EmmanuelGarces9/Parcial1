int LATCH = 6;
int inputy = 5;
int inputx = 10;
int CLKY = 7;
int CLKX = 13;
char opcion = 0;
bool mostrarMenu = true;
unsigned long tiempoInicial;
unsigned long duracionDeseada = 500;
unsigned long duracionImagen;
<<<<<<< HEAD
unsigned long secuencias;
unsigned long tiempo1;
=======

>>>>>>> 8f59401dd0e9e9ab764b09e169c74d582a7bd152

unsigned char LED[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };

unsigned char *Filas= new unsigned char[8];

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
<<<<<<< HEAD
        Imagen();
=======
>>>>>>> 8f59401dd0e9e9ab764b09e169c74d582a7bd152
        break;
      case '3':
      	patron1();
      	delay(500);
      	patron2();
      	delay(500);
      	patron3();
      	delay(500);
      	patron4();
        break;
      default:
        break;
    }
}

void verificacion() {
    Serial.println("indique el numero de secuencias: ");
    while (!Serial.available()) {}
    secuencias=Serial.parseInt();
    Serial.print(secuencias);
    Serial.println(" secuencias..");
    Serial.println("Ingrese el tiempo entre encendido y apagado: ");
    while (!Serial.available()) {}
    tiempo1=Serial.parseInt()*1000;
    Serial.println("iniciando verificacion:");
    int temp=0;
  	while(temp<secuencias){
      tiempoInicial = millis();
      while (true){
        	unsigned long tiempoActual = millis();
          unsigned long tiempoTranscurrido = tiempoActual - tiempoInicial;
          if (tiempoTranscurrido<duracionDeseada){
            for (int f = 0; f < 8; f++) {
              digitalWrite(LATCH, LOW);
              writeX(LED[f]);  
              writeY(255);
              digitalWrite(LATCH, HIGH);
            }
          }else{
              digitalWrite(LATCH, LOW);
              writeX(0);
              writeY(0);
              digitalWrite(LATCH, HIGH);
              delay(tiempo1);
            	temp++;
            	break;
          } 
      }
<<<<<<< HEAD
  	}
  	Serial.println("finalizando verificacion");
=======
      temp++;
  }
  Serial.println("finalizando verificacion");
  delete[] Filas;
  }
>>>>>>> 8f59401dd0e9e9ab764b09e169c74d582a7bd152
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
  	unsigned char *Filas= new unsigned char[8];
 	tiempoInicial = millis();
    while (true){
       unsigned long tiempoActual = millis();
    	unsigned long tiempoTranscurrido = tiempoActual - tiempoInicial;
        if (tiempoTranscurrido<duracionDeseada){
            int n=0;
            unsigned char fila = 255;
            for(int i = 6; i >= 0; i-=2, fila = 255) {
                fila = (fila >> i) << (i/2);
                Filas[n++]=fila;
            }
            for(int i = 0; i <= 6; i+=2, fila = 255) {
                fila = (fila >> i) << (i/2);
                Filas[n++]=fila;
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
    digitalWrite(LATCH, LOW);
    writeX(0);
    writeY(0);
    digitalWrite(LATCH, HIGH);
  	delete[] Filas;
}

void patron2(){
  unsigned char *Filas= new unsigned char[8];
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
        for (int i = 0; i < 8; i++) {
          unsigned char fila = 0;
          fila = (1 << i) | (1 << (7 - i));  // Enciende los bits correspondientes en la fila
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
        delete[] Filas;
        break;
      	}
     }
}

void patron3(){
  unsigned char *Filas= new unsigned char[8];
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
        short int desp=0;

        for (int i = 0; i < 8; i++) {
          unsigned char fila = 0;
          if (i %3 ==0) {
            fila = 255;
            desp=0;
          } else {
            fila = 204>>desp;
            desp+=2;
          }
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
        delete[] Filas;
        break;
      	}
     }
}

void patron4(){
  unsigned char *Filas= new unsigned char[8];
  tiempoInicial = millis();
  digitalWrite(LATCH, LOW);
  writeX(0);
  writeY(0);
  digitalWrite(LATCH, HIGH);
  while (true){
      unsigned long tiempoActual = millis();
      unsigned long tiempoTranscurrido = tiempoActual - tiempoInicial;
      if (tiempoTranscurrido<duracionDeseada){
          int n=0;
          unsigned char fila = 240;
          for(int i = 0; i < 4; i++, fila = 240) {
              fila = fila >> i;
              Filas[n++]=fila;
          }
          for(int i = 3; i >= 0; i--, fila = 240) {
              fila = fila >> i;
<<<<<<< HEAD
            Filas[n++]=fila;
=======
              Filas[n++]=fila;
>>>>>>> 8f59401dd0e9e9ab764b09e169c74d582a7bd152
          }
          for (int x = 0; x < 8; x++) {
               digitalWrite(LATCH, LOW);
                writeX(Filas[x]);
                writeY(LED[x]);
                digitalWrite(LATCH, HIGH);
           } 
      }else{
          		digitalWrite(LATCH, LOW);
                writeX(0);
                writeY(0);
                digitalWrite(LATCH, HIGH);
        		delete[] Filas;
          		break;
           }
     }
<<<<<<< HEAD
}

void Imagen() {
  	Serial.println("Ingrese duracion del patron:");
  	while (!Serial.available()) {}
  	duracionImagen=Serial.parseInt()*100;
  	Serial.print("Se mostrara: ");
  	Serial.print(duracionImagen/100);
  	Serial.println(" segundos");
  	unsigned char *Filas= new unsigned char[8];
  	unsigned short int** input = new unsigned short int*[8];
    for (int i = 0; i < 8; i++) {
      input[i] = new unsigned short int[8];
    }
  	Serial.println("Ingrese columnas de derecha a izquierda:");
    for (int fila = 0; fila < 8; fila++) {
      for (int columna = 0; columna < 8; columna++) {
        while (!Serial.available()) {}
          char valorLeido = Serial.read();
          int valorEntero = valorLeido - '0';
          input[fila][columna] = valorEntero;
          Serial.print(input[fila][columna]);
      }Serial.println();
    }
  tiempoInicial = millis();
  
  while (true){
      unsigned long tiempoActual = millis();
	  unsigned long tiempoTranscurrido = tiempoActual - tiempoInicial;
      convertToChar(input,Filas);
      unsigned long cont=0;
      while (tiempoTranscurrido<duracionImagen){
        for (int x = 0; x < 8; x++) {
               	digitalWrite(LATCH, LOW);
                writeX(LED[x]);
                writeY(Filas[x]);
          		digitalWrite(LATCH, HIGH);
        }     
        for(int o=0;o<8;o++){
        		digitalWrite(LATCH, LOW);
        		writeX(0);
        		writeY(0);
				digitalWrite(LATCH, HIGH);
        		delay(100);
      	} 
        cont++;
        if (cont==(duracionImagen/100)) break;
      }
        digitalWrite(LATCH, LOW);
        writeX(0);
        writeY(0);
        digitalWrite(LATCH, HIGH);
        break;
  }
  for (int i = 0; i < 8; i++) {
    delete[] input[i];
  }
  delete[] input;
}

void convertToChar(unsigned short int** input, unsigned char *Filas){
	for (int fila = 0; fila < 8; fila++) {
    	short int valorChar = 0;
    	unsigned short int* ptr = input[fila];
        for (int columna = 0; columna< 8; columna++) {
          	valorChar = (valorChar << 1) | *ptr;
      		ptr++;
        }
    Filas[fila] = char(valorChar);
  }
=======
>>>>>>> 8f59401dd0e9e9ab764b09e169c74d582a7bd152
}