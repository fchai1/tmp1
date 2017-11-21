#include <iostream>
#include "descmd.h"

using namespace std;

void testSplit(){
	string s = "116583500: system.cpu T0 : @process_message+2473    :   strb.w   r3, [r7, #37]   : MemWrite :  D=0x0000000000000080 A=0xbefffd7d";
	vector<string> p = split(s, " ");
	
	for(vector<string>::iterator it = p.begin(); it != p.end(); ++it) {
		cout<< *it <<endl;
	}
}

void testParse(){
	vector<DesCmd> cmdVector = parseDesCmdFromGem5Log("des.txt");

	for(vector<DesCmd>::iterator it = cmdVector.begin(); it != cmdVector.end(); ++it) {
		cout << it->getTick() << " " << it->getop() <<endl;
	}
}

int main(){
	testSplit();

	testParse();
}
