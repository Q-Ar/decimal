#include <check.h>
#include <limits.h>

#include "../s21_decimal.h"

static int src[] = {
    0,      -1,        1,        -2,          2,           -3,     3,
    -10,    10,        -128,     127,         255,         -32768, 32767,
    -32767, 137,       342,      -32860,      33223,       56210,  -65535,
    65535,  212818281, -2818281, -2147483647, 100,         1782,   -821821,
    218128, 9999,      -9999999, 2147483647,  -2147483648,
};

static s21_decimal dst[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  // -1
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x00000002, 0x00000000, 0x00000000, 0x80000000}},  // -2
    {{0x00000002, 0x00000000, 0x00000000, 0x00000000}},  // 2
    {{0x00000003, 0x00000000, 0x00000000, 0x80000000}},  // -3
    {{0x00000003, 0x00000000, 0x00000000, 0x00000000}},  // 3
    {{0x0000000A, 0x00000000, 0x00000000, 0x80000000}},  // -10
    {{0x0000000A, 0x00000000, 0x00000000, 0x00000000}},  // 10
    {{0x00000080, 0x00000000, 0x00000000, 0x80000000}},  // -128
    {{0x0000007F, 0x00000000, 0x00000000, 0x00000000}},  // 127
    {{0x000000FF, 0x00000000, 0x00000000, 0x00000000}},  // 255
    {{0x00008000, 0x00000000, 0x00000000, 0x80000000}},  // -32768
    {{0x00007FFF, 0x00000000, 0x00000000, 0x00000000}},  // 32767
    {{0x00007FFF, 0x00000000, 0x00000000, 0x80000000}},  // -32767
    {{0x00000089, 0x00000000, 0x00000000, 0x00000000}},  // 137
    {{0x00000156, 0x00000000, 0x00000000, 0x00000000}},  // 342
    {{0x0000805C, 0x00000000, 0x00000000, 0x80000000}},  // -32860
    {{0x000081C7, 0x00000000, 0x00000000, 0x00000000}},  // 33223
    {{0x0000DB92, 0x00000000, 0x00000000, 0x00000000}},  // 56210
    {{0x0000FFFF, 0x00000000, 0x00000000, 0x80000000}},  // -65535
    {{0x0000FFFF, 0x00000000, 0x00000000, 0x00000000}},  // 65535
    {{0x0CAF5969, 0x00000000, 0x00000000, 0x00000000}},  // 212818281
    {{0x002B00E9, 0x00000000, 0x00000000, 0x80000000}},  // -2818281
    {{0x7FFFFFFF, 0x00000000, 0x00000000, 0x80000000}},  // -2147483647
    {{0x00000064, 0x00000000, 0x00000000, 0x00000000}},  // 100
    {{0x000006F6, 0x00000000, 0x00000000, 0x00000000}},  // 1782
    {{0x000C8A3D, 0x00000000, 0x00000000, 0x80000000}},  // -821821
    {{0x00035410, 0x00000000, 0x00000000, 0x00000000}},  // 218128
    {{0x0000270F, 0x00000000, 0x00000000, 0x00000000}},  // 9999
    {{0x0098967F, 0x00000000, 0x00000000, 0x80000000}},  // -9999999
    {{0x7FFFFFFF, 0x00000000, 0x00000000, 0x00000000}},  // 2147483647
    {{0x80000000, 0x00000000, 0x00000000, 0x80000000}},  // -2147483648
};

START_TEST(ints) {
  for (size_t i = 0; i < sizeof(src) / sizeof(int); ++i) {
    s21_decimal tmp;
    int ret = s21_from_int_to_decimal(src[i], &tmp);
    ck_assert_int_eq(tmp.bits[0], dst[i].bits[0]);
    ck_assert_int_eq(tmp.bits[1], dst[i].bits[1]);
    ck_assert_int_eq(tmp.bits[2], dst[i].bits[2]);
    ck_assert_int_eq(tmp.bits[3], dst[i].bits[3]);
    ck_assert_int_eq(ret, 0);
  }
}
END_TEST

Suite *suite_from_int_to_decimal(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_from_int_to_decimal");
  tc = tcase_create("s21_from_int_to_decimal");

  if (s != NULL && tc != NULL) {
    tcase_add_test(tc, ints);
    suite_add_tcase(s, tc);
  }

  return (s);
}
