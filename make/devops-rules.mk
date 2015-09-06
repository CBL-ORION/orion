# DevOps, Quality Assurance rules

.gcov-note:
	@echo "If this does not give output, make sure you run the test suite first in order to intialise the counters"

# Build tests using code coverage using gcov
test.build-gcov:
	mkdir -p $(COVERAGEDIR)
	$(MAKE) test BUILD_GCOV=1
check-gcov-quick:
	$(MAKE) .gcov-note
	mkdir -p $(GCOVDIR)
	find $(BINDIR) $(BUILDDIR) .build -name "*.gcda" \
		| xargs $(GCOV) --no-output --preserve-paths \
		> $(GCOVDIR)/gcov-report
	@echo "See gcov report in $(GCOVDIR)/gcov-report"
check-gcov-full:
	$(MAKE) .gcov-note
	mkdir -p $(GCOVDIR)
	find $(BINDIR) $(BUILDDIR) .build -name "*.gcda"
check-lcov:
	$(MAKE) .gcov-note
	mkdir -p $(LCOVDIR)
	lcov --capture --directory . --output-file $(LCOVDIR)/lcov.info
	genhtml $(LCOVDIR)/lcov.info --output-directory $(LCOVDIR)
	@echo "See lcov report in $(LCOVDIR)/index.html"
