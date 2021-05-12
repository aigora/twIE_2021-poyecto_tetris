#include <LiquidCrystal.h>
#include <LiquidMenu.h>
#include <LedControl.h>

LedControl lc=LedControl (8,9,10,1);

LiquidCrystal lcd(2,3,4,5,6,7);

int X;
int Y;
int PULSADOR = 13;
int SW;


//Definición de las distintas pantallas y sus correspondientes lineas dentro del menu
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
  

//Asignación de funciones a cada linea del menu
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
  
  static long ultimo_cambio = 0; 
  long hora;
  
  int fila = 1;

  int columna = 3;
  
  int direccion_vertical = 0;  //Valores aleatorios entre -1, 0 y 1
  int direccion_horizontal = -1; //Valores alternos de -1 y 1
  
  int pala = 3;
  
  int puntuacion=-1;
  
  while (fila > -1) {
    
    hora = millis();
    if (hora - ultimo_cambio > 150) {
      ultimo_cambio = hora;
    
    
       
      Y = analogRead(A1);           // lectura de valor de eje y
  
    
      lc.setLed(0,0,pala-1,false);
      lc.setLed(0,0,pala,false);
      lc.setLed(0,0,pala+1,false);

      if (Y >= 0 && Y < 200 && pala > 1){         // si Y esta en la zona izquierda
        pala--;
      } 
  
      if (Y > 800 && Y <= 1023 && pala < 6){      // si Y esta en la zona derecha
        pala++;
      } 
  
      lc.setLed(0,0,pala-1,true);
      lc.setLed(0,0,pala,true);
      lc.setLed(0,0,pala+1,true);
    
    
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.write("Puntuacion:");
      lcd.setCursor(11,0);
      lcd.print(puntuacion);
    
      lc.setLed(0,fila,columna,false);
    
      if (columna > 1 && columna < 6) {  //Barra que sigue el movimiento de la bola
        lc.setRow(0,7,B00000000);
      }
    
    
      if (fila == 1) { //Rebote de la bola con la pala del jugador
        if (columna == pala) { //Rebote horizontal si la bola da en el centro de la pala
          direccion_horizontal = 1;
          direccion_vertical = 0;
        }
       
        if (columna == pala+1 || columna == pala-1) { //Rebote diagonal si la bola da en los extremos de la pala
          direccion_horizontal = 1;
          if (direccion_vertical == 0) {
            direccion_vertical = columna - pala;
            
            if (columna == 0 || columna == 7) { //Arreglo temporal
              direccion_vertical = -direccion_vertical;
            }
          }
        }
      
        //Casos particulares y rebote en esquinas
        if (((pala < 5 && columna == pala+2 || pala == 2 && columna == 0) && direccion_vertical == -1) || 
            ((pala > 2 && columna == pala-2 || pala == 5 && columna == 7) && direccion_vertical == 1)) {
          direccion_vertical = -direccion_vertical;
          direccion_horizontal = 1;
        }

        puntuacion++;
      }

    
      if (fila == 6) { //Rebote de la bola con la pala oponente
        direccion_horizontal = -1;
        direccion_vertical = random(-1,2);
        
        if ((columna == 0 && direccion_vertical == -1) || (columna == 7 && direccion_vertical == 1)) { //Caso particular en las esquinas
          direccion_vertical = -direccion_vertical;
        }
      }
    
      if ((columna == 0 || columna == 7) && (fila != 1 && fila != 6)) { //Rebote con las paredes
        direccion_vertical = -direccion_vertical;
      }
    
        
      if (direccion_horizontal == 1) { //Unir condiciones
        fila++;
      }
    
      if (direccion_horizontal == -1) {
        fila--;
      }
    
    
      if (direccion_vertical == 1) {
        columna++;
      }
    
      if (direccion_vertical == -1) {
        columna--;
      } 
    
    
      lc.setLed(0,fila,columna,true);
    
      lc.setLed(0,7,columna-1,true); 
      lc.setLed(0,7,columna,true); 
      lc.setLed(0,7,columna+1,true);
    }
  } 
      
        lc.clearDisplay(0);
    
        int i;
        for (i = 7; i >= 0; i--) {
          lc.setColumn(0,i,B11111111);
          delay(100);
        }
    
        lc.clearDisplay (0);
        menu.change_screen(1);
        menu.set_focusedLine(0);
      
  
}
