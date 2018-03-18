#include <vector>
#include <iostream>
#include <string>
#include <assert.h>
#include "Main.h"

using std::cout;
using std::cin;
using std::vector;
using std::string;

const vector<string> PIZZA_NAMES = {"Margarita", "Peperoni", "Hawaiian", "4Cheeses"};
const vector<string> TOPING_NAMES = {"Tomato", "Cucumber", "Chicken", "Cheese", "Sausage", "Pineapple"};
const vector<string> SAUSE_NAMES = {"Chile", "TomatoSause", "Teriyaki"};

//#################################################################################

class IBuilder;
class IFactory;
class CUserInterface;

//#################################################################################

CPizza::CPizza() {
	is_prepared_ = false;
}

void CPizza::Fry() {
	cout << "Fry pizza\n";
	is_prepared_ = true;
}

void CPizza::AddSause(CSause sause) {
	assert(!is_prepared_);
	cout << "Add " << SAUSE_NAMES[sause] << "\n";
	sause_.push_back(sause);
}

void CPizza::AddToping(CToping toping) {
	assert(!is_prepared_);
	cout << "Add " << TOPING_NAMES[toping] << "\n";
	toping_.push_back(toping);
}

vector<CToping> CPizza::GetToping() {
	return toping_;
}

vector<CSause> CPizza::GetSause() {
	return sause_;
}

bool CPizza::IsPrepared() {
	return is_prepared_;
}

//#################################################################################

bool CUserInterface::AskIsStandart() {
	cout << "1: choose standart pizza\n";
	cout << "2: create your own pizza\n";
	int x;
	cin >> x;
	return x == 1;
}

bool CUserInterface::AskMoreSause() {
	cout << "Add sause? (y/n)\n";
	char c;
	cin >> c;
	return c == 'y';
}

bool CUserInterface::AskMoreToping() {
	cout << "Add toping? (y/n)\n";
	char c;
	cin >> c;
	return c == 'y';
}

CSause CUserInterface::GetSause() {
	cout << "Choose your sause:\n";
	for (size_t i = 0; i < SAUSE_NAMES.size(); ++i) {
		cout << i + 1 << " " << SAUSE_NAMES[i] << "\n";
	}
	int x;
	cin >> x;
	return static_cast<CSause>(x - 1);
}

CToping CUserInterface::GetToping() {
	cout << "Choose your toping:\n";
	for (size_t i = 0; i < TOPING_NAMES.size(); ++i) {
		cout << i + 1 << " " << TOPING_NAMES[i] << "\n";
	}
	int x;
	cin >> x;
	return static_cast<CToping>(x - 1);
}

string CUserInterface::GetPizzaName() {
	cout << "Choose your pizza:\n";
	for (size_t i = 0; i < PIZZA_NAMES.size(); ++i) {
		cout << i + 1 << " " << PIZZA_NAMES[i] << "\n";
	}
	int x;
	cin >> x;
	return PIZZA_NAMES[x - 1];
}


//##############################################################################

IBuilder::~IBuilder() {

}

CPizza IBuilder::GetPizza() {
	return pizza_;
}

void CUserBuilder::BuildToping() {
	while (inter->AskMoreToping()) {
		pizza_.AddToping(inter->GetToping());
	}
}

void CUserBuilder::BuildSause() {
	while (inter->AskMoreSause()) {
		pizza_.AddSause(inter->GetSause());
	}
}

void CUserBuilder::BuildFrying() {
	pizza_.Fry();
}

CPizza CDirector::CreatePizza(IBuilder* builder) {
	builder->BuildToping();
	builder->BuildSause();
	builder->BuildFrying();
	return builder->GetPizza();
}

//###################################################################################

IFactory::~IFactory() {}

void CFactoryMargarita::CreateSause(CPizza& pizza) {
	pizza.AddSause(TomatoSause);
}

void CFactoryMargarita::CreateToping(CPizza& pizza) {
	pizza.AddToping(Cheese);
	pizza.AddToping(Tomato);
}

void CFactoryPeperoni::CreateSause(CPizza& pizza) {
	pizza.AddSause(Chile);
}

void CFactoryPeperoni::CreateToping(CPizza& pizza) {
	pizza.AddToping(Sausage);
	pizza.AddToping(Tomato);
}

void CFactoryHawaiian::CreateSause(CPizza& pizza) {
	pizza.AddSause(TomatoSause);
}

void CFactoryHawaiian::CreateToping(CPizza& pizza) {
	pizza.AddToping(Chicken);
	pizza.AddToping(Pineapple);
	pizza.AddToping(Cheese);
}

void CFactory4Cheeses::CreateSause(CPizza& pizza) {
	pizza.AddSause(TomatoSause);
}

void CFactory4Cheeses::CreateToping(CPizza& pizza) {
	pizza.AddToping(Cheese);
	pizza.AddToping(Cheese);
	pizza.AddToping(Cheese);
	pizza.AddToping(Cheese);
}

CPizza CMaker::MakePizza(IFactory* factory) {
	CPizza pizza;
	factory->CreateSause(pizza);
	factory->CreateToping(pizza);
	pizza.Fry();
	return pizza;
}


//###################################################################################

void run() {
	CUserInterface interface;
	if (interface.AskIsStandart()) {
		IFactory* factory = nullptr;
		string pizza_name = interface.GetPizzaName();
		if (pizza_name == "Margarita") {
			factory = static_cast<IFactory*>(new CFactoryMargarita());
		}
		else if (pizza_name == "Peperoni") {
			factory = static_cast<IFactory*>(new CFactoryPeperoni());
		}
		else if (pizza_name == "Hawaiian"){
			factory = static_cast<IFactory*>(new CFactoryHawaiian());
		}
		else if (pizza_name == "4Cheeses") {
			factory = static_cast<IFactory*>(new CFactory4Cheeses());
		}
		else {
			assert(false);
		}

		CMaker maker;
		CPizza pizza = maker.MakePizza(factory);
		delete factory;
	}
	else {
		//CUserBuilder* builder = new CUserBuilder();
		CUserBuilder* builder = new CUserBuilder();
		builder->inter = &interface;
		CDirector director;
		CPizza pizza = director.CreatePizza(builder);
		delete builder;
	}

	//system("pause");
}

//###################################################################################
