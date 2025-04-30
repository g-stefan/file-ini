// Created by Grigore Stefan <g_stefan@yahoo.com>
// Public domain (Unlicense) <http://unlicense.org>
// SPDX-FileCopyrightText: 2020-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: Unlicense

#include <XYO/FileINI.hpp>

using namespace XYO::FileINI;

void test() {
	Document ini;		
	if(!load("../../input/simple.ini",ini)){
		throw std::runtime_error("File load");
	};
	if(!save("simple.ini",ini)){
		throw std::runtime_error("File save");
	};
	printf("Done.\r\n");
};

int main(int cmdN, char *cmdS[]) {

	try {
		test();
		return 0;
	} catch (const std::exception &e) {
		printf("* Error: %s\n", e.what());
	} catch (...) {
		printf("* Error: Unknown\n");
	};

	return 1;
};
