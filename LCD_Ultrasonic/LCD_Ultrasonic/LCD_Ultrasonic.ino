#include <LiquidCrystal.h> //This librarey is insatlled by default along with IDE
#include <hcrs04.h> // this library is for the ultrasonic sensor
#include <time.h>

// interface the LCD
#define RS 40
#define EN 39
#define D4 38
#define D5 37
#define D6 36
#define D7 35
int rows = 2;
int columns = 16;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7); //Let the librarey know how we have connected the LCD

// interface the Ultrasonic sensor
#define PINTRIG 5
#define PINECHO 6
hcrs04 mySensor(PINTRIG, PINECHO);

// LCD Messages
char welcome[] = "Welcome to our Smart Mirror!";
char message1[] = "Have a good day!";
char message2[] = "You look beautiful today :)";
char message3[] = "Hey good looking ;)";
int randomNumber = 0;
const int max = 120;
float DISTANCE_MIN = 20.00;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); /* Define baud rate for serial communication */
  Serial.println("Basic HC-SR04 Ultrasonic Sensor Example");
  mySensor.begin(); /* Initialize the sensor */
  

  lcd.begin(columns, rows); 
  lcd.setCursor (0,0); //Place the cursor at 1st row 1st column 
  scrollMessage(welcome, sizeof(welcome), columns); //Display a intro message
  delay(1000);
  lcd.clear(); //Then clean it
  

 }

void loop() {
  // put your main code here, to run repeatedly: 
   //Get results from the sensor
  float DISTANCE = mySensor.read(); /* Read the distance value */
  Serial.print("Distance : ");
  Serial.print(DISTANCE);
  Serial.println(" cm"); 
  delay(200);
  
  if (DISTANCE > DISTANCE_MIN) {
      lcd.setCursor(0, 1);   // set the cursor to column 0, line 1
      
      // choose random message
      srand(millis());
      randomNumber = 1 + rand() % max;
      Serial.print("Random number: ");
      Serial.println(randomNumber);
      
      if (randomNumber <= 40) {
        scrollMessage(message1, sizeof(message1), columns);
      }
      else if (randomNumber <= 80) {
        scrollMessage(message2, sizeof(message2), columns);
        
      }
      else if (randomNumber <= 120) {
        scrollMessage(message3, sizeof(message3), columns);
      }
  }
  delay(500);
}

void scrollMessage(char array[], int arraySize, int columns){
    int messageScroll = (arraySize / columns) - 1;
    if (messageScroll < 0)
        messageScroll = 0;
    int remainderScroll = arraySize % columns;
    
    lcd.print(array);
    delay(1000);
    for (int i = 1; i < (messageScroll*columns + remainderScroll); i++) {
        lcd.scrollDisplayLeft();
        delay(600);
    }
    delay(1000);
    lcd.clear();
}
