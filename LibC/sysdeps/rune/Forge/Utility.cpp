
#include <Forge/Utility.h>

namespace Forge {
	size_t strlen(const char* str) {
		size_t count = 0;
		const char* tmp = str;
		while (*str) {
			++str;
			++count;
		}
		return count;
	}
}
