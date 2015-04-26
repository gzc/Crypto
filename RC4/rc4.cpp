/*************************************************************************
	> File Name: rc4.cpp
	> Author: Louis1992
	> Mail: zhenchaogan@gmail.com
	> Blog: http://gzc.github.io
	> Created Time: Sun Apr 26 23:09:57 2015
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


class RC4 {
public:

  	/*
     * kl is the length of private key
  	 */
	RC4(int kl):keylen(kl) {
		srand((unsigned)time(NULL));
    	for(int i=0;i < kl;++i){  //generate the private key
    		int tmp=rand()%256;
    		K.push_back(char(tmp));
    	}
	}

  	void encryption(const string &,const string &,const string &);

private:
  	unsigned char S[256]; //condition variable
  	unsigned char T[256]; //temporary variable
  	int keylen;		//the length of private key of [1,256]
  	vector<char> K;	  //private key
  	vector<char> stream;	  //cipher stream

  	/*
     * initialize  S & T
  	 */
  	void initial() {
    	for(int i=0;i<256;++i){
      		S[i]=i;
      		T[i]=K[i%keylen];
    	}
  	}
  
  	/*
     * rearrange S
  	 */
  	void rangeS() {
    	int j=0;
    	for(int i=0;i<256;++i){
      		j=(j+S[i]+T[i])%256;
      		swap(S[i], S[j]);
    	}
  	}
  	
  	/*
     *generate the stream cipher
     *len is the length of plaintext
  	 */
  	void keyStream(int len);

};



void RC4::keyStream(int len) {
  	initial();
  	rangeS();

  	int i=0,j=0,t;
  	while(len--){
    	i = (i+1)%256;
    	j = (j+S[i])%256;

    	swap(S[i], S[j]);

    	t = (S[i]+S[j])%256;
    	stream.push_back(S[t]);
  	}
}

void RC4::encryption(const string &plaintext,const string &ks,const string &ciphertext) {
  	ifstream in;
  	ofstream out,outks;

  	in.open(plaintext);
  	//get the length of plaintext
  	in.seekg(0,ios::end);
  	int lenFile = in.tellg();
  	in.seekg(0, ios::beg);

  	//write cipher stream to file
  	keyStream(lenFile);
  	outks.open(ks);
  	for(int i=0;i <l enFile;++i)
    	outks<<(stream[i]);
  
  	outks.close();

  	//read plaintext to memory
  	unsigned char *bits=new unsigned char[lenFile];
  	in.read((char *)bits,lenFile);
  	in.close();


  	out.open(ciphertext);
  	//encrypt
  	for(int i=0;i < lenFile;++i)
    	out << (unsigned char)(bits[i]^stream[i]);
	out.close();

  	delete []bits;
}

int main(){
  RC4 rc4(16); //set the length of private key to 16
  rc4.encryption("plaintext","cipherstream","ciphertext");
}
