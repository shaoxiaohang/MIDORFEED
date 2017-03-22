#include<QtCore/QCoreApplication>
#include<iostream>
int main(int argc, char** argv)
{
	QCoreApplication a(argc, argv);
	std::cout << "hello world";
	return a.exec();
}