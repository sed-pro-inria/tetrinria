#include <stdio.h>
#include <string.h>

#include "CUnit/Basic.h"

#include "rgb_color.h"

static size_t random_row_index;
static size_t const ZERO = 0;

/* Suite initialization */
int init_suite()
{
   /*random_row_index = rand() % NUMBER_OF_ROWS;*/
   return 0;
}

/* Suite termination */
int clean_suite()
{
   return 0;
}

#define ADD_TEST_TO_SUITE(suite,test) \
if ( ( CU_add_test(suite, #test, test) == NULL ) ) { \
    CU_cleanup_registry(); \
    return CU_get_error(); \
}

#define ADD_SUITE_TO_REGISTRY(suite) \
suite = CU_add_suite(#suite, init_suite, clean_suite); \
if ( suite == NULL ) { \
  CU_cleanup_registry(); \
  return CU_get_error(); \
}


//////////////////////////////////////////////////////////////////////////////
// Colors suite tests
//////////////////////////////////////////////////////////////////////////////


void testSameColors()
{
  CU_ASSERT_TRUE( sameColors(WHITE,WHITE) );
  CU_ASSERT_FALSE( sameColors(WHITE,RED) );
}


/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
  CU_pSuite suiteColor = NULL;


   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* Create Color test suite */
   ADD_SUITE_TO_REGISTRY(suiteColor)
   ADD_TEST_TO_SUITE(suiteColor, testSameColors)

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   unsigned int number_of_tests_failed = CU_get_number_of_tests_failed();
   CU_cleanup_registry();

   return number_of_tests_failed;
}
