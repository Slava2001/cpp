#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#define PI 3.1415926535

double Func(double x) { return (tan(2)*x); }
const double Start = 0, End = PI / 8, Hag = PI / 80, Eps = 0.001,Otvet = -0.168;
const int n = 10+1;
double MLP();
double MPP();
double MCP();
double MTR();
double MPR();

int main()
{
	setlocale(0, "");
	std::cout << "Метод левыx прямоугольников       " << MLP() << "\tDelta " << abs(MLP() - Otvet) << '\n';
	std::cout << "Метод прaвыx прямоугольников      " << MPP() << "\tDelta " << abs(MPP() - Otvet) << '\n';
	std::cout << "Метод центральныx прямоугольников " << MCP() << "\tDelta " << abs(MCP() - Otvet) << '\n';
	std::cout << "Метод трапеций                    " << MTR() << "\tDelta " << abs(MTR() - Otvet) << '\n';
	std::cout << "Метод парабол (Симсона)           " << MPR() << "\tDelta " << abs(MPR() - Otvet) << '\n';

	const int sizex = 800, sizey = 600;
	sf::RenderWindow window(sf::VideoMode(sizex, sizey), "Grafiki!!!");
	sf::View view;
	view.reset(sf::FloatRect(-sizex/10,-sizey/10, sizex+sizex/5, sizey+sizey/5));
	window.setView(view);
	sf::CircleShape funcdots[sizex];

	double haggrafx = (End - Start) / (sizex);
	double haggrafy = 1./sizey;//1 нaдо заменить на max func - min func

	for (int i = 0;i<sizex;i++)
	{   funcdots[i].setRadius(1.f);
		funcdots[i].setFillColor(sf::Color::Black);
		funcdots[i].setPosition(i,/*max func*/-Func(Start+haggrafx*i)/haggrafy);}

	sf::Vertex lineX[] =
	{sf::Vertex(sf::Vector2f(0, 1000)),
	sf::Vertex(sf::Vector2f(0, -1000))};

	lineX[0].color = sf::Color::Black;
	lineX[1].color = sf::Color::Black;
	sf::Vertex lineY[] =
	{ sf::Vertex(sf::Vector2f(-1000,0)),
	 sf::Vertex(sf::Vector2f(1000,0))};

	lineY[0].color = sf::Color::Black;
	lineY[1].color = sf::Color::Black;

	sf::CircleShape cirl[n];
	for (int i = 0; i < n; i++)
	{	cirl[i].setRadius(8.f);
		cirl[i].setFillColor(sf::Color::Transparent);
		cirl[i].setOutlineThickness(2.f);
		cirl[i].setOutlineColor(sf::Color::Blue);
		cirl[i].setPosition(i*(sizex/(n-1))-8,/*max func*/-8-Func(Start + haggrafx * (sizex/(n-1))*i) / haggrafy);}

	sf::Vertex lines[n][2] ={};

	for (int i = 0; i < n; i++)
	{	lines[i][0].color = sf::Color::Blue;
		lines[i][1].color = sf::Color::Blue;

		lines[i][0].position = sf::Vector2f(i*(sizex / (n - 1)), 0);
		lines[i][1].position = sf::Vector2f(i*(sizex / (n - 1)), - Func(Start + haggrafx * (sizex / (n - 1))*i) / haggrafy);}

	sf::Vertex linesMLP[n][2] = {};
	for (int i = 0; i < n-1; i++)
	{   linesMLP[i][0].color = sf::Color::Blue;
		linesMLP[i][1].color = sf::Color::Blue;

		linesMLP[i][0].position = sf::Vector2f(i*(sizex / (n - 1)), -Func(Start + haggrafx * (sizex / (n - 1))*i) / haggrafy);
		linesMLP[i][1].position = sf::Vector2f((i+1)*(sizex / (n - 1)), -Func(Start + haggrafx * (sizex / (n - 1))*(i)) / haggrafy);}

	sf::Vertex linesMLPV[n][2] = {};
	for (int i = 1; i < n-1; i++)//i=0 если функция не с нуля
	{   linesMLPV[i][0].color = sf::Color::Blue;
		linesMLPV[i][1].color = sf::Color::Blue;

		linesMLPV[i][0].position = sf::Vector2f((i+1)*(sizex / (n - 1)), 0);
		linesMLPV[i][1].position = sf::Vector2f((i+1)*(sizex / (n - 1)), -Func(Start + haggrafx * (sizex / (n - 1))*(i - 1)) / haggrafy);}

	sf::Vertex linesMPP[n][2] = {};
	for (int i = 1; i < n; i++)
	{	linesMPP[i][0].color = sf::Color::Blue;
		linesMPP[i][1].color = sf::Color::Blue;

		linesMPP[i][0].position = sf::Vector2f((i-1)*(sizex / (n - 1)), -Func(Start + haggrafx * (sizex / (n - 1))*(i)) / haggrafy);
		linesMPP[i][1].position = sf::Vector2f((i)*(sizex / (n - 1)), -Func(Start + haggrafx * (sizex / (n - 1))*(i)) / haggrafy);}

	sf::Vertex linesMPPV[n][2] = {};
	for (int i = 1; i < n; i++)
	{	linesMPPV[i][0].color = sf::Color::Blue;
		linesMPPV[i][1].color = sf::Color::Blue;

		linesMPPV[i][0].position = sf::Vector2f((i - 1)*(sizex / (n - 1)), 0);
		linesMPPV[i][1].position = sf::Vector2f((i - 1)*(sizex / (n - 1)), -Func(Start + haggrafx * (sizex / (n - 1))*i) / haggrafy);}

	sf::Vertex linesMCP[n][2] = {};
	for (int i = 1; i < n; i++)
	{
		linesMCP[i][0].color = sf::Color::Blue;
		linesMCP[i][1].color = sf::Color::Blue;

		linesMCP[i][0].position = sf::Vector2f((i - 1)*(sizex / (n - 1)), -Func((Start + haggrafx * (sizex / (n - 1))*(i))-(Hag/2)) / haggrafy);
		linesMCP[i][1].position = sf::Vector2f((i)*(sizex / (n - 1)), -Func((Start + haggrafx * (sizex / (n - 1))*(i)) - (Hag / 2)) / haggrafy);
	}

	sf::Vertex linesMCPV[n][2] = {};
	for (int i = 1; i < n; i++)
	{
		linesMCPV[i][0].color = sf::Color::Blue;
		linesMCPV[i][1].color = sf::Color::Blue;

		linesMCPV[i][0].position = sf::Vector2f((i - 1)*(sizex / (n - 1)), 0);
		linesMCPV[i][1].position = sf::Vector2f((i - 1)*(sizex / (n - 1)), -Func((Start + haggrafx * (sizex / (n - 1))*(i)) - (Hag / 2)) / haggrafy);
	}

	sf::Font font;
	sf::Text text;
	if (font.loadFromFile("arial.ttf"))
	{
		text.setFont(font);

		text.setString(L"Метод левыx прямоугольников");

		text.setCharacterSize(35);

		text.setFillColor(sf::Color::Black);

		text.setPosition(20, view.getCenter().y- view.getSize().y/2+ 5);
	}


	int CHAN = 1;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
			CHAN = 4, text.setString(L"Метод трапеций");
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
			CHAN = 1, text.setString(L"Метод левыx прямоугольников");
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
			CHAN = 2, text.setString(L"Метод прaвыx прямоугольников");
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
			CHAN = 3, text.setString(L"Метод центральныx прямоугольников");


		window.clear(sf::Color::White);
		window.draw(lineX, 2, sf::Lines);
		window.draw(lineY, 2, sf::Lines);
		for (int i = 0; i < sizex; i++)
		window.draw(funcdots[i]);
		for (int i = 0; i < n; i++)
		window.draw(cirl[i]);
		for (int i = 0; i < n; i++)
			window.draw(lines[i],2,sf::Lines);
		switch (CHAN)
		{case 1:
			for (int i = 0; i < n-1; i++)
			{
				window.draw(linesMLPV[i], 2, sf::Lines);
				window.draw(linesMLP[i], 2, sf::Lines);
			}
		break;
		case 2:
			for (int i = 1; i < n; i++)
			{
				window.draw(linesMPPV[i], 2, sf::Lines);
				window.draw(linesMPP[i], 2, sf::Lines);
			}
		break;
		case 3:
			for (int i = 1; i < n; i++)
			{
				window.draw(linesMCPV[i], 2, sf::Lines);
				window.draw(linesMCP[i], 2, sf::Lines);
			}
			break;
		}
		window.draw(text);
		window.display();
	}
	return 0;
}

double MLP() 
{
	double res = 0;
	for (double xi = Start; xi <= End - Hag; xi += Hag)
		res += Func(xi)*Hag;
	return res;
}
double MPP() 
{
	double res = 0;
	for (double xi =Start+ Hag; xi <= End ; xi += Hag)
		res += Func(xi)*Hag;
	return res;
}
double MCP() 
{
	double res = 0;
	for (double xi = Start; xi <= End-Hag; xi += Hag)
		res += Func((xi*2+Hag)/2)*Hag;
	return res;
}
double MTR() 
{
	double res = 0;
	for (double xi = Start+Hag; xi <= End - Hag; xi += Hag)
		res += Func(xi);
	res += (Func(Start) + Func(End)) / 2;
	res *= Hag;
	return res;
}
double MPR() 
{
	double res = 0;
	double CHS = 0;
	double NCHS = 0;
	////////////////////////////////////////////////////////////////
	for (double xi =Start, t = 0; xi <= End-Hag; xi += Hag,t++)
		(int)t%2?CHS += Func(xi): NCHS += Func(xi);
	////////////////////////////////////////////////////////////////
	res = (Hag / 3)*(Func(Start) + Func(End) + 4 * NCHS + 2 * CHS);
	return res;
}
