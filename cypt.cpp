
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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
char offsetChar(int c, int offset, int direction=1)
{
	offset = offset-'a';
	if(direction==1)
	{
		if( (c+offset)<='z' )
		    return c+offset;
		return c+offset-26;
	}
	else
	{
		if( (c-offset)>='a' )
		    return c-offset;
		return c-offset+26;
	}
    
}
void crypt(const char * src_name,const char * dst_name,const char * key,int direction)
{
    FILE *in = fopen(src_name,"r");
    FILE *out = fopen(dst_name,"w");
    char c;
    int i=0;
    int len = strlen(key);
    while(1)
    {
        c=fgetc(in);
        if(c==EOF)
         break;
        if(c>'z'||c<'a')
        {	
        	fprintf(out,"%c",c);
        	continue;
        }
        char k=offsetChar(c,key[i%len],direction);
        fprintf(out,"%c",k);
        i++;
    };
    fclose(in);
    fclose(out);
}

void decrypt(const char * src_name,const char * dst_name,const char * key)
{
	crypt(src_name,dst_name,key,0);
}
void encrypt(const char * src_name,const char * dst_name,const char * key)
{
	crypt(src_name,dst_name,key,1);
}

/*
int main(int n, char ** arg)
{
	if(n>0)
		cout<<arg[0]<<endl;
		
    encrypt("src.txt","dst.txt","asd");
    decrypt("dst.txt","cracked.txt","asd");    

    return 0;
}
*/

