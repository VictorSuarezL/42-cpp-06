#include "Serializer.hpp"

int	main(void)
{
	Data		data;
	uintptr_t	raw;
	Data*		restored;

	data.id = 42;
	data.name = "cpp06";
	data.value = 21.42;

	raw = Serializer::serialize(&data);
	restored = Serializer::deserialize(raw);

	std::cout << "Original pointer:     " << &data << std::endl;
	std::cout << "Serialized value:     " << raw << std::endl;
	std::cout << "Deserialized pointer: " << restored << std::endl;
	std::cout << "Same address:         ";
	if (restored == &data)
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;
	std::cout << "Data:                 " << restored->id << ", "
		<< restored->name << ", " << restored->value << std::endl;
	return 0;
}
