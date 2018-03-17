#pragma once
#include <vector>
#include <string>

using std::vector;
using std::string;

class IBuilder;
class IFactory;
class CUserInterface;

enum CToping { Tomato = 0, Cucumber, Chicken, Cheese, Sausage, Pineapple };
enum CSause { Chile = 0, TomatoSause, Teriyaki };

class CPizza {
private:
	vector<CToping> toping_;
	vector<CSause> sause_;
	bool _is_prepared;
public:
	void AddSause(CSause);
	void AddToping(CToping);
	void Fry();
};

class CUserInterface {
public:
	bool AskIsStandart();
	bool AskMoreSause();
	bool AskMoreToping();
	CSause GetSause();
	CToping GetToping();
	string GetPizzaName();
};

//--------------------------------------------------------------

class IBuilder {
protected:
	CPizza pizza_;
public:
	virtual ~IBuilder();

	virtual void BuildToping() = 0;
	virtual void BuildSause() = 0;
	virtual void BuildFrying() = 0;
	CPizza GetPizza();
};

class CUserBuilder : public IBuilder {
public:
	CUserInterface * inter;

	void BuildToping();
	void BuildSause();
	void BuildFrying();
};

class CDirector {
public:
	CPizza CreatePizza(IBuilder* builder);
};

//--------------------------------------------------------------

class IFactory {
public:
	virtual void CreateSause(CPizza&) = 0;
	virtual void CreateToping(CPizza&) = 0;
	virtual ~IFactory();
};

class CFactoryMargarita : public IFactory {
	virtual void CreateSause(CPizza&);
	virtual void CreateToping(CPizza&);
};

class CFactoryPeperoni : public IFactory {
	virtual void CreateSause(CPizza&);
	virtual void CreateToping(CPizza&);
};

class CFactoryHawaiian : public IFactory {
	virtual void CreateSause(CPizza&);
	virtual void CreateToping(CPizza&);
};

class CFactory4Cheeses : public IFactory {
	virtual void CreateSause(CPizza&);
	virtual void CreateToping(CPizza&);
};