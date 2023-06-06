#include <string.h>
#include <stdio.h>

#include "mystack.h"
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

//**********************test_mystack_create()**********************//
void test_mystack_create()
{
  StackMeta_t *list = NULL;
  list = mystack_create(sizeof(int));

  TEST_ASSERT_EQUAL(4U, list->objsize);    // test if objsize is int
  TEST_ASSERT_NOT_EQUAL(0, list->objsize); // test is objsize is not 0
  TEST_ASSERT_NULL(list->stack);           // test if stack is created
  TEST_ASSERT_NOT_NULL(list);              // test if list is not null
  TEST_ASSERT_EQUAL(0, list->numelem);     // test if numelem has starting value

  mystack_destroy(list);
}

//**********************test_mystack_push()**********************//
void test_mystack_push()
{
  StackMeta_t *list = NULL;
  int obj = 18;
  int res = 1;

  TEST_ASSERT_EQUAL(-1, mystack_push(list, &obj));  // test if not creating objsize returns error

  list = mystack_create(sizeof(int));
  res = mystack_push(list, &obj);

  TEST_ASSERT_EQUAL(0, res);                         // test if returned succesful
  TEST_ASSERT_EQUAL(18, (*(int *)list->stack->obj)); // test if first obj is pushed
  TEST_ASSERT_EQUAL(1, (list->numelem));             // test if numelem is incremented

  mystack_destroy(list);
}

//**********************test_mystack_pop()**********************//
void test_mystack_pop()
{
  StackMeta_t *list = NULL;
  list = mystack_create(sizeof(int));

  int obj[] = {18, 19, 20};
  int res = 1;

  TEST_ASSERT_EQUAL(-1, mystack_pop(list, &obj));   // test if popping an empty list returns an error

  for (int i = 0; i < 3; i++)
  {
    mystack_push(list, &obj[i]);
  }
  res = mystack_pop(list, &obj);

  TEST_ASSERT_EQUAL(0, res);                 // test if returned succesful
  TEST_ASSERT_NULL(list->stack->next->next); // test if obj 20 is popped
  TEST_ASSERT_EQUAL(2, (list->numelem));     // test if numelem is decremented

  mystack_destroy(list);
}

//**********************test_mystack_nofelem()**********************//
void test_mystack_nofelem()
{
  StackMeta_t *list = NULL;

  int obj[2] = {18, 19};
  int res = 0;
  int stored_var = 0;
  list = mystack_create(sizeof(int));

  TEST_ASSERT_EQUAL(0, list->numelem); // test if numelem is initialized as 0;

  mystack_push(list, &obj[0]);
  mystack_push(list, &obj[1]);
  res = mystack_nofelem(list);

  TEST_ASSERT_EQUAL(2, res);           // test if returned succesful
  TEST_ASSERT_EQUAL(2, list->numelem); // test if there is 2 elem inside

  mystack_pop(list, &stored_var);
  mystack_pop(list, &stored_var);
  TEST_ASSERT_EQUAL(0, list->numelem); // test if there is 0 elem inside

  mystack_destroy(list);
}

int main(int argc, char *argv[])
{
  UnityBegin();

  MY_RUN_TEST(test_mystack_create);

  MY_RUN_TEST(test_mystack_push);

  MY_RUN_TEST(test_mystack_pop);

  MY_RUN_TEST(test_mystack_nofelem);

  return UnityEnd();
}
