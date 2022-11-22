#include <Keypad.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <Ethernet.h>
LiquidCrystal lcd(8,9,4,5,6,7);

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(169, 254, 160, 151);
EthernetServer server(80);

int led = 13;
int InGate = 52;
int OutGate = 50;
int CarCount = 0;
int EmptySlots = 5;
int GreenLed = 48;
int RedLed = 46; 
// --------------TEMP----------------------
float temp;
int tempPin = A1;
// ---------------Motor connections -------------
int enA = 44;
int in1 = 42;
int in2 = 40;
//-------------------KEYPAD-------------------------
int My_Password = 1234;
int pad_int = 0;
String pad;
const byte numRows= 4;
const byte numCols= 4;
char keymap[numRows][numCols]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};
byte rowPins[numRows] = {28, 26, 24, 22};
byte colPins[numCols] = {36, 34, 32, 30};
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols); //mapping keypad
// --------------------------------------------------------------------------------------------------------------- Function Password
int Func_Keypad() {
  while(pad.length() < 4){
      char keypressed = myKeypad.getKey(); 
      String konv = String(keypressed);
      pad+=konv;
      pad_int = pad.toInt();

  }

  return pad_int;
}
// --------------------------------------------------------------------------------------------------------------- Void setup
void setup() {
  // put your setup code here, to run once:

lcd.begin(16,2);
lcd.setCursor(0,0);
pinMode (led, OUTPUT);
pinMode (GreenLed, OUTPUT);
pinMode (RedLed, OUTPUT);
pinMode (InGate, INPUT);
pinMode (OutGate, INPUT);
pinMode (enA, OUTPUT);
pinMode (in1, OUTPUT);
pinMode (in2, OUTPUT);
  // Turn off motors - Initial state
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);

Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ethernet WebServer Example");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

// --------------------------------------------------------------------------------------------------------------- Void LOOP
void loop() {
// Turn off the motor initially
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);

if (EmptySlots > 0){
  lcd.print("Empty Slots: ");
  lcd.print(EmptySlots);
  digitalWrite(GreenLed , HIGH);
  digitalWrite(RedLed , LOW);
}
//---------------------------------------------------------------
if (EmptySlots == 0){
  lcd.print("Sorry! No Slots");
  digitalWrite(RedLed , HIGH);
  digitalWrite(GreenLed , LOW);
}
//------------------------CAR IN---------------------------------------
if ((digitalRead(InGate) == HIGH)&(EmptySlots > 0)){
  
  // Check the Password (1234)
  lcd.clear();
  lcd.print("Pass: ");

  if (Func_Keypad() == My_Password){
    lcd.print(pad_int);
    delay(500);
    lcd.clear();
    lcd.print("Correct!");
  

    // Turn on the motor
    analogWrite(enA, 255);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);  
    delay(2000);
    // Turn off the motor
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  
    CarCount = CarCount + 1;
    EmptySlots = EmptySlots - 1;
    pad_int = 0; // set the password to zero every new loop
    pad = "";
  }
}
//---------------------------CAR OUT------------------------------------
if ((digitalRead(OutGate) == HIGH)&(CarCount > 0)){
  // Turn on the motor
  analogWrite(enA, 255);
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW);  
  delay(2000);
  // Turn off the motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  CarCount = CarCount - 1;
  EmptySlots = EmptySlots + 1;

}
//---------------------------Temperature------------------------------------
temp = analogRead(tempPin);
   // read analog volt from sensor and save to variable temp
temp = temp * 0.260; //0.2890
lcd.setCursor(0, 1);
lcd.print("Temprature: ");
lcd.print(temp);
//---------------------------------------------------------------
delay(500);
lcd.clear();

EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          
          // output the value of each analog input pin
          
            
            client.println("WELCOME TO THE COOLEST PROJECT !!");
            client.println("<br />");
            client.println("Number of possible slots = 5");
            client.println("<br />");
            client.print("Empty Slots: ");
            client.println(EmptySlots);
            client.println("<br />");
            client.print("Number of Cars in the Parking: ");
            client.println(CarCount);
            client.println("<br />");
            client.print("Temperature: ");
            client.print(temp);
            client.println("<br />");
          
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
