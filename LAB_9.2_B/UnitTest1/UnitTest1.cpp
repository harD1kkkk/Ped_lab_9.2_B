#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include <cmath>
#include "../LAB_9.2_B/lab_9.2_B.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace LevelBTests
{
    TEST_CLASS(UnitTestB)
    {
    public:
        TEST_METHOD(TestAverageGradeB)
        {
            StudentB s;
            s.lastName = "Test";
            s.course = 2;
            s.specialty = ComputerScience;
            s.physics = 5.0;
            s.math = 4.0;
            s.third.programming = 3.0;
            double avg = averageGradeB(s);
            Assert::AreEqual(4.0, avg, 0.001);
        }

        TEST_METHOD(TestGetThirdGradeB)
        {
            StudentB s;
            s.specialty = ComputerScience;
            s.third.programming = 5.0;
            Assert::AreEqual(5.0, getThirdGradeB(s), 0.001);
            s.specialty = InformaticsB;
            s.third.numericalMethods = 4.5;
            Assert::AreEqual(4.5, getThirdGradeB(s), 0.001);
            s.specialty = MathematicsAndEconomicsB;
            s.third.pedagogy = 3.5;
            Assert::AreEqual(3.5, getThirdGradeB(s), 0.001);
        }
    };
}
