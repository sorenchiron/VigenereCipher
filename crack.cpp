
/*
This program is designed to en/decrypt files using VigenereCipher, and also crack the cipher key
Copyright (C) 2015  Soren Chiron gionstorm@gmail.com

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

*/

#include "cypt.hpp"
#include "superposition.hpp"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
//#include <hash_map>
#define KASISKI (0.065)
#define MAX_DIFF (0.0001)
typedef union _Trichar
{
	int num;
	char data[3];
}Trichar;

double freq_table[]={
8.17,
1.49,
2.78,
4.25,
12.70,
2.23,
2.02,
6.09,
6.97,
0.15,
0.77,
4.03,
2.41,
6.75,
7.51,
1.93,
0.10,
5.99,
6.33,
9.06,
2.76,
0.98,
2.36,
0.15,
1.97,
0.07,
};


using namespace std;
double calcKasiski(vector<char> seq, int mode = 1)//mode 0:check mode
{
	int freq[26]={0};
	double result=0;
	int n = seq.size();
	for(int i=0;i<n;i++)
	{
		if( (seq[i]-'a'<0) || (seq[i]-'a'>=26) )
		{
			cout<<"calcKasisiki():seq-\'a\' overflow"<<endl;
			return 0;
		}
		
		freq[seq[i]-'a']++;
	}
	double Pi=0;
	for(int j=0;j<26;j++)
	{
		if(mode==1)
		{
			Pi = freq[j]*1.0/n;
		}
		else
		{
			Pi = freq_table[j]/100;
		}
		result = result + Pi * (freq[j]-1)*1.0/(n-1);
	}
	
	return result;
}

char kCrackShift(const vector<char> list)//only a-z in list
{
	double result[26]={0};
	for(int j=0;j<26;j++)
	{
		char token = 'a'+ j;
		vector<char> seq;
		int n=list.size();
		for(int i=0;i<n;i++)
		{
			char c = offsetChar(list[i],token,0);
			seq.push_back(c);
		}
		double ksk = calcKasiski(seq,0);
		result[j]=(ksk-KASISKI)*(ksk-KASISKI);
	}
	int k=0;
	for(int i=0;i<26;i++)
	{
		if(result[i]<result[k])
			k=i;
	}
	return 'a'+k;
}

void kCrack(const vector<char> raw_text,const int klen)
{
	int n=raw_text.size();
	vector<char> m[klen];
	char c;
	char key[klen+1]={'\0'};
	key[klen]='\0';
	for(int i=0;i<n;i++)
	{
		c=raw_text[i];
        if(c==EOF)
         break;
        if(c>'z'||c<'a')
        	continue;
		m[i%klen].push_back(c);
	}
	
	for(int i=0;i<klen;i++)
	{
		key[i]=kCrackShift(m[i]);
	}
	cout<<"result:"<<key<<endl;
	
}

double klenAssess(const vector<char> raw_text,int klen)
{
	vector<char> m[klen];
	char c;
    int n=raw_text.size();

    for(int i=0;i<n;i++)
    {
        c=raw_text[i];
        if(c==EOF)
         break;
		m[i%klen].push_back(c);
    };
    
    double sqdiff=0;
    for (int j=0;j<klen;j++)
    {
    	double ksk = calcKasiski(m[j],1);
    	sqdiff = sqdiff + (ksk-KASISKI)*(ksk-KASISKI);
    }
	sqdiff=sqdiff*1.0/klen;
	cout<<"square diff of ksk for klen="<<klen<<": "<<sqdiff<<endl;
	return sqdiff;
}

void crack(const char * src_name,const char * dst_name,int klen)
{
    FILE *in = fopen(src_name,"r");
    FILE *out = fopen(dst_name,"w");
    double klen_assess_result[256];
    vector<char> raw_text;
    char c;
    int i=0;

    while(1)
    {
        c=fgetc(in);
        if(c==EOF)
         break;
        if(c>'z'||c<'a')
        	continue;
        raw_text.push_back(c);
        i++;
    };
    fclose(in);
    
    int min_klen=(klen-3)>0?klen-3:1;
    int max_klen=klen+3;
    int best_klen=0;
    for(int i=0;i<5;i++)
    {
    	klen_assess_result[i]=klenAssess(raw_text,i+min_klen);
    }
    
    for(int i=0;i<5;i++)
    {
    	if(klen_assess_result[i]<klen_assess_result[best_klen])
    	best_klen=i;
    }
    if(klen_assess_result[best_klen]>MAX_DIFF)
    {
    	min_klen=1;
    	cout<<"cracker:diff not accepted, start deep-mining"<<endl;
    	for(int i=0;i<256;i++)
		{
			klen_assess_result[i]=klenAssess(raw_text,i+min_klen);
		}
		best_klen=0;
		for(int i=0;i<256;i++)
		{
			if(klen_assess_result[i]<klen_assess_result[best_klen])
			best_klen=i;
		}
		cout<<"cracker:mining ended"<<endl;    
    }
    best_klen+=min_klen;
    cout<<"best k len is possibly:"<<best_klen<<endl;
    cout<<"start cracking the key..."<<endl;
    
    kCrack(raw_text,best_klen);
    
    fclose(out);
}

void readFile(const char * filename,vector<char> & raw_text)
{
	FILE *in = fopen(filename,"r");
    char c;
    int i=0;

    while(1)
    {
        c=fgetc(in);
        if(c==EOF)
         break;
        if(c>'z'||c<'a')
        	continue;
        raw_text.push_back(c);
        i++;
    };
    fclose(in);
}


void printUsage()
{
	cout<<"Usage: cracker filename..."<<endl;
	cout<<"the defalut output is cracked.txt"<<endl;
}

int main(int argn, char ** argv)
{
	char * name[3]={NULL,NULL,NULL};
	int j=0;
	for(int i=1;i<argn;i++)
	{
		if(strcmp("--help",argv[i])==0)
		{
			printUsage();
			return 0;
		}
		if(j<1)
		{
			name[j]=argv[i];
			
		}
		j++;	
	}
	
	if( !name[0] )
	{
		cout<<"cracker: too few parameters"<<endl;
		printUsage();
		return 0;
	}
	vector<char> m;
	readFile(name[0],m);
	int possible_klen = superposition(m);
	crack(name[0],"cracked.txt",possible_klen);
	
	return 0;
}






