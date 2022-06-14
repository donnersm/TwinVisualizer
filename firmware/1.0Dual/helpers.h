;;/// <summary>
/// get chip temp
/// </summary>
extern float tempmonGetTemp(void);

/// <summary>
/// send RMS & PPM data als one block
/// </summary>
void sendRMSPPM() {
  int dbbuf[4];
  dbbuf[0] = (int)(dBRMSL * 1000.0f); // left RMS
  dbbuf[1] = (int)(dBRMSR * 1000.0f); // right RMS
  dbbuf[2] = (int)(dBPPML * 1000.0f); // left PPM
  dbbuf[3] = (int)(dBPPMR * 1000.0f); // right PPM

  Serial.print("*");
  Serial.write((byte*)&dbbuf, 16);
  Serial.print("#");
}





/// <summary>
/// get Teensy infos
/// </summary>
void getControllerInfos() {
  uint8_t serial[4];
  uint8_t mac[6];
  uint8_t uid64[8];

  teensySN(serial);
  teensyMAC(mac);
  teensyUID64(uid64);

  Serial.print("{[success]Hello from the audio visualizer device!}");
  Serial.printf("{[info][Device] Firmware: %s}", VERSION);
  Serial.printf("{[info][Device] Serialnumber: %s}", teensySN());
  Serial.printf("{[info][Device] MAC Address: %s}", teensyMAC());
  Serial.printf("{[info][Device] UID 64-bit: %s}", teensyUID64());
  Serial.printf("{[info][Device] CPU Clock Speed: %i MHz}", F_CPU_ACTUAL / 1000000);
  Serial.printf("{[warning][Device] CPU CoreTemp: %.1f [degrees]}", tempmonGetTemp());


}




/// <summary>
/// get dB gorrection data
/// </summary>
void getDBCorrectionData() {
  // dB Correction
  Serial.print("{RMSCorrectionLeft=" + String(RMSCorrectionLeft) + "}");
  Serial.print("{RMSCorrectionRight=" + String(RMSCorrectionRight) + "}");
  Serial.print("{PPMCorrectionLeft=" + String(PPMCorrectionLeft) + "}");
  Serial.print("{PPMCorrectionRight=" + String(PPMCorrectionRight) + "}");
}

/// <summary>
/// get configuration infos
/// </summary>
void getConfigurationInfos() {
  // ALL
  Serial.print("{Firmware=" + String(VERSION) + "}");
  Serial.print("{ModuleType=" + String(moduleType) + "}");
  Serial.print("{FlipScreen=" + String(flipScreen) + "}");
  Serial.print("{RemoteControlType=" + String(rcType) + "}");

  // DIGITAL
  Serial.print("{DIGITAL_ShowA700Frame=" + String(DIGITAL_ShowA700Frame) + "}");
  Serial.print("{DIGITAL_WorkMode=" + String(DIGITAL_WorkMode) + "}");
  Serial.print("{DIGITAL_ShowPeakBars=" + String(DIGITAL_ShowPeakBars) + "}");

  // ANALOG
  Serial.print("{ANALOG_ShowA700Frame=" + String(ANALOG_ShowA700Frame) + "}");
  Serial.print("{ANALOG_PeakLEDdB=" + String(ANALOG_PeakLEDdB) + "}");
  Serial.print("{ANALOG_Mode=" + String(ANALOG_Mode) + "}"); // black, white, warm

  // FFT
  Serial.print("{FFT_ShowA700Frame=" + String(FFT_ShowA700Frame) + "}");
  Serial.print("{FFT_WorkMode=" + String(FFT_WorkMode) + "}");
  Serial.print("{FFT_BarMode=" + String(FFT_BarMode) + "}");

  // GONIO
  Serial.print("{GONIO_ShowA700Frame=" + String(GONIO_ShowA700Frame) + "}");
  Serial.print("{GONIO_WorkMode=" + String(GONIO_WorkMode) + "}");
  Serial.print("{GONIO_DrawMode=" + String(GONIO_DrawMode) + "}");
}

/// <summary>
/// converts dB to RAD plus delimiter
/// </summary>
/// <param name="dB"></param>
/// <param name="dB_min"></param>
/// <param name="dB_max"></param>
/// <returns>RAD</returns>
float dBToRAD(float dB, float dB_min, float dB_max) {
  if (dB < dB_min) dB = dB_min;
  if (dB > dB_max) dB = dB_max;

  // range possible from -40dB to 7dB
  float rad = 0.00000015881455f * (dB * dB * dB * dB * dB) + 0.000014316862f * (dB * dB * dB * dB) + 0.00039325826f * (dB * dB * dB) + 0.0017871f * (dB * dB) - 0.0746641f * dB + 1.2338462f;

  if (rad < 1.0f) rad = 1.0f;
  if (rad > 2.15f) rad = 2.15f;

  return rad;
}

/// <summary>
/// converts RMS amplitude to dB plus delimiter
/// </summary>
/// <param name="amplitude"></param>
/// <param name="lr"></param>
/// <returns></returns>
float rmsAmplitudeTodB(float amplitude, int16_t lr /*0=left, 1=right*/) {
  float dB = 20.0f * log10f(amplitude * 2.0f) + 6.0f;

  if (lr == 0) {
    dB += RMSCorrectionLeft / 100.0f;  // left
    dBRMSL = dB;
  }
  if (lr == 1) {
    dB += RMSCorrectionRight / 100.0f;  // right
    dBRMSR = dB;
  }

  if (dB > dBHigh) dB = dBHigh;
  return dB;
}

/// <summary>
/// converts PEAK amplitude to dB plus delimiter, substract 'PeakAttenuation'
/// </summary>
/// <param name="amplitude"></param>
/// <param name="lr"></param>
/// <returns></returns>
float peakAmplitudeTodB(float amplitude, int16_t lr /*0=left, 1=right*/) {
  float dB = 20.0f * log10f(amplitude * 2.0f) + 3.0f;

  if (moduleType == 0) dB -= DIGITAL_PeakAttenuation;
  if (moduleType == 2) dB -= FFT_PeakAttenuation;
  if (moduleType == 3) dB -= GONIO_PeakAttenuation;

  if (lr == 0) {
    dB += PPMCorrectionLeft / 100.0f;  // left
    dBPPML = dB;
  }
  if (lr == 1) {
    dB += PPMCorrectionRight / 100.0f;  // light
    dBPPMR = dB;
  }

  if (dB > dBHigh) dB = dBHigh;
  return dB;
}

/// <summary>
/// converts FFT amplitude values to dB scale plus delimiter
/// </summary>
/// <param name="amplitude"></param>
/// <returns></returns>
float fftAmplitudeTodB(float amplitude) {
  if (amplitude < 0.01f) amplitude = 0.0f;
  float dB = 10.0f * log10f(amplitude / 0.775f);
  if (dB > dBHigh) dB = dBHigh;
  return dB;
}

/// <summary>
/// set bin ranges
/// </summary>
void setBins() {
  // frequency range for the 16 horizontal bars
  binStart16[0] = 0;  binEnd16[0] = 0;
  binStart16[1] = 1;  binEnd16[1] = 1;
  binStart16[2] = 2;  binEnd16[2] = 3;
  binStart16[3] = 4;  binEnd16[3] = 6;
  binStart16[4] = 7;  binEnd16[4] = 10;
  binStart16[5] = 11;  binEnd16[5] = 15;
  binStart16[6] = 16;  binEnd16[6] = 22;
  binStart16[7] = 23;  binEnd16[7] = 32;
  binStart16[8] = 33;  binEnd16[8] = 46;
  binStart16[9] = 47;  binEnd16[9] = 66;
  binStart16[10] = 67; binEnd16[10] = 94;
  binStart16[11] = 95; binEnd16[11] = 133;
  binStart16[12] = 134; binEnd16[12] = 187;
  binStart16[13] = 188; binEnd16[13] = 262;
  binStart16[14] = 263; binEnd16[14] = 366;
  binStart16[15] = 367; binEnd16[15] = 511;

  // frequency range for the 25 vertical bars
  binStart25[0] = 0;  binEnd25[0] = 0;
  binStart25[1] = 1;  binEnd25[1] = 1;
  binStart25[2] = 2;  binEnd25[2] = 2;
  binStart25[3] = 3;  binEnd25[3] = 4;
  binStart25[4] = 5;  binEnd25[4] = 6;
  binStart25[5] = 7;  binEnd25[5] = 9;
  binStart25[6] = 10;  binEnd25[6] = 12;
  binStart25[7] = 13;  binEnd25[7] = 16;
  binStart25[8] = 17;  binEnd25[8] = 20;
  binStart25[9] = 21;  binEnd25[9] = 25;
  binStart25[10] = 26; binEnd25[10] = 31;
  binStart25[11] = 32; binEnd25[11] = 39;
  binStart25[12] = 40; binEnd25[12] = 48;
  binStart25[13] = 49; binEnd25[13] = 59;
  binStart25[14] = 60; binEnd25[14] = 73;
  binStart25[15] = 74; binEnd25[15] = 89;
  binStart25[16] = 90; binEnd25[16] = 109;
  binStart25[17] = 110; binEnd25[17] = 133;
  binStart25[18] = 134; binEnd25[18] = 162;
  binStart25[19] = 163; binEnd25[19] = 197;
  binStart25[20] = 198; binEnd25[20] = 239;
  binStart25[21] = 240; binEnd25[21] = 289;
  binStart25[22] = 290; binEnd25[22] = 350;
  binStart25[23] = 351; binEnd25[23] = 423;
  binStart25[24] = 424; binEnd25[24] = 511;

  // frequency range for the 52 horizontal bars
  binStart52[0] = 0;    binEnd52[0] = 0;
  binStart52[1] = 1;    binEnd52[1] = 1;
  binStart52[2] = 2;    binEnd52[2] = 2;
  binStart52[3] = 3;    binEnd52[3] = 3;
  binStart52[4] = 4;    binEnd52[4] = 4;
  binStart52[5] = 5;    binEnd52[5] = 5;
  binStart52[6] = 6;    binEnd52[6] = 7;
  binStart52[7] = 8;    binEnd52[7] = 9;
  binStart52[8] = 10;   binEnd52[8] = 11;
  binStart52[9] = 12;   binEnd52[9] = 13;
  binStart52[10] = 14;  binEnd52[10] = 15;
  binStart52[11] = 16;  binEnd52[11] = 17;
  binStart52[12] = 18;  binEnd52[12] = 19;
  binStart52[13] = 20;  binEnd52[13] = 21;
  binStart52[14] = 22;  binEnd52[14] = 24;
  binStart52[15] = 25;  binEnd52[15] = 27;
  binStart52[16] = 28;  binEnd52[16] = 30;
  binStart52[17] = 31;  binEnd52[17] = 33;
  binStart52[18] = 34;  binEnd52[18] = 37;
  binStart52[19] = 38;  binEnd52[19] = 41;
  binStart52[20] = 42;  binEnd52[20] = 45;
  binStart52[21] = 46;  binEnd52[21] = 49;
  binStart52[22] = 50;  binEnd52[22] = 54;
  binStart52[23] = 55;  binEnd52[23] = 59;
  binStart52[24] = 60;  binEnd52[24] = 64;
  binStart52[25] = 65;  binEnd52[25] = 70;
  binStart52[26] = 71;  binEnd52[26] = 76;
  binStart52[27] = 77;  binEnd52[27] = 83;
  binStart52[28] = 84;  binEnd52[28] = 90;
  binStart52[29] = 91;  binEnd52[29] = 98;
  binStart52[30] = 99;  binEnd52[30] = 106;
  binStart52[31] = 107; binEnd52[31] = 115;
  binStart52[32] = 116; binEnd52[32] = 124;
  binStart52[33] = 125; binEnd52[33] = 134;
  binStart52[34] = 135; binEnd52[34] = 145;
  binStart52[35] = 146; binEnd52[35] = 157;
  binStart52[36] = 158; binEnd52[36] = 169;
  binStart52[37] = 170; binEnd52[37] = 182;
  binStart52[38] = 183; binEnd52[38] = 196;
  binStart52[39] = 197; binEnd52[39] = 211;
  binStart52[40] = 212; binEnd52[40] = 228;
  binStart52[41] = 229; binEnd52[41] = 246;
  binStart52[42] = 247; binEnd52[42] = 265;
  binStart52[43] = 266; binEnd52[43] = 285;
  binStart52[44] = 286; binEnd52[44] = 307;
  binStart52[45] = 308; binEnd52[45] = 330;
  binStart52[46] = 331; binEnd52[46] = 355;
  binStart52[47] = 356; binEnd52[47] = 382;
  binStart52[48] = 383; binEnd52[48] = 411;
  binStart52[49] = 412; binEnd52[49] = 442;
  binStart52[50] = 443; binEnd52[50] = 475;
  binStart52[51] = 476; binEnd52[51] = 511;

  // frequency range for the 69 vertical bars
  binStart69[0] = 0;    binEnd69[0] = 0;
  binStart69[1] = 1;    binEnd69[1] = 1;
  binStart69[2] = 2;    binEnd69[2] = 2;
  binStart69[3] = 3;    binEnd69[3] = 3;
  binStart69[4] = 4;    binEnd69[4] = 4;
  binStart69[5] = 5;    binEnd69[5] = 5;
  binStart69[6] = 6;    binEnd69[6] = 6;
  binStart69[7] = 7;    binEnd69[7] = 7;
  binStart69[8] = 8;    binEnd69[8] = 8;
  binStart69[9] = 9;    binEnd69[9] = 10;
  binStart69[10] = 11;  binEnd69[10] = 12;
  binStart69[11] = 13;  binEnd69[11] = 14;
  binStart69[12] = 15;  binEnd69[12] = 16;
  binStart69[13] = 17;  binEnd69[13] = 18;
  binStart69[14] = 19;  binEnd69[14] = 20;
  binStart69[15] = 21;  binEnd69[15] = 22;
  binStart69[16] = 23;  binEnd69[16] = 24;
  binStart69[17] = 25;  binEnd69[17] = 26;
  binStart69[18] = 27;  binEnd69[18] = 28;
  binStart69[19] = 29;  binEnd69[19] = 30;
  binStart69[20] = 31;  binEnd69[20] = 33;
  binStart69[21] = 34;  binEnd69[21] = 36;
  binStart69[22] = 37;  binEnd69[22] = 39;
  binStart69[23] = 40;  binEnd69[23] = 42;
  binStart69[24] = 43;  binEnd69[24] = 45;
  binStart69[25] = 46;  binEnd69[25] = 48;
  binStart69[26] = 49;  binEnd69[26] = 51;
  binStart69[27] = 52;  binEnd69[27] = 55;
  binStart69[28] = 56;  binEnd69[28] = 59;
  binStart69[29] = 60;  binEnd69[29] = 63;
  binStart69[30] = 64;  binEnd69[30] = 67;
  binStart69[31] = 68;  binEnd69[31] = 71;
  binStart69[32] = 72;  binEnd69[32] = 76;
  binStart69[33] = 77;  binEnd69[33] = 81;
  binStart69[34] = 82;  binEnd69[34] = 86;
  binStart69[35] = 87;  binEnd69[35] = 91;
  binStart69[36] = 92;  binEnd69[36] = 96;
  binStart69[37] = 97;  binEnd69[37] = 102;
  binStart69[38] = 103; binEnd69[38] = 108;
  binStart69[39] = 109; binEnd69[39] = 114;
  binStart69[40] = 115; binEnd69[40] = 121;
  binStart69[41] = 122; binEnd69[41] = 128;
  binStart69[42] = 129; binEnd69[42] = 135;
  binStart69[43] = 136; binEnd69[43] = 143;
  binStart69[44] = 144; binEnd69[44] = 151;
  binStart69[45] = 152; binEnd69[45] = 159;
  binStart69[46] = 160; binEnd69[46] = 168;
  binStart69[47] = 169; binEnd69[47] = 177;
  binStart69[48] = 178; binEnd69[48] = 187;
  binStart69[49] = 188; binEnd69[49] = 197;
  binStart69[50] = 198; binEnd69[50] = 208;
  binStart69[51] = 209; binEnd69[51] = 219;
  binStart69[52] = 220; binEnd69[52] = 231;
  binStart69[53] = 232; binEnd69[53] = 243;
  binStart69[54] = 244; binEnd69[54] = 256;
  binStart69[55] = 257; binEnd69[55] = 269;
  binStart69[56] = 270; binEnd69[56] = 283;
  binStart69[57] = 284; binEnd69[57] = 298;
  binStart69[58] = 299; binEnd69[58] = 313;
  binStart69[59] = 314; binEnd69[59] = 329;
  binStart69[60] = 330; binEnd69[60] = 346;
  binStart69[61] = 347; binEnd69[61] = 364;
  binStart69[62] = 365; binEnd69[62] = 382;
  binStart69[63] = 383; binEnd69[63] = 401;
  binStart69[64] = 402; binEnd69[64] = 421;
  binStart69[65] = 422; binEnd69[65] = 442;
  binStart69[66] = 443; binEnd69[66] = 464;
  binStart69[67] = 465; binEnd69[67] = 487;
  binStart69[68] = 488; binEnd69[68] = 511;
}
