#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter(void)
{}

ScalarConverter::ScalarConverter(const ScalarConverter& other)
{
	*this = other;
}

ScalarConverter&	ScalarConverter::operator=(const ScalarConverter& other)
{
	if (this != &other)
	{
		;
	}
	return *this;
}

ScalarConverter::~ScalarConverter(void)
{}

bool	isInteger(double value)
{
	return (!std::isnan(value)
		&& value != std::numeric_limits<double>::infinity()
		&& value != -std::numeric_limits<double>::infinity()
		&& std::floor(value) == value);
}

bool	isValidLiteral(const std::string& literal)
{
	std::size_t	i;
	std::size_t	end;
	bool		hasDigit;
	bool		hasPoint;

	if (literal.empty())
		return false;
	i = 0;
	end = literal.length();
	hasDigit = false;
	hasPoint = false;
	if (literal[end - 1] == 'f')
	{
		if (end == 1)
			return false;
		end--;
	}
	if (literal[i] == '+' || literal[i] == '-')
		i++;
	if (i == end)
		return false;
	while (i < end)
	{
		if (literal[i] == '.')
		{
			if (hasPoint)
				return false;
			hasPoint = true;
		}
		else if (std::isdigit(static_cast<unsigned char>(literal[i])))
			hasDigit = true;
		else
			return false;
		i++;
	}
	if (literal[literal.length() - 1] == 'f' && !hasPoint)
		return false;
	return hasDigit;
}

void	printImpossible(void)
{
	std::cout << "char: impossible\n";
	std::cout << "int: impossible\n";
	std::cout << "float: impossible\n";
	std::cout << "double: impossible\n";
}

void	printFloat(double value)
{
	std::cout << "float: ";
	if (std::isnan(value))
		std::cout << "nanf\n";
	else if (value == std::numeric_limits<double>::infinity())
		std::cout << "+inff\n";
	else if (value == -std::numeric_limits<double>::infinity())
		std::cout << "-inff\n";
	else if (value > static_cast<double>(std::numeric_limits<float>::max())
		|| value < -static_cast<double>(std::numeric_limits<float>::max()))
		std::cout << "impossible\n";
	else
	{
		if (isInteger(value))
			std::cout << std::fixed << std::setprecision(1);
		else
			std::cout << std::setprecision(7);
		std::cout << static_cast<float>(value) << "f\n";
		std::cout.unsetf(std::ios::floatfield);
	}
}

void	printDouble(double value)
{
	std::cout << "double: ";
	if (std::isnan(value))
		std::cout << "nan\n";
	else if (value == std::numeric_limits<double>::infinity())
		std::cout << "+inf\n";
	else if (value == -std::numeric_limits<double>::infinity())
		std::cout << "-inf\n";
	else
	{
		if (isInteger(value))
			std::cout << std::fixed << std::setprecision(1);
		else
			std::cout << std::setprecision(15);
		std::cout << value << "\n";
		std::cout.unsetf(std::ios::floatfield);
	}
}

void	printValue(double value)
{
	std::cout << "char: ";
	if (std::isnan(value) || value < 0 || value > 127)
		std::cout << "impossible\n";
	else if (!std::isprint(static_cast<unsigned char>(static_cast<char>(value))))
		std::cout << "Non displayable\n";
	else
		std::cout << '\'' << static_cast<char>(value) << "'\n";

	std::cout << "int: ";
	if (std::isnan(value)
		|| value > static_cast<double>(std::numeric_limits<int>::max())
		|| value < static_cast<double>(std::numeric_limits<int>::min()))
		std::cout << "impossible\n";
	else
		std::cout << static_cast<int>(value) << "\n";

	printFloat(value);
	printDouble(value);
}

void	ScalarConverter::convert(const std::string& literal)
{
	double	value;
	char*	end;

	if (literal.length() == 1
		&& std::isprint(static_cast<unsigned char>(literal[0]))
		&& !std::isdigit(static_cast<unsigned char>(literal[0])))
		value = static_cast<double>(literal[0]);
	else if (literal == "nanf")
		value = std::numeric_limits<float>::quiet_NaN();
	else if (literal == "+inff")
		value = std::numeric_limits<float>::infinity();
	else if (literal == "-inff")
		value = -std::numeric_limits<float>::infinity();
	else if (literal == "nan")
		value = std::numeric_limits<double>::quiet_NaN();
	else if (literal == "+inf")
		value = std::numeric_limits<double>::infinity();
	else if (literal == "-inf")
		value = -std::numeric_limits<double>::infinity();
	else
	{
		errno = 0;
		value = std::strtod(literal.c_str(), &end);
		if (errno || !isValidLiteral(literal)
			|| (end[0] != '\0' && !(end[0] == 'f' && end[1] == '\0')))
		{
			printImpossible();
			return ;
		}
	}
	printValue(value);
}
