#include <iostream>
#include <stdlib.h>
#include "../src/athm.h"

using namespace zer::athm;

int test__sort()
{
	std::vector<int> vec({3, 4, 2, 1, 5});

	sort(vec.begin(), vec.end(), [](int& i1, int& i2){
		return i1 < i2;
	});

	if (!(vec == std::vector<int>({1, 2, 3, 4, 5})))
		return 1;
	return 0;
}

int test__keys__values()
{
	std::map<int, int> m({
		{1, 10},
		{2, 20},
		{3, 30}
	});

	
	if (!(keys(m) == std::vector<int>({1, 2, 3})))
		return 1;
	if (!(values(m) == std::vector<int>({10, 20, 30})))
		return 1;
	return 0;
}

int test__listDir()
{	
	if (!(listDir("./") == std::vector<std::string>({".", "..", "tests.cpp", "tests.exe"})))
		return 1;
	return 0;
}

int test__split()
{
	if (!(split("1, 2, 3", ", ") == std::vector<std::string>({"1", "2", "3"})))
		return 1;
	return 0;
}

int test__collapseReps()
{
	if (!(collapseReps("++++-----") == "4+5-"))
		return 1;
	return 0;
}

int test__expandReps()
{
	if (!(expandReps("4+5-") == "++++-----"))
		return 1;
	return 0;
}

int test__replace()
{
	
	if (!(replace("12335", "33", "34") == "12345"))
		return 1;
	return 0;
}

int test__index()
{
	if (!(index("12345", "3") == 2))
		return 1;
	return 0;
}

int test__toRadians()
{
	if (!(int(toRadians(90) * 10000.0 + 0.5) == 15708))
		return 1;
	return 0;
}

int test__getAngleBetweenPoints()
{
	if (!(int(abs(toDegrees(getAngleBetweenPoints(0, 0, 10, 10))) + 0.5) == 45))
		return 1;
	return 0;
}

int test__getDistance2D()
{
	if (!((int)getDistance2D(0, 0, 10, 10) == 14))
		return 1;
	return 0;
}

int test__sign()
{
	if (!(sign(3) == 1))
		return 1;
	if (!(sign(-3) == -1))
		return 1;
	return 0;
}

int test__vectorHas()
{
	std::vector<int> vec({1, 2, 3});
	
	if (!(vectorHas(vec, 1) == true))
		return 1;
	if (!(vectorHas(vec, 5) == false))
		return 1;
	return 0;
}

int test__isFolder()
{
	if (!(isFolder("../tests") == true))
		return 1;
	if (!(isFolder("./tests.cpp") == false))
		return 1;
	return 0;
}

int test__isNumber()
{
	if (!(isNumber("3") == true))
		return 1;	
	if (!(isNumber("3a") == false))
		return 1;
	if (!(isNumber("03") == false))
		return 1;
	if (!(isNumber("3.14") == true))
		return 1;
	if (!(isNumber(".14") == true))
		return 1;
	if (!(isNumber("14.") == true))
		return 1;
	return 0;
}

int test__inRange2D()
{	
	if (!(inRange2D(10, 10, 5, 5) == true))
		return 1;
	if (!(inRange2D(10, 10, -1, 5) == false))
		return 1;
	return 0;
}

int main(int argc, char const *argv[])
{
	int iCode = 0;

	iCode += test__sort();
	iCode += test__keys__values();
	iCode += test__listDir();
	iCode += test__split();
	iCode += test__collapseReps();
	iCode += test__expandReps();
	iCode += test__replace();
	iCode += test__index();
	iCode += test__toRadians();
	iCode += test__getAngleBetweenPoints();
	iCode += test__getDistance2D();
	iCode += test__vectorHas();
	iCode += test__isFolder();
	iCode += test__isNumber();
	iCode += test__inRange2D();
	
	if (iCode != 0)
		exit(EXIT_FAILURE);

	return 0;
}