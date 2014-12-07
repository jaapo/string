#include <stddef.h>

class string {
	private:
		size_t length;
		char content[];

	public:
		string();
		size_t getLength();
};
