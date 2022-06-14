// basics
int16_t moduleType = 0;
int16_t rcType = 0;

//added by Mark Donners
bool InputSelect=AUDIO_INPUT_LINEIN; // Choose AUDIO_INPUT_MIC or AUDIO_INPUT_LINEIN

bool calibrate = false;
bool lockScreenUpdate = false;
bool flipScreen = false;
bool showCalibrationFrame = false;
bool DIGITAL_UseWheel = false;
bool DIGITAL_ShowHeader = true;
bool DIGITAL_ShowPeakBars = true;
bool FFT_UseWheel = true;
bool FFT_PeakHold = false;
bool DIGITAL_MenuActive = false;
bool ANALOG_MenuActive = false;
bool FFT_MenuActive = false;
bool GONIO_MenuActive = false;

// dB
float DIGITAL_dBLow = -40.0f;
float FFT_dBLow = -40.0f;
float GONIO_dBLow = -40.0f;
float dBHigh = 6.1f;
float dBRMSL = -100.0f;
float dBRMSR = -100.0f;
float dBPPML = -100.0f;
float dBPPMR = -100.0f;

// remotecontrol
uint32_t IR_Up = 2011287606;
uint32_t IR_Left = 2011238454;
uint32_t IR_Right = 2011291702;
uint32_t IR_Down = 2011279414;
uint32_t IR_PlayStop = 2011242550;
uint32_t IR_Menu = 2011250742;

// digital
uint16_t DIGITAL_SampleBlocks = 8;
uint16_t DIGITAL_dBnullPosition = 0;
bool DIGITAL_PeakHold = false;

// gonio
uint16_t GONIO_SampleBlocks = 8;
bool GONIO_PeakHold = false;

// A700Frame
bool DIGITAL_ShowA700Frame = false;
bool ANALOG_ShowA700Frame = false;
bool FFT_ShowA700Frame = false;
bool GONIO_ShowA700Frame = false;

// offset
uint16_t DIGITAL_Offset = 0;
uint16_t ANALOG_Offset = 0;
uint16_t FFT_Offset = 0;
uint16_t GONIO_Offset = 0;

// calibration
int RMSCorrectionLeft = 0;
int RMSCorrectionRight = 0;
int PPMCorrectionLeft = 0;
int PPMCorrectionRight = 0;

// mode
int16_t DIGITAL_WorkMode = 0;
int16_t ANALOG_Mode = 0;
int16_t FFT_WorkMode = 1;
int16_t FFT_BarMode = 3;
int16_t FFT_LevelBarMode = 0; // 0=peak, 1=vu
uint16_t GONIO_Samples = 0;
int16_t GONIO_WorkMode = 1;
uint16_t GONIO_BarMode = 0;  // 0=peak, 1=vu
int16_t GONIO_DrawMode = 0; //0=pixel, 1=lines
bool GONIO_ShowSamplesCount = true;
bool GONIO_SwapX = true;
bool GONIO_SwapY = true;

// peakAttenuation
float DIGITAL_PeakAttenuation = 0.0f;
float FFT_PeakAttenuation = 0.0f;
float GONIO_PeakAttenuation = 0.0f;

// ballistics
uint16_t DIGITAL_VUBarAttack = 4;
uint16_t DIGITAL_VUBarRelease = 2;
uint16_t DIGITAL_VUPeakHoldTime = 50;
uint16_t DIGITAL_VUPeakRelease = 2;
uint16_t DIGITAL_PEAKBarAttack = 18;
uint16_t DIGITAL_PEAKBarRelease = 2;
uint16_t DIGITAL_PEAKPeakHoldTime = 50;
uint16_t DIGITAL_PEAKPeakRelease = 2;

uint16_t ANALOG_NeedleAttack = 10;
uint16_t ANALOG_NeedleRelease = 10;
int16_t ANALOG_PeakLEDdB = 6;
uint16_t ANALOG_PeakLEDHoldTime = 500;

uint16_t FFT_VUBarAttack = 16;
uint16_t FFT_VUBarRelease = 2;
uint16_t FFT_VUPeakHoldTime = 50;
uint16_t FFT_VUPeakRelease = 2;
uint16_t FFT_PEAKBarAttack = 16;
uint16_t FFT_PEAKBarRelease = 2;
uint16_t FFT_PEAKPeakHoldTime = 50;
uint16_t FFT_PEAKPeakRelease = 2;
uint16_t FFT_FFTBarAttack = 12;
uint16_t FFT_FFTBarRelease = 3;
uint16_t FFT_FFTPeakHoldTime = 100;
uint16_t FFT_FFTPeakRelease = 1;

uint16_t GONIO_VUBarAttack = 16;
uint16_t GONIO_VUBarRelease = 2;
uint16_t GONIO_PEAKBarAttack = 16;
uint16_t GONIO_PEAKBarRelease = 2;
uint16_t GONIO_VUPeakHoldTime = 50;
uint16_t GONIO_PEAKPeakHoldTime = 50;
uint16_t GONIO_VUPeakRelease = 2;
uint16_t GONIO_PEAKPeakRelease = 2;

// segments
uint16_t DIGITAL_VUPeakHeight = 1;
uint16_t DIGITAL_VUSegmentHeight = 0;
uint16_t DIGITAL_PEAKPeakHeight = 5;
uint16_t DIGITAL_PEAKSegmentHeight = 1;
uint16_t FFT_VUPeakHeight = 5;
uint16_t FFT_VUSegmentHeight = 1;
uint16_t FFT_FFTPeakHeight = 1;
uint16_t FFT_FFTSegmentHeight = 0;
uint16_t GONIO_PeakHeight = 5;
uint16_t GONIO_SegmentHeight = 1;

// colors
uint16_t DIGITAL_DisplayBackColor = 0;                    // Black
uint16_t DIGITAL_LRColor = 0xF7BE;                        // WhiteSmoke
uint16_t DIGITAL_HeaderForeColor = 0xAD55;                // DarkGray
uint16_t DIGITAL_ScaleForeColor = 0xBDF7;                 // Gray
uint16_t DIGITAL_ScaleMarkerColor = 0xBDF7;               // Gray
uint16_t DIGITAL_LineColor = 0x2945;                      // 40,40,40
uint16_t DIGITAL_VUNullDBMarkerColor = 0xB104;            // FireBrick
uint16_t DIGITAL_VUPeakColor = 0xDEFB;                    // Gainsboro 
uint16_t DIGITAL_VUBarColorNormal = 0x1C9F;               // DodgerBlue
uint16_t DIGITAL_VUBarColorMid = 0xFD20;                  // Orange
uint16_t DIGITAL_VUBarColorOver = 0xF800;                 // Red
uint16_t DIGITAL_PEAKPeakColor = 0xFEA0;                  // Gold
uint16_t DIGITAL_PEAKBarColor = 0xBDF7;                   // Gray
uint16_t DIGITAL_CorrelationTextColor = 0xFEA0;           // Gold
uint16_t DIGITAL_CorrelationMinusColor = 0xF800;          // Red
uint16_t DIGITAL_CorrelationNullColor = 0xF800;           // Red
uint16_t DIGITAL_CorrelationPlusColor = 0x3666;           // LimeGreen 
uint16_t DIGITAL_CorrelationBackgroundColor = 0x2104;     // 32,32,32
uint16_t DIGITAL_CorrelationMarkerColor = 0x6B4D;         // DimGray
uint16_t DIGITAL_CorrelationHoldColor = 0x6B4D;           // DimGray
uint16_t DIGITAL_CorrelationHoldBackgroundColor = 0x2104; // 32,32,32
uint16_t DIGITAL_LineMarkerColor = 0x4208;                // 64,64,64
uint16_t ANALOG_PeakLEDColor = 0xF800;                    // 255,0,0
uint16_t ANALOG_NeedleColor = 0xF81F;                     // Magenta
uint16_t FFT_DisplayBackColor = 0;                        // Black
uint16_t FFT_LRColor = 0xF7BE;                            // WhiteSmoke
uint16_t FFT_LineColor = 0x4208;                          // 64,64,64
uint16_t FFT_ScaleForeColor = 0xBDF7;                     // Gray
uint16_t FFT_ScaleBackgroundColor = 0x10A2;               // 20,20,20
uint16_t FFT_VUBarsBackColor = 0x2104;                    // 32,32,32
uint16_t FFT_VUBarColorNormal = 0x1C9F;                   // DodgerBlue
uint16_t FFT_VUBarColorMid = 0xFD20;                      // Orange
uint16_t FFT_VUBarColorOver = 0xF800;                     // Red
uint16_t FFT_VUPeakColor = 0xFEA0;                        // Gold
uint16_t FFT_VUMarkerColor = 0xFF9C;                      // Linen
uint16_t FFT_FFTBarColor = 0x1C9F;                        // DodgerBlue
uint16_t FFT_FFTPeakColor = 0xDEFB;                       // Gainsboro
uint16_t FFT_HeaderForeColor = 0xAD55;                    // DarkGray
uint16_t GONIO_DisplayBackColor = 0;                      // Black
uint16_t GONIO_LRColor = 0xF7BE;                          // WhiteSmoke
uint16_t GONIO_HeaderForeColor = 0xAD55;                  // DarkGray
uint16_t GONIO_ScaleForeColor = 0xBDF7;                   // Gray
uint16_t GONIO_MarkerColor = 0xFF9C;                      // Linen
uint16_t GONIO_PeakColor = 0xFEA0;                        // Gold
uint16_t GONIO_BarColorNormal = 0x1C9F;                   // DodgerBlue
uint16_t GONIO_BarColorMid = 0xFD20;                      // Orange
uint16_t GONIO_BarColorOver = 0xF800;                     // Red
uint16_t GONIO_BarsBackColor = 0x2104;                    // 32,32,32
uint16_t GONIO_GoniometerColor = 0xBFE0;                  // Lime 
uint16_t GONIO_CorrelationTextColor = 0xFEA0;             // Gold
uint16_t GONIO_CorrelationMinusColor = 0xF800;            // Red
uint16_t GONIO_CorrelationNullColor = 0xFEA0;             // Gold
uint16_t GONIO_CorrelationPlusColor = 0x3666;             // LimeGreen 
uint16_t GONIO_CorrelationBackgroundColor = 0x2104;       // 32,32,32
uint16_t GONIO_CorrelationMarkerColor = 0x6B4D;           // DimGray
uint16_t GONIO_CorrelationHoldColor = 0x6B4D;             // DimGray
uint16_t GONIO_CorrelationHoldBackgroundColor = 0x2104;   // 32,32,32
uint16_t GONIO_CrossColor = 0x7412;                       // SlateGray

// bins
uint16_t binStart16[16] = { 0 }, binEnd16[16] = { 0 };
uint16_t binStart25[25] = { 0 }, binEnd25[25] = { 0 };
uint16_t binStart52[52] = { 0 }, binEnd52[52] = { 0 };
uint16_t binStart69[69] = { 0 }, binEnd69[69] = { 0 };

/// <summary>
/// digitalmeter menu
/// </summary>
const char* strMenuDIGITAL[4] = {
 "-40dB to 6dB",
 "-30dB to 6dB",
 "-40dB to 6dB Hold",
 "-30dB to 6dB Hold"
};

/// <summary>
/// analogmeter menu
/// </summary>
const char* strMenuANALOG[7] = {
   "Show Peak-LED from 0dB",
   "Show Peak-LED from 1dB",
   "Show Peak-LED from 2dB",
   "Show Peak-LED from 3dB",
   "Show Peak-LED from 4dB",
   "Show Peak-LED from 5dB",
   "Show Peak-LED from 6dB"
};

/// <summary>
/// spectrumanalyzer menu
/// </summary>
const char* strMenuFFT[12] = {
    "-40dB to 6dB RMS",
    "-40dB to 6dB PPM",
    "-30dB to 6dB RMS",
    "-30dB to 6dB PPM",
    "-40dB to 6dB RMS Hold",
    "-40dB to 6dB PPM Hold",
    "-30dB to 6dB RMS Hold",
    "-30dB to 6dB PPM Hold",
    "-40dB to 6dB RMS 4 Sec.",
    "-40dB to 6dB PPM 4 Sec.",
    "-30dB to 6dB RMS 4 Sec.",
    "-30dB to 6dB PPM 4 Sec."
};

/// <summary>
/// goniometer menu
/// </summary>
const char* strMenuGONIO[8] = {
    "-40dB to 6dB RMS",
    "-40dB to 6dB PPM",
    "-30dB to 6dB RMS",
    "-30dB to 6dB PPM",
    "-40dB to 6dB RMS HOLD",
    "-40dB to 6dB PPM HOLD",
    "-30dB to 6dB RMS HOLD",
    "-30dB to 6dB PPM HOLD"
};
