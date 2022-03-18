#include <LiquidCrystalSerial_Master.h>

LiquidCrystalSerial_Master::LiquidCrystalSerial_Master(){
}

void LiquidCrystalSerial_Master::lcdSerialBegin(unsigned long speed){
	Serial.begin(speed);
}

byte LiquidCrystalSerial_Master::lcdBegin(byte col, byte row){
	LiquidCrystalSerial_Master::screenSize = col * row;
	lcdColRowStruct lcr = {col, row};
	return sendCmd(LCD_BEGIN, (byte*) &lcr, sizeof(lcr));
}

byte LiquidCrystalSerial_Master::lcdClear(){
	return sendCmd(LCD_CLEAR);
}

byte LiquidCrystalSerial_Master::lcdHome(){
	return sendCmd(LCD_HOME);
}

byte LiquidCrystalSerial_Master::lcdSetCursor(byte col, byte row){
	lcdColRowStruct lcr = {col, row};
	return sendCmd(LCD_SET_CURSOR, (byte*) &lcr, sizeof(lcr));
}

void LiquidCrystalSerial_Master::lcdWrite(byte data){
	sendCmd(LCD_WRITE, &data, sizeof(data));
}

void LiquidCrystalSerial_Master::lcdWrite(char* data){
	sendCmd(LCD_WRITE, (byte*) data, stringSize(data));
}

void LiquidCrystalSerial_Master::lcdWrite(byte* data, byte nBytes){
	sendCmd(LCD_WRITE, data, nBytes);
}

void LiquidCrystalSerial_Master::lcdPrint(char* data){
	sendCmd(LCD_PRINT, (byte*) data, stringSize(data));
}

byte LiquidCrystalSerial_Master::lcdCursor(){
	return sendCmd(LCD_CURSOR);
}

byte LiquidCrystalSerial_Master::lcdNoCursor(){
	return sendCmd(LCD_NO_CURSOR);
}

byte LiquidCrystalSerial_Master::lcdBlink(){
	return sendCmd(LCD_BLINK);
}

byte LiquidCrystalSerial_Master::lcdNoBlink(){
	return sendCmd(LCD_NO_BLINK);
}

byte LiquidCrystalSerial_Master::lcdDisplay(){
	return sendCmd(LCD_DISPLAY);
}

byte LiquidCrystalSerial_Master::lcdNoDisplay(){
	return sendCmd(LCD_NO_DISPLAY);
}

byte LiquidCrystalSerial_Master::lcdScrollDisplayLeft(){
	return sendCmd(LCD_SCROLL_DISPLAY_LEFT);
}

byte LiquidCrystalSerial_Master::lcdScrollDisplayRight(){
	return sendCmd(LCD_SCROLL_DISPLAY_RIGHT);
}

byte LiquidCrystalSerial_Master::lcdAutoscroll(){
	return sendCmd(LCD_AUTOSCROLL);
}

byte LiquidCrystalSerial_Master::lcdNoAutoscroll(){
	return sendCmd(LCD_NO_AUTOSCROLL);
}

byte LiquidCrystalSerial_Master::lcdLeftToRight(){
	return sendCmd(LCD_LEFT_TO_RIGHT);
}

byte LiquidCrystalSerial_Master::lcdRightToLeft(){
	return sendCmd(LCD_RIGHT_TO_LEFT);
}

byte LiquidCrystalSerial_Master::lcdCreateChar(byte charval, byte* charmap){
	lcdCreateCharStruct lcc;
	lcc.charval = charval;
	memcpy(lcc.charmap, charmap, sizeof(lcc.charmap));
	return sendCmd(LCD_CREATE_CHAR, (byte*) &lcc, sizeof(lcc));
}

byte LiquidCrystalSerial_Master::lcdSetRowOffsets(byte row1){
	return sendCmd(LCD_SET_ROW_OFFSETS, (byte*) &row1, sizeof(row1));
}

byte LiquidCrystalSerial_Master::lcdSetRowOffsets(byte row1, byte row2){
	lcdSet2RowOffsetsStruct ls2ro = {row1, row2};
	return sendCmd(LCD_SET_ROW_OFFSETS, (byte*) &ls2ro, sizeof(ls2ro));
}

byte LiquidCrystalSerial_Master::lcdSetRowOffsets(byte row1, byte row2, byte row3){
	lcdSet3RowOffsetsStruct ls3ro = {row1, row2, row3};
	return sendCmd(LCD_SET_ROW_OFFSETS, (byte*) &ls3ro, sizeof(ls3ro));
}

byte LiquidCrystalSerial_Master::lcdSetRowOffsets(byte row1, byte row2, byte row3, byte row4){
	lcdSet4RowOffsetsStruct ls4ro = {row1, row2, row3, row4};
	return sendCmd(LCD_SET_ROW_OFFSETS, (byte*) &ls4ro, sizeof(ls4ro));
}

byte LiquidCrystalSerial_Master::lcdCommand(byte data){
	sendCmd(LCD_COMMAND, &data, sizeof(data));
}

byte LiquidCrystalSerial_Master::lcdBacklight(){
	return sendCmd(LCD_BACKLIGHT);
}

byte LiquidCrystalSerial_Master::lcdNoBacklight(){
	return sendCmd(LCD_NO_BACKLIGHT);
}

byte LiquidCrystalSerial_Master::lcdLineWrap(){
	return sendCmd(LCD_LINE_WRAP);
}

byte LiquidCrystalSerial_Master::lcdNoLineWrap(){
	return sendCmd(LCD_NO_LINE_WRAP);
}

byte LiquidCrystalSerial_Master::lcdMoveCursorLeft(){
	return sendCmd(LCD_MOVE_CURSOR_LEFT);
}

byte LiquidCrystalSerial_Master::lcdMoveCursorRight(){
	return sendCmd(LCD_MOVE_CURSOR_RIGHT);
}

void LiquidCrystalSerial_Master::lcdSetExecTimes(uint16_t chUs, uint16_t insU){
	lcdSetExecTimesStruct let = {chUs, insU};
	sendCmd(LCD_SET_EXEC_TIMES, (byte*) &let, sizeof(let));
}

byte LiquidCrystalSerial_Master::lcdOn(){
	return sendCmd(LCD_ON);
}

byte LiquidCrystalSerial_Master::lcdOff(){
	return sendCmd(LCD_OFF);
}

byte LiquidCrystalSerial_Master::stringSize(char* data){
	byte i = 0;
	while(data[i] != 0x00){
		if(i == LiquidCrystalSerial_Master::screenSize){
			data[i] = 0x00;
			break;
		}
		i++;
	}
	return i + 1;
}

byte LiquidCrystalSerial_Master::sendCmd(byte command){
	byte result;
	Serial.write(LCD_PAYLOAD_START);
	Serial.write(command);
	Serial.write((byte) 0);
	Serial.readBytes(&result, sizeof(result));
	return result;
}

byte LiquidCrystalSerial_Master::sendCmd(byte command, byte* payload, byte nBytesPayload){
	byte result;
	Serial.write(LCD_PAYLOAD_START);
	Serial.write(command);
	Serial.write(nBytesPayload);
	Serial.write(payload, nBytesPayload);
	Serial.readBytes(&result, sizeof(result));
	return result;
}
