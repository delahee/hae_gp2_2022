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

struct Vec2{
    float x = 0;
    float y = 0;
    Vec2(){}
    Vec2(float _x, float _y) {
		x = _x;
        y = _y;
    };
	void add(Vec2 v) {
		x += v.x;
		y += v.y;
	};

	void addRef(Vec2& v) {
		x += v.x;
		y += v.y;
	};

	void addPtr(Vec2* v) {
		//??

       // x += v->x;
        x += (*v).x;
        //y += v->y;
	};
};

struct Vec3 : public Vec2{
	float z = 0;

    Vec3(){}

    Vec3(float _x, float _y, float _z) : Vec2(_x, _y) {
        z = _z;
    };

    void add(Vec3 v) {
        Vec2::add(v);
        z += v.z;
    };

	void addRef(Vec3& v) {
		Vec2::addRef(v);
		z += v.z;
	}; 

    void addPtr(Vec3*v) {
		Vec2::addPtr(v);
        z += v->z;
    };

};

struct Vec4{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;

    Vec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    //
    Vec4 add(const Vec4& v) {
        return Vec4(x + v.x, y + v.y, z + v.z, w + v.w);
    };

	Vec4 sub(const Vec4& v) {
		return Vec4(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	Vec4 mul(const Vec4& v) {
        return Vec4(x * v.x, y * v.y, z * v.z, w * v.w);
	}

	Vec4 div(const Vec4& v) {
        return Vec4(x / v.x, y / v.y, z / v.z, w / v.w);
	}

	void incr(const Vec4& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
	}
};

int main()
{
    {
        Vec3 sapin;

        Vec3 v0( 6,7,8 );
        Vec3 v1( 1,2,3 );

        //v1.add(v0);
        v1.addRef(v0);
        int here = 0;


    }

    {
		Vec3 v0(6, 7, 8);
		Vec3 v1(1, 2, 3);

        v0.addPtr(&v1);
        int here = 0;
    }

    {
        Vec4 a(0,1,0,1);
        Vec4 b(0,1);

        {
            Vec4 res = a.add(b);
            if (res.x != 0) throw "assert";
            if (res.y != 2) throw "assert";
            int here = 0;
        }

        {
            Vec4 res = a.sub(b);
            if (res.x != 0) throw "assert";
            if (res.y != 0) throw "assert";
            int here = 0;
        }
    }
}
