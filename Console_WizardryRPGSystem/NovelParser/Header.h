#pragma once
#include "Common.h"

namespace Cto{
	
	class Novel;
	class File;
	class BouyomiChan;

	using namespace std;

	class File{
	private:
		const char* SCENE;
	public:
		File();
		File(const char* scene);
		~File();
		bool readFile(Novel* novel);
	};
	class BouyomiChan{
	private:
		sockaddr_in server;
		WSADATA wsadata;
		SOCKET sock;
		typedef struct _Buf{
			short cmd;
			short speed;
			short tone;
			short volume;
			short voice;
			char characterCode;
			long len;
		}BUF;
		string msg;
		BUF buf, tempBuf;
	public:
		BouyomiChan();
		~BouyomiChan();
		void setMsg(string argumentMsg);
		void setLen();
		void setBuf(short cmd = 0x0001, short speed = -1, short tone = -1, short volume = -1, short voice = 0, char charaterCode = 2, long len = 0);
		void setBuf(BUF argumentbuf);
		void setserver();
		void sendData(BUF buf, string msg, long len);
		BUF getTempBuf(){ return tempBuf; }
		BUF getBuf(){ return buf; }
		void setSockect(){
			//Winsock2初期化
			WSAStartup(MAKEWORD(1, 1), &wsadata);
			//ソケット作成
			sock = socket(AF_INET, SOCK_STREAM, 0);
			//サーバに接続
			connect(sock, (struct sockaddr *)&server, sizeof(server));
		}
		void deleteSokect(){closesocket(sock);}
	};

	class Novel{
	private:
		File readNovelText;
		string conversation[500];
		//string bouyomiData[500];
		int manyLines;
	public:
		Novel();
		~Novel();
		void setConversation(string str, int index);
		string getConversation(int index);

		void setManyLines(int index);
		int getManyLines(){ return manyLines; }

		void callReadFile();
		void callBouyomiChan();
	};

	class Tool{
	private:
		Novel novel;
		BouyomiChan bouyomiChan;
	public:
		Tool();
		~Tool();
		void draw(int index);
		//File
		void callReadFile();
		//Novel
		int getManyLines();
		string getConversation(int index);
		//BouyomiChan
		void setMsg(int index);
		void setTempBuf(short cmd = 1, short speed = -1, short tone = -1, short volume = -1, short voice = 0, char charaterCode = 2, long len = 0);
		void setBuf();
		void sendData(int index);
		void setLen();
		void setSockect();
		void deleteSokect();
	};
}