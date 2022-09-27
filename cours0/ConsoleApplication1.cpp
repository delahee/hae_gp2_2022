// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>

#include <string> //fichier systeme
//#include "string" // fichier du projet

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
		cout << to_string(val64)<<"\n";
    }

    {
        Toto a;
		cout << to_string(a.x) << "\n";
    }
}
