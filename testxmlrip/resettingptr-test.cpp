
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop

#include "resettingptr.h"

using namespace std;

class ResetTester
{
public:
	ResetTester() : m_resetCount{0}, m_funcCalls{0} {}
	virtual void Reset() { ++m_resetCount; }
	int m_resetCount;
	void Func() { ++m_funcCalls; }
	int m_funcCalls;
};

/******************************************************************************************/
/* operator=(T*)                                                                 */
/******************************************************************************************/

TEST(ResettingPtr, AssignCallsReset) {
	// Arrange
	ResetTester tester;
	ResettingPtr<ResetTester> ptr;
	
	// Act
	ptr = &tester;
	
	// Assert
	EXPECT_EQ(1, tester.m_resetCount);
	
}

TEST(ResettingPtr, AssignDoesNotCallResetOnNullPtr) {
	// Arrange
	ResetTester tester;
	ResettingPtr<ResetTester> ptr;
	ptr = &tester;
	
	// Act
	ptr = nullptr;
	
	// Assert
	EXPECT_EQ(1, tester.m_resetCount);
	
}

TEST(ResettingPtr, PtrCallCallsFuncOnContainedObject) {
	// Arrange
	ResetTester tester;
	ResettingPtr<ResetTester> ptr;
	ptr = &tester;
	
	// Act
	ptr->Func();
	
	// Assert
	EXPECT_EQ(1, tester.m_funcCalls);
	
}
