#include <LiquidCrystal.h>
#include <LiquidMenu.h>
#include <LedControl.h>

LedControl lc = LedControl (8, 9, 10, 1);

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);


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
  pinMode(13, INPUT);

  lc.shutdown (0, false);
  lc.setIntensity (0, 5); // intensidad 0-15
  lc.clearDisplay (0);

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

  lcd.setCursor(0, 0);
  lcd.write("Elegir jugador");

  int SW = digitalRead(13);

  while (SW == true) {
    SW = digitalRead(13);
    delay(5);
  }

  lcd.clear();
  menu.update();
}


void loop() {
  int Y = analogRead(A1);      // lectura de valor de eje y
  int SW = digitalRead(13);   // lectura pulsador

  static long ultimo_cambio = 0;
  long hora;

  selectOption();

  hora = millis();
  if (hora - ultimo_cambio > 200) {
    ultimo_cambio = hora;
    if (Y >= 900 && Y <= 1023) {      // si el joystick se acciona hacia arriba
      menu.switch_focus(false);     // el menu sube
    }

    if (Y >= 0 && Y <= 100) {      // si el joystick se acciona hacia abajo
      menu.switch_focus(true);      // el menu baja
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

void fn_restart() {
  fn_play();
}


void fn_play() {

  static long ultimo_cambio = 0;
  long hora;

  int fila = 1;
  int pala;

  while (fila > -1) {

    hora = millis();
    if (hora - ultimo_cambio > 150) {
      ultimo_cambio = hora;

      pala = PosicionPala ();
      fila = MovimientoBola (pala);
    }
  }

  GameOver ();
}

int PosicionPala () {

  static int pala = 3;
  int Y = analogRead(A1);           // lectura de valor de eje y

  lc.setLed(0, 0, pala - 1, false);
  lc.setLed(0, 0, pala, false);
  lc.setLed(0, 0, pala + 1, false);

  if (Y >= 0 && Y < 200 && pala > 1) {          // si Y esta en la zona izquierda
    pala--;
  }

  if (Y > 800 && Y <= 1023 && pala < 6) {     // si Y esta en la zona derecha
    pala++;
  }

  lc.setLed(0, 0, pala - 1, true);
  lc.setLed(0, 0, pala, true);
  lc.setLed(0, 0, pala + 1, true);

  return (pala);
}

int MovimientoBola (int pala) {

  static int fila = 1;
  static int columna = 3;

  static int direccion_vertical = 0;  //Valores aleatorios entre -1, 0 y 1
  static int direccion_horizontal = -1; //Valores alternos de -1 y 1

  static int puntuacion = -1;

  if (fila == -1) {
    fila = 1;
    columna = 3;
    direccion_horizontal = 1;
    direccion_vertical = 0;
    puntuacion = -1;
  }

  lc.setLed(0, fila, columna, false);

  if (columna > 1 && columna < 6) {  //Barra que sigue el movimiento de la bola
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

    if (columna == pala + 1 || columna == pala - 1) { //Rebote diagonal si la bola da en los extremos de la pala
      direccion_horizontal = 1;

      if (direccion_vertical == 0) {
        direccion_vertical = columna - pala;

        if (columna == 0 || columna == 7) { //Rebote con las paredes
          direccion_vertical = -direccion_vertical;
        }
      }
    }


    //Rebote con el borde de la pala
    if ((columna == pala + 2 && direccion_vertical == -1) ||
        (columna == pala - 2 && direccion_vertical == 1)) {
      direccion_vertical = -direccion_vertical;
      direccion_horizontal = 1;

      if (columna == 0 || columna == 7) { //Rebote con las paredes
        direccion_vertical = -direccion_vertical;
      }
    }

    puntuacion++;
  }

  if (fila == 6) { //Rebote de la bola con la pala oponente
    direccion_horizontal = -1;
    direccion_vertical = random(-1, 2);

    if ((columna == 0 && direccion_vertical == -1) || (columna == 7 && direccion_vertical == 1)) { //Caso particular rebote en esquinas
      direccion_vertical = -direccion_vertical;
    }
  }


  fila += direccion_horizontal;
  columna += direccion_vertical;


  lc.setLed(0, fila, columna, true);

  lc.setLed(0, 7, columna - 1, true);
  lc.setLed(0, 7, columna, true);
  lc.setLed(0, 7, columna + 1, true);


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("Puntuacion:");
  lcd.setCursor(11, 0);
  lcd.print(puntuacion);


  return (fila);
}

void GameOver () {

  lc.clearDisplay(0);

  int i;
  for (i = 7; i >= 0; i--) {
    lc.setColumn(0, i, B11111111);
    delay(100);
  }

  lc.clearDisplay (0);
  menu.change_screen(1);
  menu.set_focusedLine(0);
}
