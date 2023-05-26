#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_12_10/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            Node* root = new Node;
            root->info = 1;

            Node* node2 = new Node;
            node2->info = 2;

            Node* node3 = new Node;
            node3->info = 3;

            Node* node4 = new Node;
            node4->info = 4;

            Node* node5 = new Node;
            node5->info = 5;

            root->left = node2;
            root->right = node3;
            node2->left = node4;
            node2->right = node5;

            // Call the function
            int result = CountLevels(root);
            Assert::AreEqual(result, 3);

		}
	};
}
