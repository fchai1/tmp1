#ifndef DES_CMD_H
#define DES_CMD_H 
#include <vector>
#include <string>

using namespace std;

enum cmdType {
	MOV,
	LDR,
	STR,
	ADD,
	SUB,
	OOR,
	CMP,
	UNKNOW,
};

class DesCmd {
private:
	long long tick;
	cmdType op;
	long long para1;
	long long para2;
	long long para3;
	double power;
	string opstr;
	
	cmdType toCmdType(string str) {
		if(str.find("mov") != std::string::npos) {
			return MOV; 
		} else if (str.find("ldr") != std::string::npos){
			return LDR;
		} else if (str.find("str") != std::string::npos){
			return STR;
		} else if (str.find("add") != std::string::npos){
			return ADD;
		} else if (str.find("sub") != std::string::npos){
			return SUB;
		} else if (str.find("oor") != std::string::npos){
			return OOR;
		} else if (str.find("cmps") != std::string::npos){
			return OOR;
		}

		return UNKNOW;
	}
public:
	DesCmd(long long t, string o, int p1, int p2, int p3){
		this->tick = t;
		this->para1 = p1;
		this->para2 = p2;
		this->para3 = p3;

		this->op = toCmdType(o);
		this->opstr = o;
	}

	long long getTick(){
		return this->tick;
	}
	cmdType getop() {
		return this->op;
	}

	int getpara1(){
		return this->para1;
	}

	int getpara2(){
		return this->para2;
	}
	
	double getPower(){
		return this->power;
	}

	void setPower(double p){
		this->power = p;
	}
	
	string getopstr(){
		return this->opstr;
	}
	void setp1(long long p1){
		this->para1 = p1;
	}
	void setp2(long long p2){
		this->para2 = p2;
	}
	void setp3(long long p3){
		this->para3 = p3;
	}
};



using namespace std;

vector<string> split(const string& str, const string& delim);

vector <DesCmd> parseDesCmdFromGem5Log(string file);


#endif

