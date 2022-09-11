//
// Created by heyjude on 2022/8/1.
//

#include "cJson.h"
#include <gmock/gmock.h>

using namespace testing;

// test parse null
TEST(TestParse, TestNull) {
  json_value v;
  v.type = JSON_TRUE;
  ASSERT_THAT(json_parse(&v, "null"), Eq(JSON_PARSE_OK));
  ASSERT_THAT(json_get_type(&v), Eq(JSON_NULL));
}

// test parse true
TEST(TestParse, TestTrue) {
  json_value v;
  v.type = JSON_NULL;
  ASSERT_THAT(json_parse(&v, "true"), Eq(JSON_PARSE_OK));
  ASSERT_THAT(json_get_type(&v), Eq(JSON_TRUE));
}

// test parse false
TEST(TestParse, TestFalse) {
  json_value v;
  v.type = JSON_NULL;
  ASSERT_THAT(json_parse(&v, "false"), Eq(JSON_PARSE_OK));
  ASSERT_THAT(json_get_type(&v), Eq(JSON_FALSE));
}

void TEST_NUMBER(double expect, std::string actual) {
  json_value v;
  ASSERT_THAT(json_parse(&v, actual.c_str()), Eq(JSON_PARSE_OK));
  ASSERT_THAT(json_get_type(&v), Eq(JSON_NUMBER));
  ASSERT_THAT(json_get_number(&v), DoubleEq(expect));
}
// test parse integer
TEST(TestParse, TestInteger) {
  TEST_NUMBER(0.0, "0");
  TEST_NUMBER(0.0, "-0");
  TEST_NUMBER(1.0, "1");
}

TEST(TestParse, TestDecimal) {
  TEST_NUMBER(0.0, "-0.0");
  TEST_NUMBER(-1.0, "-1.0");
  TEST_NUMBER(1.5, "1.5");
  TEST_NUMBER(-1.5, "-1.5");
  TEST_NUMBER(3.1416, "3.1416");
}

TEST(TestParse, TestScientificNotion) {
  TEST_NUMBER(1E10, "1E10");
  TEST_NUMBER(1e10, "1e10");
  TEST_NUMBER(1E+10, "1E+10");
  TEST_NUMBER(1E-10, "1E-10");
  TEST_NUMBER(-1E10, "-1E10");
  TEST_NUMBER(-1e10, "-1e10");
  TEST_NUMBER(-1E+10, "-1E+10");
  TEST_NUMBER(-1E-10, "-1E-10");
  TEST_NUMBER(1.234E+10, "1.234E+10");
  TEST_NUMBER(1.234E-10, "1.234E-10");
  TEST_NUMBER(0.0, "1e-10000");
}

TEST(TestParse, TestExtremeVal) {
  TEST_NUMBER(1.0000000000000002,
              "1.0000000000000002"); /* the smallest number > 1 */
  TEST_NUMBER(4.9406564584124654e-324,
              "4.9406564584124654e-324"); /* minimum denormal */
  TEST_NUMBER(-4.9406564584124654e-324, "-4.9406564584124654e-324");
  TEST_NUMBER(2.2250738585072009e-308,
              "2.2250738585072009e-308"); /* Max subnormal double */
  TEST_NUMBER(-2.2250738585072009e-308, "-2.2250738585072009e-308");
  TEST_NUMBER(2.2250738585072014e-308,
              "2.2250738585072014e-308"); /* Min normal positive double */
  TEST_NUMBER(-2.2250738585072014e-308, "-2.2250738585072014e-308");
  TEST_NUMBER(1.7976931348623157e+308,
              "1.7976931348623157e+308"); /* Max double */
  TEST_NUMBER(-1.7976931348623157e+308, "-1.7976931348623157e+308");
}

TEST()
