/*
   ****************************************
   *                                      * 
   * Author: Ammar Alsayed Ibrahim        * 
   * Sec: 2          BN: 4                * 
   * GitHibLink:                          * 
   * desc: this prog is designed for      * 
   * bonus task in term holiday			  * 
   * for D.Khaled                         * 
   *                                      * 
   ****************************************
*/

/// usage: divide your shape into rectangles in paint and get the vertices, then pass to constrctor


#include"asmShape.h"
#include<string>
#include<fstream>
#include <windows.h>
using namespace std;


///////////	for unicode (the arabic comments)
std::string to_utf8(const wchar_t* buffer, int len)
{
	int nChars = ::WideCharToMultiByte(
		CP_UTF8,
		0,
		buffer,
		len,
		NULL,
		0,
		NULL,
		NULL);
	if (nChars == 0) return "";

	string newbuffer;
	newbuffer.resize(nChars);
	::WideCharToMultiByte(
		CP_UTF8,
		0,
		buffer,
		len,
		const_cast< char* >(newbuffer.c_str()),
		nChars,
		NULL,
		NULL);

	return newbuffer;
}

std::string to_utf8(const std::wstring& str)
{
	return to_utf8(str.c_str(), (int)str.size());
}
///////////



// عدل مكان البروجكت علي حسب مكانه لو عايز تغير في الفايلز و بعدين compile
#define PROJ_PATH "C:\\Data\\Work and projects\\CMP projects\\CMP2.projects\\Micro\\Holiday MP\\"


class Duck : public asmShape
{
public:
	Duck(vector<Rect> basicVerices) : asmShape(basicVerices){}


	virtual void generateDrawingAsm(string fileName, string macroName)
	{
		ofstream newOutFile(PROJ_PATH + fileName + ".inc");
		if (!newOutFile.is_open())
		{
			cout << "\n\ncan't put the data to a text file!!";
			return;
		}

		
		// equs
		newOutFile << to_utf8(L"; بعرف طول البطة و عرضها عشان بحتاجه عشان اعرف الصندوق اللي بيحدد البطة") << endl;
		newOutFile << "duck_length equ " << getLength() << "d\n";
		newOutFile << "duck_width equ " << getWidht() << "d\n";


		newOutFile << ";take color = mem(color)\n";
		newOutFile << ";take duck x min = mem(drxmin)\n";
		newOutFile << ";take duck y min = mem(drymin)\n";
		newOutFile << macroName << " macro xmin,ymin ,color\n";

		newOutFile << "push cx\n";
		newOutFile << "push dx\n";

		newOutFile << to_utf8(L"; بخلي اللون اللي هرسم بيه كل المربعات الللون المبعوتلي في الماكرو") << endl;
		newOutFile << "mov cl,color\n";
		newOutFile << "mov drcolor, cl\n";

		newOutFile << to_utf8(L"; بنقل أقل نقطة في الرجسترز عشان لكل مربع بنقلهم كقيمة ابتدائية للمربع لأن أقل نقطة هيه المسافة اللي هيتعملها translation") << endl;
		newOutFile << "mov cx,xmin\n";
		newOutFile << "mov dx,ymin\n";

		vector<Rect> vertices = getVertices();
		for each (Rect rect in vertices)
		{
			newOutFile << to_utf8(L"; المربع من ") << rect.min.x << ", " << rect.min.y << to_utf8(L" ل") << rect.max.x << ", " << rect.max.y << endl;

			newOutFile << to_utf8(L"; بدي القيمة الابتدائية للنقطتين بتوع المربع أقل نقطة للبطة و بعدين بزود بعد النقطة اللي معايا عن الصفر و الصفر بالنسبة للشكل الأصلي اللي معايا من غير أي ترانسليشن") << endl;
			newOutFile << "mov drxmax, cx\n"; 
			newOutFile << "mov drymax, dx\n"; 
			newOutFile << "mov drxmin, cx\n"; 
			newOutFile << "mov drymin, dx\n"; 

			newOutFile << to_utf8(L"; بظبط الداتا المبعوتة باني ازود النقطتين") << endl;
			newOutFile << "add drxmax, " << rect.max.x << "d" << endl;
			newOutFile << "add drymax, " << rect.max.y << "d" << endl;
			newOutFile << "add drxmin, " << rect.min.x << "d" << endl;
			newOutFile << "add drymin, " << rect.min.y << "d" << endl;
			
			newOutFile << to_utf8(L"; بارسم المربع اللي هوه جزء من البطة") << endl;
			newOutFile << "call drawrect\n";

			newOutFile << "\n\n";
		}

		Rect& eye = vertices[vertices.size() - 1];
		newOutFile << "\n";

		newOutFile << ";eye\n";
		newOutFile << to_utf8(L"; بدي القيمة الابتدائية للنقطتين بتوع المربع أقل نقطة للبطة و بعدين بزود بعد النقطة اللي معايا عن الصفر و الصفر بالنسبة للشكل الأصلي اللي معايا من غير أي ترانسليشن") << endl;
		newOutFile << "mov drxmax, cx\n";
		newOutFile << "mov drymax, dx\n";
		newOutFile << "mov drxmin, cx\n";
		newOutFile << "mov drymin, dx\n";

		newOutFile << to_utf8(L"; بظبط الداتا المبعوتة باني ازود النقطتين") << endl;
		newOutFile << "add drxmax, " << eye.max.x << "d" << endl;
		newOutFile << "add drymax, " << eye.max.y << "d" << endl;
		newOutFile << "add drxmin, " << eye.min.x << "d" << endl;
		newOutFile << "add drymin, " << eye.min.y << "d" << endl;

		newOutFile << to_utf8(L"; بخلي لون عينها لون الخلفية دايما") << endl;
		newOutFile << "mov drcolor, backgroundcolor\n";

		newOutFile << to_utf8(L"; برسم المربع اللي هوه عين البطة") << endl;
		newOutFile << "call drawrect\n";

		newOutFile << "\n\n";
		newOutFile << "pop dx\n";
		newOutFile << "pop cx\n";
		newOutFile << macroName << " endm";
	}

};

class Obst : public asmShape
{


public:
	Obst(vector<Rect> basicVerices) : asmShape(basicVerices){}

	virtual void generateDrawingAsm(string fileName, string macroName)
	{
		ofstream newOutFile(PROJ_PATH + fileName + ".inc");
		if (!newOutFile.is_open())
		{
			cout << "\n\ncan't put the data to a text file!!";
			return;
		}

		newOutFile << to_utf8(L"; كل الكومنتات هنا هتبقي نفس الفكرة زي رسم البطة") << endl;

		// equs
		newOutFile << "obst_length equ " << getLength() << endl;
		newOutFile << "obst_width equ " << getWidht() << endl;


		newOutFile << ";take color = mem(color)\n";
		newOutFile << ";take duck x min = mem(drxmin)\n";
		newOutFile << ";take duck y min = mem(drymin)\n";
		newOutFile << macroName << " macro xmin, ymin, color\n";

		newOutFile << "push cx\n";
		newOutFile << "push dx\n";

		newOutFile << "mov cl,color\n";
		newOutFile << "mov drcolor, cl\n";

		newOutFile << "mov cx,xmin\n";
		newOutFile << "mov dx,ymin\n";

		vector<Rect> vertices = getVertices();
		for each (Rect rect in vertices)
		{
			newOutFile << "mov drxmax, cx\n";
			newOutFile << "mov drymax, dx\n";
			newOutFile << "mov drxmin, cx\n";
			newOutFile << "mov drymin, dx\n";

			newOutFile << "add drxmax, " << rect.max.x << "d" << endl;
			newOutFile << "add drymax, " << rect.max.y << "d" << endl;
			newOutFile << "add drxmin, " << rect.min.x << "d" << endl;
			newOutFile << "add drymin, " << rect.min.y << "d" << endl;

			newOutFile << "call drawrect\n";

			newOutFile << "\n\n";
		}

		newOutFile << "pop dx\n";
		newOutFile << "pop cx\n";
		newOutFile << macroName << " endm";
	}
};





#define EYE_POS_MIN 80,39
#define EYE_POS_MAX 81,40


void load_vertices(vector<Rect>& basicVerices);
vector<Rect> load_vertices_obst();
vector<Rect> load_vertices_obst_shok(int num, int one_width, int one_height);
void load_vertices_duckRight2(vector<Rect>& basicVerices);

int main()
{
	/// duck1 (up state)
	vector<Rect> basicVerices;
	load_vertices(basicVerices);

	basicVerices.push_back(Rect(Vertix(EYE_POS_MIN), Vertix(EYE_POS_MAX)));
	Duck duckRight(basicVerices);
	duckRight.scale(0.4f);
	duckRight.generateDrawingAsm("drawDuckRight", "drawDuckRightM");

	Duck duckLeft(duckRight);
	duckLeft.reflectAbouty();
	duckLeft.generateDrawingAsm("drawDuckLeft", "drawDuckLeftM");

	/// duck2 (down state)
	load_vertices_duckRight2(basicVerices);
	basicVerices.push_back(Rect(Vertix(EYE_POS_MIN), Vertix(EYE_POS_MAX)));
	Duck duckRight2(basicVerices);
	duckRight2.scale(0.4f);
	duckRight2.generateDrawingAsm("drawDuckRight2", "drawDuckRight2M");

	Duck duckLeft2(duckRight2);
	duckLeft2.reflectAbouty();
	duckLeft2.generateDrawingAsm("drawDuckLeft2", "drawDuckLeft2M");

	/// obstacles:
	//basicVerices = load_vertices_obst();
	basicVerices = load_vertices_obst_shok(3,4,8); // choose oneWidth, one height divisable by scaling
	Obst obst(basicVerices);
	obst.scale(0.5f);
	obst.generateDrawingAsm("drawObst", "drawObstM");
	return 0;
}



void load_vertices(vector<Rect>& basicVerices)
{
	basicVerices.clear();

	//									   36
	basicVerices.push_back(Rect(Vertix(77, 34), Vertix(96, 47)));

	basicVerices.push_back(Rect(Vertix(74, 37), Vertix(77, 47)));

	basicVerices.push_back(Rect(Vertix(68, 56), Vertix(84, 69)));

	//
	basicVerices.push_back(Rect(Vertix(74, 48), Vertix(86, 53)));

	basicVerices.push_back(Rect(Vertix(87, 51), Vertix(94, 53)));

	basicVerices.push_back(Rect(Vertix(68, 69), Vertix(81, 73)));

	//
	basicVerices.push_back(Rect(Vertix(96, 47), Vertix(99, 37)));

	basicVerices.push_back(Rect(Vertix(72, 53), Vertix(84, 56)));

	basicVerices.push_back(Rect(Vertix(68, 74), Vertix(79, 76)));

	//
	basicVerices.push_back(Rect(Vertix(69, 76), Vertix(76, 78)));

	basicVerices.push_back(Rect(Vertix(64, 58), Vertix(68, 80)));

	basicVerices.push_back(Rect(Vertix(62, 61), Vertix(64, 85)));

	//
	basicVerices.push_back(Rect(Vertix(62, 86), Vertix(66, 88)));

	basicVerices.push_back(Rect(Vertix(74, 78), Vertix(81, 81)));

	basicVerices.push_back(Rect(Vertix(49, 53), Vertix(51, 67)));


	//
	basicVerices.push_back(Rect(Vertix(52, 58), Vertix(54, 71)));


	//
	basicVerices.push_back(Rect(Vertix(84, 58), Vertix(89, 61)));
	basicVerices.push_back(Rect(Vertix(86, 61), Vertix(89, 64)));
	basicVerices.push_back(Rect(Vertix(55, 61), Vertix(57, 73)));
	basicVerices.push_back(Rect(Vertix(58, 64), Vertix(61, 78)));

}

//void load_vertices_duckRight2(vector<Rect>& basicVerices)
//
//{
//	basicVerices.push_back(Rect(Vertix(28, 0), Vertix(47, 3)));
//
//	basicVerices.push_back(Rect(Vertix(25, 3), Vertix(50, 13)));
//
//	basicVerices.push_back(Rect(Vertix(25, 14), Vertix(35, 34)));
//
//	basicVerices.push_back(Rect(Vertix(36, 16), Vertix(45, 18)));
//
//	basicVerices.push_back(Rect(Vertix(36, 14), Vertix(37, 15)));
//
//	basicVerices.push_back(Rect(Vertix(13, 16), Vertix(45, 18)));
//
//	basicVerices.push_back(Rect(Vertix(36, 23), Vertix(40, 26)));
//
//	basicVerices.push_back(Rect(Vertix(37, 27), Vertix(40, 30)));
//
//	/// tail
//	basicVerices.push_back(Rect(Vertix(0, 18), Vertix(3, 33)));
//
//	basicVerices.push_back(Rect(Vertix(3, 23), Vertix(5, 36)));
//
//	basicVerices.push_back(Rect(Vertix(5, 26), Vertix(7, 38)));
//
//	basicVerices.push_back(Rect(Vertix(8, 28), Vertix(10, 41)));
//
//	basicVerices.push_back(Rect(Vertix(10, 28), Vertix(12, 43)));
//
//	/// for legs 2
//	basicVerices.push_back(Rect(Vertix(13, 26), Vertix(17, 46)));
//
//	basicVerices.push_back(Rect(Vertix(15, 46), Vertix(20, 48)));
//
//	basicVerices.push_back(Rect(Vertix(15, 24), Vertix(18, 26)));
//
//	basicVerices.push_back(Rect(Vertix(18, 21), Vertix(23, 43)));
//
//	basicVerices.push_back(Rect(Vertix(23, 18), Vertix(25, 46)));
//
//	basicVerices.push_back(Rect(Vertix(25, 35), Vertix(27, 53)));
//
//	basicVerices.push_back(Rect(Vertix(28, 51), Vertix(30, 53)));
//
//	basicVerices.push_back(Rect(Vertix(28, 35), Vertix(32, 41)));
//
//}


void load_vertices_duckRight2(vector<Rect>& basicVerices)
{
	basicVerices.clear();

	//									   36
	basicVerices.push_back(Rect(Vertix(77, 34), Vertix(96, 47)));

	basicVerices.push_back(Rect(Vertix(74, 37), Vertix(77, 47)));

	basicVerices.push_back(Rect(Vertix(68, 56), Vertix(84, 69)));

	//
	basicVerices.push_back(Rect(Vertix(74, 48), Vertix(86, 53)));

	basicVerices.push_back(Rect(Vertix(87, 51), Vertix(94, 53)));

	basicVerices.push_back(Rect(Vertix(68, 69), Vertix(81, 73)));

	//
	basicVerices.push_back(Rect(Vertix(96, 47), Vertix(99, 37)));

	basicVerices.push_back(Rect(Vertix(72, 53), Vertix(84, 56)));

	basicVerices.push_back(Rect(Vertix(68, 74), Vertix(79, 76)));

	//
	basicVerices.push_back(Rect(Vertix(69, 76), Vertix(76, 78)));

	basicVerices.push_back(Rect(Vertix(64, 58), Vertix(68, 80)));

	basicVerices.push_back(Rect(Vertix(62, 61), Vertix(64, 80)));

	//
	basicVerices.push_back(Rect(Vertix(62, 81), Vertix(66, 83)));

	basicVerices.push_back(Rect(Vertix(74, 78), Vertix(81, 86)));

	basicVerices.push_back(Rect(Vertix(49, 53), Vertix(51, 67)));


	//
	basicVerices.push_back(Rect(Vertix(52, 58), Vertix(54, 71)));


	//
	basicVerices.push_back(Rect(Vertix(84, 58), Vertix(89, 61)));
	basicVerices.push_back(Rect(Vertix(86, 61), Vertix(89, 64)));
	basicVerices.push_back(Rect(Vertix(55, 61), Vertix(57, 73)));
	basicVerices.push_back(Rect(Vertix(58, 64), Vertix(61, 78)));

}
vector<Rect> load_vertices_obst()
{
	vector<Rect> basicVerices;
	//
	basicVerices.push_back(Rect(Vertix(9, 0), Vertix(18, 56)));

	basicVerices.push_back(Rect(Vertix(0, 17), Vertix(5, 34)));

	basicVerices.push_back(Rect(Vertix(23, 17), Vertix(27, 34)));

	basicVerices.push_back(Rect(Vertix(6, 33), Vertix(23, 37)));

	return basicVerices;
}



vector<Rect> load_vertices_obst_shok(int num, int one_width, int one_height)
{
	vector<Rect> basicVerices;
	const int xstart = 0;
	const int ystart = 0;
	//
	for (int i = 0; i < num; i++)
	{
		basicVerices.push_back(Rect(Vertix(8*i, 0), Vertix(8*i + one_width, one_height)));
	}
	basicVerices.push_back(Rect(Vertix(0, one_height + 1), Vertix(8 * (num - 1) + one_width, one_height + 4)));
	return basicVerices;
}