#include <string.h>
#include <stdio.h>
#include "mystack.h"
#include "myqueue.h"
#include "unity.h"
#include "testrunner.h"

// I rather dislike keeping line numbers updated, so I made my own macro to ditch the line number
#define MY_RUN_TEST(func) RUN_TEST(func, 0)

void setUp(void)
{
}

void tearDown(void)
{
	// This is run after EACH test
}

void test_queue_create_delete(void)
{
	QueueMeta_t *QUEUE = NULL;
	int obj = 1;
	int res = 0;

	QUEUE = myqueue_create(sizeof(int));

	TEST_ASSERT_NOT_NULL(QUEUE);					  // test if function returned NULL
	TEST_ASSERT_EQUAL(sizeof(int), QUEUE->item_size); // test if item size is int
	TEST_ASSERT_NULL(QUEUE->stack_in->stack);		  // test if stack_in is created
	TEST_ASSERT_NULL(QUEUE->stack_out->stack);		  // test if stack_out is created

	res = myqueue_enqueue(QUEUE, &obj);

	TEST_ASSERT_NOT_EQUAL(-1, res); // test if returned value is an error value

	myqueue_delete(QUEUE);
}

void test_enqueue_dequeue(void)
{
	QueueMeta_t *QUEUE = NULL;
	int obj = 1;
	int obj2 = 2;
	int obj3 = 3;
	int stored_var = 0;
	int stored_var2 = 0;
	int stored_var3 = 0;
	int stored_var4 = 0;
	int res = 0;

	TEST_ASSERT_EQUAL(-1, myqueue_enqueue(QUEUE, &obj));	// test if enqueueing obj while objsize is not created would return error

	QUEUE = myqueue_create(sizeof(int));


	res = myqueue_enqueue(QUEUE, &obj);

	myqueue_dequeue(QUEUE, &stored_var);

	myqueue_enqueue(QUEUE, &obj2);
	myqueue_dequeue(QUEUE, &stored_var2);

	myqueue_enqueue(QUEUE, &obj3);
	myqueue_dequeue(QUEUE, &stored_var3);
	

	TEST_ASSERT_EQUAL(0, res);			   // test if function return succesfully
	TEST_ASSERT_NOT_EQUAL(0, stored_var);  // test if stored_var has taken a value
	TEST_ASSERT_EQUAL(1, stored_var);	   // checks if enqueue popped out the first stack obj in stack_out which is 1
	TEST_ASSERT_NOT_EQUAL(0, stored_var2); // test if stored_var2 has taken a value
	TEST_ASSERT_EQUAL(2, stored_var2);	   // checks if enqueue popped out the first stack obj in stack_out which is 2
	TEST_ASSERT_NOT_EQUAL(0, stored_var3); // test if stored_var3 has taken a value
	TEST_ASSERT_EQUAL(3, stored_var3);	   // checks if enqueue popped out the first stack obj in stack_out which is 3
	TEST_ASSERT_EQUAL(-1, myqueue_dequeue(QUEUE, &stored_var4));	   //  test if dequeueing from empty stack_out would return error

	myqueue_delete(QUEUE);
}

void test_enqueue_dequeue_store_and_remove_3_nodes(void) // Test if myqueue_dequeue can pop multiple values in FIFO order
{
	QueueMeta_t *QUEUE = NULL;
	int obj[3] = {1, 2, 3};
	int actual_value[3] = {};
	int expected_value[3] = {1, 2, 3};
	QUEUE = myqueue_create(sizeof(int));

	for (int i = 0; i < 3; i++)
	{
		myqueue_enqueue(QUEUE, &obj[i]);
	}

	for (int i = 0; i < 3; i++)
	{
		myqueue_dequeue(QUEUE, &actual_value[i]);
	}

	TEST_ASSERT_EQUAL_INT_ARRAY(expected_value, actual_value, 3);

	myqueue_delete(QUEUE);
}

int main()
{
	UnityBegin();
	MY_RUN_TEST(test_queue_create_delete);
	MY_RUN_TEST(test_enqueue_dequeue);
	MY_RUN_TEST(test_enqueue_dequeue_store_and_remove_3_nodes);
	return UnityEnd();
}
