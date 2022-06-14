/// <summary>
/// check of first controller start
/// </summary>
/// <returns></returns>
bool isFirstStart() {
    return (EEPROM.read(1000) == 234) ? false : true;
}

/// <summary>
/// clear EEPROM
/// </summary>
void clearEEPROM() {
    for (int i = 0; i < EEPROM.length(); i++)
        EEPROM.write(i, 0);

    EEPROM.write(1000, 234);
    writeGLOBALConfig();
    writeDBCorrection();
    writeDIGITALConfig();
    writeANALOGConfig();
    writeFFTConfig();
    writeGONIOConfig();
    writeREMOTECONTROLConfig();

    im.fillScreen(RGB565_Black);
    drawTextCenterX(im, "RESET TO", 150, 240, RGB565_Orange, Arial_16_Bold);
    drawTextCenterX(im, "FACTORY", 180, 240, RGB565_Orange, Arial_16_Bold);
    drawTextCenterX(im, "DEFAULTS", 210, 240, RGB565_Orange, Arial_16_Bold);
    tft.update(frontBuffer, true);
}

/// <summary>
/// read global config
/// </summary>
void readGLOBALConfig() {
    EEPROM.get(1, flipScreen); // bool, 1 byte
    EEPROM.get(3, showCalibrationFrame); // bool, 1 byte
    EEPROM.get(20, moduleType);
}

/// <summary>
/// write global config
/// </summary>
void writeGLOBALConfig() {
    EEPROM.put(1, flipScreen); // bool, 1 byte
    EEPROM.put(3, showCalibrationFrame); // bool, 1 byte
    EEPROM.put(20, moduleType);
}

/// <summary>
/// read remote control config
/// </summary>
void readREMOTECONTROLConfig() {
    EEPROM.get(100, IR_Up);
    EEPROM.get(110, IR_Left);
    EEPROM.get(120, IR_Right);
    EEPROM.get(130, IR_Down);
    EEPROM.get(140, IR_PlayStop);
    EEPROM.get(150, IR_Menu);
    EEPROM.get(160, rcType);
}

/// <summary>
/// write remote control config
/// </summary>
void writeREMOTECONTROLConfig() {
    EEPROM.put(100, IR_Up);
    EEPROM.put(110, IR_Left);
    EEPROM.put(120, IR_Right);
    EEPROM.put(130, IR_Down);
    EEPROM.put(140, IR_PlayStop);
    EEPROM.put(150, IR_Menu);
    EEPROM.put(160, rcType);
}

/// <summary>
/// read dB correction
/// </summary>
void readDBCorrection() {
    EEPROM.get(200, RMSCorrectionLeft);
    EEPROM.get(210, RMSCorrectionRight);
    EEPROM.get(220, PPMCorrectionLeft);
    EEPROM.get(230, PPMCorrectionRight);
}

/// <summary>
/// write dB correction
/// </summary>
void writeDBCorrection() {
    EEPROM.put(200, RMSCorrectionLeft);
    EEPROM.put(210, RMSCorrectionRight);
    EEPROM.put(220, PPMCorrectionLeft);
    EEPROM.put(230, PPMCorrectionRight);
}

/// <summary>
/// read digital config
/// </summary>
void readDIGITALConfig() {
    EEPROM.get(4, DIGITAL_Offset); // uint16_t, 2 bytes

    EEPROM.get(30, DIGITAL_ShowA700Frame); // bool, 1 byte

    EEPROM.get(504, DIGITAL_WorkMode);
    EEPROM.get(506, DIGITAL_UseWheel);
    EEPROM.get(508, DIGITAL_ShowHeader);
    EEPROM.get(510, DIGITAL_ShowPeakBars);
    EEPROM.get(512, DIGITAL_VUBarAttack);
    EEPROM.get(514, DIGITAL_VUBarRelease);
    EEPROM.get(516, DIGITAL_VUPeakHoldTime);
    EEPROM.get(518, DIGITAL_VUPeakRelease);
    EEPROM.get(520, DIGITAL_PEAKBarAttack);
    EEPROM.get(522, DIGITAL_PEAKBarRelease);
    EEPROM.get(524, DIGITAL_PEAKPeakHoldTime);
    EEPROM.get(526, DIGITAL_PEAKPeakRelease);
    EEPROM.get(528, DIGITAL_VUPeakHeight);
    EEPROM.get(530, DIGITAL_VUSegmentHeight);
    EEPROM.get(532, DIGITAL_PEAKPeakHeight);
    EEPROM.get(534, DIGITAL_PEAKSegmentHeight);
    EEPROM.get(536, DIGITAL_DisplayBackColor);
    EEPROM.get(538, DIGITAL_LRColor);
    EEPROM.get(540, DIGITAL_HeaderForeColor);
    EEPROM.get(542, DIGITAL_ScaleForeColor);
    EEPROM.get(544, DIGITAL_ScaleMarkerColor);
    EEPROM.get(546, DIGITAL_LineColor);
    EEPROM.get(548, DIGITAL_VUNullDBMarkerColor);
    EEPROM.get(550, DIGITAL_VUPeakColor);
    EEPROM.get(552, DIGITAL_VUBarColorNormal);
    EEPROM.get(554, DIGITAL_VUBarColorMid);
    EEPROM.get(556, DIGITAL_VUBarColorOver);
    EEPROM.get(558, DIGITAL_PEAKPeakColor);
    EEPROM.get(560, DIGITAL_PEAKBarColor);
    EEPROM.get(562, DIGITAL_CorrelationTextColor);
    EEPROM.get(564, DIGITAL_CorrelationMinusColor);
    EEPROM.get(566, DIGITAL_CorrelationNullColor);
    EEPROM.get(568, DIGITAL_CorrelationPlusColor);
    EEPROM.get(570, DIGITAL_CorrelationBackgroundColor);
    EEPROM.get(572, DIGITAL_CorrelationMarkerColor);
    EEPROM.get(574, DIGITAL_CorrelationHoldColor);
    EEPROM.get(576, DIGITAL_CorrelationHoldBackgroundColor);
    EEPROM.get(578, DIGITAL_LineMarkerColor);
    EEPROM.get(590, DIGITAL_PeakAttenuation);
}

/// <summary>
/// write digital config
/// </summary>
void writeDIGITALConfig() {
    EEPROM.put(4, DIGITAL_Offset); // uint16_t, 2 bytes

    EEPROM.put(30, DIGITAL_ShowA700Frame); // bool, 1 byte

    EEPROM.put(504, DIGITAL_WorkMode);
    EEPROM.put(506, DIGITAL_UseWheel);
    EEPROM.put(508, DIGITAL_ShowHeader);
    EEPROM.put(510, DIGITAL_ShowPeakBars);
    EEPROM.put(512, DIGITAL_VUBarAttack);
    EEPROM.put(514, DIGITAL_VUBarRelease);
    EEPROM.put(516, DIGITAL_VUPeakHoldTime);
    EEPROM.put(518, DIGITAL_VUPeakRelease);
    EEPROM.put(520, DIGITAL_PEAKBarAttack);
    EEPROM.put(522, DIGITAL_PEAKBarRelease);
    EEPROM.put(524, DIGITAL_PEAKPeakHoldTime);
    EEPROM.put(526, DIGITAL_PEAKPeakRelease);
    EEPROM.put(528, DIGITAL_VUPeakHeight);
    EEPROM.put(530, DIGITAL_VUSegmentHeight);
    EEPROM.put(532, DIGITAL_PEAKPeakHeight);
    EEPROM.put(534, DIGITAL_PEAKSegmentHeight);
    EEPROM.put(536, DIGITAL_DisplayBackColor);
    EEPROM.put(538, DIGITAL_LRColor);
    EEPROM.put(540, DIGITAL_HeaderForeColor);
    EEPROM.put(542, DIGITAL_ScaleForeColor);
    EEPROM.put(544, DIGITAL_ScaleMarkerColor);
    EEPROM.put(546, DIGITAL_LineColor);
    EEPROM.put(548, DIGITAL_VUNullDBMarkerColor);
    EEPROM.put(550, DIGITAL_VUPeakColor);
    EEPROM.put(552, DIGITAL_VUBarColorNormal);
    EEPROM.put(554, DIGITAL_VUBarColorMid);
    EEPROM.put(556, DIGITAL_VUBarColorOver);
    EEPROM.put(558, DIGITAL_PEAKPeakColor);
    EEPROM.put(560, DIGITAL_PEAKBarColor);
    EEPROM.put(562, DIGITAL_CorrelationTextColor);
    EEPROM.put(564, DIGITAL_CorrelationMinusColor);
    EEPROM.put(566, DIGITAL_CorrelationNullColor);
    EEPROM.put(568, DIGITAL_CorrelationPlusColor);
    EEPROM.put(570, DIGITAL_CorrelationBackgroundColor);
    EEPROM.put(572, DIGITAL_CorrelationMarkerColor);
    EEPROM.put(574, DIGITAL_CorrelationHoldColor);
    EEPROM.put(576, DIGITAL_CorrelationHoldBackgroundColor);
    EEPROM.put(578, DIGITAL_LineMarkerColor);
    EEPROM.put(590, DIGITAL_PeakAttenuation);
}

/// <summary>
/// read analog config
/// </summary>
void readANALOGConfig() {
    EEPROM.get(6, ANALOG_Offset); // uint16_t, 2 bytes

    EEPROM.get(32, ANALOG_ShowA700Frame); // bool, 1 byte

    EEPROM.get(604, ANALOG_Mode);
    EEPROM.get(606, ANALOG_NeedleAttack);
    EEPROM.get(608, ANALOG_NeedleRelease);
    EEPROM.get(610, ANALOG_PeakLEDdB);
    EEPROM.get(612, ANALOG_PeakLEDHoldTime);
    EEPROM.get(614, ANALOG_PeakLEDColor);
    EEPROM.get(616, ANALOG_NeedleColor);
}

/// <summary>
/// write analog config
/// </summary>
void writeANALOGConfig() {
    EEPROM.put(6, ANALOG_Offset); // uint16_t, 2 bytes

    EEPROM.put(32, ANALOG_ShowA700Frame); // bool, 1 byte

    EEPROM.put(604, ANALOG_Mode);
    EEPROM.put(606, ANALOG_NeedleAttack);
    EEPROM.put(608, ANALOG_NeedleRelease);
    EEPROM.put(610, ANALOG_PeakLEDdB);
    EEPROM.put(612, ANALOG_PeakLEDHoldTime);
    EEPROM.put(614, ANALOG_PeakLEDColor);
    EEPROM.put(616, ANALOG_NeedleColor);
}

/// <summary>
/// read FFT config
/// </summary>
void readFFTConfig() {
    EEPROM.get(8, FFT_Offset); // uint16_t, 2 bytes

    EEPROM.get(34, FFT_ShowA700Frame); // bool, 1 byte

    EEPROM.get(704, FFT_BarMode);
    EEPROM.get(706, FFT_WorkMode);
    EEPROM.get(708, FFT_UseWheel);
    EEPROM.get(710, FFT_VUBarAttack);
    EEPROM.get(712, FFT_VUBarRelease);
    EEPROM.get(714, FFT_VUPeakHoldTime);
    EEPROM.get(716, FFT_VUPeakRelease);
    EEPROM.get(718, FFT_FFTBarAttack);
    EEPROM.get(720, FFT_FFTBarRelease);
    EEPROM.get(722, FFT_FFTPeakHoldTime);
    EEPROM.get(724, FFT_FFTPeakRelease);
    EEPROM.get(726, FFT_VUPeakHeight);
    EEPROM.get(728, FFT_VUSegmentHeight);
    EEPROM.get(730, FFT_FFTPeakHeight);
    EEPROM.get(732, FFT_FFTSegmentHeight);
    EEPROM.get(734, FFT_DisplayBackColor);
    EEPROM.get(736, FFT_VUBarsBackColor);
    EEPROM.get(738, FFT_FFTBarColor);
    EEPROM.get(740, FFT_VUBarColorNormal);
    EEPROM.get(742, FFT_VUBarColorMid);
    EEPROM.get(744, FFT_VUBarColorOver);
    EEPROM.get(746, FFT_FFTPeakColor);
    EEPROM.get(748, FFT_VUPeakColor);
    EEPROM.get(750, FFT_VUMarkerColor);
    EEPROM.get(752, FFT_LRColor);
    EEPROM.get(754, FFT_HeaderForeColor);
    EEPROM.get(756, FFT_ScaleForeColor);
    EEPROM.get(758, FFT_ScaleBackgroundColor);
    EEPROM.get(760, FFT_LineColor);

    EEPROM.get(770, FFT_PEAKBarAttack);
    EEPROM.get(772, FFT_PEAKBarRelease);
    EEPROM.get(774, FFT_PEAKPeakHoldTime);
    EEPROM.get(776, FFT_PEAKPeakRelease);

    EEPROM.get(790, FFT_PeakAttenuation);
}

/// <summary>
/// write FFT config
/// </summary>
void writeFFTConfig() {
    EEPROM.put(8, FFT_Offset); // uint16_t, 2 bytes

    EEPROM.put(34, FFT_ShowA700Frame); // bool, 1 byte

    EEPROM.put(704, FFT_BarMode);
    EEPROM.put(706, FFT_WorkMode);
    EEPROM.put(708, FFT_UseWheel);
    EEPROM.put(710, FFT_VUBarAttack);
    EEPROM.put(712, FFT_VUBarRelease);
    EEPROM.put(714, FFT_VUPeakHoldTime);
    EEPROM.put(716, FFT_VUPeakRelease);
    EEPROM.put(718, FFT_FFTBarAttack);
    EEPROM.put(720, FFT_FFTBarRelease);
    EEPROM.put(722, FFT_FFTPeakHoldTime);
    EEPROM.put(724, FFT_FFTPeakRelease);
    EEPROM.put(726, FFT_VUPeakHeight);
    EEPROM.put(728, FFT_VUSegmentHeight);
    EEPROM.put(730, FFT_FFTPeakHeight);
    EEPROM.put(732, FFT_FFTSegmentHeight);
    EEPROM.put(734, FFT_DisplayBackColor);
    EEPROM.put(736, FFT_VUBarsBackColor);
    EEPROM.put(738, FFT_FFTBarColor);
    EEPROM.put(740, FFT_VUBarColorNormal);
    EEPROM.put(742, FFT_VUBarColorMid);
    EEPROM.put(744, FFT_VUBarColorOver);
    EEPROM.put(746, FFT_FFTPeakColor);
    EEPROM.put(748, FFT_VUPeakColor);
    EEPROM.put(750, FFT_VUMarkerColor);
    EEPROM.put(752, FFT_LRColor);
    EEPROM.put(754, FFT_HeaderForeColor);
    EEPROM.put(756, FFT_ScaleForeColor);
    EEPROM.put(758, FFT_ScaleBackgroundColor);
    EEPROM.put(760, FFT_LineColor);

    EEPROM.put(770, FFT_PEAKBarAttack);
    EEPROM.put(772, FFT_PEAKBarRelease);
    EEPROM.put(774, FFT_PEAKPeakHoldTime);
    EEPROM.put(776, FFT_PEAKPeakRelease);

    EEPROM.put(790, FFT_PeakAttenuation);
}

/// <summary>
/// read gonio config
/// </summary>
void readGONIOConfig() {
    EEPROM.get(10, GONIO_Offset); // uint16_t, 2 bytes

    EEPROM.get(36, GONIO_ShowA700Frame); // bool, 1 byte

    EEPROM.get(800, GONIO_ShowSamplesCount);
    EEPROM.get(802, GONIO_Samples);
    EEPROM.get(804, GONIO_DrawMode);
    EEPROM.get(806, GONIO_WorkMode);
    EEPROM.get(808, GONIO_SwapX);
    EEPROM.get(810, GONIO_SwapY);
    EEPROM.get(812, GONIO_VUBarAttack);
    EEPROM.get(814, GONIO_VUBarRelease);
    EEPROM.get(816, GONIO_PEAKBarAttack);
    EEPROM.get(818, GONIO_PEAKBarRelease);
    EEPROM.get(820, GONIO_VUPeakHoldTime);
    EEPROM.get(822, GONIO_PEAKPeakHoldTime);
    EEPROM.get(824, GONIO_VUPeakRelease);
    EEPROM.get(826, GONIO_PEAKPeakRelease);
    EEPROM.get(828, GONIO_PeakHeight);
    EEPROM.get(830, GONIO_SegmentHeight);
    EEPROM.get(832, GONIO_DisplayBackColor);
    EEPROM.get(834, GONIO_LRColor);
    EEPROM.get(836, GONIO_HeaderForeColor);
    EEPROM.get(838, GONIO_ScaleForeColor);
    EEPROM.get(842, GONIO_MarkerColor);
    EEPROM.get(844, GONIO_PeakColor);
    EEPROM.get(846, GONIO_BarColorNormal);
    EEPROM.get(848, GONIO_BarColorMid);
    EEPROM.get(850, GONIO_BarColorOver);
    EEPROM.get(852, GONIO_BarsBackColor);
    EEPROM.get(854, GONIO_GoniometerColor);
    EEPROM.get(856, GONIO_CorrelationTextColor);
    EEPROM.get(858, GONIO_CorrelationMinusColor);
    EEPROM.get(860, GONIO_CorrelationNullColor);
    EEPROM.get(862, GONIO_CorrelationPlusColor);
    EEPROM.get(864, GONIO_CorrelationBackgroundColor);
    EEPROM.get(866, GONIO_CorrelationMarkerColor);
    EEPROM.get(868, GONIO_CorrelationHoldColor);
    EEPROM.get(870, GONIO_CorrelationHoldBackgroundColor);
    EEPROM.get(872, GONIO_CrossColor);

    EEPROM.get(890, GONIO_PeakAttenuation);
}

/// <summary>
/// write gonio config
/// </summary>
void writeGONIOConfig() {
    EEPROM.put(10, GONIO_Offset); // uint16_t, 2 bytes

    EEPROM.put(36, GONIO_ShowA700Frame); // bool, 1 byte

    EEPROM.put(800, GONIO_ShowSamplesCount);
    EEPROM.put(802, GONIO_Samples);
    EEPROM.put(804, GONIO_DrawMode);
    EEPROM.put(806, GONIO_WorkMode);
    EEPROM.put(808, GONIO_SwapX);
    EEPROM.put(810, GONIO_SwapY);
    EEPROM.put(812, GONIO_VUBarAttack);
    EEPROM.put(814, GONIO_VUBarRelease);
    EEPROM.put(816, GONIO_PEAKBarAttack);
    EEPROM.put(818, GONIO_PEAKBarRelease);
    EEPROM.put(820, GONIO_VUPeakHoldTime);
    EEPROM.put(822, GONIO_PEAKPeakHoldTime);
    EEPROM.put(824, GONIO_VUPeakRelease);
    EEPROM.put(826, GONIO_PEAKPeakRelease);
    EEPROM.put(828, GONIO_PeakHeight);
    EEPROM.put(830, GONIO_SegmentHeight);
    EEPROM.put(832, GONIO_DisplayBackColor);
    EEPROM.put(834, GONIO_LRColor);
    EEPROM.put(836, GONIO_HeaderForeColor);
    EEPROM.put(838, GONIO_ScaleForeColor);
    EEPROM.put(842, GONIO_MarkerColor);
    EEPROM.put(844, GONIO_PeakColor);
    EEPROM.put(846, GONIO_BarColorNormal);
    EEPROM.put(848, GONIO_BarColorMid);
    EEPROM.put(850, GONIO_BarColorOver);
    EEPROM.put(852, GONIO_BarsBackColor);
    EEPROM.put(854, GONIO_GoniometerColor);
    EEPROM.put(856, GONIO_CorrelationTextColor);
    EEPROM.put(858, GONIO_CorrelationMinusColor);
    EEPROM.put(860, GONIO_CorrelationNullColor);
    EEPROM.put(862, GONIO_CorrelationPlusColor);
    EEPROM.put(864, GONIO_CorrelationBackgroundColor);
    EEPROM.put(866, GONIO_CorrelationMarkerColor);
    EEPROM.put(868, GONIO_CorrelationHoldColor);
    EEPROM.put(870, GONIO_CorrelationHoldBackgroundColor);
    EEPROM.put(872, GONIO_CrossColor);

    EEPROM.put(890, GONIO_PeakAttenuation);
}
