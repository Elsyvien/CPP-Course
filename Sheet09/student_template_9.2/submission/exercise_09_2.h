/*
Philipp Schmid: 5703070
Max Staneker: 7018590
*/
#pragma once

#include <map>
#include <cstdlib>

void slow_producer();
void fast_producer();
void consumer(std::map<unsigned long, size_t> *diff_count);
