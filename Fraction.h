#pragma once
#include <iostream>
#include <string>
#include <algorithm>

class Fraction {
public:
	Fraction();
	Fraction(int num, int denom = 1);
	Fraction(const std::string& str);
	int numerator()const;
	int denominator()const;
	void setNumerator(double new_element);
	void setDenominator(double new_element);
	Fraction& operator += (const Fraction& other);
	Fraction& operator -= (const Fraction& other);
	Fraction& operator *= (const Fraction& other);
	Fraction& operator /= (const Fraction& other);
	operator double();
	operator bool()const;

	void to_decimal_string();
	std::string to_fraction_string();

	void print_decimal()const;

private:
	int numerator_;
	int denominator_;
	bool is_recurring = true;
	std::string str_fraction_to_decimal;
	std::string str_decimal_to_fraction;

	void normalized();
	static int gcd(int a, int b);
};

Fraction operator + (const Fraction& first, const Fraction& second);
Fraction operator - (const Fraction& first, const Fraction& second);
Fraction operator / (const Fraction& first, const Fraction& second);
std::ostream& operator << (std::ostream& out, const Fraction& other);
std::istream& operator >> (std::istream& in, Fraction& other);
