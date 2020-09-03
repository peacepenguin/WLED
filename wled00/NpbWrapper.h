//this code is a modified version of https://github.com/Makuna/NeoPixelBus/issues/103
#ifndef NpbWrapper_h
#define NpbWrapper_h

//PIN CONFIGURATION
#ifndef LEDPIN
#define LEDPIN 2  //strip pin. Any for ESP32, gpio2 or 3 is recommended for ESP8266 (gpio2/3 are labeled D4/RX on NodeMCU and Wemos)
#endif
//#define USE_APA102  // Uncomment for using APA102 LEDs.
//#define USE_WS2801  // Uncomment for using WS2801 LEDs (make sure you have NeoPixelBus v2.5.6 or newer)
//#define USE_LPD8806 // Uncomment for using LPD8806
//#define USE_TM1814  // Uncomment for using TM1814 LEDs (make sure you have NeoPixelBus v2.5.7 or newer)
//#define USE_P9813   // Uncomment for using P9813 LEDs (make sure you have NeoPixelBus v2.5.8 or newer)
//#define WLED_USE_ANALOG_LEDS //Uncomment for using "dumb" PWM controlled LEDs (see pins below, default R: gpio5, G: 12, B: 15, W: 13)
//#define WLED_USE_H801 //H801 controller. Please uncomment #define WLED_USE_ANALOG_LEDS as well
//#define WLED_USE_5CH_LEDS  //5 Channel H801 for cold and warm white
//#define WLED_USE_BWLT11
//#define WLED_USE_SHOJO_PCB

#ifndef BTNPIN
#define BTNPIN  0  //button pin. Needs to have pullup (gpio0 recommended)
#endif

#ifndef IR_PIN
#define IR_PIN -1 //infrared pin (-1 to disable)  MagicHome: 4, H801 Wifi: 0
#endif

#ifndef RLYPIN
#define RLYPIN -1  //pin for relay, will be set HIGH if LEDs are on (-1 to disable). Also usable for standby leds, triggers,...
#endif

#ifndef AUXPIN
#define AUXPIN -1  //debug auxiliary output pin (-1 to disable)
#endif

#ifndef RLYMDE
#define RLYMDE  1  //mode for relay, 0: LOW if LEDs are on 1: HIGH if LEDs are on
#endif

// How many strips will be connected:
#define NUM_STRIPS 2

// What pins to use:
#define STRIP1_PIN LEDPIN  // first strip uses same pin as default LEDPIN output pin for whatever platform is being used.
#define STRIP2_PIN 13
#define STRIP3_PIN 12
#define STRIP4_PIN 14
#define STRIP5_PIN 27
#define STRIP6_PIN 26
#define STRIP7_PIN 25
#define STRIP8_PIN 33

// How many LEDs are on each strip:
#define STRIP1_LEDCOUNT 54
#define STRIP2_LEDCOUNT 18
#define STRIP3_LEDCOUNT 18
#define STRIP4_LEDCOUNT 18
#define STRIP5_LEDCOUNT 18
#define STRIP6_LEDCOUNT 18
#define STRIP7_LEDCOUNT 18
#define STRIP8_LEDCOUNT 18

// What pixelmethod to use on each strip?
#define STRIP1_PIXELMETHOD NeoEsp32Rmt0Ws2812xMethod    // the board specific PIXELMETHOD variable is being ignored now, so make sure it's set here!
#define STRIP2_PIXELMETHOD NeoEsp32Rmt1Ws2812xMethod    // define what method you want to use to drive the extra pins. For esp32 RMT 0-7 works best.
#define STRIP3_PIXELMETHOD NeoEsp32Rmt2Ws2812xMethod
#define STRIP4_PIXELMETHOD NeoEsp32Rmt3Ws2812xMethod
#define STRIP5_PIXELMETHOD NeoEsp32Rmt4Ws2812xMethod
#define STRIP6_PIXELMETHOD NeoEsp32Rmt5Ws2812xMethod
#define STRIP7_PIXELMETHOD NeoEsp32Rmt6Ws2812xMethod
#define STRIP8_PIXELMETHOD NeoEsp32Rmt7Ws2812xMethod


//END CONFIGURATION

// do calculations to find the  starting LED index position of each strip:
#define STRIP1_STARTLED 0
#define STRIP2_STARTLED STRIP1_STARTLED + STRIP1_LEDCOUNT
#define STRIP3_STARTLED STRIP2_STARTLED + STRIP2_LEDCOUNT
#define STRIP4_STARTLED STRIP3_STARTLED + STRIP3_LEDCOUNT
#define STRIP5_STARTLED STRIP4_STARTLED + STRIP4_LEDCOUNT
#define STRIP6_STARTLED STRIP5_STARTLED + STRIP5_LEDCOUNT
#define STRIP7_STARTLED STRIP6_STARTLED + STRIP6_LEDCOUNT
#define STRIP8_STARTLED STRIP7_STARTLED + STRIP7_LEDCOUNT
#define STRIP9_STARTLED STRIP8_STARTLED + STRIP8_LEDCOUNT // using this for calculation of strip8's end led

// calculate the ending LED index of each strip:
#define STRIP1_ENDLED STRIP2_STARTLED - 1
#define STRIP2_ENDLED STRIP3_STARTLED - 1
#define STRIP3_ENDLED STRIP4_STARTLED - 1
#define STRIP4_ENDLED STRIP5_STARTLED - 1
#define STRIP5_ENDLED STRIP6_STARTLED - 1
#define STRIP6_ENDLED STRIP7_STARTLED - 1
#define STRIP7_ENDLED STRIP8_STARTLED - 1
#define STRIP8_ENDLED STRIP9_STARTLED - 1




// find the total number of LEDs available in the physical system by reusing the math done above, then do strip 8 math
#if NUM_STRIPS == 1
#define NUM_LEDS STRIP2_STARTLED
#endif

#if NUM_STRIPS == 2
#define NUM_LEDS STRIP3_STARTLED
#endif

#if NUM_STRIPS == 3
#define NUM_LEDS STRIP4_STARTLED
#endif

#if NUM_STRIPS == 4
#define NUM_LEDS STRIP5_STARTLED
#endif

#if NUM_STRIPS == 5
#define NUM_LEDS STRIP6_STARTLED
#endif

#if NUM_STRIPS == 6
#define NUM_LEDS STRIP7_STARTLED
#endif

#if NUM_STRIPS == 7
#define NUM_LEDS STRIP8_STARTLED
#endif

#if NUM_STRIPS == 8
#define NUM_LEDS STRIP8_STARTLED + STRIP8_LEDCOUNT
#endif


//END calculations

#if defined(USE_APA102) || defined(USE_WS2801) || defined(USE_LPD8806) || defined(USE_P9813)
 #ifndef CLKPIN
  #define CLKPIN 0
 #endif
 #ifndef DATAPIN
  #define DATAPIN 2
 #endif
 #if BTNPIN == CLKPIN || BTNPIN == DATAPIN
  #undef BTNPIN   // Deactivate button pin if it conflicts with one of the APA102 pins.
 #endif
#endif

#ifdef WLED_USE_ANALOG_LEDS
  //PWM pins - PINs 15,13,12,14 (W2 = 04)are used with H801 Wifi LED Controller
  #ifdef WLED_USE_H801
    #define RPIN 15   //R pin for analog LED strip   
    #define GPIN 13   //G pin for analog LED strip
    #define BPIN 12   //B pin for analog LED strip
    #define WPIN 14   //W pin for analog LED strip 
    #define W2PIN 04  //W2 pin for analog LED strip
    #undef BTNPIN
    #undef IR_PIN
    #define IR_PIN  0 //infrared pin (-1 to disable)  MagicHome: 4, H801 Wifi: 0
  #elif defined(WLED_USE_BWLT11)
  //PWM pins - to use with BW-LT11
    #define RPIN 12  //R pin for analog LED strip
    #define GPIN 4   //G pin for analog LED strip
    #define BPIN 14  //B pin for analog LED strip
    #define WPIN 5   //W pin for analog LED strip
  #elif defined(WLED_USE_SHOJO_PCB)
  //PWM pins - to use with Shojo PCB (https://www.bastelbunker.de/esp-rgbww-wifi-led-controller-vbs-edition/)
    #define RPIN 14  //R pin for analog LED strip
    #define GPIN 4   //G pin for analog LED strip
    #define BPIN 5   //B pin for analog LED strip
    #define WPIN 15  //W pin for analog LED strip
    #define W2PIN 12 //W2 pin for analog LED strip
  #elif defined(WLED_USE_PLJAKOBS_PCB)
  // PWM pins - to use with esp_rgbww_controller from patrickjahns/pljakobs (https://github.com/pljakobs/esp_rgbww_controller)
    #define RPIN 12  //R pin for analog LED strip
    #define GPIN 13  //G pin for analog LED strip
    #define BPIN 14  //B pin for analog LED strip
    #define WPIN 4   //W pin for analog LED strip
    #define W2PIN 5  //W2 pin for analog LED strip
    #undef IR_PIN
  #else
  //PWM pins - PINs 5,12,13,15 are used with Magic Home LED Controller
    #define RPIN 5   //R pin for analog LED strip
    #define GPIN 12  //G pin for analog LED strip
    #define BPIN 15  //B pin for analog LED strip
    #define WPIN 13  //W pin for analog LED strip
  #endif
  #undef RLYPIN
  #define RLYPIN -1 //disable as pin 12 is used by analog LEDs
#endif

//automatically uses the right driver method for each platform
#ifdef ARDUINO_ARCH_ESP32
 #ifdef USE_APA102
  #define PIXELMETHOD DotStarMethod
 #elif defined(USE_WS2801)
  #define PIXELMETHOD NeoWs2801Method
 #elif defined(USE_LPD8806)
  #define PIXELMETHOD Lpd8806Method
 #elif defined(USE_TM1814)
  #define PIXELMETHOD NeoTm1814Method  
 #elif defined(USE_P9813)
  #define PIXELMETHOD P9813Method  
 #else
  #define PIXELMETHOD NeoEsp32Rmt0Ws2812xMethod
 #endif
#else //esp8266
 //autoselect the right method depending on strip pin
 #ifdef USE_APA102
  #define PIXELMETHOD DotStarMethod
 #elif defined(USE_WS2801)
  #define PIXELMETHOD NeoWs2801Method
 #elif defined(USE_LPD8806)
  #define PIXELMETHOD Lpd8806Method
 #elif defined(USE_TM1814)
  #define PIXELMETHOD NeoTm1814Method  
 #elif defined(USE_P9813)
  #define PIXELMETHOD P9813Method  
 #elif LEDPIN == 2
  #define PIXELMETHOD NeoEsp8266Uart1Ws2813Method //if you get an error here, try to change to NeoEsp8266UartWs2813Method or update Neopixelbus
 #elif LEDPIN == 3
  #define PIXELMETHOD NeoEsp8266Dma800KbpsMethod
 #else
  #define PIXELMETHOD NeoEsp8266BitBang800KbpsMethod
  #pragma message "Software BitBang will be used because of your selected LED pin. This may cause flicker. Use GPIO 2 or 3 for best results."
 #endif
#endif


//you can now change the color order in the web settings
#ifdef USE_APA102
 #define PIXELFEATURE3 DotStarBgrFeature
 #define PIXELFEATURE4 DotStarLbgrFeature
#elif defined(USE_LPD8806)
 #define PIXELFEATURE3 Lpd8806GrbFeature 
#elif defined(USE_WS2801)
 #define PIXELFEATURE3 NeoRbgFeature
 #define PIXELFEATURE4 NeoRbgFeature
#elif defined(USE_TM1814)
  #define PIXELFEATURE3 NeoWrgbTm1814Feature
  #define PIXELFEATURE4 NeoWrgbTm1814Feature
#elif defined(USE_P9813)
 #define PIXELFEATURE3 P9813BgrFeature 
 #define PIXELFEATURE4 NeoGrbwFeature   
#else
 #define PIXELFEATURE3 NeoGrbFeature
 #define PIXELFEATURE4 NeoGrbwFeature
#endif


#include <NeoPixelBrightnessBus.h>

enum NeoPixelType
{
  NeoPixelType_None = 0,
  NeoPixelType_Grb  = 1,
  NeoPixelType_Grbw = 2,
  NeoPixelType_End  = 3
};

class NeoPixelWrapper
{
public:
  NeoPixelWrapper() :
    // initialize each member to null
    _pGrb(NULL),     // strip1
    #if NUM_STRIPS > 1
      _pGrb2(NULL),  // strip2
    #endif
    #if NUM_STRIPS > 2
      _pGrb3(NULL),  // strip3
    #endif
    #if NUM_STRIPS > 3
      _pGrb4(NULL),  // strip4
    #endif
    #if NUM_STRIPS > 4
      _pGrb5(NULL),  // strip5
    #endif
    #if NUM_STRIPS > 5
      _pGrb6(NULL),  // strip6
    #endif
    #if NUM_STRIPS > 6
      _pGrb7(NULL),  // strip7
    #endif
    #if NUM_STRIPS > 7
      _pGrb8(NULL),  // strip8
    #endif
    _pGrbw(NULL),
    _type(NeoPixelType_None)
  {

  }

  ~NeoPixelWrapper()
  {
    cleanup();
  }

  void Begin(NeoPixelType type, uint16_t countPixels)
  {
    cleanup();
    _type = type;

    switch (_type)
    {
      case NeoPixelType_Grb:
      #if defined(USE_APA102) || defined(USE_WS2801) || defined(USE_LPD8806) || defined(USE_P9813)
        _pGrb = new NeoPixelBrightnessBus<PIXELFEATURE3,PIXELMETHOD>(countPixels, CLKPIN, DATAPIN);
      #else
        _pGrb = new NeoPixelBrightnessBus<PIXELFEATURE3,STRIP1_PIXELMETHOD>(STRIP1_LEDCOUNT, STRIP1_PIN);     // strip1
        _pGrb->Begin();  // strip1
        #if NUM_STRIPS > 1
          _pGrb2 = new NeoPixelBrightnessBus<PIXELFEATURE3, STRIP2_PIXELMETHOD>(STRIP2_LEDCOUNT, STRIP2_PIN); // strip2
          _pGrb2->Begin(); // strip2
        #endif
        #if NUM_STRIPS > 2
          _pGrb3 = new NeoPixelBrightnessBus<PIXELFEATURE3, STRIP3_PIXELMETHOD>(STRIP3_LEDCOUNT, STRIP3_PIN); // strip3
          _pGrb3->Begin(); // strip3
        #endif
        #if NUM_STRIPS > 3
          _pGrb4 = new NeoPixelBrightnessBus<PIXELFEATURE3, STRIP4_PIXELMETHOD>(STRIP4_LEDCOUNT, STRIP4_PIN); // strip4
          _pGrb4->Begin(); // strip4
        #endif
        #if NUM_STRIPS > 4
          _pGrb5 = new NeoPixelBrightnessBus<PIXELFEATURE3, STRIP5_PIXELMETHOD>(STRIP5_LEDCOUNT, STRIP5_PIN); // strip5
          _pGrb5->Begin(); // strip5
        #endif
        #if NUM_STRIPS > 5
          _pGrb6 = new NeoPixelBrightnessBus<PIXELFEATURE3, STRIP6_PIXELMETHOD>(STRIP6_LEDCOUNT, STRIP6_PIN); // strip6
          _pGrb6->Begin(); // strip6
        #endif
        #if NUM_STRIPS > 6
          _pGrb7 = new NeoPixelBrightnessBus<PIXELFEATURE3, STRIP7_PIXELMETHOD>(STRIP7_LEDCOUNT, STRIP7_PIN); // strip7
          _pGrb7->Begin(); // strip7
        #endif
        #if NUM_STRIPS > 7
          _pGrb8 = new NeoPixelBrightnessBus<PIXELFEATURE3, STRIP8_PIXELMETHOD>(STRIP8_LEDCOUNT, STRIP8_PIN); // strip8
          _pGrb8->Begin(); // strip8
        #endif
      #endif
      break;

      case NeoPixelType_Grbw:
      #if defined(USE_APA102) || defined(USE_WS2801) || defined(USE_LPD8806) || defined(USE_P9813)
        _pGrbw = new NeoPixelBrightnessBus<PIXELFEATURE4,PIXELMETHOD>(countPixels, CLKPIN, DATAPIN);
      #else
        _pGrbw = new NeoPixelBrightnessBus<PIXELFEATURE4,PIXELMETHOD>(countPixels, LEDPIN);
      #endif
        _pGrbw->Begin();
      break;
    }

    #ifdef WLED_USE_ANALOG_LEDS 
      #ifdef ARDUINO_ARCH_ESP32
        ledcSetup(0, 5000, 8);
        ledcAttachPin(RPIN, 0);
        ledcSetup(1, 5000, 8);
        ledcAttachPin(GPIN, 1);
        ledcSetup(2, 5000, 8);        
        ledcAttachPin(BPIN, 2);
        if(_type == NeoPixelType_Grbw) 
        {
          ledcSetup(3, 5000, 8);        
          ledcAttachPin(WPIN, 3);
          #ifdef WLED_USE_5CH_LEDS
            ledcSetup(4, 5000, 8);        
            ledcAttachPin(W2PIN, 4);
          #endif
        }
      #else  // ESP8266
        //init PWM pins
        pinMode(RPIN, OUTPUT);
        pinMode(GPIN, OUTPUT);
        pinMode(BPIN, OUTPUT); 
        if(_type == NeoPixelType_Grbw) 
        {
          pinMode(WPIN, OUTPUT); 
          #ifdef WLED_USE_5CH_LEDS
            pinMode(W2PIN, OUTPUT);
          #endif
        }
        analogWriteRange(255);  //same range as one RGB channel
        analogWriteFreq(880);   //PWM frequency proven as good for LEDs
      #endif 
    #endif
  }

#ifdef WLED_USE_ANALOG_LEDS      
    void SetRgbwPwm(uint8_t r, uint8_t g, uint8_t b, uint8_t w, uint8_t w2=0)
    {
      #ifdef ARDUINO_ARCH_ESP32
        ledcWrite(0, r);
        ledcWrite(1, g);
        ledcWrite(2, b);
        switch (_type) {
          case NeoPixelType_Grb:                                                  break;
          #ifdef WLED_USE_5CH_LEDS
            case NeoPixelType_Grbw: ledcWrite(3, w); ledcWrite(4, w2);            break;
          #else
            case NeoPixelType_Grbw: ledcWrite(3, w);                              break;
          #endif
        }        
      #else   // ESP8266
        analogWrite(RPIN, r);
        analogWrite(GPIN, g);
        analogWrite(BPIN, b);
        switch (_type) {
          case NeoPixelType_Grb:                                                  break;
          #ifdef WLED_USE_5CH_LEDS
            case NeoPixelType_Grbw: analogWrite(WPIN, w); analogWrite(W2PIN, w2); break;
          #else
            case NeoPixelType_Grbw: analogWrite(WPIN, w);                         break;
          #endif
        }
      #endif 
    }
#endif

  void Show()
  {
    byte b;
    switch (_type)
    {
      case NeoPixelType_Grb:  {
        _pGrb->Show();     //strip1
        #if NUM_STRIPS > 1
          _pGrb2->Show();  //strip2
        #endif
        #if NUM_STRIPS > 2
          _pGrb3->Show();  //strip3
        #endif
        #if NUM_STRIPS > 3
          _pGrb4->Show();  //strip4
        #endif
        #if NUM_STRIPS > 4
          _pGrb5->Show();  //strip5
        #endif
        #if NUM_STRIPS > 5
          _pGrb6->Show();  //strip6
        #endif
        #if NUM_STRIPS > 6
          _pGrb7->Show();  //strip7
        #endif
        #if NUM_STRIPS > 7
          _pGrb8->Show();  //strip8
        #endif
        break;
      }
      case NeoPixelType_Grbw: _pGrbw->Show(); break;
    }
  }

  void SetPixelColor(uint16_t indexPixel, RgbwColor color)
  {
    switch (_type) {
      case NeoPixelType_Grb: {
        // using the preprocessor math variables, assign the color to the correct LED on the correct strip based on its index
        // calculate the strip specific location from the indexPixel provided, again re-using the math variables.
        switch (indexPixel) {
          case STRIP1_STARTLED ... STRIP1_ENDLED:
            _pGrb->SetPixelColor(indexPixel, RgbColor(color.R,color.G,color.B));
          break;
          #if NUM_STRIPS > 1
            case STRIP2_STARTLED ... STRIP2_ENDLED:
              _pGrb2->SetPixelColor((indexPixel -= STRIP2_STARTLED), RgbColor(color.R,color.G,color.B));
            break;
          #endif
          #if NUM_STRIPS > 2
            case STRIP3_STARTLED ... STRIP3_ENDLED:
              _pGrb3->SetPixelColor((indexPixel -= STRIP3_STARTLED), RgbColor(color.R,color.G,color.B));
            break;
          #endif
          #if NUM_STRIPS > 3
            case STRIP4_STARTLED ... STRIP4_ENDLED:
              _pGrb4->SetPixelColor((indexPixel -= STRIP4_STARTLED), RgbColor(color.R,color.G,color.B));
            break;
          #endif
          #if NUM_STRIPS > 4
            case STRIP5_STARTLED ... STRIP5_ENDLED:
              _pGrb5->SetPixelColor((indexPixel -= STRIP5_STARTLED), RgbColor(color.R,color.G,color.B));
            break;
          #endif
          #if NUM_STRIPS > 5
            case STRIP6_STARTLED ... STRIP6_ENDLED:
              _pGrb6->SetPixelColor((indexPixel -= STRIP6_STARTLED), RgbColor(color.R,color.G,color.B));
            break;
          #endif
          #if NUM_STRIPS > 6
            case STRIP7_STARTLED ... STRIP7_ENDLED:
              _pGrb7->SetPixelColor((indexPixel -= STRIP7_STARTLED), RgbColor(color.R,color.G,color.B));
            break;
          #endif
          #if NUM_STRIPS > 7
            case STRIP8_STARTLED ... STRIP8_ENDLED:
              _pGrb8->SetPixelColor((indexPixel -= STRIP8_STARTLED), RgbColor(color.R,color.G,color.B));
            break;
          #endif
        }
      }
      break;
      case NeoPixelType_Grbw: {
        #if defined(USE_LPD8806) || defined(USE_WS2801)
        _pGrbw->SetPixelColor(indexPixel, RgbColor(color.R,color.G,color.B));
        #else
        _pGrbw->SetPixelColor(indexPixel, color);
        #endif
      }
      break;
    }
    
  }

  void SetBrightness(byte b)
  {
    switch (_type) {
      case NeoPixelType_Grb: { 
        _pGrb->SetBrightness(b);     //strip1
        #if NUM_STRIPS > 1
          _pGrb2->SetBrightness(b);  //strip2
        #endif
        #if NUM_STRIPS > 2
          _pGrb3->SetBrightness(b);  //strip3
        #endif
        #if NUM_STRIPS > 3
          _pGrb4->SetBrightness(b);  //strip4
        #endif
        #if NUM_STRIPS > 4
          _pGrb5->SetBrightness(b);  //strip5
        #endif
        #if NUM_STRIPS > 5
          _pGrb6->SetBrightness(b);  //strip6
        #endif
        #if NUM_STRIPS > 6
          _pGrb7->SetBrightness(b);  //strip7
        #endif
        #if NUM_STRIPS > 7
          _pGrb8->SetBrightness(b);  //strip8
        #endif
        break;
      }
      case NeoPixelType_Grbw:_pGrbw->SetBrightness(b);  break;
    }
  }

  // NOTE:  Due to feature differences, some support RGBW but the method name
  // here needs to be unique, thus GetPixeColorRgbw
  RgbwColor GetPixelColorRgbw(uint16_t indexPixel) const
  {
    switch (_type) {
      case NeoPixelType_Grb: 
        switch (indexPixel) {
          case STRIP1_STARTLED ... STRIP1_ENDLED:
            return _pGrb->GetPixelColor(indexPixel);
            break;
          #if NUM_STRIPS > 1
            case STRIP2_STARTLED ... STRIP2_ENDLED:
              return _pGrb2->GetPixelColor((indexPixel -= STRIP2_STARTLED));
              break;
          #endif
          #if NUM_STRIPS > 2
            case STRIP3_STARTLED ... STRIP3_ENDLED:
              return _pGrb3->GetPixelColor((indexPixel -= STRIP3_STARTLED));
              break;
          #endif
          #if NUM_STRIPS > 3
            case STRIP4_STARTLED ... STRIP4_ENDLED:
              return _pGrb4->GetPixelColor((indexPixel -= STRIP4_STARTLED));
              break;
          #endif
          #if NUM_STRIPS > 4
            case STRIP5_STARTLED ... STRIP5_ENDLED:
              return _pGrb5->GetPixelColor((indexPixel -= STRIP5_STARTLED));
              break;
          #endif
          #if NUM_STRIPS > 5
            case STRIP6_STARTLED ... STRIP6_ENDLED:
              return _pGrb6->GetPixelColor((indexPixel -= STRIP6_STARTLED));
              break;
          #endif
          #if NUM_STRIPS > 6
            case STRIP7_STARTLED ... STRIP7_ENDLED:
              return _pGrb7->GetPixelColor((indexPixel -= STRIP7_STARTLED));
              break;
          #endif
          #if NUM_STRIPS > 7
            case STRIP8_STARTLED ... STRIP8_ENDLED:
              return _pGrb8->GetPixelColor((indexPixel -= STRIP8_STARTLED));
              break;
          #endif
        }
      case NeoPixelType_Grbw: return _pGrbw->GetPixelColor(indexPixel); break;
    }
    return 0;
  }

  uint8_t* GetPixels(void)  //ignoring this GetPixels function for now as this isn't used in WLED:
  {
    switch (_type) {
      case NeoPixelType_Grb:  return _pGrb->Pixels();  break;
      case NeoPixelType_Grbw: return _pGrbw->Pixels(); break;
    }
    return 0;
  }


private:
  NeoPixelType _type;

  // have a member for every possible type
  NeoPixelBrightnessBus<PIXELFEATURE3,PIXELMETHOD>*  _pGrb;                   //strip1
  #if NUM_STRIPS > 1
    NeoPixelBrightnessBus<PIXELFEATURE3,STRIP2_PIXELMETHOD>*  _pGrb2;  //strip2
  #endif
  #if NUM_STRIPS > 2
    NeoPixelBrightnessBus<PIXELFEATURE3,STRIP3_PIXELMETHOD>*  _pGrb3;  //strip3
  #endif
  #if NUM_STRIPS > 3
    NeoPixelBrightnessBus<PIXELFEATURE3,STRIP4_PIXELMETHOD>*  _pGrb4;  //strip4
  #endif
  #if NUM_STRIPS > 4
    NeoPixelBrightnessBus<PIXELFEATURE3,STRIP5_PIXELMETHOD>*  _pGrb5;  //strip5
  #endif
  #if NUM_STRIPS > 5
    NeoPixelBrightnessBus<PIXELFEATURE3,STRIP6_PIXELMETHOD>*  _pGrb6;  //strip6
  #endif
  #if NUM_STRIPS > 6
    NeoPixelBrightnessBus<PIXELFEATURE3,STRIP7_PIXELMETHOD>*  _pGrb7;  //strip7
  #endif
  #if NUM_STRIPS > 7
    NeoPixelBrightnessBus<PIXELFEATURE3,STRIP8_PIXELMETHOD>*  _pGrb8;  //strip8
  #endif
  NeoPixelBrightnessBus<PIXELFEATURE4,PIXELMETHOD>* _pGrbw;

  void cleanup()
  {
    switch (_type) {
      case NeoPixelType_Grb:  {
        delete _pGrb ; _pGrb  = NULL;    //strip1
        #if NUM_STRIPS > 1
          delete _pGrb2 ; _pGrb2  = NULL;  //strip2
        #endif
        #if NUM_STRIPS > 2
          delete _pGrb3 ; _pGrb3  = NULL;  //strip3
        #endif
        #if NUM_STRIPS > 3
          delete _pGrb4 ; _pGrb4  = NULL;  //strip4
        #endif
        #if NUM_STRIPS > 4
          delete _pGrb5 ; _pGrb5  = NULL;  //strip5
        #endif
        #if NUM_STRIPS > 5
          delete _pGrb6 ; _pGrb6  = NULL;  //strip6
        #endif
        #if NUM_STRIPS > 6
          delete _pGrb7 ; _pGrb7  = NULL;  //strip7
        #endif
        #if NUM_STRIPS > 7
          delete _pGrb8 ; _pGrb8  = NULL;  //strip8
        #endif
        break;
      }
      case NeoPixelType_Grbw: delete _pGrbw; _pGrbw = NULL; break;
    }
  }
};
#endif
