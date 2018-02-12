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
	MATH,
	UNKNOW,
};

class DesCmd {
private:
	long long tick;
	cmdType op;
	long long para1;
	long long para2;
	long long para3;
	string p1string;
	string p2string;
	string p3string;
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
		} else if (str.find("cmps") != std::string::npos){
			return MATH;
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
		this->p1string = string("");
		this->p2string = string("");
		this->p3string = string("");
	}
	
	DesCmd(const DesCmd &cmd){
		tick = cmd.tick;
		op = cmd.op;
		p1string = cmd.p1string;
		p2string = cmd.p2string;
		p3string = cmd.p3string;
		para1 = cmd.para1;
		para2 = cmd.para2;
		para3 = cmd.para3;
		power = cmd.power;
		opstr = cmd.opstr;
	}

	void setTick(long long t){
		this->tick = t;
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
	
	void setP1String(string s){
		this->p1string = s;
	}
	void setP2String(string s){
		this->p2string = s;
	}
	void setP3String(string s){
		this->p3string = s;
	}

	string getP1String() {
		return p1string;
	}
};



using namespace std;

vector<string> split(const string& str, const string& delim);

vector <DesCmd> parseDesCmdFromGem5Log(string file);


#endif

