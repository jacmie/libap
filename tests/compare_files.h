#include <iostream>
#include <fstream>

int Files2str(const std::string &fileName, std::string &str1, std::string &str2)
{
	std::ifstream in1("./ref/ref_" + fileName);
	if(!in1) return 1;
	std::stringstream buf1;
	buf1 << in1.rdbuf();
	str1 = buf1.str();
	in1.close();

	std::ifstream in2("./out/out_" + fileName);
	if(!in2) return 2;
	std::stringstream buf2;
	buf2 << in2.rdbuf();
	str2 = buf2.str();
	in2.close();

	return 0;
}

