
/**
*  @DATE: 2021/11/30 10:00
*  @author: heyjude
*  @email: 1944303766@qq.com
*/
//
// Created by heyjude on 2021/11/30.
//

#ifndef CJSON_CJSON_H
#define CJSON_CJSON_H

// json类型
typedef enum {
    JSON_NULL,
    JSON_FALSE,
    JSON_TRUE,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} json_type;

typedef struct {
    json_type type;
    union {
        struct {
            char *s;
            size_t len;
        } s; // string
        double n;   // double
    } u;

} json_value;

enum {
    JSON_PARSE_OK = 0,
    JSON_PARSE_EXPECT_VALUE,
    JSON_PARSE_INVALID_VALUE,
    JSON_PARSE_ROOT_NOT_SINGULAR,
    JSON_PARSE_NUMBER_TOO_BIG,
    JSON_PARSE_MISS_QUOTATION_MARK,
    JSON_PARSE_INVALID_STRING_ESCAPE,
    JSON_PARSE_INVALID_STRING_CHAR
};

#define json_init(v) do{ (v)->type = JSON_NULL; }while(0)
#define json_set_null(v) json_free(v)

// 解析json字符串
int json_parse(json_value *v, const char *json);

// 访问json类型
json_type json_get_type(const json_value *v);

void json_free(json_value *v);

double json_get_number(const json_value *v);

int json_get_boolean(const json_value *v);

void json_set_boolean(json_value *v, int b);

double json_get_number(const json_value *v);

void json_set_number(json_value *v, double n);

const char *json_get_string(const json_value *v);

size_t json_get_string_length(const json_value *v);

void json_set_string(json_value *v, const char *s, size_t len);

#endif //CJSON_CJSON_H


