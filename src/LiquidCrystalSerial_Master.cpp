#include <LiquidCrystalSerial_Master.h>

LiquidCrystalSerial_Master::LiquidCrystalSerial_Master(SoftwareSerial* lcdSerial, unsigned long lcdDelay){
	LiquidCrystalSerial_Master::lcdSerial = lcdSerial;
	LiquidCrystalSerial_Master::lcdDelay = lcdDelay;
}

void LiquidCrystalSerial_Master::lcdSerialBegin(unsigned long speed){
	LiquidCrystalSerial_Master::lcdSerial->begin(speed);
}

uint8_t LiquidCrystalSerial_Master::lcdBegin(uint8_t col, uint8_t row){
	LiquidCrystalSerial_Master::screenSize = col * row;
	lcdColRowStruct lcr = {col, row};
	return sendCmd(LCD_BEGIN, (byte*) &lcr, sizeof(lcr));
}

uint8_t LiquidCrystalSerial_Master::lcdClear(){
	return sendCmd(LCD_CLEAR);
}

uint8_t LiquidCrystalSerial_Master::lcdHome(){
	return sendCmd(LCD_HOME);
}

uint8_t LiquidCrystalSerial_Master::lcdSetCursor(uint8_t col, uint8_t row){
	lcdColRowStruct lcr = {col, row};
	return sendCmd(LCD_SET_CURSOR, (byte*) &lcr, sizeof(lcr));
}

void LiquidCrystalSerial_Master::lcdWrite(byte data){
	sendCmd(LCD_WRITE, &data, sizeof(data));
}

void LiquidCrystalSerial_Master::lcdWrite(char* data){
	sendCmd(LCD_WRITE, (byte*) data, stringSize(data));
}

void LiquidCrystalSerial_Master::lcdWrite(byte* data, uint8_t nBytes){
	sendCmd(LCD_WRITE, data, nBytes);
}

void LiquidCrystalSerial_Master::lcdPrint(char* data){
	sendCmd(LCD_PRINT, (byte*) data, stringSize(data));
}

uint8_t LiquidCrystalSerial_Master::lcdCursor(){
	return sendCmd(LCD_CURSOR);
}

uint8_t LiquidCrystalSerial_Master::lcdBlink(){
	return sendCmd(LCD_BLINK);
}

uint8_t LiquidCrystalSerial_Master::lcdNoBlink(){
	return sendCmd(LCD_NO_BLINK);
}

uint8_t LiquidCrystalSerial_Master::lcdDisplay(){
	return sendCmd(LCD_DISPLAY);
}

uint8_t LiquidCrystalSerial_Master::lcdNoDisplay(){
	return sendCmd(LCD_NO_DISPLAY);
}

uint8_t LiquidCrystalSerial_Master::lcdScrollDisplayLeft(){
	return sendCmd(LCD_SCROLL_DISPLAY_LEFT);
}

uint8_t LiquidCrystalSerial_Master::lcdScrollDisplayRight(){
	return sendCmd(LCD_SCROLL_DISPLAY_RIGHT);
}

uint8_t LiquidCrystalSerial_Master::lcdAutoscroll(){
	return sendCmd(LCD_AUTOSCROLL);
}

uint8_t LiquidCrystalSerial_Master::lcdNoAutoscroll(){
	return sendCmd(LCD_NO_AUTOSCROLL);
}

uint8_t LiquidCrystalSerial_Master::lcdLeftToRight(){
	return sendCmd(LCD_LEFT_TO_RIGHT);
}

uint8_t LiquidCrystalSerial_Master::lcdRightToLeft(){
	return sendCmd(LCD_RIGHT_TO_LEFT);
}

uint8_t LiquidCrystalSerial_Master::lcdCreateChar(uint8_t charval, uint8_t* charmap){
	lcdCreateCharStruct lcc;
	lcc.charval = charval;
	memcpy(lcc.charmap, charmap, sizeof(lcc.charmap));
	return sendCmd(LCD_CREATE_CHAR, (byte*) &lcc, sizeof(lcc));
}

uint8_t LiquidCrystalSerial_Master::lcdSetRowOffsets(uint8_t row1){
	return sendCmd(LCD_SET_ROW_OFFSETS, (byte*) &row1, sizeof(row1));
}

uint8_t LiquidCrystalSerial_Master::lcdSetRowOffsets(uint8_t row1, uint8_t row2){
	lcdSet2RowOffsetsStruct ls2ro = {row1, row2};
	return sendCmd(LCD_SET_ROW_OFFSETS, (byte*) &ls2ro, sizeof(ls2ro));
}

uint8_t LiquidCrystalSerial_Master::lcdSetRowOffsets(uint8_t row1, uint8_t row2, uint8_t row3){
	lcdSet3RowOffsetsStruct ls3ro = {row1, row2, row3};
	return sendCmd(LCD_SET_ROW_OFFSETS, (byte*) &ls3ro, sizeof(ls3ro));
}

uint8_t LiquidCrystalSerial_Master::lcdSetRowOffsets(uint8_t row1, uint8_t row2, uint8_t row3, uint8_t row4){
	lcdSet4RowOffsetsStruct ls4ro = {row1, row2, row3, row4};
	return sendCmd(LCD_SET_ROW_OFFSETS, (byte*) &ls4ro, sizeof(ls4ro));
}

uint8_t LiquidCrystalSerial_Master::lcdCommand(byte data){
	sendCmd(LCD_COMMAND, &data, sizeof(data));
}

uint8_t LiquidCrystalSerial_Master::lcdBacklight(){
	return sendCmd(LCD_BACKLIGHT);
}

uint8_t LiquidCrystalSerial_Master::lcdNoBacklight(){
	return sendCmd(LCD_NO_BACKLIGHT);
}

uint8_t LiquidCrystalSerial_Master::lcdLineWrap(){
	return sendCmd(LCD_LINE_WRAP);
}

uint8_t LiquidCrystalSerial_Master::lcdNoLineWrap(){
	return sendCmd(LCD_NO_LINE_WRAP);
}

uint8_t LiquidCrystalSerial_Master::lcdMoveCursorLeft(){
	return sendCmd(LCD_MOVE_CURSOR_LEFT);
}

uint8_t LiquidCrystalSerial_Master::lcdMoveCursorRight(){
	return sendCmd(LCD_MOVE_CURSOR_RIGHT);
}

uint8_t LiquidCrystalSerial_Master::lcdOn(){
	return sendCmd(LCD_ON);
}

uint8_t LiquidCrystalSerial_Master::lcdOff(){
	return sendCmd(LCD_OFF);
}

uint8_t LiquidCrystalSerial_Master::stringSize(char* data){
	uint8_t i = 0;
	while(data[i] != 0x00){
		if(i == LiquidCrystalSerial_Master::screenSize){
			data[i] = 0x00;
			break;
		}
		i++;
	}
	return i + 1;
}

uint8_t LiquidCrystalSerial_Master::sendCmd(uint8_t command){
	delay(LiquidCrystalSerial_Master::lcdDelay);
	byte result[1];
	LiquidCrystalSerial_Master::lcdSerial->write(LCD_PAYLOAD_START);
	LiquidCrystalSerial_Master::lcdSerial->write(command);
	LiquidCrystalSerial_Master::lcdSerial->write(LCD_PAYLOAD_END);
	LiquidCrystalSerial_Master::lcdSerial->readBytes(result, 1);
	return *result;
}

uint8_t LiquidCrystalSerial_Master::sendCmd(uint8_t command, byte* data, uint8_t nBytes){
	delay(LiquidCrystalSerial_Master::lcdDelay);
	byte result[1];
	LiquidCrystalSerial_Master::lcdSerial->write(LCD_PAYLOAD_START);
	LiquidCrystalSerial_Master::lcdSerial->write(command);
	LiquidCrystalSerial_Master::lcdSerial->write(data, nBytes);
	LiquidCrystalSerial_Master::lcdSerial->write(LCD_PAYLOAD_END);
	LiquidCrystalSerial_Master::lcdSerial->readBytes(result, 1);
	return *result;
}
