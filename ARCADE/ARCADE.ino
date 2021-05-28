#include <LiquidCrystal.h>
#include <LiquidMenu.h>
#include <LedControl.h>
#include <SPI.h>
#include <SD.h>

#define SSpin 53    // Slave Select en pin digital 53

LedControl lc = LedControl (8, 9, 10, 1);

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

File archivo;     // objeto archivo del tipo File


//Definición de las distintas pantallas y sus correspondientes lineas dentro del menu
LiquidLine linea1_1(1, 0, "Santi");
LiquidLine linea1_2(1, 1, "Jose");
LiquidLine linea1_3(1, 0, "Pablo");
LiquidScreen pantalla1(linea1_1, linea1_2, linea1_3);

LiquidLine linea2_1(1, 0, "Reanudar");
LiquidLine linea2_2(1, 1, "Finalizar la partida");
LiquidScreen pantalla2(linea2_1, linea2_2);

LiquidMenu menu(lcd, pantalla1, pantalla2);


void setup() {
  pinMode(13, INPUT); //Pulsador joystick

  //Inicializacion matriz led
  lc.shutdown (0, false);
  lc.setIntensity (0, 1); // intensidad 0-15
  lc.clearDisplay (0);

  //Inicializacion pantalla LCD
  lcd.begin(16, 2);

  randomSeed(analogRead(A15));


  linea1_1.set_focusPosition(Position::LEFT);
  linea1_2.set_focusPosition(Position::LEFT);
  linea1_3.set_focusPosition(Position::LEFT);

  linea1_1.attach_function(1, fn_play);
  linea1_2.attach_function(1, fn_play);
  linea1_3.attach_function(1, fn_play);

  menu.add_screen(pantalla1);

  linea2_1.set_focusPosition(Position::LEFT);
  linea2_2.set_focusPosition(Position::LEFT);

  pantalla1.set_displayLineCount(2);
  pantalla2.set_displayLineCount(2);

  menu.add_screen(pantalla2);
  menu.set_focusedLine(0);
  
  //Inicializacion tarjeta SD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("Iniciando");
  lcd.setCursor(0, 1);
  lcd.write("tarjeta SD");
  delay(1500);
  
  if (!SD.begin(SSpin)) {
  
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write("Fallo en la");
    lcd.setCursor(0, 1);
    lcd.write("inicializacion!");
    delay(1500);
    
    return;
  }
  
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write("Inicializacion");
    lcd.setCursor(0, 1);
    lcd.write("correcta");
    delay(1500);
  }
  
  //Pantalla inicial
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("Elegir jugador");

  int SW = digitalRead(13);

  while (SW == true) {
    SW = digitalRead(13);
  }

  lcd.clear();
  delay(700);
  menu.update();
}


void loop() {
  int Y = analogRead(A1);     // lectura de valor de eje y
  int SW = digitalRead(13);   // lectura pulsador

  static long ultimo_cambio = 0;
  long hora;

  selectOption();

  hora = millis();
  if (hora - ultimo_cambio > 200) {
    ultimo_cambio = hora;
    if (Y >= 900 && Y <= 1023) {    // si el joystick se acciona hacia arriba
      menu.switch_focus(false);     // el menu sube
    }

    if (Y >= 0 && Y <= 100) {      // si el joystick se acciona hacia abajo
      menu.switch_focus(true);     // el menu baja
    }
  }

  menu.update();
  delay(8);
}


//Funciones
void selectOption() {

  int SW = digitalRead(13);
  if (SW == false) {
    delay (30);
    SW = digitalRead(13);
    if (SW == true) {
      menu.call_function(1);

    }
  }
}

void fn_play() {

  static long ultimo_cambio = 0;
  long hora;

  int fila = 1;
  int pala;
  
  int puntuacion = 0;

  while (fila > -1) {

    hora = millis();
    if (hora - ultimo_cambio > 150) {
      ultimo_cambio = hora;

      pala = PosicionPala ();
      fila = MovimientoBola (pala);
      
      if (fila == 1)
        puntuacion++;
        
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.write("Puntuacion:");
        lcd.setCursor(11, 0);
        lcd.print(puntuacion);
    }
  }

  GameOver (puntuacion);
}

int PosicionPala () {

  static int pala = 3;
  int Y = analogRead(A1);           // lectura de valor de eje y del joystick

  lc.setLed(0, 0, pala - 1, false);
  lc.setLed(0, 0, pala, false);
  lc.setLed(0, 0, pala + 1, false);

  if (Y >= 0 && Y < 200 && pala > 1) {      // si el joystick se acciona hacia abajo
    pala--;                                 // la pala baja
  }

  if (Y > 800 && Y <= 1023 && pala < 6) {   // si el joystick se acciona hacia arriba
    pala++;                                 // la pala sube
  }

  lc.setLed(0, 0, pala - 1, true);
  lc.setLed(0, 0, pala, true);
  lc.setLed(0, 0, pala + 1, true);

  return (pala);
}

int MovimientoBola (int pala) {

  static int fila = 1;
  static int columna = 3;

  static int direccion_vertical = 0;
  static int direccion_horizontal = -1;


  if (fila == -1) {
    fila = 1;
    columna = 3;
    direccion_horizontal = 1;
    direccion_vertical = 0;
  }

  lc.setLed(0, fila, columna, false); //Apaga el led de la bola

  if (columna > 1 && columna < 6) {  //Apaga la pala del oponente
    lc.setRow(0, 7, B00000000);
  }

  if (columna == 0 || columna == 7) { //Rebote con las paredes
    direccion_vertical = -direccion_vertical;
  }


  if (fila == 1) { //Rebote de la bola con la pala del jugador
    if (columna == pala) { //Rebote horizontal si la bola da en el centro de la pala
      direccion_horizontal = 1;
      direccion_vertical = 0;
    }

    else if (columna == pala + 1 || columna == pala - 1) { //Rebote diagonal si la bola da en los extremos de la pala
      direccion_horizontal = 1;

      if (direccion_vertical == 0) {
        direccion_vertical = columna - pala;

        if (columna == 0 || columna == 7) { //Rebote con las paredes
          direccion_vertical = -direccion_vertical;
        }
      }
    }

    //Rebote con el borde de la pala
    else if ((columna == pala + 2 && direccion_vertical == -1) ||
             (columna == pala - 2 && direccion_vertical == 1)) {
      direccion_vertical = -direccion_vertical;
      direccion_horizontal = 1;

      if (columna == 0 || columna == 7) { //Rebote con las paredes
        direccion_vertical = -direccion_vertical;
      }
    }
  }

  if (fila == 6) { //Rebote de la bola con la pala oponente
    direccion_horizontal = -1;
    direccion_vertical = random(-1, 2);

    if ((columna == 0 && direccion_vertical == -1) || 
        (columna == 7 && direccion_vertical == 1)) { //Caso particular rebote en esquinas
      direccion_vertical = -direccion_vertical;
    }
  }

  //Asignacion de los nuevos valores a la posicion de la bola dependiendo de su direccion
  fila += direccion_horizontal;
  columna += direccion_vertical;


  lc.setLed(0, fila, columna, true); //Vuelve a encender el led de la bola en su nueva posicion

  lc.setLed(0, 7, columna - 1, true);
  lc.setLed(0, 7, columna, true);     //Enciende la pala del oponente
  lc.setLed(0, 7, columna + 1, true);

  return (fila);
}

void GameOver (int puntuacion) {

  int i;
  for (i = 7; i >= 0; i--) {
    lc.setColumn(0, i, B11111111);
    delay(100);
  }
  

  archivo = SD.open("puntuacion.txt", FILE_WRITE);

  if (archivo) {
    archivo.println(puntuacion);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write("Guardando puntuacion");
    delay(1000);
    
    archivo.close();
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write("Completado");
    delay(1000);
  } 
  
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write("Error guardado");
    lcd.setCursor(0, 1);
    lcd.write("puntuacion");
    delay(1000);
  }
  
  
  for (i = 7; i >= 0; i--) {
    lc.setColumn(0, i, B00000000);
    delay(100);
  }
  menu.change_screen(1);    //Vuelve al menu de jugadores
  menu.set_focusedLine(0);
}
