#


#is program is designed to en/decrypt files using VigenereCipher, and also crack the cipher key
#pyright (C) 2015  Soren Chiron gionstorm@gmail.com

#is program is free software; you can redistribute it and/or
#dify it under the terms of the GNU General Public License
# published by the Free Software Foundation; either version 2
# the License, or (at your option) any later version.

#is program is distributed in the hope that it will be useful,
#t WITHOUT ANY WARRANTY; without even the implied warranty of
#RCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#U General Public License for more details.

#u should have received a copy of the GNU General Public License
#ong with this program; if not, write to the Free Software
#undation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#



objects = encrypt decrypt cracker
all: $(objects)

.PHONY: all

encrypt: encrypt.cpp cypt.hpp cypt.o
	c++ -o encrypt encrypt.cpp cypt.o

decrypt: decrypt.cpp cypt.hpp cypt.o
	c++ -o decrypt decrypt.cpp cypt.o

cracker: crack.cpp cypt.hpp superposition.hpp cypt.o superposition.o
	c++ -o cracker crack.cpp cypt.o superposition.o
		
cypt.o: cypt.cpp
	c++ -o cypt.o -c cypt.cpp

superposition.o: superposition.cpp
	c++ -o superposition.o -c superposition.cpp

clean: 
	rm *.o
	rm $(objects) *~
	
run:
	./cypt	
	
crack:
	./crack


