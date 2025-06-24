
#include "unity.h"
#include "linked_queue.h"
#include "mutation.h"

static Queue* q;
static char *base;

void setUp(void) {
    srand(123);
    q = queue_create();         
    base = strdup("Linoone");  
}

void tearDown(void) {
    queue_destroy(q);
    q = NULL;
    free(base);     
    base = NULL;
}

// LINKED QUEUE TESTS

void test_queue_create(void) {
    TEST_ASSERT_NOT_NULL(q);
}

void test_queue_enqueue(void) {
    int res = enqueue(q, "test");
    TEST_ASSERT_EQUAL_INT(0, res);
}

void test_queue_dequeue(void) {
    enqueue(q, "test");
    char *res = dequeue(q);
    TEST_ASSERT_EQUAL_STRING("test", res);
    free(res);  
}

void test_queue_dequeue_empty(void) {
    char *res = dequeue(q);
    TEST_ASSERT_NULL(res);
}

void test_queue_dequeue_thrice(void) {
    enqueue(q, "test 1");
    enqueue(q, "test 2");
    enqueue(q, "test 3");
    char *res1 = dequeue(q);
    char *res2 = dequeue(q);
    char *res3 = dequeue(q);
    TEST_ASSERT_EQUAL_STRING("test 1", res1);
    TEST_ASSERT_EQUAL_STRING("test 2", res2);
    TEST_ASSERT_EQUAL_STRING("test 3", res3);
    free(res1);
    free(res2);
    free(res3);
}

void test_queue_unique_single(void) {
    enqueue(q, "test 1");
    char *res1 = dequeue(q);
    enqueue(q, "test 2");
    char *res2 = dequeue(q);
    TEST_ASSERT_EQUAL_STRING("test 1", res1);
    TEST_ASSERT_EQUAL_STRING("test 2", res2);
    free(res1);
    free(res2);
}

// MUTATION TESTS

void test_char_delete(void) {
   char *res = char_delete(strdup(base));
   TEST_ASSERT_NOT_NULL(res);           
   printf("After char_delete: %s\n", res);
   free(res);
}

void run_tests(void) {
    // LINKED QUEUE
    RUN_TEST(test_queue_create);
    RUN_TEST(test_queue_enqueue);
    RUN_TEST(test_queue_dequeue);
    RUN_TEST(test_queue_dequeue_empty);
    RUN_TEST(test_queue_dequeue_thrice);
    RUN_TEST(test_queue_unique_single);

    // MUTATION
    RUN_TEST(test_char_delete);
}

int main(void) {
    UNITY_BEGIN();
    run_tests();
    return UNITY_END();
}

