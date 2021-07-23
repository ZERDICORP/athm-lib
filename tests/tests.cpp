#include <iostream>
#include "../src/athm.h"

using namespace zer::athm;

void test__sort()
{
	std::vector<int> vec({3, 4, 2, 1, 5});

	sort(vec.begin(), vec.end(), [](int& i1, int& i2){
		return i1 < i2;
	});

	assert(vec == std::vector<int>({1, 2, 3, 4, 5}));
}

void test__keys__values()
{
	std::map<int, int> m({
		{1, 10},
		{2, 20},
		{3, 30}
	});

	assert(keys(m) == std::vector<int>({1, 2, 3}));
	assert(values(m) == std::vector<int>({10, 20, 30}));
}

void test__listDir()
{
	assert(listDir("./") == std::vector<std::string>({".", "..", "tests.cpp", "tests.exe"}));
}

void test__split()
{
	assert(split("1, 2, 3", ", ") == std::vector<std::string>({"1", "2", "3"}));
}

void test__collapseReps()
{
	assert(collapseReps("++++-----") == "4+5-");
}

void test__expandReps()
{
	assert(expandReps("4+5-") == "++++-----");
}

void test__replace()
{
	assert(replace("12335", "33", "34") == "12345");
}

void test__index()
{
	assert(index("12345", "3") == 2);
}

void test__toRadians()
{
	assert(int(toRadians(90) * 10000.0 + 0.5) == 15708);
}

void test__getAngleBetweenPoints()
{
	assert(int(abs(toDegrees(getAngleBetweenPoints(0, 0, 10, 10))) + 0.5) == 45);
}

void test__getDistance2D()
{
	assert((int)getDistance2D(0, 0, 10, 10) == 14);
}

void test__sign()
{
	assert(sign(3) == 1);
	assert(sign(-3) == -1);
}

void test__vectorHas()
{
	std::vector<int> vec({1, 2, 3});

	assert(vectorHas(vec, 1) == true);
	assert(vectorHas(vec, 5) == false);
}

void test__isFolder()
{
	assert(isFolder("../tests") == true);
	assert(isFolder("./tests.cpp") == false);
}

void test__isNumber()
{
	assert(isNumber("3") == true);
	assert(isNumber("3a") == false);
	assert(isNumber("03") == false);
	assert(isNumber("3.14") == true);
	assert(isNumber(".14") == true);
	assert(isNumber("14.") == true);
}

void test__inRange2D()
{
	assert(inRange2D(10, 10, 5, 5) == true);
	assert(inRange2D(10, 10, -1, 5) == false);
}

int main(int argc, char const *argv[])
{
	test__sort();
	test__keys__values();
	test__listDir();
	test__split();
	test__collapseReps();
	test__expandReps();
	test__replace();
	test__index();
	test__toRadians();
	test__getAngleBetweenPoints();
	test__getDistance2D();
	test__vectorHas();
	test__isFolder();
	test__isNumber();
	test__inRange2D();

	system("pause > nul");
	return 0;
}