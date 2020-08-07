#include "Fraction.h"

void test() {
	Fraction fraction0;
	std::cout << "input: ";
	std::cin >> fraction0;// ex. 4/5
	std::cout << "output: " << fraction0 << std::endl;// 4 / 5

	Fraction fraction1(1, 5);
	Fraction fraction2(4, 8);
	Fraction fraction3 = fraction1 + fraction2;
	std::cout << fraction3 << "\n";// 7/10

	Fraction fraction4 = fraction1 - fraction2;
	std::cout << fraction4 << "\n";// -3/10

	Fraction fraction5(2, 3);
	fraction5 *= fraction2;
	std::cout << fraction5 << "\n";// 1/3

	Fraction fraction6 = fraction1 / fraction2;
	std::cout << fraction6 << "\n";// 2/5

	Fraction(1, 2).to_decimal_string();//0.5
	Fraction(1, 3).to_decimal_string();// 0.(3)
	Fraction(10, 4).to_decimal_string();// 2.5
	Fraction(50, 22).to_decimal_string();// 2.(27)
	Fraction(50, 0).to_decimal_string();// 50
	Fraction(8, 2).to_decimal_string();// 4
	Fraction frac(50, 22);
	frac.to_decimal_string();
	frac.print_decimal();// 2.(27)
	std::cout << "\n";

	Fraction fraction7("2.(6)");
	fraction7.to_fraction_string();// 8/3


	Fraction fraction8("0.(3)");
	fraction8.to_fraction_string();// 1/3
	std::cout << fraction8 << "\n";// 1/3

	Fraction fraction9("0.(201)");
	fraction9.to_fraction_string();// 67/333

	Fraction fraction10("2.(27)");
	fraction10.to_fraction_string();// 25/11
	std::cout << fraction10 << std::endl;

	Fraction frac1("5.5");
	std::string str = frac1.to_fraction_string();// 11/2
	std::cout << "str: " << str << std::endl;
}

int main()
{
	test();
}
