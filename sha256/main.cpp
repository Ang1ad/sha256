#include <iostream>
#include <vector>
#include "hash.h"
#include <bitset>

std::vector<std::bitset<8>> seq;

int main()
{
	std::bitset<8> b1{ 0x68 };
	std::bitset<8> b2{ 0x65 };
	std::bitset<8> b3{ 0x6C };
	std::bitset<8> b4{ 0x6C };
	std::bitset<8> b5{ 0x6F };
	std::bitset<8> b6{ 0x20 };
	std::bitset<8> b7{ 0x77 };
	std::bitset<8> b8{ 0x6F };
	std::bitset<8> b9{ 0x72 };
	std::bitset<8> b10{ 0x6C };
	std::bitset<8> b11{ 0x64 };
	std::cout << b1 << ' ' << b2 << ' ' << b3 << ' ' << b4 << ' ' << b5 << ' ' << b6 << ' ' << b7 << ' ' << b8 << ' ' << b9 << ' ' << b10 << ' ' << b11 << std::endl << std::endl;


	seq.push_back(b1);
	seq.push_back(b2);
	seq.push_back(b3);
	seq.push_back(b4);
	seq.push_back(b5);
	seq.push_back(b6);
	seq.push_back(b7);
	seq.push_back(b8);
	seq.push_back(b9);
	seq.push_back(b10);
	seq.push_back(b11);
	seq.push_back(0x80);

	

	for (auto i = 0; i < seq.size(); i++)
	{
		std::cout << seq[i] << ' ';
	}
	
	
	


	auto h0 = 0x6a09e667;
	auto h1 = 0xbb67ae85;
	auto h2 = 0x3c6ef372;
	auto h3 = 0xa54ff53a;
	auto h4 = 0x510e527f;
	auto h5 = 0x9b05688c;
	auto h6 = 0x1f83d9ab;
	auto h7 = 0x5be0cd19;

	return 0;
}