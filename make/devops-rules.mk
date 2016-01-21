# DevOps, Quality Assurance rules

.gcov-note:
	@echo "If this does not give output, make sure you run the test suite first in order to intialise the counters"

.valgrind-note:
	@echo "If this does not give output, make sure that AddressSantizer is not enabled: make BUILD_ENABLE_ASAN=0 all test"

# Build tests using code coverage using gcov
test.build-gcov:
	mkdir -p $(COVERAGEDIR)
	$(MAKE) test BUILD_GCOV=1
check-gcov-quick:
	$(MAKE) .gcov-note
	mkdir -p $(GCOVDIR)
	find $(BINDIR) $(BUILDDIR) -path $(BUILDDIR)/t -prune -o -name "*.gcda" -print \
		| xargs $(GCOV) --no-output --preserve-paths \
		> $(GCOVDIR)/gcov-report
	@echo "See gcov report in $(GCOVDIR)/gcov-report"
check-gcov-full:
	$(MAKE) .gcov-note
	mkdir -p $(GCOVDIR)
	find $(BINDIR) $(BUILDDIR) -path $(BUILDDIR)/t -prune -o -name "*.gcda" -print \
		| xargs $(GCOV) -r --preserve-paths
	mv *.gcov $(GCOVDIR)
check-lcov:
	$(MAKE) .gcov-note
	mkdir -p $(LCOVDIR)
	lcov --capture --directory . --output-file $(LCOVDIR)/lcov.info
	genhtml $(LCOVDIR)/lcov.info --output-directory $(LCOVDIR)
	@echo "See lcov report in $(LCOVDIR)/index.html"
check-valgrind:
	$(MAKE) .valgrind-note
	find $(BUILDTESTDIR) -type f -executable \
		| xargs -n1 valgrind --leak-check=full --show-leak-kinds=all
