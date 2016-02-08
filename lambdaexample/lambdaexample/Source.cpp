#include <iostream>
#include <functional>
#include <vector>

class Event
{
public:
	void Register(std::function<void()> f)
	{
		mHandlers.emplace_back(f);
	}

	void Trigger()
	{
		for (auto& f : mHandlers)
		{
			f();
		}
	}
private:
	std::vector<std::function<void()>> mHandlers;
};
struct TestClass
{
	void f1()
	{
		auto lmbda = [this]()
		{
			f2(); 
		}; 

	}

	void f2()
	{

	}
};
int main()
{
	//[] capture clause
	int x = 5;
	int y = 10; 
	auto lambda1 = [&x,&y]() {
		std::cout << "Hello, world!\n";
		y--;
		std::cout << x << " " << y << std::endl; 
		//outputs 5 9
	};

	Event e;
	e.Register(lambda1);
	e.Register([&y]() {

		std::cout << "Lambdas are cool!\n";
		std::cout << " " << y << std::endl;

		//outputs 9
		//get's y reference 

	});

	e.Trigger();
	system("pause"); 
	return 0;
}