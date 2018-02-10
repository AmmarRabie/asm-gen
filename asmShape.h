/*
****************************************
*                                      *
* Author: Ammar Alsayed Ibrahim        *
* Sec: 2          BN: 4                *
* GitHibLink:                          *
* desc: this prog is designed for      *
* bonus task in term holiday		   *
* for D.Khaled                         *
*                                      *
****************************************
*/

#pragma once
#include<vector>
#include<iostream>
using namespace std;

struct Vertix
{
	int x;
	int y;
	Vertix(int x, int y);
	Vertix();
};

struct Rect
{
	Vertix min;
	Vertix max;
	Rect(Vertix v1, Vertix v2);

	void move(int x, int y);

	void multiply(float x, float y);
};


class asmShape abstract
{
	vector<Rect> _verices;	// rectangles forming this duck
	Vertix _center;
	Vertix _vmin;
	Vertix _vmax;

	Vertix getVmin(const vector<Rect>& basicVerices);
	Vertix getVmax(const vector<Rect>& basicVerices);

protected:
	void refresh();

public:
	asmShape(vector<Rect> basicVerices);
	vector<Rect> getVertices()const;
	Vertix getCenter() const;
	Vertix getVmin() const;
	Vertix getVmax() const;
	int getLength() const;
	int getWidht() const;

	void subFromAll(int x, int y);
	void scale(float factor);
	void reflectAbouty();
	void print();

	virtual void generateDrawingAsm(string fileName, string macroName) = 0;

};