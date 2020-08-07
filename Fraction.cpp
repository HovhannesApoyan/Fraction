#include "Fraction.h"

Fraction::Fraction()
	:numerator_(0)
	, denominator_(1)
{
}

Fraction::Fraction(int num, int denom)
	: numerator_(num)
	, denominator_(denom)
{
	normalized();
}

Fraction::Fraction(const std::string& str)
	:str_decimal_to_fraction(str)
	, numerator_(0)
	, denominator_(1)
{
}

int Fraction::numerator() const
{
	return numerator_;
}

int Fraction::denominator() const
{
	return denominator_;
}

void Fraction::setNumerator(double new_element)
{
	numerator_ = new_element;
}

void Fraction::setDenominator(double new_element)
{
	denominator_ = new_element;
}

Fraction& Fraction::operator += (const Fraction& other)
{
	if (this->denominator_ == other.denominator_) {
		this->numerator_ += other.numerator_;
	}
	else {
		this->numerator_ *= other.denominator_;
		this->numerator_ += this->denominator_ * other.numerator_;
		this->denominator_ *= other.denominator_;
	}
	normalized();
	return *this;
}

Fraction& Fraction::operator -= (const Fraction& other)
{
	if (this->denominator_ == other.denominator_) {
		this->numerator_ -= other.numerator_;
	}
	else {
		this->numerator_ *= other.denominator_;
		this->numerator_ -= this->denominator_ * other.numerator_;
		this->denominator_ *= other.denominator_;
	}
	normalized();
	return *this;
}

Fraction& Fraction::operator *= (const Fraction& other)
{
	this->numerator_ *= other.numerator_;
	this->denominator_ *= other.denominator_;
	normalized();
	return *this;
}

Fraction& Fraction::operator /= (const Fraction& other)
{
	this->numerator_ *= other.denominator_;
	this->denominator_ *= other.numerator_;
	normalized();
	return *this;
}

Fraction::operator double()
{
	double x = (static_cast<double>(numerator_) / static_cast<double>(denominator_));
	return x;
}

Fraction::operator bool() const
{
	return (denominator_ == 0);
}

void Fraction::to_decimal_string()
{
	normalized();
	int current_balance = numerator_ % denominator_;
	int initial_balance = current_balance;
	double result = (int)numerator_ / denominator_;

	current_balance *= 10;
	result += (double)(0.1) * (int)(current_balance / denominator_);
	current_balance = current_balance % denominator_;
	if (current_balance == 0)
		is_recurring = false;
	int degree = 1;
	while (initial_balance != current_balance && current_balance != 0) {
		current_balance *= 10;
		result += (double)(0.1 / pow(10, degree)) * (int)(current_balance / denominator_);
		current_balance = current_balance % denominator_;
		degree++;
		if (current_balance == 0)
			is_recurring = false;
	}
	str_fraction_to_decimal = std::to_string(result);
	//erase last all zero
	for (int i = str_fraction_to_decimal.size() - 1; i >= 0; --i) {
		if (str_fraction_to_decimal[i] == '0')
			str_fraction_to_decimal.erase(i);
		else
			break;
	}
	auto it = std::find(str_fraction_to_decimal.begin(), str_fraction_to_decimal.end(), '.');
	if (is_recurring) {
		str_fraction_to_decimal.insert(it + 1, '(');
		str_fraction_to_decimal.insert(str_fraction_to_decimal.end(), ')');
	}
	else {
		// erase last point
		if ((it + 1) == str_fraction_to_decimal.end()) {
			str_fraction_to_decimal.erase(str_fraction_to_decimal.size() - 1);
		}
	}
}

std::string Fraction::to_fraction_string()
{
	auto it = std::find(str_decimal_to_fraction.begin(), str_decimal_to_fraction.end(), '(');
	if (it != str_decimal_to_fraction.end()) {
		str_decimal_to_fraction.erase(it);
		str_decimal_to_fraction.erase(str_decimal_to_fraction.end() - 1);
		double res = stod(str_decimal_to_fraction);// string to double
		int integral_part = res;

		auto it2 = std::find(str_decimal_to_fraction.begin(), str_decimal_to_fraction.end(), '.');
		std::string str_right = "";
		str_right.insert(str_right.begin(), it2 + 1, str_decimal_to_fraction.end());

		numerator_ = stod(str_right);
		denominator_ = pow(10, str_right.size()) - 1;

		if (integral_part != 0) {
			numerator_ = integral_part * denominator_ + numerator_;
		}
		normalized();
		//	std::cout << "numerator_: " << numerator_ << std::endl;
		//	std::cout << "denominator_: " << denominator_ << std::endl;
	}
	else {
		double number = stod(str_decimal_to_fraction);
		std::string::iterator it = std::find(str_decimal_to_fraction.begin(), str_decimal_to_fraction.end(), '.');
		int index;
		for (int i = 0; i < str_decimal_to_fraction.size(); ++i) {
			if (str_decimal_to_fraction[i] == '.')
				index = i;
		}
		int mycount = str_decimal_to_fraction.size() - index - 1;
		numerator_ = number * pow(10, mycount);
		denominator_ = pow(10, mycount);
		normalized();
	}
	std::string str = "";
	str = "";
	str = std::to_string(numerator_);
	str += '/';
	str += std::to_string(denominator_);
	return str;
}

void Fraction::print_decimal() const
{
	(is_recurring) ? std::cout << "This is recurring sequence: " << str_fraction_to_decimal :
		std::cout << "This isn't recurring sequence: " << str_fraction_to_decimal;
}

void Fraction::normalized()
{
	if (denominator_ == 0) {
		denominator_ = 1;
	}
	if (denominator_ < 0) {
		numerator_ *= -1;
		denominator_ *= -1;
	}
	int m = gcd(numerator_, denominator_);
	numerator_ /= m;
	denominator_ /= m;
}

int Fraction::gcd(int a, int b)
{
	if (b == 0)
		return abs(a);
	return gcd(b, a % b);
}

Fraction operator + (const Fraction& first, const Fraction& second)
{
	Fraction frac = first;
	frac += second;
	return frac;
}

Fraction operator - (const Fraction& first, const Fraction& second)
{
	Fraction frac = first;
	frac -= second;
	return frac;
}

Fraction operator / (const Fraction& first, const Fraction& second)
{
	Fraction c = first;
	c /= second;
	return c;
}

std::ostream& operator << (std::ostream& out, const Fraction& other)
{
	(other.denominator() == 1) ? out << other.numerator() :
		out << other.numerator() << "/" << other.denominator();
	return out;
}

std::istream& operator >> (std::istream& in, Fraction& other)
{
	double x;
	in >> x;
	other.setNumerator(x);
	char c = std::cin.get();
	in >> x;
	other.setDenominator(x);
	std::cin.putback(c);
	return in;
}