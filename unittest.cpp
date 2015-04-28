/// @file  unittest.cpp

#include "unittest.h"

void assertTrue(bool x, const std::string& s) {
	assertEquals(x, true, s);
}

void assertFalse(bool x, const std::string& s) {
	assertEquals(x, false, s);
}
