#include <vector>
#include <iostream>
#include <string>
#include <assert.h>

using std::cout;
using std::cin;
using std::vector;
using std::string;

enum CToping{Tomato = 0, Cucumber, Chicken, Cheese, Sausage, Pineapple};
enum CSause{Chile = 0, TomatoSause, Teriyaki};

const vector<string> PIZZA_NAMES = {"Margarita", "Peperoni", "Hawaiian", "4Cheeses"};
const vector<string> TOPING_NAMES = {"Tomato", "Cucumber", "Chicken", "Cheese", "Sausage", "Pineapple"};
const vector<string> SAUSE_NAMES = {"Chile", "TomatoSause", "Teriyaki"};

struct CPizza {
public:
	vector<CToping> toping;
	vector<CSause> sause;
};

//#################################################################################

class IBuilder;
class IFactory;
class CInterface;

//#################################################################################

void PreparePizza(CPizza pizza_) {
	cout << "Prepare dough\n";

	for (int i = 0; i < pizza_.sause.size(); ++i) {
		cout << "Add " << SAUSE_NAMES[pizza_.sause[i]] << "\n";
	}

	for (int i = 0; i < pizza_.toping.size(); ++i) {
		cout << "Add " << TOPING_NAMES[pizza_.toping[i]] << "\n";
	}

	cout << "Send pizza\n";
}

class CInterface {
public:
	bool AskIsStandart() {
		cout << "1: choose standart pizza\n";
		cout << "2: create your own pizza\n";
		int x;
		cin >> x;
		return x == 1;
	}

	bool AskMoreSause() {
		cout << "Add sause? (y/n)\n";
		char c;
		cin >> c;
		return c == 'y';
	}
	bool AskMoreToping() {
		cout << "Add toping? (y/n)\n";
		char c;
		cin >> c;
		return c == 'y';
	}

	CSause GetSause() {
		cout << "Choose your sause:\n";
		for (size_t i = 0; i < SAUSE_NAMES.size(); ++i) {
			cout << i + 1 << " " << SAUSE_NAMES[i] << "\n";
		}
		int x;
		cin >> x;
		return static_cast<CSause>(x - 1);
	}
	CToping GetToping() {
		cout << "Choose your toping:\n";
		for (size_t i = 0; i < TOPING_NAMES.size(); ++i) {
			cout << i + 1 << " " << TOPING_NAMES[i] << "\n";
		}
		int x;
		cin >> x;
		return static_cast<CToping>(x - 1);
	}
	string GetPizzaName() {
		cout << "Choose your pizza:\n";
		for (size_t i = 0; i < PIZZA_NAMES.size(); ++i) {
			cout << i + 1 << " " << PIZZA_NAMES[i] << "\n";
		}
		int x;
		cin >> x;
		return PIZZA_NAMES[x - 1];
	}
};

//##############################################################################


class IBuilder {
protected:
	CPizza pizza_;
public:
	virtual void BuildToping() = 0;
	virtual void BuildSause() = 0;
	CPizza GetPizza() { return pizza_; }
};

class CUserBuilder : public IBuilder {
public:
	CInterface* inter;

	void BuildToping() {
		while (inter->AskMoreToping()) {
			pizza_.toping.push_back(inter->GetToping());
		}
	}

	void BuildSause() {
		while (inter->AskMoreSause()) {
			pizza_.sause.push_back(inter->GetSause());
		}
	}
};

class CDirector {
public:
	CPizza CreatePizza(IBuilder* builder) {
		builder->BuildToping();
		builder->BuildSause();
		return builder->GetPizza();
	}
};

//###################################################################################

class IFactory {
public:
	virtual vector<CSause> CreateSause() = 0;
	virtual vector<CToping> CreateToping() = 0;
};

class CFactoryMargarita : public IFactory {
public:
	vector<CSause> CreateSause() {
		vector<CSause> vec = {TomatoSause};
		return vec;
	}

	vector<CToping> CreateToping() {
		vector<CToping> vec = {Tomato, Cheese};
		return vec;
	}
};

class CFactory4Cheeses : public IFactory {
public:
	vector<CSause> CreateSause() {
		vector<CSause> vec = {TomatoSause};
		return vec;
	}

	vector<CToping> CreateToping() {
		vector<CToping> vec = {Cheese, Cheese, Cheese, Cheese};
		return vec;
	}
};

class CFactoryPeperoni : public IFactory {
public:
	vector<CSause> CreateSause() {
		vector<CSause> vec = {Chile};
		return vec;
	}

	vector<CToping> CreateToping() {
		vector<CToping> vec = {Tomato, Sausage, Cheese};
		return vec;
	}
};

class CFactoryHawaiian : public IFactory {
public:
	vector<CSause> CreateSause() {
		vector<CSause> vec = {TomatoSause};
		return vec;
	}

	vector<CToping> CreateToping() {
		vector<CToping> vec = {Chicken, Pineapple, Cheese};
		return vec;
	}
};

class CMaker {
public:
	CPizza MakePizza(IFactory* factory) {
		CPizza pizza;
		pizza.sause = factory->CreateSause();
		pizza.toping = factory->CreateToping();
		return pizza;
	}
};

//###################################################################################

int main() {
	CInterface interface;
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
		PreparePizza(pizza);
	}
	else {
		CUserBuilder* builder = new CUserBuilder();
		builder->inter = &interface;
		CDirector director;
		CPizza pizza = director.CreatePizza(builder);
		PreparePizza(pizza);
	}

	system("pause");
}

//###################################################################################

