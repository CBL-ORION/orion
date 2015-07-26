#include <stddef.h>
#include <tap/basic.h>

#include "ndarray/ndarray3.h"

int main(void) {
	plan(1);
	ndarray3* nd_test = ndarray3_new(3, 3, 3);
	ok(1, "the first test");

	return 0;
}
