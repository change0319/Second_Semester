#pragma once
#include<string>
#include"str.h"
int main() {
	std::string s;
	My::String a("absdefg");
	My::String b("d");
	My::String d('a');
	b += a;
	a = b;
	d.append('2');
	d.resize(10, '3');
	int k = b.findStr("d", 0);
	return 0;
}