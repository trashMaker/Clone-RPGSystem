#include "Header.h"

namespace Cto{
	//ReadFile//////////////////////////////////////////////////////////////
	File::File() :SCENE("../Conversation/Ｃトの熱愛ストーリー.txt"){
	}
	File::File(const char* scene) : SCENE(scene){
	}
	File::~File(){
	}
	bool File::readFile(Novel* novel){
		ifstream fin(SCENE);
		string temp;
		int index = 0;
		if (!fin){
			cout << "ファイルオープンできませんでした" << endl;
			return false;
		}
		//try{
		//	if (!fin)throw "ファイルを読み込めませんでした。";
		//}
		//catch (char* ss){
		//	cout << ss << endl;
		//}
		while (!fin.eof()){
			fin >> temp;
			novel->setConversation(temp, index);
			index++;
		}
		novel->setManyLines(index);
		return true;
	}
	//Novel//////////////////////////////////////////////////////////////
	Novel::Novel(){

	}

	Novel::~Novel(){

	}
	void Novel::setConversation(string str, int index){
		conversation[index] = str;
	}
	void Novel::callReadFile(){
		readNovelText.readFile(this);
	}
	void Novel::setManyLines(int index){
		manyLines = index;
	}
	string Novel::getConversation(int index){
		return conversation[index];
	}
//BouyomiChan////////////////////////////////////////////////////////
	BouyomiChan::BouyomiChan(){
		setserver();
	}
	BouyomiChan::~BouyomiChan(){
		//Winsock2終了
		WSACleanup();
	}
	void BouyomiChan::setMsg(string argumentMsg){
		msg = argumentMsg;
	}
	void BouyomiChan::setLen(){
		buf.len = static_cast<long>(msg.size());
		//buf.len = static_cast<long>(msg.length());
		//buf.len = static_cast<long>(strlen(msg.c_str());
	}
	void BouyomiChan::setBuf(short cmd, short speed, short tone, short volume, short voice, char charaterCode,long len){
		//送信するデータの生成(文字列を除いた先頭の部分)
		tempBuf.cmd = cmd;						//[0-1]  (16Bit) コマンド          （ 0:メッセージ読み上げ）
		tempBuf.speed = speed;					//[2-3]  (16Bit) 速度              （-1:棒読みちゃん画面上の設定）
		tempBuf.tone = tone;					//[4-5]  (16Bit) 音程              （-1:棒読みちゃん画面上の設定）
		tempBuf.volume = volume;				//[6-7]  (16Bit) 音量              （-1:棒読みちゃん画面上の設定）
		tempBuf.voice = voice;					//[8-9]  (16Bit) 声質              （ 0:棒読みちゃん画面上の設定、1:女性1、2:女性2、3:男性1、4:男性2、5:中性、6:ロボット、7:機械1、8:機械2、10001～:SAPI5）
		tempBuf.characterCode = charaterCode;	//[10]   ( 8Bit) 文字列の文字コード（ 0:UTF-8, 1:Unicode, 2:Shift-JIS）
		tempBuf.len = len;						//[11-14](32Bit) 文字列の長さ
	}
	void BouyomiChan::setBuf(BUF argumentbuf){
		buf = argumentbuf;
	}
	void BouyomiChan::setserver(){
		server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		server.sin_port				= htons(50001);
		server.sin_family			= AF_INET;
	}
	void BouyomiChan::sendData(BUF buf, string msg, long len){
		//void *p = (void *)&buf;
		send(sock, reinterpret_cast<char*>(&buf), 15, 0);
		send(sock, msg.c_str(), len, 0);
	}

//Tool//////////////////////////////////////////////////////////
	Tool::Tool(){
		
	}

	Tool::~Tool(){

	}

	void Tool::draw(int index){
		int number = -1;
		bool stop = false;
		bool clear = false;
		bool indention = false;
		
		if ((number = novel.getConversation(index).rfind("@")) != -1){
			string temp = (novel.getConversation(index)).erase(number,1);
			novel.setConversation(temp, index);
			stop = true;
		}
		if ((number = novel.getConversation(index).rfind("\\")) != -1){
			string temp = novel.getConversation(index).erase(number, 1);
			novel.setConversation(temp, index);
			clear = true;
		}
		if ((number = novel.getConversation(index).rfind("/")) != -1){
			string temp = novel.getConversation(index).erase(number, 1);
			novel.setConversation(temp, index);
			indention = true;
		}
		cout << novel.getConversation(index);

		if (stop == true){
			getch();
		}
		if (clear == true){
			system("cls");
		}
		if (indention == true){
			cout << endl;
		}
	}
	void Tool::callReadFile(){
		novel.callReadFile();
	}
	int Tool::getManyLines(){
		return novel.getManyLines();
	}
	void Tool::setMsg(int index){
		bouyomiChan.setMsg(novel.getConversation(index));
	}
	void Tool::setTempBuf(short cmd, short speed, short tone, short volume, short voice, char charaterCode, long len){
		bouyomiChan.setBuf(cmd, speed,tone,volume,voice,charaterCode,len);
	}
	void Tool::setBuf(){
		bouyomiChan.setBuf(bouyomiChan.getTempBuf());
	}
	void Tool::sendData(int index){
		bouyomiChan.sendData(bouyomiChan.getBuf(), novel.getConversation(index), bouyomiChan.getBuf().len);
	}
	string Tool::getConversation(int index){
		return novel.getConversation(index);
	}
	void Tool::setLen(){
		bouyomiChan.setLen();
	}
	void Tool::setSockect(){
		bouyomiChan.setSockect();
	}
	void Tool::deleteSokect(){
		bouyomiChan.deleteSokect();
	}
}
