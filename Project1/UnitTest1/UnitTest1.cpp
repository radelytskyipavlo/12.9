#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestAddNode)
        {
            Node* root = nullptr;
            AddNode(root, 5);
            Assert::IsNotNull(root);
            Assert::AreEqual(root->info, 5);

            AddNode(root, 3);
            AddNode(root, 7);
            Assert::IsNotNull(root->left);
            Assert::IsNotNull(root->right);
            Assert::AreEqual(root->left->info, 3);
            Assert::AreEqual(root->right->info, 7);
        }
	};
}
