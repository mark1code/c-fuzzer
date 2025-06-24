#include <time.h>
#include "unity.h"
#include "linked_queue.h"
#include "mutation.h"

static Queue* q;
static char *base;

void setUp(void) {
    srand(time(NULL));
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
   TEST_ASSERT_NOT_EQUAL(0, strcmp(base, res));
   TEST_ASSERT_NOT_EQUAL(strlen(base), strlen(res));
   printf("After char_delete: %s\n", res);
   free(res);
}

void test_char_insert(void) {
    char *res = char_insert(strdup(base));
    TEST_ASSERT_NOT_NULL(res);
    TEST_ASSERT_NOT_EQUAL(0, strcmp(base, res));
    TEST_ASSERT_NOT_EQUAL(strlen(base), strlen(res));
    printf("After char_insert: %s\n", res);
    free(res);
}

void test_char_flip(void) {
    char *res = char_flip(strdup(base));
    TEST_ASSERT_NOT_NULL(res);
    TEST_ASSERT_NOT_EQUAL(0, strcmp(base, res));
    TEST_ASSERT_EQUAL(strlen(base), strlen(res));
    printf("After char_flip: %s\n", res);
    free(res);
}

void test_char_flip_changes_one(void) {
    char *res = char_flip(strdup(base));
    TEST_ASSERT_NOT_NULL(res);

    int diff = 0;
    for (int i = 0; base[i] && res[i]; i++) {
        if (base[i] != res[i]) diff++;
    }
    TEST_ASSERT_EQUAL(1, diff);
    free(res);
}

void test_mutate(void) {
    char *res = mutate(strdup(base));
    TEST_ASSERT_NOT_NULL(res);
    TEST_ASSERT_NOT_EQUAL(0, strcmp(base, res));
    free(res);
}

void test_mutate_empty(void) {
    const char *empty_str = "";
    char *res = mutate(strdup(empty_str));
    TEST_ASSERT_EQUAL(1, strlen(res));
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
    RUN_TEST(test_char_insert);
    RUN_TEST(test_char_flip);
    RUN_TEST(test_char_flip_changes_one);
    RUN_TEST(test_mutate);
    RUN_TEST(test_mutate_empty);

}

int main(void) {
    UNITY_BEGIN();
    run_tests();
    return UNITY_END();
}

