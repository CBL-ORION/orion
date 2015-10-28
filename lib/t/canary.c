#include <stdlib.h>
#include <tap/basic.h>
#include <tap/float.h>

/*
Canary test
*/
int main(void) {
	plan(2);

	ok(1, "the first test");
	is_int(42, 42, NULL);
	diag("a diagnostic, ignored by the harness");
	/*skip("a skipped test");*/

	return EXIT_SUCCESS;
}
