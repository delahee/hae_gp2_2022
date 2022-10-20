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


	// P(0) => P(1)
	// P(N) => P(N+1)
	// combine ces deux vérité => l'algo est correcte
	static void MemcpyRec(char* dest, char* src, int size) {
		//cas initial ( p(0) => p(1) )
		if (size <= 0)
			return;
		//cas recurrent ( p(n) => pn+1)
		*dest = *src;
		MemcpyRec(dest + 1, src + 1, size - 1);
		//combine
		;
		//on retourne
		return;
	};


	static const char* StrChrRec(const char* src, char c) {
		//cas initial ( p(0) => p(1) )
		if (!*src)
			return nullptr;
		//on a resolu ( un des cas initiaux )
		if (*src == c)
			return src;
		//cas recurrent  p(n) => pn+1
		return //combine
			StrChrRec(src + 1, c);
	};

	static bool StrPrefixRec(const char* src, const char* c){
		if (src == nullptr) return false;
		if (*c == 0 ) return true;
		if(*src != *c )
			return false;
		return StrPrefixRec(src+1,c+1);
	}

	static const char* StrStrRec(const char* src, const char* prefix) {
		//y a peut etre une sous fonction a se créer pour se simplifier la vie
		//cas initial ( p(0) => p(1) )
		if (src == nullptr) return nullptr;
		if (*src == 0) {
			if (*src == *prefix)
				return src;
			return nullptr;
		}
		if (StrPrefixRec(src, prefix))
			return src;
		//cas recurrent  p(n) => pn+1
		//combine
		return  StrStrRec(src + 1, prefix);
	}

};