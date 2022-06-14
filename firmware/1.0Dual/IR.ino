/// <summary>
/// decode results from IR remote control
/// </summary>
/// <param name="value"></param>
void decodeIR(uint32_t value) {
  
    if (value != 0xFFFFFFFF) {
        // write IR code out
        Serial.printf("{[ir]%x}", value);

        if (value == IR_Left) { // left
            if (--moduleType < 0) moduleType = 3;
            modeSwitch();

        } else if (value == IR_Right) { // right
            if (++moduleType > 3) moduleType = 0;
            modeSwitch();

        } else if (value == IR_Up) { // up
            switch (moduleType) {
            case 0:
                DIGITAL_ShowPeakBars = !DIGITAL_ShowPeakBars;
                Serial.print("{DIGITAL_ShowPeakBars=" + String(DIGITAL_ShowPeakBars) + "}");
                break;

            case 1:
                if (++ANALOG_Mode > 2) ANALOG_Mode = 0;
                Serial.print("{ANALOG_Mode=" + String(ANALOG_Mode) + "}"); // black, white, warm
                displayInitAnalog();
                break;

            case 2:
                if (++FFT_BarMode > 5) FFT_BarMode = 0;
                Serial.print("{FFT_BarMode=" + String(FFT_BarMode) + "}");
                displayInitFFT(false);
                break;

            case 3:
                if (++GONIO_DrawMode > 1) GONIO_DrawMode = 0;
                Serial.print("{GONIO_DrawMode=" + String(GONIO_DrawMode) + "}");
                break;
            }

        } else if (value == IR_Down) { // down
            switch (moduleType) {
            case 0:
                DIGITAL_ShowPeakBars = !DIGITAL_ShowPeakBars;
                Serial.print("{DIGITAL_ShowPeakBars=" + String(DIGITAL_ShowPeakBars) + "}");
                break;

            case 1:
                if (--ANALOG_Mode < 0) ANALOG_Mode = 2;
                Serial.print("{ANALOG_Mode=" + String(ANALOG_Mode) + "}");
                displayInitAnalog();
                break;

            case 2:
                if (--FFT_BarMode < 0) FFT_BarMode = 5;
                Serial.print("{FFT_BarMode=" + String(FFT_BarMode) + "}");
                displayInitFFT(false);
                break;

            case 3:
                if (--GONIO_DrawMode < 0) GONIO_DrawMode = 1;
                Serial.print("{GONIO_DrawMode=" + String(GONIO_DrawMode) + "}");
                break;
            }

        } else if (value == IR_PlayStop) { // play/stop
            calibrate = !calibrate;
            initalizeDisplayFromModuleType(moduleType);

        } else if (value == IR_Menu) { // menu

            Serial.print("{MenuVisible=1}");

            switch (moduleType) {
            case 0: // DIGITAL
                DIGITAL_MenuActive = true;
                drawMenu(strMenuDIGITAL, DIGITAL_WorkMode);
                break;
            case 1: // ANALOG
                ANALOG_MenuActive = true;
                drawMenu(strMenuANALOG, ANALOG_PeakLEDdB);
                break;
            case 2: // SPECTRUMANALYZER
                FFT_MenuActive = true;
                drawMenu(strMenuFFT, FFT_WorkMode);
                break;
            case 3: // GONIO
                GONIO_MenuActive = true;
                drawMenu(strMenuGONIO, GONIO_WorkMode);
                break;
            }
        }
    }
    
}

/// <summary>
/// DIGITAL menu
/// </summary>
/// <param name="value"></param>
void decodeMenuDigital(uint32_t value) {
 
    if (value != 0xFFFFFFFF) {
        if (value == IR_Up) { // up
            if (--DIGITAL_WorkMode < 0) DIGITAL_WorkMode = 3;
            drawMenu(strMenuDIGITAL, DIGITAL_WorkMode);

        } else if (value == IR_Down) { // down
            if (++DIGITAL_WorkMode > 3) DIGITAL_WorkMode = 0;
            drawMenu(strMenuDIGITAL, DIGITAL_WorkMode);

        } else if (results.value == IR_Menu) { // menu
            int16_t testRead = 0;
            EEPROM.get(504, testRead);
            if (DIGITAL_WorkMode != testRead) {
                EEPROM.put(504, DIGITAL_WorkMode);
                Serial.print("{DIGITAL_WorkMode=" + String(DIGITAL_WorkMode) + "}");
            }

            setMode(false);
            displayInitDigital(false);
            Serial.print("{MenuVisible=0}");
            DIGITAL_MenuActive = false;
        }
    }
    
}

/// <summary>
/// ANALOG menu
/// </summary>
/// <param name="value"></param>
void decodeMenuAnalog(uint32_t value) {
  
    if (value != 0xFFFFFFFF) {
        if (value == IR_Up) { // up
            if (--ANALOG_PeakLEDdB < 0) ANALOG_PeakLEDdB = 6;
            drawMenu(strMenuANALOG, ANALOG_PeakLEDdB);

        } else if (value == IR_Down) { // down
            if (++ANALOG_PeakLEDdB > 6) ANALOG_PeakLEDdB = 0;
            drawMenu(strMenuANALOG, ANALOG_PeakLEDdB);

        } else if (results.value == IR_Menu) { // menu
            int16_t testRead = 0;
            EEPROM.get(610, testRead);
            if (ANALOG_PeakLEDdB != testRead) {
                EEPROM.put(610, ANALOG_PeakLEDdB);
                Serial.print("{ANALOG_PeakLEDdB=" + String(ANALOG_PeakLEDdB) + "}");
            }

            displayInitAnalog();
            Serial.print("{MenuVisible=0}");
            ANALOG_MenuActive = false;
        }
    }
    
}

/// <summary>
/// SPECTRUMANALYZER menu
/// </summary>
/// <param name="value"></param>
void decodeMenuFFT(uint32_t value) {
  
    if (value != 0xFFFFFFFF) {
        if (value == IR_Up) { // up
            if (--FFT_WorkMode < 0) FFT_WorkMode = 11;
            drawMenu(strMenuFFT, FFT_WorkMode);

        } else if (value == IR_Down) { // down
            if (++FFT_WorkMode > 11) FFT_WorkMode = 0;
            drawMenu(strMenuFFT, FFT_WorkMode);

        } else if (results.value == IR_Menu) { // menu
            int16_t testRead = 0;
            EEPROM.get(706, testRead);
            if (FFT_WorkMode != testRead) {
                EEPROM.put(706, FFT_WorkMode);
                Serial.print("{FFT_WorkMode=" + String(FFT_WorkMode) + "}");
            }

            setMode(false);
            displayInitFFT(false);
            Serial.print("{MenuVisible=0}");
            FFT_MenuActive = false;
        }
    }
    
}

/// <summary>
/// GONIO Menu
/// </summary>
/// <param name="value"></param>
void decodeMenuGoniometer(uint32_t value) {
  
    if (value != 0xFFFFFFFF) {
        if (value == IR_Up) { // up
            if (--GONIO_WorkMode < 0) GONIO_WorkMode = 7;
            drawMenu(strMenuGONIO, GONIO_WorkMode);

        } else if (value == IR_Down) { // down
            if (++GONIO_WorkMode > 7) GONIO_WorkMode = 0;
            drawMenu(strMenuGONIO, GONIO_WorkMode);

        } else if (results.value == IR_Menu) { // menu
            int16_t testRead = 0;
            EEPROM.get(806, testRead);
            if (GONIO_WorkMode != testRead) {
                EEPROM.put(806, GONIO_WorkMode);
                Serial.print("{GONIO_WorkMode=" + String(GONIO_WorkMode) + "}");
            }

            setMode(false);
            displayInitGonio(false);
            Serial.print("{MenuVisible=0}");
            GONIO_MenuActive = false;
        }
    }
    
}
