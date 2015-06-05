#include <Servo.h> 
//Mugbot Project Tokyo City University Koike Lab. 2014  
//Mugbot System ver. 1.0.0.
//English notes by Hans Chun using Google Translate

Servo eye_servo;
Servo head_servo;

static int pos = 0; //Rotation angle of the servo
static int g = 0; //Position of the Web interface slider
char ch=0;


int l_mouse=7; //Mouth LED left side (as viewed from the front)
int m_mouse=8; //Mouth center LED
int r_mouse=9; //Mouth LED right side

int l_eye=11; //Left eye (as viewed from the front)
int r_eye=13; //Right eye

//Setting the position of the eyes (head)
int eye_default = 90; //Set the forward (center) eye position
int eye_min = 75; //Set the minimum (lowest?) position of the eye
int eye_max = 105; //Set the maximum (highest?) position of the eye

//Setting the position of the neck (head)
int head_default = 90; //Set the forward (center) position of the neck
int head_min = 0; //Set the minimum (left-most?) angle of the neck
int head_max = 180; //Set the maximum (right-most?) angle of the neck

int eye_light_default = 50; //Set the default brightness value of the eye

void setup()
{   
   Serial.begin(9600);

   eye_servo.attach(2); //The low and high of the servo eyes
   head_servo.attach(4); //Left and right of the servo neck

//Initialize eye, neck and brightness settings
   pinMode(l_eye, OUTPUT);    
   pinMode(r_eye, OUTPUT);  
   pinMode(l_mouse, OUTPUT);  
   pinMode(m_mouse, OUTPUT);   
   pinMode(r_mouse, OUTPUT);  


   analogWrite(l_eye, eye_light_default);
   analogWrite(r_eye, eye_light_default);
   digitalWrite(l_mouse, LOW);
   digitalWrite(m_mouse, LOW);
   digitalWrite(r_mouse, LOW); 
   eye_servo.write(eye_default);   
   head_servo.write(head_default );
}

void loop(){
  if(Serial.available()>0){
     ch = Serial.read();
	 
    //Input received from Raspberry Pi.
    switch(ch) {
      case '0'...'9':
        g = g * 10 + ch - '0';
        //For example,'100X' is read one character at a time from the Raspberry Pi
        //The digits 1,0,0 are read in sequence and '100' is stored in the variable.
 
      break;
     
      case 'x':
        //Move the neck side to side.
        head_servo.write( g );
        //Then changing the angle of a servo 100, which enters the variable g to load a x.
        //I have no idea what the above note means. ^^^
		delay( 15 );      
        g=0;
            //g reset to 0
      break;
 
      case 'y': //Move the eyes up and down.
        eye_servo.write( g );
          delay( 15 );
        g=0;
      break;
     
      case 'z': //Modulate the brightness of the eye.
        analogWrite(l_eye,g);
        analogWrite(r_eye,g);
          delay( 15 );
        g=0;
      break;

      case 't': //Mouth blink/start talking. Ends with 'n'.
            delay( 2000 );
        digitalWrite(l_mouse, HIGH);
        digitalWrite(m_mouse, HIGH);
        digitalWrite(r_mouse, HIGH);
            
        for ( pos = eye_default; pos < 110; pos += 1 ) {
          eye_servo.write( pos );
            delay( 15 );        
        } ;
  
        for ( pos = 110; pos > 80; pos -= 1 ) {
          eye_servo.write( pos );
            delay( 15 );
        } ;

        for ( pos = 80; pos < eye_default; pos += 1 ) {
          eye_servo.write( pos );
            delay( 15 );
        } ;         
      break;

      case 'n': //Reset to defaults/stop talking(paired with 't')
        analogWrite(l_eye, eye_light_default);
        analogWrite(r_eye, eye_light_default);
        digitalWrite(r_mouse, LOW);
        digitalWrite(l_mouse, LOW);
        digitalWrite(m_mouse, LOW);

        eye_servo.write(eye_default); 
        head_servo.write(head_default); 
      break;
          
      case 'l': //"Laughing" expression
        analogWrite(l_eye, eye_light_default);
        analogWrite(r_eye, eye_light_default);
         
        digitalWrite(l_mouse, HIGH);
        digitalWrite(m_mouse, HIGH);
        digitalWrite(r_mouse, HIGH);
        eye_servo.write( 120 );
            delay(100 );
        eye_servo.write( 100 );
            delay(100 ); 
        eye_servo.write( 120 );
            delay(100 );
        eye_servo.write( 100 );
            delay(100 ); 
        eye_servo.write( 120 );
            delay(100 );
        eye_servo.write( 100 );
            delay(100 ); 
        eye_servo.write( 120 );
            delay(100 );
        eye_servo.write( 100 );
            delay(100 ); 
        eye_servo.write( 120 );
            delay(100 );
        eye_servo.write( 100 );
            delay(100 ); 
        eye_servo.write( 120 );
            delay(100 );
        eye_servo.write( 100 );
            delay(100 ); 
        eye_servo.write( 120 );
            delay(100 );
        eye_servo.write( 100 );
            delay(100 ); 
        eye_servo.write( 120 );
            delay(100 );
        eye_servo.write( eye_default );
            delay(100 );
        digitalWrite(r_mouse, LOW);
        digitalWrite(l_mouse, LOW);
        digitalWrite(m_mouse, LOW);                  
      break;
 
      case 's': //"Sad" expression
        for ( pos = eye_default; pos > 70; pos -= 1 ) {
          eye_servo.write( pos );
          delay( 15 );
        } ;        
         
        for ( pos = eye_light_default; pos > 20; pos -= 1 ) {
          analogWrite(l_eye, pos);
          analogWrite(r_eye, pos);
            delay( 10);
        } ; 
        eye_servo.write(eye_default);
        head_servo.write(head_default);

        analogWrite(l_eye, eye_light_default);
        analogWrite(r_eye, eye_light_default);
        digitalWrite(r_mouse, LOW);
        digitalWrite(l_mouse, LOW);
        digitalWrite(m_mouse, LOW);
      break;

      case 'h': //"Yes" expression
        analogWrite(l_eye, eye_light_default);
        analogWrite(r_eye, eye_light_default);

        for ( pos = eye_default; pos > 70; pos -= 1 ) {
          eye_servo.write( pos );
            delay( 15 );
        } ;

        for ( pos = 70; pos < eye_default; pos += 1 ) {
          eye_servo.write( pos );
            delay( 15 );
          eye_servo.write( pos );
            delay( 15 );
        } ;       
 
        for ( pos =eye_default; pos > 70; pos -= 1 ) {
          eye_servo.write( pos );
            delay( 15 );  
        } ;

        for ( pos = 70; pos < eye_default; pos += 1 ) {
          eye_servo.write( pos );
            delay( 15 );
          eye_servo.write( pos );
            delay( 15 );
        } ;          
      break;
 
      case 'f': //"No" expression
        analogWrite(l_eye, eye_light_default);
        analogWrite(r_eye, eye_light_default);

        for ( pos = 85; pos < 135; pos += 1 ) {
          head_servo.write( pos );
            delay( 15 );
        } ;
  
        for ( pos = 135; pos > 55; pos -= 1 ) {
          head_servo.write( pos );
            delay( 15 );
        } ;

        for ( pos = 55; pos < 85; pos += 1 ) {
          head_servo.write( pos );
            delay( 15 );
        } ;     
      break;
       
      case 'w': //"Wink" expression
        analogWrite(l_eye, eye_light_default);
        digitalWrite(r_eye, LOW);
          delay( 500 );
        analogWrite(l_eye, eye_light_default);
        analogWrite(r_eye, eye_light_default);
          delay( 500 );
        digitalWrite(l_eye,LOW);
        analogWrite(r_eye, eye_light_default);
          delay( 500 );
        analogWrite(l_eye, eye_light_default);
        analogWrite(r_eye, eye_light_default);
      break;

      case 'b': //"Suprised" expression
        for ( pos = eye_default; pos < 105; pos += 1 ) {
          eye_servo.write( pos );
          delay( 15 );
        } ; 
        analogWrite(l_eye, 250);
        analogWrite(r_eye, 250);
          delay( 350 );
        analogWrite(l_eye, eye_light_default);
        analogWrite(r_eye, eye_light_default);
          delay( 100 );
        eye_servo.write(eye_default);
          delay( 100 );
      break;
              
      case 'e': //"Anxious?" "Stressed?" expression
        for ( ch = 0; ch <5; ch += 1 ) {         
          digitalWrite(l_mouse, HIGH);
          digitalWrite(m_mouse, HIGH);
          digitalWrite(r_mouse, HIGH);
            
          analogWrite(l_eye, eye_light_default);
          digitalWrite(r_eye, LOW);
            delay( 100 );
          digitalWrite(l_eye, LOW);
          analogWrite(r_eye, eye_light_default);
            delay( 100 ); 
          eye_servo.write(random(eye_default,110) );   
          head_servo.write(random(25,135) ); 
            delay( 100 ); 
          analogWrite(l_eye, eye_light_default);
          analogWrite(r_eye, eye_light_default);
            delay( 100 );  
          digitalWrite(l_mouse, LOW);
          digitalWrite(m_mouse, LOW);
          digitalWrite(r_mouse, LOW);  
            delay( 100 ); 
        }          
           
        eye_servo.write(eye_default);
        head_servo.write(head_default);

        analogWrite(l_eye, eye_light_default);
        analogWrite(r_eye, eye_light_default);
        digitalWrite(r_mouse, LOW);
        digitalWrite(l_mouse, LOW);
        digitalWrite(m_mouse, LOW);
      break;  

      default:
        eye_servo.write(eye_default);
        head_servo.write(head_default);

        analogWrite(l_eye, eye_light_default);
        analogWrite(r_eye, eye_light_default);
        digitalWrite(r_mouse, LOW);
        digitalWrite(l_mouse, LOW);
        digitalWrite(m_mouse, LOW);
      break;
    }
  }
}
