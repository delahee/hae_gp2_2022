// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>

#include <string> //fichier systeme
//#include "string" // fichier du projet
#include <unordered_map>

using namespace std;

struct Toto{
    float x = 0.777f;
};

int main()
{
    {
        //std::cout << "Hello World!\n";
        printf("12345\n");
        printf("0\n");
        std::string zero = "0";
        char zeroC[] = "0";

        std::cout << zeroC << " c++ style \n";
        //console.print( zeroC ) 
        printf("%s c style\n", zeroC);
        printf("%f \n", 0.66666f);

        float half = 0.5f;
        //afficher ca en c style avec la chaine de format %f
        printf("%f\n", half);

        // 
        //et en c++ style avec std::to_string()

        std::cout << std::to_string(half) << "\n";
    }
    {
        int val = 123456789123456789;//supérieur a md cad plus de 32bits
        printf("%i\n", val);
        cout << to_string(val) << "\n";
        printf("%d\n", 666);

        auto val64 = 123456789123456789;
        printf("%lld\n", val64);
        cout << to_string(val64) << "\n";
    }

    {
        Toto a;
        cout << to_string(a.x) << "\n";
    }

    {
        std::unordered_map<int, std::string> t;
        t[0] = "toto";
        cout << t[0] << "\n";

        for (std::unordered_map<int, std::string>::iterator iter = t.begin(); iter != t.end(); iter++) {
            auto& p = *iter;
            cout << p.first << "=" << p.second << "\n";
        }

        for (std::pair<const int, std::string>& p : t) {
            cout << p.first << "=" << p.second << "\n";
        }

    }

    {
        int c = 0;
        int tab[] = { 0,1,2,3,4 };
        int* d = &tab[0];
        d++;
        *d = 666;
        int* e0 = nullptr;
        int* e1 = NULL;
        int* e2 = 0;
        int here = 0;
    }
    {
        int c = 0;
        // int& d;
        // int d & = c;
         //d++;
        int here = 0;
    }

    std::vector<std::string> p;
    for (int i = 0; i < 100000; ++i) {
        p.push_back(std::to_string(i));
    }

    int here = 0;
    for (int i = 0; i < p.size(); ++i) {
        std::string& pelem = p[i];
    }
    int there = 0;
    int tab[] = { 0,1,2,3 };
}
