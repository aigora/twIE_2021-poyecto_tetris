#include <LiquidCrystal.h>
#include <LiquidMenu.h>
#include <LedControl.h>

LedControl lc=LedControl (8,9,10,1);

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int X;
int Y;
int PULSADOR = 13;
int SW;

int puntuacion=0;


LiquidLine linea1(1, 0, "Elegir Jugador");
//LiquidLine linea2(1, 1, "Controles");
LiquidLine linea3(1, /*0*/1, "Puntuaciones");
LiquidScreen pantalla1(linea1, /*linea2,*/ linea3);

LiquidLine linea1_1(1, 0, "Santi");
LiquidLine linea1_2(1, 1, "Jose");
LiquidLine linea1_3(1, 0, "Pablo");
LiquidLine linea1_4(1, 1, "Atras");
LiquidScreen pantalla2(linea1_1, linea1_2, linea1_3, linea1_4);
/*
LiquidLine linea2_1(1, 0, "Atras");
LiquidScreen pantalla3(linea2_1);
*/
LiquidLine linea3_1(1, 0, "Santi");
LiquidLine linea3_2(1, 1, "Jose");
LiquidLine linea3_3(1, 0, "Pablo");
LiquidLine linea3_4(1, 1, "Highest Score");
LiquidLine linea3_5(1, 0, "Atras");
LiquidScreen pantalla4(linea3_1, linea3_2, linea3_3, linea3_4/*, linea3_5*/);

LiquidLine linea4_1(1, 0, "Reanudar");
LiquidLine linea4_2(1, 1, "Volver a empezar");
LiquidLine linea4_3(1, 0, "Salir");
LiquidScreen pantalla5(linea4_1, linea4_2, linea4_3);

LiquidMenu menu(lcd, pantalla1, pantalla2, /*pantalla3,*/ pantalla4, pantalla5);


void setup() {
  pinMode(PULSADOR, INPUT);
  
  lc.shutdown (0, false);
  lc.setIntensity (0,5); // intensidad 0-15
  lc.clearDisplay (0);
  
  lcd.begin(16, 2);
  
  randomSeed(analogRead(A15));
  

  linea1.set_focusPosition(Position::LEFT); 
//  linea2.set_focusPosition(Position::LEFT); 
  linea3.set_focusPosition(Position::LEFT); 
   
  linea1.attach_function(1, fn_jugador); 
//  linea2.attach_function(1, fn_controles);
  linea3.attach_function(1, fn_puntuaciones);
  
  menu.add_screen(pantalla1);
  

  linea1_1.set_focusPosition(Position::LEFT); 
  linea1_2.set_focusPosition(Position::LEFT); 
  linea1_3.set_focusPosition(Position::LEFT); 
  linea1_4.set_focusPosition(Position::LEFT); 
  
  linea1_1.attach_function(1, fn_play); 
  linea1_2.attach_function(1, fn_play);
  linea1_3.attach_function(1, fn_play);
  linea1_4.attach_function(1, fn_atras);
   
  menu.add_screen(pantalla2);
  
/*
  linea2_1.set_focusPosition(Position::LEFT);
  
  linea2_1.attach_function(1,fn_atras);
  
  menu.add_screen(pantalla3);
*/

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
  
  linea4_1.set_focusPosition(Position::LEFT); 
  linea4_2.set_focusPosition(Position::LEFT); 
  linea4_3.set_focusPosition(Position::LEFT); 
   
  linea4_1.attach_function(1, fn_play); 
  linea4_2.attach_function(1, fn_restart);
  linea4_3.attach_function(1, fn_atras);
  
  menu.add_screen(pantalla5);


  pantalla1.set_displayLineCount(2);
  pantalla2.set_displayLineCount(2);
//  pantalla3.set_displayLineCount(2);
  pantalla4.set_displayLineCount(2);
  pantalla5.set_displayLineCount(2);
  
  menu.set_focusedLine(0);

  menu.update();
}


void loop() {
  Y = analogRead(A1);            // lectura de valor de eje y
  SW = digitalRead(PULSADOR);   // lectura pulsador
  
  delay(200);
  selectOption();

  if (Y >= 900 && Y <= 1023){     // si el joystick se acciona hacia arriba
    menu.switch_focus(false);     // el menu sube
  } 
  
  if (Y >= 0 && Y <= 100){        // si el joystick se acciona hacia abajo
    menu.switch_focus(true);      // el menu baja
  } 
  
    menu.update();
}


//Funciones
void selectOption(){
  
  if (SW == false){
  delay (30);
    SW = digitalRead(PULSADOR); 
    if (SW == true){
      menu.call_function(1);
//      delay(500);
    }
  }
} 

void fn_atras(){
  menu.change_screen(1);
  menu.set_focusedLine(0);
}

void fn_jugador(){
  menu.change_screen(2);
  menu.set_focusedLine(0);
}
/*
void fn_controles(){
  menu.change_screen(3);
  menu.set_focusedLine(0);
}
*/
void fn_puntuaciones(){
  menu.change_screen(/*4*/3);
  menu.set_focusedLine(0);
}

void fn_santip(){
  menu.change_screen(1);
  menu.set_focusedLine(0);
}

void fn_josep(){
  menu.change_screen(1);
  menu.set_focusedLine(0);
}

void fn_pablop(){
  menu.change_screen(1);
  menu.set_focusedLine(0);
}

void fn_hs(){
  menu.change_screen(1);
  menu.set_focusedLine(0);
}

void fn_restart(){
  fn_play();
}


void fn_play(){

  while (SW == true){
    SW = digitalRead(PULSADOR);
  
    PosicionBarra();
    MovimientoBola();
  }
  
  lc.clearDisplay (0);
  menu.change_screen(/*5*/4);
  menu.set_focusedLine(0);
}


void PosicionBarra() {
  
  static long ultimo_cambio = 0; 
  long hora = millis();
  
  if (hora - ultimo_cambio > 200) {
    ultimo_cambio = hora;
  
    Y = analogRead(A1);           // lectura de valor de eje y
  
    static int columna = 3;


    lc.setLed(0,0,columna-1,false);
    lc.setLed(0,0,columna,false);
    lc.setLed(0,0,columna+1,false);

   if (Y >= 0 && Y < 200 && columna > 1){         // si Y esta en la zona izquierda
     columna--;
   } 
  
   if (Y > 800 && Y <= 1023 && columna < 6){      // si Y esta en la zona derecha
     columna++;
   } 
  
   lc.setLed(0,0,columna-1,true);
   lc.setLed(0,0,columna,true);
   lc.setLed(0,0,columna+1,true);
  }
}

void MovimientoBola(){
  
  static long ultimo_cambio = 0; 
  long hora = millis();
  
  static int fila_actual = 1;
  static int ultima_fila;

  static int columna_actual = 3;
  static int ultima_columna;
  
  int direccion_aleatoria;


  if (hora - ultimo_cambio > 200) {
    ultimo_cambio = hora;
    

    lc.setLed(0,ultima_fila,ultima_columna,false);
    lc.setLed(0,fila_actual,columna_actual,true); 
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(puntuacion);
    
    if (columna_actual != 0 && columna_actual != 7) {  //Barra que sigue el movimiento de la bola
      lc.setLed(0,7,ultima_columna-1,false);
      lc.setLed(0,7,ultima_columna,false);
      lc.setLed(0,7,ultima_columna+1,false);
    
      lc.setLed(0,7,columna_actual-1,true); 
      lc.setLed(0,7,columna_actual,true); 
      lc.setLed(0,7,columna_actual+1,true); 
    }
    
    //Movimiento horizontal de la bola
    if ((fila_actual > ultima_fila || fila_actual == 1) && fila_actual != 6) {
      ultima_fila = fila_actual;
      fila_actual++;
    }
    
    else if ((fila_actual < ultima_fila || fila_actual == 6) && fila_actual != 1) {
      ultima_fila = fila_actual;
      fila_actual--;
    }
    
    //Movimiento vertical aleatorio de la bola
    if (ultima_fila == 1 || ultima_fila == 6) {
      direccion_aleatoria = random(-1,2);
    }
    
    if (ultima_fila == 1) {
      puntuacion++;
    }
    
    if (columna_actual == 0 || columna_actual == 7) {
      direccion_aleatoria = -direccion_aleatoria;
    }
    
    if (columna_actual == 0 && (ultima_fila == 1 || ultima_fila == 6)){
      direccion_aleatoria = random(0,2);
    }
    
    if (columna_actual == 7 && (ultima_fila == 1 || ultima_fila == 6)){
      direccion_aleatoria = random(-1,1);
    }
    
    if (direccion_aleatoria == 1) {
      ultima_columna = columna_actual;
      columna_actual++;
    }
    
    else if (direccion_aleatoria == -1) {
      ultima_columna = columna_actual;
      columna_actual--;
    }
    
    else {
      ultima_columna = columna_actual;
    }
  }
}
