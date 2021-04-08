#include <LiquidCrystal.h>
#include <LiquidMenu.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int X;
int Y;
int PULSADOR = 23;
int SW;


LiquidLine linea1(1, 0, "Elegir Jugador");
LiquidLine linea2(1, 1, "Controles");
LiquidLine linea3(1, 0, "Puntuaciones");
LiquidScreen pantalla1(linea1, linea2, linea3);

LiquidLine linea1_1(1, 0, "Santi");
LiquidLine linea1_2(1, 1, "Jose");
LiquidLine linea1_3(1, 0, "Pablo");
LiquidLine linea1_4(1, 1, "Atras");
LiquidScreen pantalla2(linea1_1, linea1_2, linea1_3, linea1_4);

LiquidLine linea2_1(1, 0, "Atras");
LiquidScreen pantalla3(linea2_1);

LiquidLine linea3_1(1, 0, "Santi");
LiquidLine linea3_2(1, 1, "Jose");
LiquidLine linea3_3(1, 0, "Pablo");
LiquidLine linea3_4(1, 1, "Highest Score");
LiquidLine linea3_5(1, 0, "Atras");
LiquidScreen pantalla4(linea3_1, linea3_2, linea3_3, linea3_4);

LiquidMenu menu(lcd, pantalla1, pantalla2, pantalla3, pantalla4);


void setup() {
  pinMode(PULSADOR, INPUT);

  lcd.begin(16, 2);


  linea1.set_focusPosition(Position::LEFT);
  linea2.set_focusPosition(Position::LEFT);
  linea3.set_focusPosition(Position::LEFT);

  linea1.attach_function(1, fn_jugador);
  linea2.attach_function(1, fn_controles);
  linea3.attach_function(1, fn_puntuaciones);

  menu.add_screen(pantalla1);


  linea1_1.set_focusPosition(Position::LEFT);
  linea1_2.set_focusPosition(Position::LEFT);
  linea1_3.set_focusPosition(Position::LEFT);
  linea1_4.set_focusPosition(Position::LEFT);

  linea1_1.attach_function(1, fn_santij);
  linea1_2.attach_function(1, fn_josej);
  linea1_3.attach_function(1, fn_pabloj);
  linea1_4.attach_function(1, fn_atras);

  menu.add_screen(pantalla2);


  linea2_1.set_focusPosition(Position::LEFT);

  linea2_1.attach_function(1, fn_atras);

  menu.add_screen(pantalla3);


  linea3_1.set_focusPosition(Position::LEFT);
  linea3_2.set_focusPosition(Position::LEFT);
  linea3_3.set_focusPosition(Position::LEFT);
  linea3_4.set_focusPosition(Position::LEFT);
  linea3_5.set_focusPosition(Position::LEFT);

  linea3_1.attach_function(1, fn_santip);
  linea3_2.attach_function(1, fn_josep);
  linea3_3.attach_function(1, fn_pablop);
  linea3_4.attach_function(1, fn_hs);
  linea3_5.attach_function(1, fn_atras);

  menu.add_screen(pantalla4);


  pantalla1.set_displayLineCount(2);
  pantalla2.set_displayLineCount(2);
  pantalla3.set_displayLineCount(2);
  pantalla4.set_displayLineCount(2);

  menu.set_focusedLine(0);

  menu.update();

}


void loop() {
  X = analogRead(A0);            // lectura de valor de eje x
  Y = analogRead(A1);           // lectura de valor de eje y
  SW = digitalRead(PULSADOR);   // lectura pulsador

  delay(200);
  seleccionar();

  if (X >= 0 && X <= 100) {       // si el joystick se acciona hacia arriba
    menu.switch_focus(false);     // el menu sube
  }

  if (X >= 900 && X <= 1023) {    // si el joystick se acciona hacia abajo
    menu.switch_focus(true);      // el menu baja
  }

  menu.update();
}


//Funciones
void seleccionar() {

  if (SW == false) {
    delay (30);
    SW = digitalRead(PULSADOR);
    if (SW == true) {
      menu.call_function(1);
      //      delay(500);
    }
  }
}

void fn_atras() {
  menu.change_screen(1);
  menu.set_focusedLine(0);
}

void fn_jugador() {
  menu.change_screen(2);
  menu.set_focusedLine(0);
}

void fn_controles() {
  menu.change_screen(3);
  menu.set_focusedLine(0);
}

void fn_puntuaciones() {
  menu.change_screen(4);
  menu.set_focusedLine(0);
}

void fn_santij() {
  menu.change_screen(1);
  menu.set_focusedLine(0);
}

void fn_josej() {
  menu.change_screen(1);
  menu.set_focusedLine(0);
}

void fn_pabloj() {
  menu.change_screen(1);
  menu.set_focusedLine(0);
}

void fn_santip() {
  menu.change_screen(1);
  menu.set_focusedLine(0);
}

void fn_josep() {
  menu.change_screen(1);
  menu.set_focusedLine(0);
}

void fn_pablop() {
  menu.change_screen(1);
  menu.set_focusedLine(0);
}

void fn_hs() {
  menu.change_screen(1);
  menu.set_focusedLine(0);
}
