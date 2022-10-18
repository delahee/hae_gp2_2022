#pragma once

class Lib{
public:
	static void Memcpy(char* dest, const char* src, int size) {
		for(int i = 0; i < size;++i)
			dest[i] = src[i];
	};

	//renvoie nullptr si le char c n'est pas trouvé
	//sinon renvoie le ptr vers la u est le character
	static const char* StrChr(const char* src, char c) {
		while (*src && (*src != c))
			src++;
		if (!*src)
			return nullptr;
		return src;
	};

	static bool StrPrefix( const char* src, const char*tok){
		int i = 0;
		while (tok[i]) {
			if (tok[i] != src[i])
				return false;
			else 
				i++;
		}
		return true;
	}

	//sapin
	//pin
	static const char* StrStr(const char * src, const char * tok){
		while (*src && !StrPrefix(src, tok)) 
			src++;
		if (!*src)
			return nullptr;
		return src;
	};
};