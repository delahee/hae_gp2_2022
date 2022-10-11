#pragma once

class Lib{
public:
	static void Memcpy(char* dest, const char* src, int size) {
		for(int i = 0; i < size;++i)
			dest[i] = src[i];
	};
};