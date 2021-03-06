
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

// direction : 1 enc     0 dec
char offsetChar(int c, int offset, int direction=1);

void decrypt(const char * src_name,const char * dst_name,const char * key);

void encrypt(const char * src_name,const char * dst_name,const char * key);

