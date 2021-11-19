#ifndef LiquidCrystalSerial_Master_h
#define LiquidCrystalSerial_Master_h

#include <Arduino.h>

//commands
#define LCD_PAYLOAD_START 0x02
#define LCD_PAYLOAD_END 0x03
#define LCD_BEGIN 0x80
#define LCD_CLEAR 0x81
#define LCD_HOME 0x82
#define LCD_SET_CURSOR 0x83
#define LCD_WRITE 0x84
#define LCD_PRINT 0x85
#define LCD_CURSOR 0x86
#define LCD_NO_CURSOR 0x87
#define LCD_BLINK 0x88
#define LCD_NO_BLINK 0x89
#define LCD_DISPLAY 0x8A
#define LCD_NO_DISPLAY 0x8B
#define LCD_SCROLL_DISPLAY_LEFT 0x8C
#define LCD_SCROLL_DISPLAY_RIGHT 0x8D
#define LCD_AUTOSCROLL 0x8E
#define LCD_NO_AUTOSCROLL 0x8F
#define LCD_LEFT_TO_RIGHT 0x90
#define LCD_RIGHT_TO_LEFT 0x91
#define LCD_CREATE_CHAR 0x92
#define LCD_SET_ROW_OFFSETS 0x93
#define LCD_COMMAND 0x94
#define LCD_BACKLIGHT 0x95
#define LCD_NO_BACKLIGHT 0x96
#define LCD_LINE_WRAP 0x97
#define LCD_NO_LINE_WRAP 0x98
#define LCD_MOVE_CURSOR_LEFT 0x99
#define LCD_MOVE_CURSOR_RIGHT 0x9A
#define LCD_ON 0x9B
#define LCD_OFF 0x9C

class LiquidCrystalSerial_Master
{
  public:
    LiquidCrystalSerial_Master(HardwareSerial* lcdSerial, unsigned long lcdDelay=100);
	void begin(unsigned long speed);
	uint8_t lcdBegin(uint8_t col, uint8_t row);
	uint8_t lcdClear();
	uint8_t lcdHome();
	uint8_t lcdSetCursor(uint8_t col, uint8_t row);
	void lcdWrite(byte data);
	void lcdWrite(char* data);
	void lcdWrite(byte* data, uint8_t nBytes);
	void lcdPrint(char* data);
	uint8_t lcdCursor();
	uint8_t lcdBlink();
	uint8_t lcdNoBlink();
	uint8_t lcdDisplay();
	uint8_t lcdNoDisplay();
	uint8_t lcdScrollDisplayLeft();
	uint8_t lcdScrollDisplayRight();
	uint8_t lcdAutoscroll();
	uint8_t lcdNoAutoscroll();
	uint8_t lcdLeftToRight();
	uint8_t lcdRightToLeft();
	uint8_t lcdCreateChar(uint8_t charval, uint8_t* charmap);
	uint8_t lcdSetRowOffsets(uint8_t row1);
	uint8_t lcdSetRowOffsets(uint8_t row1, uint8_t row2);
	uint8_t lcdSetRowOffsets(uint8_t row1, uint8_t row2, uint8_t row3);
	uint8_t lcdSetRowOffsets(uint8_t row1, uint8_t row2, uint8_t row3, uint8_t row4);
	uint8_t lcdCommand(byte data);
	uint8_t lcdBacklight();
	uint8_t lcdNoBacklight();
	uint8_t lcdLineWrap();
	uint8_t lcdNoLineWrap();
	uint8_t lcdMoveCursorLeft();
	uint8_t lcdMoveCursorRight();
	uint8_t lcdOn();
	uint8_t lcdOff();
	
  private:
	uint8_t stringSize(char* data);
	uint8_t sendCmd(uint8_t command);
	uint8_t sendCmd(uint8_t command, byte* data, uint8_t nBytes);
	HardwareSerial* lcdSerial;
	unsigned long lcdDelay;
	struct lcdColRowStruct {
		uint8_t col;
		uint8_t row;
	};
	struct lcdCreateCharStruct {
		uint8_t charval;
		uint8_t charmap[8];
	};
	struct lcdSet2RowOffsetsStruct {
		uint8_t row1;
		uint8_t row2;
	};
	struct lcdSet3RowOffsetsStruct {
		uint8_t row1;
		uint8_t row2;
		uint8_t row3;
	};
	struct lcdSet4RowOffsetsStruct {
		uint8_t row1;
		uint8_t row2;
		uint8_t row3;
		uint8_t row4;
	};
};

#endif
