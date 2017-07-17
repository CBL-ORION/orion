#!/usr/bin/env perl

use strict;
use warnings;

use Text::ParseWords;

my @words = shellwords(<>);
my @ldlibs = grep { /(^-l)|\.a$|\.so/ } @words;
print "@ldlibs";
