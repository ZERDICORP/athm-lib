#include <iostream>
#include <cxxtest/TestSuite.h>
#include <athm.h>

using namespace zer::athm;

class TestSuite : public CxxTest::TestSuite
{
	public:
		void test__sort(void)
		{
			std::vector<int> vec({3, 4, 2, 1, 5});

			sort(vec.begin(), vec.end(), [](int& i1, int& i2){
				return i1 < i2;
			});

			TS_ASSERT(vec == std::vector<int>({1, 2, 3, 4, 5}));
		}

		void test__keys__values(void)
		{
			std::map<int, int> m({
				{1, 10},
				{2, 20},
				{3, 30}
			});

			TS_ASSERT(keys(m) == std::vector<int>({1, 2, 3}));
			TS_ASSERT(values(m) == std::vector<int>({10, 20, 30}));
		}

		void test__split(void)
		{
			TS_ASSERT(split("1, 2, 3", ", ") == std::vector<std::string>({"1", "2", "3"}));
		}

		void test__collapseReps(void)
		{
			TS_ASSERT(collapseReps("++++-----") == "4+5-");
		}

		void test__expandReps(void)
		{
			TS_ASSERT(expandReps("4+5-") == "++++-----");
		}

		void test__replace(void)
		{
			TS_ASSERT(replace("12335", "33", "34") == "12345");
		}

		void test__index(void)
		{
			TS_ASSERT(index("12345", "3") == 2);
		}

		void test__toRadians(void)
		{
			TS_ASSERT(int(toRadians(90) * 10000.0 + 0.5) == 15708);
		}

		void test__getAngleBetweenPoints(void)
		{
			TS_ASSERT(int(abs(toDegrees(getAngleBetweenPoints(0, 0, 10, 10))) + 0.5) == 45);
		}

		void test__getDistance2D(void)
		{
			TS_ASSERT((int)getDistance2D(0, 0, 10, 10) == 14);
		}

		void test__sign(void)
		{
			TS_ASSERT(sign(3) == 1);
			TS_ASSERT(sign(-3) == -1);
		}

		void test__vectorHas(void)
		{
			std::vector<int> vec({1, 2, 3});

			TS_ASSERT(vectorHas(vec, 1) == true);
			TS_ASSERT(vectorHas(vec, 5) == false);
		}

		void test__exists(void)
		{
			TS_ASSERT(exists("./cxxtest") == true);
			TS_ASSERT(exists("./tests.h") == true);
			TS_ASSERT(exists("./folder") == false);
			TS_ASSERT(exists("./tests.cpp") == false);
		}

		void test__isFolder(void)
		{
			TS_ASSERT(isFolder("../tests") == true);
			TS_ASSERT(isFolder("./folder") == false);
		}

		void test__isNumber(void)
		{
			TS_ASSERT(isNumber("3") == true);
			TS_ASSERT(isNumber("3a") == false);
			TS_ASSERT(isNumber("03") == false);
			TS_ASSERT(isNumber("3.14") == true);
			TS_ASSERT(isNumber(".14") == true);
			TS_ASSERT(isNumber("14.") == true);
		}

		void test__inRange2D(void)
		{
			TS_ASSERT(inRange2D(10, 10, 5, 5) == true);
			TS_ASSERT(inRange2D(10, 10, -1, 5) == false);
		}
};
