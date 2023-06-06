#include "stack.h"
#include "gtest/gtest.h"

class StackTest : public ::testing::Test
{
protected:
  virtual void SetUp()
  {
  }

  virtual void TearDown()
  {
    // Code here will be called immediately after each test

    // (right before the destructor).
  }
};

TEST_F(StackTest, test_Stack_class_object_created)
{
  Stacks *stack = new Stacks(sizeof(int));
  size_t obj_param_size = sizeof(int);
  int count_stack = 0;

  count_stack = stack->getNumelem();

  EXPECT_EQ(nullptr, stack->getStack());          // test if stack_out is created
  EXPECT_EQ(obj_param_size, stack->getObjsize()); // test if objsize has the correct size
  EXPECT_EQ(0, count_stack);                      // test if numelem for stack starts from 0

  delete stack;
}

TEST_F(StackTest, mystack_push_and_nofelem)
{
  Stacks *stack = new Stacks(sizeof(int));
  int data[2] = {1, 2};
  int data_to_push = 3;
  int res = 0;
  int num_res = 0;
  for (int i = 0; i < 2; i++)
  {
    stack->mystack_push(&data[i]);
  }

  res = stack->mystack_push(&data_to_push);
  num_res = stack->mystack_nofelem();

  EXPECT_EQ(0, res);                            // test if stack_push returned successfully
  EXPECT_EQ(3, *(int *)stack->getStack()->obj); // test if pushed obj is HEAD
  EXPECT_EQ(3, num_res);                        // test if nofelem is equal to the amount of objects inside stack

  delete stack;
}

TEST_F(StackTest, mystack_pop)
{
  Stacks *stack = new Stacks(sizeof(int));
  int data[2] = {1, 2};
  int res = 0;
  int num_res = 0;
  int error_res = 0;
  int popped_data = 0;

  for (int i = 0; i < 2; i++)
  {
    stack->mystack_push(&data[i]);
  }

  stack->mystack_pop(&popped_data);
  res = stack->mystack_pop(&popped_data);
  error_res = stack->mystack_pop(&popped_data);
  num_res = stack->mystack_nofelem();

  EXPECT_EQ(0, res);                     // test if stack_pop returned successfully
  EXPECT_EQ(1, popped_data);             // test if correst obj is popped
  EXPECT_EQ(-1, error_res);              // test if popping without an obj would return error
  EXPECT_EQ(nullptr, stack->getStack()); // test if stack is empty
  EXPECT_NE(-1, num_res);                // test if stack nofelem does not return error

  delete stack;
}