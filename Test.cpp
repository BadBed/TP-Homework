#include "Main.h"
#include "gtest/gtest.h"
#include <fstream>

TEST(test, factory) {
	IFactory* fac = new CFactoryMargarita;
	CMaker maker;
	CPizza pizza = maker.MakePizza(fac);

	EXPECT_TRUE(pizza.IsPrepared());
	EXPECT_EQ(pizza.GetSause()[0], TomatoSause);
	EXPECT_EQ(pizza.GetToping()[1], Tomato);

	delete fac;
}

TEST(test, builder) {
	std::ofstream fout;
	fout.open("fortest");
	fout << "y 2 y 3 n y 2 n";
	fout.close();
	freopen("fortest", "r", stdin);

	CUserInterface inter;
	CUserBuilder* builder = new CUserBuilder;
	builder->inter = &inter;
	CDirector dir;
	CPizza pizza = dir.CreatePizza(builder);

	EXPECT_TRUE(pizza.IsPrepared());
	EXPECT_EQ(pizza.GetSause()[0], TomatoSause);
	EXPECT_EQ(pizza.GetToping()[1], Chicken);

	delete builder;
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
