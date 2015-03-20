
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

#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <fstream>

#define CONFI_LEN 3
#define MIN_EMERGE 2
using namespace std;

typedef union _Trichar
{
	long Index;
	char data[CONFI_LEN];
}Trichar;

Trichar trichar(char a,char b,char c)
{
	Trichar result;
	result.Index=0;
	result.data[0]=a;
	result.data[1]=b;
	result.data[2]=c;
	return result;
}
Trichar trichar(char * cp)
{
	Trichar result;
	result.Index=0;
	for(int i=0;i<CONFI_LEN;i++)
		result.data[i]=cp[i];
	return result;
}
Trichar trichar(const vector<char> raw_text,long pos)
{
	Trichar result;
	result.Index=0;
	long n=raw_text.size();
	if(pos+CONFI_LEN>n)
		goto RETURN;

	for(long i=0;i<CONFI_LEN;i++)
		result.data[i]=raw_text[pos+i];

RETURN:
	return result;
}

long GCD(long u, long v) {
    while ( v != 0) {
        long r = u % v;
        u = v;
        v = r;
    }
    return u;
}

int superposition(const vector<char> raw_text)// raw text without special characters \n\r\0\N
{
	long n = raw_text.size();
	std::map<long,vector<long> > m;
	vector<long> intervals;

	//analysis superposition count for each pattern
	for(long i=0;i<n-CONFI_LEN;i++)
	{
		Trichar t = trichar(raw_text,i);
		m[t.Index].push_back(i);
	}
	// get the gcd of confident-patterns' intervals
	for(map<long,vector<long> >::iterator i= m.begin();i!= m.end();i++)
	{
		long pattern = (i->first);
		long emerge = (i->second).size();
		if(emerge>MIN_EMERGE)
		{
			int gcd= (i->second)[0];
			for(long j=0;j<emerge;j++)
			{
				gcd = GCD(gcd,(i->second)[j]);
			}
			intervals.push_back(gcd);
		}
	}
	int max_interval=intervals[0],min_interval=intervals[0];
	int intv_n = intervals.size();
	cout<<"possible klen: ";
	for(long i=0;i<intv_n;i++)
	{
		int tmp = intervals[i];
		if(tmp>max_interval)
			max_interval=tmp;
		if(tmp<min_interval)
			min_interval = tmp;
		cout<<tmp<<" ";
	}
	cout<<endl;
	cout<<"suggested klen:"<<max_interval<<endl;
	return max_interval;

}

