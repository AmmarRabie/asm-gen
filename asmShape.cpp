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

#include"asmShape.h"
using namespace std;



Vertix::Vertix(int x, int y) :x(x), y(y) {}
Vertix::Vertix() {}




Rect::Rect(Vertix v1, Vertix v2)
{
	int xmin = v1.x < v2.x ? v1.x : v2.x;
	int ymin = v1.y < v2.y ? v1.y : v2.y;
	int xmax = v1.x > v2.x ? v1.x : v2.x;
	int ymax = v1.y > v2.y ? v1.y : v2.y;
	min.x = xmin;
	min.y = ymin;
	max.x = xmax;
	max.y = ymax;
}

void Rect:: move(int x, int y)
{
	min.x += x;
	min.y += y;

	max.x += x;
	max.y += y;

}

void Rect::multiply(float x, float y)
{
	min.x = round(x*min.x);
	min.y = round(y*min.y);

	max.x = round(x*max.x);
	max.y = round(y*max.y);

}



Vertix asmShape::getVmin(const vector<Rect>& basicVerices)
{
	int xMin = _verices[0].min.x;
	int yMin = _verices[0].min.y;
	for (int i = 1; i < _verices.size(); i++)
	{
		Vertix curr = _verices[i].min;
		if (curr.x < xMin)
			xMin = curr.x;
	}
	for (int i = 1; i < _verices.size(); i++)
	{
		Vertix curr = _verices[i].min;
		if (curr.y < yMin)
			yMin = curr.y;
	}
	return Vertix(xMin, yMin);
}
Vertix asmShape::getVmax(const vector<Rect>& basicVerices)
{
	int xMax = _verices[0].max.x;
	int yMax = _verices[0].max.y;
	for (int i = 1; i < _verices.size(); i++)
	{
		Vertix curr = _verices[i].max;
		if (curr.x > xMax)
			xMax = curr.x;
	}
	for (int i = 1; i < _verices.size(); i++)
	{
		Vertix curr = _verices[i].max;
		if (curr.y > yMax)
			yMax = curr.y;
	}
	return Vertix(xMax, yMax);
}


void asmShape::refresh()
{
	for (int i = 0; i < _verices.size(); i++)
	{
		Rect &rect = _verices[i];
		if (rect.max.x < rect.min.x)
		{
			/*
			rect.min.x += rect.max.x;
			rect.max.x = rect.min.x - rect.max.x;
			rect.min.x -= rect.max.x;*/
			int temp = rect.min.x;
			rect.min.x = rect.max.x;
			rect.max.x = temp;
		}
		if (rect.max.y < rect.min.y)
		{
			/*swap(rect.min.y, rect.max.y);*/
			rect.min.y += rect.max.y;
			rect.max.y = rect.min.y - rect.max.y;
			rect.min.y -= rect.max.y;
		}
	}

	_vmin = getVmin(_verices);
	_vmax = getVmax(_verices);
	_center = Vertix(round(_vmax.x - _vmin.x) / 2.0, round(_vmax.y - _vmin.y) / 2.0);
	_center.x -= _vmin.x;
	_center.y -= _vmin.y;
	subFromAll(_vmin.x, _vmin.y);

	_vmax.x = _vmax.x - _vmin.x;
	_vmax.y = _vmax.y - _vmin.y;
	_vmin = Vertix(0, 0);

}


asmShape::asmShape(vector<Rect> basicVerices)
{
	_verices = basicVerices;
	refresh();
}
vector<Rect> asmShape::getVertices()const { return _verices; }
Vertix asmShape::getCenter() const { return _center; }
Vertix asmShape::getVmin() const { return _vmin; }
Vertix asmShape::getVmax() const { return _vmax; }
int asmShape::getLength() const { return _vmax.y - _vmin.y; }
int asmShape::getWidht() const { return _vmax.x - _vmin.x; }

void asmShape::subFromAll(int x, int y)
{
	for (int i = 0; i < _verices.size(); i++)
	{
		_verices[i].move(-1 * x, -1 * y);
	}
}
void asmShape::scale(float factor)
{
	subFromAll(_center.x, _center.y);
	// vertices
	for (int i = 0; i < _verices.size(); i++)
	{
		_verices[i].multiply(factor, factor);
	}
	subFromAll(-1 * _center.x, -1 * _center.y);

	//subFromAll((_vmin.x - _center.x)* factor, (_vmin.y - _center.y) * factor);
	//_vmin = Vertix((_vmin.x - _center.x)* factor + _center.x, (_vmin.y - _center.y) * factor + _center.y);
	//_vmax = Vertix((_vmax.x - _center.x)* factor + _center.x, (_vmax.y - _center.y) * factor + _center.y);
	refresh();
}
void asmShape::reflectAbouty()
{
	subFromAll(_center.x, _center.y);
	// reflect vertices
	for (int i = 0; i < _verices.size(); i++)
	{
		_verices[i].multiply(-1, 1);
	}
	subFromAll(-1 * _center.x, -1 * _center.y);

	refresh();
}
void asmShape::print()
{
	for each (Rect rect in _verices)
	{
		cout << "min = " << rect.min.x << ", " << rect.min.y << "\t";
		cout << "max = " << rect.max.x << ", " << rect.max.y;
		cout << endl << endl;
	}
}