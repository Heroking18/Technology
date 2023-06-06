#include <string.h>

#include "linkedlist.h"
#include "unity.h"



#define MY_RUN_TEST(func) RUN_TEST(func, 0)


void setUp(void)
{
    // This is run before EACH test
}

void tearDown(void)
{
  // This is run after EACH test
}
//**********************test_add_first()**********************//
void test_add_first(void)
{
  int ret;
  ITEM *list = NULL;
  ret = add_first(&list, 1);
  TEST_ASSERT_EQUAL(0, ret);
  clean(&list);
}

void test_add_first_firstNode(void)
{
  ITEM *list = NULL;
  add_first(&list, 1);
  TEST_ASSERT_EQUAL(1, list->value);
  clean(&list);
}

void test_add_first_secondNode(void)
{
  ITEM *list = NULL;
  add_first(&list, 1);
  add_first(&list, 2);
  TEST_ASSERT_EQUAL(2, list->value);
  clean(&list);
}

//**********************test_add_last()**********************//
void test_add_last(void)
{
  ITEM *list = NULL;
  
  add_first(&list, 1);
  add_last(&list, 5);
  TEST_ASSERT_EQUAL(5, list->next->value);
  clean(&list);
}

void test_add_last_lastAfterLast(void)
{
  ITEM *list = NULL;
  
  add_last(&list, 5);
  add_last(&list, 6);
  TEST_ASSERT_EQUAL(6, list->next->value);
  clean(&list);
}

//**********************test_add_after()**********************//
void test_add_after(void)
{
  ITEM *list = NULL;
  add_first(&list, 2);
  add_first(&list, 3);
  add_after(list, list, 4);
  TEST_ASSERT_EQUAL(4, list->next->value);
  clean(&list);
}

void test_add_after_emptyList(void)
{
  ITEM *list = NULL;
  int ret = 0;
  ret = add_after(list, list, 4);
  TEST_ASSERT_EQUAL(-1, ret);
  clean(&list);
}

//**********************test_rem_first()**********************//
void test_rem_first(void)
{
  int ret;
  ITEM *list = NULL;
  
  add_first(&list, 2);
  ret = rem_first(&list);
  TEST_ASSERT_EQUAL(0, ret);
  clean(&list);
}

void test_rem_first_deletedFirstValue(void)
{
  ITEM *list = NULL;
  
  add_first(&list, 2);
  add_first(&list, 3);
  rem_first(&list);
  TEST_ASSERT_NOT_EQUAL(3, list->value);
  clean(&list);
}

//**********************test_rem_last()**********************//
void test_rem_last(void)
{
  ITEM *list = NULL;
  add_first(&list, 2);
  add_first(&list, 3);
  rem_last(&list);
  TEST_ASSERT_NOT_EQUAL(2, list->value);
  clean(&list);
}

void test_rem_last_emptyNode(void)
{
  int ret;
  ITEM *list = NULL;
  ret = rem_last(&list);
  TEST_ASSERT_EQUAL(-1, ret);
  clean(&list);
}

//**********************test_rem_after()**********************//
void test_rem_after(void)
{
  ITEM *list = NULL;
  add_first(&list, 2);
  add_first(&list, 3);
  rem_after(list, list->next);
  TEST_ASSERT_NOT_EQUAL(2, list->value);
  clean(&list);
}

void test_rem_after_emptyList(void)
{
  int ret = 0;
  ITEM *list = NULL;
  ret = rem_after(list, list);
  TEST_ASSERT_EQUAL(-1, ret);
  clean(&list);
}

int main (int argc, char * argv[])
{
    UnityBegin();

    /* Put your UTs here */
    MY_RUN_TEST(test_add_first);
    MY_RUN_TEST(test_add_first_firstNode);
    MY_RUN_TEST(test_add_first_secondNode);
    
	MY_RUN_TEST(test_add_last);
	MY_RUN_TEST(test_add_last_lastAfterLast);
	
	MY_RUN_TEST(test_add_after);
	MY_RUN_TEST(test_add_after_emptyList);

	MY_RUN_TEST(test_rem_first);	
	MY_RUN_TEST(test_rem_first_deletedFirstValue);
	
	MY_RUN_TEST(test_rem_last);	
	MY_RUN_TEST(test_rem_last_emptyNode);
	
	MY_RUN_TEST(test_rem_after);
	MY_RUN_TEST(test_rem_after_emptyList);

    return UnityEnd();
}
