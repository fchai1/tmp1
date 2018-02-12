#include <fstream>
#include "descmd.h"
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "desparse.h"

using namespace std;

vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}


arm_registers arm_reg;


string getDatafromCmd(vector<string> cmd){
	for(vector<string>::iterator it = cmd.begin(); it != cmd.end(); ++it) {
		if(it->find("D=") != std::string::npos){
			return it->erase(0, 4);
		}
	}
	return string("");
}

DesCmd toDesCmd(vector<string> cmd) {
	string o = cmd[0].substr(0, cmd[0].size()-1);

	string::size_type sz;

	DesCmd retcmd(atoll(o.c_str()), cmd[6], 0, 0, 0);
	
	string reg = cmd[7];
	reg.erase(reg.length() -1);
	retcmd.setP1String(reg);

	string val = getDatafromCmd(cmd);
	
	if(val == string("")){
		return retcmd;
	}	
	arm_reg.parseRegister(reg, getDatafromCmd(cmd));
	switch(retcmd.getop()) {
		case MOV:
			retcmd.setp1(arm_reg.getRegValByName(reg));
			retcmd.setp2(0);
			retcmd.setp3(0);
			break;
		case LDR:
			retcmd.setp1(arm_reg.getRegValByName(reg));
			retcmd.setp2(0);
			break;
		case STR:
			retcmd.setp1(arm_reg.getRegValByName(reg));
			retcmd.setp2(0);
			break;
		case ADD:
			retcmd.setp1(arm_reg.getRegValByName(reg));
			retcmd.setp2(0);
			retcmd.setp3(0);
			break;
		case SUB:
			retcmd.setp1(arm_reg.getRegValByName(reg));
			retcmd.setp2(0);
			retcmd.setp3(0);
			break;
		case CMP:
			retcmd.setp1(arm_reg.getRegValByName(reg));
			retcmd.setp2(0);
			break;
		default:
			break;
	}

	return retcmd;
}

vector <DesCmd> cmdVector;

vector <DesCmd> parseDesCmdFromGem5Log(string file){
	vector <DesCmd> cmdVector ;

	std::ifstream infile("des.txt");

	if (infile.is_open()) {
		cout << "file opened." << endl;
		string str;
		bool start = false;
		while(getline(infile, str)) {
			if(str.find("REAL SIMULATION") != std::string::npos 
				&& !start){
				start = true;
				continue;
			}
			if(start) {
				vector<string> cmdStringVector = split(str, " ");
				if(cmdStringVector.size() >= 12) {
					DesCmd cmd = toDesCmd(cmdStringVector);
					cmdVector.push_back(cmd);
				}

				// cout <<  str << "\n";	
			}
		}
	}

	infile.close();

	return cmdVector;
}

vector <DesCmd> parseSchedule() {
	vector <DesCmd> cmdVector ;

	std::ifstream infile("schedule.log");

	if (infile.is_open()) {
		string str;
		bool start = false;
		while(getline(infile, str)) {
			if(str.find("REAL SIMULATION") != std::string::npos 
				&& !start){
				start = true;
				continue;
			}
			if(start) {
				vector<string> cmdStringVector = split(str, " ");
				if(cmdStringVector.size() >= 12) {
					DesCmd cmd = toDesCmd(cmdStringVector);
					cmdVector.push_back(cmd);
					cmd.setTick(0);
				}

				// cout <<  str << "\n";	
			}
		}
	}

	infile.close();

	return cmdVector;
}


int schedulerInit = 0;
vector <DesCmd> scheduleVector;

void init_schedule () {
	if(!schedulerInit) {
		scheduleVector = parseSchedule();
		schedulerInit = 1;
	}
}

void addSchedulingBlock(vector <DesCmd> &target, vector<DesCmd>::iterator &it, arm_registers &regs) {
	for(vector<DesCmd>::iterator scheduleit = scheduleVector.begin(); scheduleit != scheduleVector.end(); ++scheduleit){
		scheduleit->setTick(0);
		string reg = scheduleit->getP1String();
		
		if(reg.find("r1") != std::string::npos)
			scheduleit->setp1(regs.r[0]);
		if(reg.find("r2") != std::string::npos)
			scheduleit->setp1(regs.r[1]);
		if(reg.find("r3") != std::string::npos)
			scheduleit->setp1(regs.r[2]);
		if(reg.find("r4") != std::string::npos)
			scheduleit->setp1(regs.r[3]);
		if(reg.find("r5") != std::string::npos)
			scheduleit->setp1(regs.r[4]);
		if(reg.find("r6") != std::string::npos)
			scheduleit->setp1(regs.r[5]);
		if(reg.find("r7") != std::string::npos)
			scheduleit->setp1(regs.r[6]);
		if(reg.find("r8") != std::string::npos)
			scheduleit->setp1(regs.r[7]);
		if(reg.find("r9") != std::string::npos)
			scheduleit->setp1(regs.r[8]);
		if(reg.find("r10") != std::string::npos)
			scheduleit->setp1(regs.r[9]);
		if(reg.find("r12") != std::string::npos)
			scheduleit->setp1(regs.r12);
		if(reg.find("sp") != std::string::npos)
			scheduleit->setp1(regs.sp);
		if(reg.find("lr") != std::string::npos)
			scheduleit->setp1(regs.lr);
		if(reg.find("fp") != std::string::npos)
			scheduleit->setp1(regs.fp);

		DesCmd cmd(*scheduleit);
		
		target.insert(it, cmd);
	}
	// target.insert(it, scheduleVector.begin(), scheduleVector.end());
		
}
