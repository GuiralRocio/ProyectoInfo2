import processing.serial.*;
import controlP5.*;
Serial myPort;  // Crea objecto desde la clase Serial 
ControlP5 cp5;  // Crea objeto desde la clase control
PImage img; 
PImage Alto;
ArrayList<String> data = new ArrayList<String>();  // Lista para almacenar los datos
boolean isLoading = false;  // Variable para rastrear el estado de carga
int loadProgress = 0;  // Variable para rastrear el progreso de carga
String receivedData = "";  // Variable para rastrear el dato recibido
String val; 

void setup() {
  size(800, 400);  // Tamaño de pantalla 
   img = loadImage("img.jpeg");  
   Alto = loadImage("alto.png");  
    String Puerto=Serial.list()[0];
   myPort = new Serial(this, Puerto, 9600);  // Abre el puerto al que esta conectado arduino
   myPort.clear();
  myPort.bufferUntil('\n');
  cp5 = new ControlP5(this);  // Crea una nueva instancia de control

  // Crea botones para up, down, left, right
  cp5.addButton("up")
   .setValue(0)
   .setPosition(150, 100)
   .setSize(50, 50)
   .setCaptionLabel("F");

  cp5.addButton("down")
   .setValue(0)
   .setPosition(150, 200)
   .setSize(50, 50)
   .setCaptionLabel("B");

  cp5.addButton("left")
   .setValue(0)
   .setPosition(100, 150)
   .setSize(50, 50)
   .setCaptionLabel("L");

  cp5.addButton("right")
   .setValue(0)
   .setPosition(200, 150)
   .setSize(50, 50)
   .setCaptionLabel("R");

  // Crea un boton para guardar un archivo en el centro de la pantalla
  cp5.addButton("save")
   .setValue(0)
   .setPosition(width/2 + 150, height/2 + 130)
   .setSize(100, 50)
   .setCaptionLabel("Guardar");
}

void draw() {
  background(20);  // Establece el fondo en blanco
   fill(255, 0, 0);  // Red color
   image(img, 0, 0, width/2, height);

  // Dibuja un rectangulo en el lado derecho de la pantalla de otro color
  fill(#C2D3ED);  // Blue color
  rect(width/2, 0, width/2, height);
  if (keyPressed) {
    if (key == CODED) {
      if (keyCode == UP) {
        cp5.getController("up").setColorBackground(color(255,0,0));
         myPort.write('F');
      } else if (keyCode == DOWN) {
        cp5.getController("down").setColorBackground(color(255,0,0));
         myPort.write('B');
      } else if (keyCode == LEFT) {
        cp5.getController("left").setColorBackground(color(255,0,0));
         myPort.write('L');
      } else if (keyCode == RIGHT) {
        cp5.getController("right").setColorBackground(color(255,0,0));
         myPort.write('R');
      }
      myPort.clear();
    }
  }
  
  // Dibuja la barra de carga si se está cargando
  if (isLoading) {
    fill(255);
    rect(width/2 + 100, height/2 + 80, 200, 20);  // Cambia la posición a arriba del botón "Guardar"
    fill(0, 255, 0);
    rect(width/2 +100, height/2 + 80, loadProgress * 2, 20);  // Cambia la posición a arriba del botón "Guardar"
    fill(0);
    text("Cargando...", width/2+170, height/2 + 95);  // Cambia la posición a arriba del botón "Guardar"
    
    // Incrementa el progreso de carga
    loadProgress++;
    if (loadProgress > 100) {
      isLoading = false;
      loadProgress = 0;
      }
    }
    
  // Dibuja un cartel que dice "Alto" si se recibe un dato desde el puerto serie
   if ( myPort.available() > 0) { 
     char a = myPort.readChar();
    print(a);
    val = myPort.readString();
    print(val);
    data.add(val);  // Almacena los datos recibidos en la lista
    switch (a){
     case 'u': // Calcula las coordenadas del centro de la pantalla
      int centerX = width / 2;
      int centerY = height / 2;

      // Define el tamaño de la imagen
      int imgWidth = 220;  // Cambia esto por el ancho que desees
      int imgHeight = 220;  // Cambia esto por la altura que desees

      // Calcula las coordenadas para centrar la imagen
      int imgX = centerX - imgWidth / 2+200;
      int imgY = centerY - imgHeight / 2-60;

      // Dibuja la imagen
      image(Alto, imgX, imgY, imgWidth, imgHeight);
      delay(1);
      break;
      }
    }
   }


void keyReleased() {
  if (key == CODED) {
    if (keyCode == UP) {
      cp5.getController("up").setColorBackground(color(0,0,255));  // Cambia el color del botón a azul
      myPort.write('S');
    } else if (keyCode == DOWN) {
      cp5.getController("down").setColorBackground(color(0,0,255));  // Cambia el color del botón a azul
      myPort.write('S');
    } else if (keyCode == LEFT) {
      cp5.getController("left").setColorBackground(color(0,0,255));  // Cambia el color del botón a azul
      myPort.write('S');
    } else if (keyCode == RIGHT) {
      cp5.getController("right").setColorBackground(color(0,0,255));  // Cambia el color del botón a azul
       myPort.write('S');
    }
  }
  myPort.clear();
}

 
// Función que se llama cuando se presiona el botón "Guardar"
void save() {
   // Inicia la carga
    isLoading = true;
  String[] dataArr = data.toArray(new String[data.size()]);  // Convierte la lista a un array
  saveStrings("data.txt", dataArr);  // Guarda el array en un archivo
  
  data.clear();  // Limpia la lista para el próximo guardado
}


