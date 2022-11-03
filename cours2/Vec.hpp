#pragma once
struct Vec2 {
	float x = 0;
	float y = 0;
	Vec2() {}
	Vec2(float _x, float _y);
	void add(Vec2 v) {
		x += v.x;
		y += v.y;
	};

	void addRef(Vec2& v) {
		x += v.x;
		y += v.y;
	};

	void addPtr(Vec2* v) {
		x += v->x;
		y += v->y;
	};
};

struct Vec3 : public Vec2 {
	float z = 0;

	Vec3() {}

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

	void addPtr(Vec3* v) {
		Vec2::addPtr(v);
		z += v->z;
	};
};

struct Vec4 {
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

	static Vec4 ZERO;
};

