#pragma once
class TriangleStack
{
private:
	float mBase, mHeight;

public:
	void SetBase(float _base) { mBase = _base; }
	void SetHeight(float _height) { mHeight = _height; }

	float GetArea() { return (mBase * mHeight) / 2.0f; }

	//new default constructor, base and height of 1
	TriangleStack() { mBase = 1.0f; mHeight = 1.0f; };
};

