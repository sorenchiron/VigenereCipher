
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
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

void printUsage()
{
	cout<<"Usage: decrypt src_filename dst_filename key ..."<<endl;
}

int main(int argn,char** argv)
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
		if(j<3)
		{
			name[j]=argv[i];
			
		}
		j++;	
	}
	
	if( !(name[0]&&name[1]&&name[2]) )
	{
		cout<<"too few parameters"<<endl;
		printUsage();
		return 0;
	}
	decrypt(name[0],name[1],name[2]);
	
}











