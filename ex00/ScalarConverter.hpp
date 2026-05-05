#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <cerrno>
# include <cstdlib>
# include <cctype>
# include <cmath>
# include <iomanip>
# include <iostream>
# include <limits>
# include <string>

class ScalarConverter
{
	public:
		static void	convert(const std::string& literal);

	private:
		ScalarConverter(void);
		ScalarConverter(const ScalarConverter& other);
		~ScalarConverter(void);
		ScalarConverter&	operator=(const ScalarConverter& other);
};

#endif
