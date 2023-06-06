#include "queue.h"
#include "stack.h"
#include "gtest/gtest.h"

class queueTest : public ::testing::Test
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

TEST_F(queueTest, test_Queue_class_object_created)
{
  Queue *queue = new Queue(sizeof(int));
  size_t obj_param_size = sizeof(int);
  int count_stack_in = 0;
  int count_stack_out = 0;

  count_stack_in = queue->getStack_in()->getNumelem();
  count_stack_out = queue->getStack_out()->getNumelem();

  EXPECT_EQ(nullptr, queue->getStack_in()->getStack());  // test if stack_in is created
  EXPECT_EQ(nullptr, queue->getStack_out()->getStack()); // test if stack_out is created
  EXPECT_EQ(obj_param_size, queue->getItem_size());      // test if item_size has the correct size
  EXPECT_EQ(0, count_stack_in);                          // test if numelem for stack_in starts from 0
  EXPECT_EQ(0, count_stack_out);                         // test if numelem for stack_out starts from 0
  delete queue;
}

TEST_F(queueTest, test_enqueue)
{
  int obj = 1;
  int res = 0;
  int count_stack_in = 0;
  Queue *queue = new Queue(sizeof(int));

  res = queue->myqueue_enqueue(&obj);
  count_stack_in = queue->getStack_in()->getNumelem();

  EXPECT_EQ(1, *(int *)queue->getStack_in()->getStack()->obj); // test if enqueue'd obj is equal to the first value inside the stack
  EXPECT_NE(-1, res);                                          // test if result did not enter error
  EXPECT_EQ(0, res);                                           // test if enqueue is successfull
  EXPECT_EQ(1, count_stack_in);                                // test if numelem for stack_in increment by 1
  delete queue;
}

TEST_F(queueTest, test_enqueue_dequeue_store_and_remove_3_nodes)
{
  int obj[3] = {1, 2, 3};
  int count_stack_in = 0;
  int count_stack_out = 0;
  int res = 0;
  int error_res = 0;
  int SIZE = 3;
  int stores_obj = 0;
  int stores_obj2 = 0;
  int stores_obj3 = 0;
  int stores_obj4 = 0;
  Queue *queue = new Queue(sizeof(int));

  for (int i = 0; i < SIZE; i++)
  {
    queue->myqueue_enqueue(&obj[i]);
  }
  count_stack_in = queue->getStack_in()->getNumelem();

  EXPECT_EQ(3, *(int *)queue->getStack_in()->getStack()->obj); // test if last enqueue'd (HEAD) obj is 3
  EXPECT_EQ(3, count_stack_in);                                // test if nofelem is equal to amount of enqueue'd objects

  res = queue->myqueue_dequeue(&stores_obj);
  queue->myqueue_dequeue(&stores_obj2);
  queue->myqueue_dequeue(&stores_obj3);
  error_res = queue->myqueue_dequeue(&stores_obj4);
  count_stack_out = queue->getStack_in()->getNumelem();

  EXPECT_NE(-1, count_stack_out); // test if stack_out nofelem does not return error
  EXPECT_EQ(0, res);              // test if object dequeue'd successfully
  EXPECT_EQ(1, stores_obj);       // test if first object is stored
  EXPECT_EQ(2, stores_obj2);      // test if second object is stored
  EXPECT_EQ(3, stores_obj3);      // test if third object is stored
  EXPECT_EQ(-1, error_res);       // test if dequeue in an empty stack would return error
  delete queue;
}
