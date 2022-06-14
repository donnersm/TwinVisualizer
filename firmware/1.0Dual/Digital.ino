/// <summary>
/// initialize display
/// </summary>
/// <param name="reset"></param>
void displayInitDigital(bool reset) {
    // refresh: 200, frames: 100
    tft.setRefreshRate(200);
    tft.setVSyncSpacing(2);

    setMode(false);
    setSampleBlocks();
    queueStart();

    (flipScreen) ? tft.setRotation(2) : tft.setRotation(0);
    tft.setScroll((flipScreen) ? 320 - DIGITAL_Offset : DIGITAL_Offset);

    // fill screen
    bg.fillScreen(DIGITAL_ShowA700Frame ? RGB565_Black : DIGITAL_DisplayBackColor);

    // show the A700 frame
    if (DIGITAL_ShowA700Frame) bg.fillRoundRect(0, 26, 240, 294, 7, DIGITAL_DisplayBackColor);

    // show the calibration frame
    if (showCalibrationFrame) bg.drawRoundRect(0, 26, 240, 294, 7, RGB565_Magenta);

    // send calibration data
    if (calibrate) bg.drawRoundRect(0, 26, 240, 294, 7, RGB565_Red);

    // draw vertical middle line
    bg.drawFastVLine(120, 40, 257, DIGITAL_LineColor);

    // draw correlation max hold box middle marker
    bg.drawFastVLine(120, 315, 3, DIGITAL_CorrelationMarkerColor);

    float dBPre = 0.0f;
    for (uint16_t y = 0; y < 260; y++) {
        float dB = roundf(map((float)y, 0, 260, DIGITAL_dBLow, 6.0f));

        if (dB != dBPre) {
            if (dB == 6) { bg.drawText("6", iVec2(46, 300 - y), RGB565_Red, Arial_9_Bold, false);  bg.drawFastHLine(65, 296 - y, 8, RGB565_Red); bg.drawFastHLine(168, 296 - y, 8, RGB565_Red);  bg.drawText("6", iVec2(189, 300 - y), RGB565_Red, Arial_9_Bold, false); }
            if (dB == 5) { bg.drawFastHLine(67, 296 - y, 4, RGB565_Red); bg.drawFastHLine(170, 296 - y, 4, RGB565_Red); }
            if (dB == 4) { bg.drawFastHLine(67, 296 - y, 4, RGB565_Red); bg.drawFastHLine(170, 296 - y, 4, RGB565_Red); }
            if (dB == 3) { bg.drawFastHLine(67, 296 - y, 4, RGB565_Red); bg.drawFastHLine(170, 296 - y, 4, RGB565_Red); }
            if (dB == 2) { bg.drawFastHLine(67, 296 - y, 4, RGB565_Red); bg.drawFastHLine(170, 296 - y, 4, RGB565_Red); }
            if (dB == 1) { bg.drawFastHLine(67, 296 - y, 4, RGB565_Red); bg.drawFastHLine(170, 296 - y, 4, RGB565_Red); }
            if (dB == 0) { bg.drawText("0", iVec2(46, 300 - y), RGB565_Red, Arial_9_Bold, false); DIGITAL_dBnullPosition = y; bg.drawFastHLine(65, 296 - y, 8, RGB565_Red); bg.drawFastHLine(168, 296 - y, 8, RGB565_Red); bg.drawText("0", iVec2(189, 300 - y), RGB565_Red, Arial_9_Bold, false); }
            if (dB == -1) { bg.drawFastHLine(67, 296 - y, 4, DIGITAL_ScaleMarkerColor); bg.drawFastHLine(170, 296 - y, 4, DIGITAL_ScaleMarkerColor); }
            if (dB == -2) { bg.drawFastHLine(67, 296 - y, 4, DIGITAL_ScaleMarkerColor); bg.drawFastHLine(170, 296 - y, 4, DIGITAL_ScaleMarkerColor); }
            if (dB == -3) { bg.drawFastHLine(67, 296 - y, 4, DIGITAL_ScaleMarkerColor); bg.drawFastHLine(170, 296 - y, 4, DIGITAL_ScaleMarkerColor); }
            if (dB == -4) { bg.drawFastHLine(67, 296 - y, 4, DIGITAL_ScaleMarkerColor); bg.drawFastHLine(170, 296 - y, 4, DIGITAL_ScaleMarkerColor); }
            if (dB == -5) { bg.drawText("5", iVec2(46, 300 - y), DIGITAL_ScaleForeColor, Arial_9_Bold, false);  bg.drawFastHLine(65, 296 - y, 8, DIGITAL_ScaleMarkerColor); bg.drawFastHLine(118, 296 - y, 5, DIGITAL_LineMarkerColor); bg.drawFastHLine(168, 296 - y, 8, DIGITAL_ScaleMarkerColor); bg.drawText("5", iVec2(189, 300 - y), DIGITAL_ScaleForeColor, Arial_9_Bold, false); }
            if (dB == -10) { bg.drawText("10", iVec2(41, 300 - y), DIGITAL_ScaleForeColor, Arial_10_Bold, false);  bg.drawFastHLine(65, 296 - y, 8, DIGITAL_ScaleMarkerColor); bg.drawFastHLine(118, 296 - y, 5, DIGITAL_LineMarkerColor); bg.drawFastHLine(168, 296 - y, 8, DIGITAL_ScaleMarkerColor); bg.drawText("10", iVec2(185, 300 - y), DIGITAL_ScaleForeColor, Arial_10_Bold, false); }
            if (dB == -15) { bg.drawFastHLine(67, 296 - y, 4, DIGITAL_ScaleMarkerColor); bg.drawFastHLine(170, 296 - y, 4, DIGITAL_ScaleMarkerColor); }
            if (dB == -20) { bg.drawText("20", iVec2(41, 300 - y), DIGITAL_ScaleForeColor, Arial_10_Bold, false);  bg.drawFastHLine(65, 296 - y, 8, DIGITAL_ScaleMarkerColor); bg.drawFastHLine(118, 296 - y, 5, DIGITAL_LineMarkerColor); bg.drawFastHLine(168, 296 - y, 8, DIGITAL_ScaleMarkerColor); bg.drawText("20", iVec2(185, 300 - y), DIGITAL_ScaleForeColor, Arial_10_Bold, false); }
            if (dB == -25) { bg.drawFastHLine(67, 296 - y, 4, DIGITAL_ScaleMarkerColor); bg.drawFastHLine(170, 296 - y, 4, DIGITAL_ScaleMarkerColor); }
            if (dB == -30) { bg.drawText("30", iVec2(41, 300 - y - ((DIGITAL_dBLow == -40) ? 0 : 4)), DIGITAL_ScaleForeColor, Arial_10_Bold, false);  bg.drawFastHLine(65, 296 - y, 8, DIGITAL_ScaleMarkerColor); bg.drawFastHLine(118, 296 - y, 5, DIGITAL_LineMarkerColor); bg.drawFastHLine(168, 296 - y, 8, DIGITAL_ScaleMarkerColor); bg.drawText("30", iVec2(185, 300 - y - ((DIGITAL_dBLow == -40) ? 0 : 4)), DIGITAL_ScaleForeColor, Arial_10_Bold, false); }
            if (dB == -35) { bg.drawFastHLine(67, 296 - y, 4, DIGITAL_ScaleMarkerColor); bg.drawFastHLine(170, 296 - y, 4, DIGITAL_ScaleMarkerColor); }
            if (dB == -40) { bg.drawText("40", iVec2(41, 300 - y - 4), DIGITAL_ScaleForeColor, Arial_10_Bold, false);  bg.drawFastHLine(65, 296 - y, 8, DIGITAL_ScaleMarkerColor); bg.drawFastHLine(118, 296 - y, 5, DIGITAL_LineMarkerColor); bg.drawFastHLine(168, 296 - y, 8, DIGITAL_ScaleMarkerColor); bg.drawText("40", iVec2(185, 300 - y - 4), DIGITAL_ScaleForeColor, Arial_10_Bold, false); }
            dBPre = dB;
        }
    }

    // draw correlation backgrounds
    bg.fillRect(40, 304, 161, 8, DIGITAL_CorrelationBackgroundColor);
    bg.drawFastHLine(40, 316, 161, DIGITAL_CorrelationHoldBackgroundColor);

    // draw correlation frame marker
    bg.drawFastVLine(39, 304, 8, DIGITAL_CorrelationMarkerColor);
    bg.drawFastVLine(201, 304, 8, DIGITAL_CorrelationMarkerColor);
    bg.drawFastVLine(39, 315, 3, DIGITAL_CorrelationMarkerColor);
    bg.drawFastVLine(120, 315, 3, DIGITAL_CorrelationTextColor);
    bg.drawFastVLine(201, 315, 3, DIGITAL_CorrelationMarkerColor);

    // draw correlation -1/+1
    bg.drawText("-1", iVec2(18, 316), DIGITAL_CorrelationTextColor, Arial_10, false);
    bg.drawText("+1", iVec2(210, 316), DIGITAL_CorrelationTextColor, Arial_10, false);

    // draw "L" & "R"
    bg.drawText("L", iVec2(11, 182), DIGITAL_LRColor, Arial_18, false);
    bg.drawText("R", iVec2(211, 182), DIGITAL_LRColor, Arial_18, false);

    // copy background to front
    memcpy(frontBuffer, backBuffer, 153600);
    drawDigital(reset);
    tft.update(frontBuffer, true);
    
}

/// <summary>
/// all draws & update framebuffer
/// </summary>
/// /// <param name="reset"></param>
void drawDigital(bool reset) {
    getSamples(DIGITAL_SampleBlocks);
    drawCorrelationDigital(drawLeftBarDigital(reset) + drawRightBarDigital(reset), reset);
    drawHeaderDigital();
    tft.update(frontBuffer, false);

}

/// <summary>
/// draw left bar
/// </summary>
/// <param name="reset"></param>
/// <returns>rms bar length</returns>
uint16_t drawLeftBarDigital(bool reset) {
    // static vars
    static uint16_t pastPeak = 0, pastRms = 0, rmsHoldCounter = 0, peakHoldCounter = 0, rmsFallingCounter = 0, peakFallingCounter = 0, peakHoldMax = 0, rmsHoldMax = 0;

    // clear hold max
    if (reset) { peakHoldMax = 0; rmsHoldMax = 0; }

    if (rms1.available()) {
        // read RMS & PEAK, calculate dB & scale dB range to bar length
        uint16_t rmsVal = map(rmsAmplitudeTodB(rms1.read(), 0), DIGITAL_dBLow, dBHigh, 0, 260);
        uint16_t peakVal = (DIGITAL_ShowPeakBars) ? map(peakAmplitudeTodB(peak1.read(), 0), DIGITAL_dBLow, dBHigh, 0, 260) : 0;

        // get previous bar data
        uint16_t peakTmp = pastPeak;
        uint16_t rmsTmp = pastRms;

        // ballistics
        if (peakVal < peakTmp - DIGITAL_PEAKBarRelease) peakVal = peakTmp - DIGITAL_PEAKBarRelease; // peak
        if (peakTmp < peakVal - DIGITAL_PEAKBarAttack) peakVal = peakTmp + DIGITAL_PEAKBarAttack; // peak
        if (rmsVal < rmsTmp - DIGITAL_VUBarRelease) rmsVal = rmsTmp - DIGITAL_VUBarRelease; // rms
        if (rmsTmp < rmsVal - DIGITAL_VUBarAttack) rmsVal = rmsTmp + DIGITAL_VUBarAttack; // rms
        if (++rmsHoldCounter > DIGITAL_VUPeakHoldTime && rmsFallingCounter > DIGITAL_VUPeakRelease) rmsFallingCounter -= DIGITAL_VUPeakRelease; // rms
        if (++peakHoldCounter > DIGITAL_PEAKPeakHoldTime && peakFallingCounter > DIGITAL_PEAKPeakRelease) peakFallingCounter -= DIGITAL_PEAKPeakRelease; // peak

        // store bar data
        pastPeak = peakVal;
        pastRms = rmsVal;

        // store new RMS level and reset the hold counter 
        if (rmsVal > rmsFallingCounter) {
            rmsFallingCounter = rmsVal + 1.; // +1 is very important!
            rmsHoldCounter = 0;
        }

        // store new PEAK level and reset the hold counter 
        if (peakVal > peakFallingCounter) {
            peakFallingCounter = peakVal + 1.; // +1 is very important!
            peakHoldCounter = 0;
        }

        // store new max level for RMS peakhold
        if (rmsVal > rmsHoldMax) {
            rmsHoldMax = rmsVal + 1; // +1 is very important!
        }

        // store new max level for PEAK peakhold
        if (peakVal > peakHoldMax) {
            peakHoldMax = peakVal + 1; // +1 is very important!
        }

        // draw bars and peaks
        for (uint16_t y = 0; y < 260; y++) {
            float dB = roundf(map((float)y, 0, 260, DIGITAL_dBLow, 6.0f));

            uint16_t color = DIGITAL_VUBarColorNormal;
            if (DIGITAL_UseWheel) color = rainbow(map(y, 260, 0, 0, 127));
            else if (dB >= 0.0f) color = DIGITAL_VUBarColorOver;
            else if (dB >= -5.0f) color = DIGITAL_VUBarColorMid;

            // draw PEAK bars
            if (y < peakTmp) {
                im.drawFastHLine(113, 296 - y, 4, (DIGITAL_PEAKSegmentHeight == 0) ? DIGITAL_PEAKBarColor : (y % (DIGITAL_PEAKSegmentHeight + 1) == 0) ? DIGITAL_DisplayBackColor : DIGITAL_PEAKBarColor); // bar
            } else {
                if (DIGITAL_PeakHold) {
                    im.drawFastHLine(113, 296 - y, 4, (y > 10 && y >= peakHoldMax && y < peakHoldMax + DIGITAL_PEAKPeakHeight) ? DIGITAL_PEAKPeakColor : DIGITAL_DisplayBackColor);
                } else {
                    im.drawFastHLine(113, 296 - y, 4, (y > 10 && y >= peakFallingCounter && y < peakFallingCounter + DIGITAL_PEAKPeakHeight) ? DIGITAL_PEAKPeakColor : DIGITAL_DisplayBackColor);
                }
            }

            // draw RMS bars
            if (y < rmsTmp) {
                im.drawFastHLine(79, 296 - y, 29, (DIGITAL_VUSegmentHeight == 0) ? color : (y % (DIGITAL_VUSegmentHeight + 1) == 0) ? DIGITAL_DisplayBackColor : color); // bar
            } else {
                if (y == DIGITAL_dBnullPosition) { // draw 0dB line
                    im.drawFastHLine(79, 296 - y, 29, DIGITAL_VUNullDBMarkerColor);
                } else { // draw peak
                    if (DIGITAL_PeakHold) {
                        im.drawFastHLine(79, 296 - y, 29, (y > 10 && y >= rmsHoldMax && y <= rmsHoldMax + DIGITAL_VUPeakHeight) ? DIGITAL_VUPeakColor : DIGITAL_DisplayBackColor);
                    } else {
                        im.drawFastHLine(79, 296 - y, 29, (y > 10 && y >= rmsFallingCounter && y < rmsFallingCounter + DIGITAL_VUPeakHeight) ? DIGITAL_VUPeakColor : DIGITAL_DisplayBackColor);
                    }
                }
            }
        }
        return rmsVal;
    }
    return 0;
}

/// <summary>
/// draw right bar
/// </summary>
/// <param name="reset"></param>
/// <returns>rms bar length</returns>
uint16_t drawRightBarDigital(bool reset) {
    // static vars
    static uint16_t  pastPeak = 0, pastRms = 0, rmsHoldCounter = 0, peakHoldCounter = 0, rmsFallingCounter = 0, peakFallingCounter = 0, peakHoldMax = 0, rmsHoldMax = 0;

    // clear hold max
    if (reset) { peakHoldMax = 0; rmsHoldMax = 0; }

    if (rms2.available()) {
        // read RMS & PEAK, calculate dB & scale dB range to bar length
        uint16_t rmsVal = map(rmsAmplitudeTodB(rms2.read(), 1), DIGITAL_dBLow, dBHigh, 0, 260);
        uint16_t peakVal = (DIGITAL_ShowPeakBars) ? map(peakAmplitudeTodB(peak2.read(), 1), DIGITAL_dBLow, dBHigh, 0, 260) : 0;

        // get previous bar data
        uint16_t peakTmp = pastPeak;
        uint16_t rmsTmp = pastRms;

        // ballistics
        if (peakVal < peakTmp - DIGITAL_PEAKBarRelease) peakVal = peakTmp - DIGITAL_PEAKBarRelease; // peak
        if (peakTmp < peakVal - DIGITAL_PEAKBarAttack) peakVal = peakTmp + DIGITAL_PEAKBarAttack; // peak
        if (rmsVal < rmsTmp - DIGITAL_VUBarRelease) rmsVal = rmsTmp - DIGITAL_VUBarRelease; // rms
        if (rmsTmp < rmsVal - DIGITAL_VUBarAttack) rmsVal = rmsTmp + DIGITAL_VUBarAttack; // rms
        if (++rmsHoldCounter > DIGITAL_VUPeakHoldTime && rmsFallingCounter > DIGITAL_VUPeakRelease) rmsFallingCounter -= DIGITAL_VUPeakRelease; // rms
        if (++peakHoldCounter > DIGITAL_PEAKPeakHoldTime && peakFallingCounter > DIGITAL_PEAKPeakRelease) peakFallingCounter -= DIGITAL_PEAKPeakRelease; // peak

        // store bar data
        pastPeak = peakVal;
        pastRms = rmsVal;

        // store new RMS level and reset the hold counter 
        if (rmsVal > rmsFallingCounter) {
            rmsFallingCounter = rmsVal + 1.; // +1 is very important!
            rmsHoldCounter = 0;
        }

        // store new PEAK level and reset the hold counter 
        if (peakVal > peakFallingCounter) {
            peakFallingCounter = peakVal + 1.; // +1 is very important!
            peakHoldCounter = 0;
        }

        // store new max level for RMS peakhold
        if (rmsVal > rmsHoldMax) {
            rmsHoldMax = rmsVal + 1; // +1 is very important!
        }

        // store new max level for PEAK peakhold
        if (peakVal > peakHoldMax) {
            peakHoldMax = peakVal + 1; // +1 is very important!
        }

        // draw bars and peaks
        for (uint16_t y = 0; y < 260; y++) {
            float dB = roundf(map((float)y, 0, 260, DIGITAL_dBLow, 6.0f));

            uint16_t color = DIGITAL_VUBarColorNormal;
            if (DIGITAL_UseWheel) color = rainbow(map(y, 260, 0, 0, 127));
            else if (dB >= 0.0f) color = DIGITAL_VUBarColorOver;
            else if (dB >= -5.0f) color = DIGITAL_VUBarColorMid;

            // draw PEAK bars
            if (y < peakTmp) {
                im.drawFastHLine(124, 296 - y, 4, (DIGITAL_PEAKSegmentHeight == 0) ? DIGITAL_PEAKBarColor : (y % (DIGITAL_PEAKSegmentHeight + 1) == 0) ? DIGITAL_DisplayBackColor : DIGITAL_PEAKBarColor); // bar
            } else {
                if (DIGITAL_PeakHold) {
                    im.drawFastHLine(124, 296 - y, 4, (y > 10 && y >= peakHoldMax && y < peakHoldMax + DIGITAL_PEAKPeakHeight) ? DIGITAL_PEAKPeakColor : DIGITAL_DisplayBackColor);
                } else {
                    im.drawFastHLine(124, 296 - y, 4, (y > 10 && y >= peakFallingCounter && y < peakFallingCounter + DIGITAL_PEAKPeakHeight) ? DIGITAL_PEAKPeakColor : DIGITAL_DisplayBackColor);
                }
            }

            // draw RMS bars
            if (y < rmsTmp) {
                im.drawFastHLine(133, 296 - y, 29, (DIGITAL_VUSegmentHeight == 0) ? color : (y % (DIGITAL_VUSegmentHeight + 1) == 0) ? DIGITAL_DisplayBackColor : color); // bar
            } else {
                if (y == DIGITAL_dBnullPosition) { // draw 0dB line
                    im.drawFastHLine(133, 296 - y, 29, DIGITAL_VUNullDBMarkerColor);
                } else { // draw peak
                    if (DIGITAL_PeakHold) {
                        im.drawFastHLine(133, 296 - y, 29, (y > 10 && y >= rmsHoldMax && y <= rmsHoldMax + DIGITAL_VUPeakHeight) ? DIGITAL_VUPeakColor : DIGITAL_DisplayBackColor);
                    } else {
                        im.drawFastHLine(133, 296 - y, 29, (y > 10 && y >= rmsFallingCounter && y < rmsFallingCounter + DIGITAL_VUPeakHeight) ? DIGITAL_VUPeakColor : DIGITAL_DisplayBackColor);
                    }
                }
            }
        }
        return rmsVal;
    }
    return 0;
}

/// <summary>
/// draw correlation
/// </summary>
/// <param name="totalLength"></param>
/// <param name="reset"></param>
void drawCorrelationDigital(uint16_t totalLength, bool reset) {
    // static vars
    static float avgPrev = 0.0f;
    static uint16_t frame = 0, negativeMax = 0, negativeMaxHold = 0, positiveMax = 0, positiveMaxHold = 0;

    // vars
    float  normL = 0.0f, normR = 0.0f, value = 0.0f, runningTotal = 0.0f, avg = 0.0f;
    uint16_t corrPos = 0, corrBarLength = 0;

    // loop through the samples
    for (uint16_t i = 0; i < DIGITAL_SampleBlocks * 128; i++) {
        normL = samplesLeft[i] / 32767.0f;
        normR = samplesRight[i] / 32767.0f;

        // correlation
        runningTotal += cosf((atan2f(normL, normR) - 0.78539816f) * 2.0f);
    }

    // correlation avg
    avg = runningTotal / (float)(DIGITAL_SampleBlocks * 128);

    // bars avaiable -> reset clear trigger, not -> reset avg 
    if (totalLength > 0) frame = 0; else avg = 0.0f;

    // ballistics for correlation
    value = (abs(avg - avgPrev) > 0.01f) ? (avg > avgPrev) ? avgPrev + 0.01f : avgPrev - 0.01f : avg; avgPrev = value;

    // delimiter
    if (value > 1.0f) value = 1.0f;
    if (value < -1.0f) value = -1.0f;

    // set correlation box color from value and hysteresis
    corrPos = 120.0f + (80.0f * value);
    corrBarLength = abs(80.0f * value);

    // set colors for correlation rectangle and store min/max values for correlation maxhold view
    uint16_t corBox = DIGITAL_CorrelationNullColor;
    if (corrPos > 120) {
        if (corrPos > 122) corBox = DIGITAL_CorrelationPlusColor;
        if (corrBarLength > positiveMax) {
            positiveMax = corrBarLength;
            if (positiveMax > positiveMaxHold) positiveMaxHold = positiveMax;
        }
    } else if (corrPos < 120) {
        if (corrPos < 118) corBox = DIGITAL_CorrelationMinusColor;
        if (corrBarLength > negativeMax) {
            negativeMax = corrBarLength;
            if (negativeMax > negativeMaxHold) negativeMaxHold = negativeMax;
        }
    } else {
        corBox = DIGITAL_CorrelationNullColor;
    }

    // optical delimiter
    if (corrPos <= 40) corrPos = 40;
    else if (corrPos > 194) corrPos = 194;
    else corrPos -= 3;

    // reset maxhold values after 2000 frames or reset
    if ((++frame == 2000 && !DIGITAL_PeakHold) || reset) {
        negativeMax = 0; positiveMax = 0; positiveMaxHold = 0; negativeMaxHold = 0;
        // copy background to front (from line 304 to 317)
        memcpy(frontBuffer + 72960, backBuffer + 72960, 6240);
    } else {
        // draw correlation box and middle marker
        im.fillRect(40, 304, 161, 8, DIGITAL_CorrelationBackgroundColor);
        im.drawFastVLine(120, 304, 8, DIGITAL_CorrelationTextColor);
        im.fillRect(corrPos, 304, 7, 8, corBox);
    }

    // draw negative hold correlation
    if (negativeMaxHold > 0) im.drawFastHLine(120 - negativeMaxHold, 316, negativeMaxHold, DIGITAL_CorrelationHoldColor);

    // draw positive hold correlation
    if (positiveMaxHold > 0) im.drawFastHLine(121, 316, positiveMaxHold, DIGITAL_CorrelationHoldColor);
}

/// <summary>
/// draw header
/// </summary>
void drawHeaderDigital() {
    if (DIGITAL_ShowHeader) {
        im.fillRect(80, 32, 80, 10, DIGITAL_DisplayBackColor);
        im.drawText(DIGITAL_ShowPeakBars ? "RMS  PPM  RMS" : "RMS", iVec2(DIGITAL_ShowPeakBars ? 83 : 110, 41), DIGITAL_HeaderForeColor, Arial_8, false);
    }
}
