/*************************************************************************
	> File Name: rc4_decryption.cpp
	> Author: Louis1992
	> Mail: zhenchaogan@gmail.com
	> Blog: http://gzc.github.io
	> Created Time: Sun Apr 26 23:43:48 2015
 ************************************************************************/
#include<iostream>
#include<cstdio>
#include<list>
#include<vector>
#include<unordered_map>
#include<climits>
#include<unordered_set>
#include<map>
#include<set>
#include<stack>
#include<queue>
#include<fstream>
using namespace std;


class RC4_decryption{
public:

	  RC4_decryption(const string ks,const string ct):keystream(ks),ciphertext(ct) {}

	  void decryption(const string &);

private:
  	string ciphertext,keystream;
};

void RC4_decryption::decryption(const string &res){
  	ifstream inks,incp;
  	ofstream out;

  	inks.open(keystream);
  	incp.open(ciphertext);

  	//calculate the length
  	inks.seekg(0,ios::end);
  	const int lenFile=inks.tellg();
  	inks.seekg(0, ios::beg);
  
  	//get the cipher stream
  	unsigned char *bitKey=new unsigned char[lenFile];
  	inks.read((char *)bitKey,lenFile);
  	inks.close();
  
  	//get the ciphertext
  	unsigned char *bitCip=new unsigned char[lenFile];
  	incp.read((char *)bitCip,lenFile);
  	incp.close();

  	//write output to file
  	out.open(res);
  	for(int i=0;i<lenFile;++i)
    	out<<(unsigned char)(bitKey[i]^bitCip[i]);

  	out.close();
}

int main(){
  	RC4_decryption decrypt("cipherstream","ciphertext");
  	decrypt.decryption("decrypt_file");
}
