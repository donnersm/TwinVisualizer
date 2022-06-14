/// <summary>
/// draw menu bars
/// </summary>
/// <param name="arr"></param>
/// <param name="selectedIdx"></param>
void drawMenu(const char* arr[], uint16_t selectedIdx) {
    uint16_t aSize = 0;

    // menu items count
    switch (moduleType) {
    case 0: aSize = 4; break;  // DIGITAL
    case 1: aSize = 7; break;  // ANALOG
    case 2: aSize = 12; break; // SPECTRUMANALYZER
    case 3: aSize = 8; break;  // GONIO
    }

    uint16_t h = aSize * 24;
    uint16_t w = 210;
    uint16_t x = 120 - (w / 2);
    uint16_t y = (147 - (h / 2)) + 26; // 294px and 26px offset

    im.fillScreen(RGB565_Black);
    im.fillRect(x - 3, y - 3, w + 6, h + 5, RGB565_Black);
    im.drawRect(x - 3, y - 3, w + 6, h + 5, (uint16_t)0x8410);

    for (uint16_t i = 0; i < aSize; i++) {
        if (i == selectedIdx) {
            im.fillRect(x, y + i * 24, w, 23, RGB565_Red);
            im.drawText(arr[i], iVec2(x + 5, y + 17 + i * 24), RGB565_White, Arial_12_Bold, false);
        } else {
            im.fillRect(x, y + i * 24, w, 23, (uint16_t)0x4208);
            im.drawText(arr[i], iVec2(x + 5, y + 17 + i * 24), (uint16_t)0xD69A, Arial_12, false);
        }

    }

    tft.update(frontBuffer, true);
}