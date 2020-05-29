
enum keys{
Escape=0x29,
F01=0x3A,F02=0x3B,F03=0x3C,F04=0x3D,F05=0x3E,F06=0x3F,F07=0x40,F08=0x41,F9=0x42,F10=0x43,F11=0x44,F12=0x45,
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Backquote=0x35,
Digit1=0x1E,Digit2=0x1F,Digit3=0x20,Digit4=0x21,Digit5=0x22,Digit6=0x23,Digit7=0x24,Digit8=0x25,Digit9=0x26,Digit0=0x27,
Minus=0x2D,Equal=0x2E,Backspace=0x2A,
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Tab=0x2B,
KeyQ=0x14,KeyW=0x1A,KeyE=0x08,KeyR=0x15,KeyT=0x17,KeyY=0x1C,KeyU=0x18,KeyI=0x0C,KeyO=0x12,KeyP=0x13,
BracketLeft=0x2F,BracketRight=0x30,Backslash=0x31,
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Capslock=0x39,
keyA=0x04,keyS=0x16,keyD=0x07,keyF=0x09,keyG=0x0A,keyH=0x0B,keyJ=0x0D,keyK=0x0E,keyL=0x0F,
Semicolon=0x33,Quote=0x34,Enter=0x28,
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ShiftLeft=0x02,
keyZ=0x1D,keyX=0x1B,keyC=0x06,keyV=0x19,keyB=0x05,keyN=0x11,keyM=0x10,
Comma=0x36,Period=0x37,Slash=0x38,
ShiftRight=0x20,
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ControlLeft=0x01,MetaLeft=0x08,AltLeft=0x04,Space=0x2C,AltRight=0x40,ContextMenu=0x65,ControlRight=0x10,MetaRight=0x80,
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PrintScreen=0x46,ScrollLock=0x47,Pause=0x48,
Insert=0x49,Home=0x4A,PageUp=0x4B,
Delete=0x4C,End=0x4D,PageDown=0x4E,
ArrowUp=0x52,
ArrowLeft=0x50,ArrowDown=0x51,ArrowRight=0x4F,
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NumLock=0x53,NumpadDivide=0x54,NumpadMultiply=0x55,NumpadSubtract=0x56,
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Numpad7=0x5F,Numpad8=0x60,Numpad9=0x61,
NumpadAdd=0x57,
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Numpad4=0x5C,Numpad5=0x5D,Numpad6=0x5E,
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Numpad1=0x59,Numpad2=0x5A,Numpad3=0x5B,
NumpadEnter=0x58,
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Num0Numpad0=0x62,
NumpadDecimal=0x63
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};








const int keyPin = 7; //the number of the key pin
const int ledPin = 13;//the number of the led pin
void setup() {
  pinMode(keyPin,INPUT);//initialize the key pin as input 
  pinMode(ledPin,OUTPUT);//initialize the led pin as output
  Serial.begin(9600);
}

void keyHit(bool ctrl,bool alt,bool shift,bool meta,byte key1,byte key2,byte key3,byte key4,byte key5,byte key6){
  unsigned char sum=0;
  unsigned char d[]={
    0x57,0xAB,// 头
    0x00,     // 地址码
    0x02,     // CMD
    0x08,     // 后续长度
      ctrl ?0b00000001:0b00000000|   // 右Win,右Alt,右Shift,右Ctrl,左Win,左Alt,左Shift,左Ctrl
      shift?0b00000010:0b00000000|
      alt  ?0b00000100:0b00000000|
      meta ?0b00001000:0b00000000,
      0x00,   // 必须为 0x00
      key1,   // 普通按键值(CH9329 键码表)
      key2,   // 普通按键值
      key3,   // 普通按键值
      key4,   // 普通按键值
      key5,   // 普通按键值
      key6,   // 普通按键值
  //0x10,     // 累加和
  };
  for(int i=0;i<sizeof(d);i++){
    sum+=d[i];
    Serial.print((char)d[i]);
  }
  Serial.print((char)sum);
}

bool _press=false;
void loop() {
  // Serial.read();

  bool press=false;
  if(HIGH==digitalRead(keyPin)) {
    digitalWrite(ledPin,LOW);
  }
  else
  {
    digitalWrite(ledPin,HIGH);
    press=true;
  }
  
  if(_press!=press){
      keyHit( false,//ctrl,
              false,//alt,
              false,//shift,
              false,//meta,
              
              press?KeyI:0,//key1,
              0,//key2,
              0,//key3,
              0,//key4,
              0,//key5,
              0//key6
              );
      _press=press;
  }

  //delay(1000);

}
