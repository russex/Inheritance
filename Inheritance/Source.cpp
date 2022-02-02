#define _USE_MATH_DEFINES
#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<cmath>
using namespace std;

namespace Geometry
{
	//#define DRAW*
//#define DRAW_CONSOLE
#define DRAW_RACTANGLE

	enum Color
	{
		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,
		yellow = 0x0000FFFF,
		white = 0xFFFFFF,

		console_default = 0x07,
		console_blue = 0x99,
		console_green = 0xAA,
		console_purpul = 0x55,
		conslole_yellow = 0xEE,
		conslode_white = 0xFF
	};
	class Shape
	{
		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_thickness;
	protected:
		Color color;
	public:
		Shape(unsigned int start_x, unsigned int start_y, unsigned int line_thickness, Color color) :
			start_x(start_x), start_y(start_y), line_thickness(line_thickness), color(color) {}
		virtual ~Shape() {}
		int get_start_x()const
		{
			return start_x;
		}
		int get_start_y()const
		{
			return start_y;
		}
		int get_line_thickness()const
		{
			return line_thickness;
		}
		//На зянятии:
		void set_line_thickness(unsigned int line_thickness)
		{
			if (line_thickness >= 120)line_thickness = 120;
			this->line_thickness = line_thickness;
		}
		void set_start_x(unsigned int start_x)
		{
			HWND hwnd = GetConsoleWindow();
			RECT rect;
			GetWindowRect(hwnd, &rect);

			if (start_x < 400)start_x = 400;
			if (start_x > (rect.right - rect.left) / 2)start_x = (rect.right - rect.left) / 2;
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			HWND hwnd = GetConsoleWindow();
			RECT rect;
			GetWindowRect(hwnd, &rect);
			if (start_y < 100)start_y = 100;
			if (start_y > (rect.bottom - rect.top) * .5)start_y = (rect.bottom - rect.top) * .5;
			this->start_y = start_y;
		}

		virtual double get_area()const = 0;  
		virtual double get_perimeter()const = 0; 
		virtual void draw()const = 0;            
	};

	class Square :public Shape
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side <= 0) side = 1;
			this->side = side;
		}
		Square(unsigned int start_x, unsigned int start_y, unsigned int line_thickness, double side, Color color) :
			Shape(start_x, start_y, line_thickness, color)
		{
			set_side(side);
		}
		~Square() {};

		double get_area()const
		{
			return side * side;
		}
		double get_perimeter()const
		{
			return side * 4;
		}

		void draw()const
		{
#ifdef DRAW*
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < side; i++)
			{
				for (int i = 0; i < side; i++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);
#endif // DRAW*

#ifdef DRAW_CONSOLE
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, get_line_thickness(), color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			/*int start_x = 400;;
			int start_y = 200;*/
			const POINT verticies[] =
			{
				{get_start_x(),get_start_y()},
				{get_start_x(),get_start_y() + side},
				{get_start_x() + side,get_start_y() + side},
				{get_start_x() + side,get_start_y()}
			};

			Polygon(hdc, verticies, sizeof(verticies) / sizeof(POINT));

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
#endif // 
#ifdef DRAW_RACTANGLE
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, get_line_thickness(), color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Rectangle(hdc, get_start_x(), get_start_y(), get_start_x() + side, get_start_y() + side);

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
#endif // DRAW_RACTANGLE

		}
		void info()
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны:\t" << side << endl;
			cout << "Площадь:\t" << get_area() << endl;
			cout << "Периметр:\t" << get_perimeter() << endl;
			char key;
			do
			{
				draw();
				if (key = _kbhit())key = _getch();
			} while (key != 27);
			system("CLS");
		}
	};

	class Rectangle :public Shape
	{
		double side_A;
		double side_B;
	public:
		double get_side_A()const
		{
			return side_A;
		}
		double get_side_B()const
		{
			return side_B;
		}
		void set_side_A(double side_A)
		{
			if (side_A <= 0)side_A = 1;
			this->side_A = side_A;
		}
		void set_side_B(double side_B)
		{
			if (side_B <= 0)side_B = 1;
			this->side_B = side_B;
		}
		Rectangle(unsigned int start_x, unsigned int start_y, unsigned int line_thickness, double side_A, double side_B, Color color) :
			Shape(start_x, start_y, line_thickness, color)
		{
			set_side_A(side_A);
			set_side_B(side_B);
		}
		~Rectangle() {};

		double get_area()const
		{
			return side_A * side_B;
		}
		double get_perimeter()const
		{
			return (side_A + side_B) * 2;
		}
		void draw()const
		{
#ifdef DRAW*
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			for (int i = 0; i < side_A; i++)
			{
				SetConsoleTextAttribute(hConsole, color);
				for (int j = 0; j < side_B; j++)
				{
					cout << "* ";
				}
				SetConsoleTextAttribute(hConsole, Color::console_default);
				cout << endl;
			}
#endif // DRAW*

#ifdef DRAW_CONSOLE
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, get_line_thickness(), color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			/*int start_x = 400;
			int start_y = 200;*/
			const POINT verticies[] =
			{
				{get_start_x(),get_start_y()},
				{get_start_x(),get_start_y() + side_A},
				{get_start_x() + side_B,get_start_y() + side_A},
				{get_start_x() + side_B,get_start_y()}
			};
			Polygon(hdc, verticies, sizeof(verticies) / sizeof(POINT));

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
#endif // DRAW_CONSOLE

#ifdef DRAW_RACTANGLE
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, get_line_thickness(), color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Rectangle(hdc, get_start_x(), get_start_y(), get_start_x() + side_B, get_start_y() + side_A);

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
#endif // DRAW_RACTANGLE

		}
		void info()
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны A:\t" << side_A << endl;
			cout << "Длина стороны B:\t" << side_B << endl;
			cout << "Площадь:\t" << get_area() << endl;
			cout << "Периметр:\t" << get_perimeter() << endl;
			char key;
			do
			{
				draw();
				if (key = _kbhit())key = _getch();
			} while (key != 27);
			system("CLS");
		}
	};

	class Circle : public Shape
	{
		double radius;
	public:
		Circle(unsigned int start_x, unsigned  int start_y, unsigned int line_thickness, double radius, Color color = Color::white) :
			//На зянятии:
			//Circle( double radius, Color color = Color::white,unsigned int start_x=5, unsigned  int start_y=400, unsigned int line_thickness=100) :
			Shape(start_x, start_y, line_thickness, color)
		{
			set_radius(radius);
		}
		~Circle() {};
		void set_radius(double radius)
		{
			if (radius <= 0)radius = 1;
			this->radius = radius;
		}
		double get_radius()const
		{
			return radius;
		}

		double get_area()const
		{
			return pow(radius, 2) * M_PI;
		}
		double get_perimeter()const
		{
			return 2 * radius * M_PI;
		}
		void draw() const
		{
		
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, get_line_thickness(), color);
			HBRUSH hbrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hbrush);

			Ellipse(hdc, get_start_x(), get_start_y(), get_start_x() + 2 * radius, get_start_y() + 2 * radius);

			DeleteObject(hPen);
			DeleteObject(hbrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус круга:\t" << get_radius() << endl;
			cout << "Площадь круга:\t" << get_area() << endl;
			cout << "Периметр круга:\t" << get_perimeter() << endl;
			char key;
			do
			{
				draw();
				if (key = _kbhit())key = _getch();
			} while (key != 27);
			system("CLS");
		}

	};

	class Triangle :public Shape
	{
	public:
		Triangle(int start_x, int start_y, int line_thickness, Color color = Color::white) :
			Shape(start_x, start_y, line_thickness, color) {};
		~Triangle() {};
		virtual double get_height()const = 0;
	};

	class EquilateralTriangle :public Triangle
	{
		double side;
	public:
		EquilateralTriangle(unsigned int start_x, unsigned int start_y, unsigned  int line_thickness, double side, Color color = Color::white) :
			Triangle(start_x, start_y, line_thickness, color)
		{
			set_side(side);
		}
		~EquilateralTriangle() {};
		void set_side(double side)
		{
			if (side <= 0)side = 1;
			this->side = side;
		}
		double get_side()const
		{
			return side;
		}
		double get_height()const
		{
			return sqrt(side * side - pow(side / 2, 2));
		}
		double get_area()const
		{
			return (side * get_height()) / 2;
		}
		double get_perimeter()const
		{
			return 3 * side;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, get_line_thickness(), color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			const POINT verticies[] =
			{
				{get_start_x(), get_start_y() + side},
				{get_start_x() + side , get_start_y() + side},
				{get_start_x() + side / 2,get_start_y() + side - get_height()}
			};

			Polygon(hdc, verticies, sizeof(verticies) / sizeof(POINT));

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info() const
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны:\t" << get_side() << endl;
			cout << "Высота треуголька:\t" << get_height() << endl;
			cout << "Площадь треугольника:\t" << get_area() << endl;
			cout << "Периметр треугольника:\t" << get_perimeter() << endl;
			char key;
			do
			{
				draw();
				if (key = _kbhit())key = _getch();
			} while (key != 27);
			system("CLS");
		}
	};

	class IsoscelesTriangle : public Triangle
	{
		double side_S;
		double side_G;
	public:
		IsoscelesTriangle(int start_x, int start_y, int line_thickness, double side_S, double side_G, Color color = Color::white) :
			Triangle(start_x, start_y, line_thickness, color)
		{
			set_side_G(side_G);
			set_side_S(side_S);
		}
		~IsoscelesTriangle() {}
		void set_side_S(double side_S)
		{
			if (side_S <= 0)side_S = 1;
			this->side_S = side_S;
		}
		void set_side_G(double side_G)
		{
			if (side_G <= 0)side_G = 1;
			this->side_G = side_G;
		}
		double get_side_S()const
		{
			return side_S;
		}
		double get_side_G()const
		{
			return side_G;
		}
		double get_height()const
		{
			return sqrt(side_S * side_S - pow(side_G / 2, 2));
		}
		double get_area()const
		{
			return (side_G * get_height()) / 2;
		}
		double get_perimeter()const
		{
			return side_S * 2 + side_G;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, get_line_thickness(), color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			const POINT verticies[] =
			{
				{get_start_x(),get_start_y() + side_S},
				{get_start_x() + side_G,get_start_y() + side_S},
				{get_start_x() + side_G / 2,get_start_y() + side_S - get_height()}
			};

			Polygon(hdc, verticies, sizeof(verticies) / sizeof(POINT));

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info() const
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина сторон:\t" << get_side_S() << endl;
			cout << "Длина основания:\t" << get_side_G() << endl;
			cout << "Высота треуголька:\t" << get_height() << endl;
			cout << "Площадь треугольника:\t" << get_area() << endl;
			cout << "Периметр треугольника:\t" << get_perimeter() << endl;
			char key;
			do
			{
				draw();
				if (key = _kbhit())key = _getch();
			} while (key != 27);
			system("CLS");
		}
	};

	class RightTriangle : public Triangle
	{
		double side_K;
	public:
		RightTriangle(int start_x, int start_y, int line_thickness,
			double side_K, Color color = Color::white) :
			Triangle(start_x, start_y, line_thickness, color)
		{
			set_side_K(side_K);
		}
		~RightTriangle() {}

		void set_side_K(double side_K)
		{
			if (side_K <= 0)side_K = 1;
			this->side_K = side_K;
		}

		double get_side_K(double side_K)
		{
			return side_K;
		}
		double get_height()const
		{
			return sqrt(side_K * side_K - (pow(((sqrt(pow(side_K, 2) + pow(side_K, 2))) / 2), 2)));
		}
		double get_area()const
		{
			return (side_K * side_K) / 2;
		}
		double get_perimeter()const
		{
			return side_K + side_K + (sqrt(pow(side_K, 2) + pow(side_K, 2)));
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, get_line_thickness(), color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			const POINT verticies[] =
			{
				{get_start_x(),get_start_y()},
			{get_start_x(),get_start_y() + side_K},
				{get_start_x() + side_K,get_start_y() + side_K}
			};

			Polygon(hdc, verticies, sizeof(verticies) / sizeof(POINT));

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info() const
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина катетов:\t" << side_K << endl;
			cout << "Длина гипотенузы:\t" << sqrt(pow(side_K, 2) + pow(side_K, 2)) << endl;
			cout << "Высота треуголька:\t" << get_height() << endl;
			cout << "Площадь треугольника:\t" << get_area() << endl;
			cout << "Периметр треугольника:\t" << get_perimeter() << endl;
			char key;
			do
			{
				draw();
				if (key = _kbhit())key = _getch();
			} while (key != 27);
			system("CLS");
		}
	};
}


void main()
{
	setlocale(LC_ALL, "Rus");
	Geometry::Square square(400, 200, 100, 200, Geometry::Color::yellow); square.info();
	Geometry::Rectangle rect(350, 200, 120, 200, 300, Geometry::Color::conslole_yellow); rect.info();
	Geometry::Circle kr(70, 200, 5, 100, Geometry::Color::yellow); kr.info();
	Geometry::EquilateralTriangle tr(350, 250, 15, 200, Geometry::Color::green); tr.info();
	Geometry::IsoscelesTriangle tre(150, 400, 5, 200, 250, Geometry::Color::red); tre.info();
	Geometry::RightTriangle  k(350, 400, 5, 200, Geometry::Color::red); k.info();

}