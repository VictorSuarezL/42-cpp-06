#include "identify.hpp"

int	main(void)
{
	Base*	ptr;

	std::srand(std::time(NULL));
	for (int i = 0; i < 10; i++)
	{
		ptr = generate();
		std::cout << "Pointer identify:   ";
		identify(ptr);
		std::cout << "Reference identify: ";
		identify(*ptr);
		delete ptr;
		std::cout << std::endl;
	}
	return 0;
}
