
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

typedef struct json_value json_value;
typedef struct json_member json_member;

struct json_value {
    json_type type;
    union {
        struct {
            char *s;
            size_t len;
        } s; // string
        struct {
            json_value *e;
            size_t size;
        } a; // array
        struct {
            json_member *m;
            size_t size;
        } o; // object
        double n;   // double
    } u;
};

struct json_member {
    char *k;
    size_t klen;
    json_value v;
};

enum {
    JSON_PARSE_OK = 0,
    JSON_PARSE_EXPECT_VALUE,
    JSON_PARSE_INVALID_VALUE,
    JSON_PARSE_ROOT_NOT_SINGULAR,
    JSON_PARSE_NUMBER_TOO_BIG,
    JSON_PARSE_MISS_QUOTATION_MARK,
    JSON_PARSE_INVALID_STRING_ESCAPE,
    JSON_PARSE_INVALID_STRING_CHAR,
    JSON_PARSE_INVALID_UNICODE_HEX,
    JSON_PARSE_INVALID_UNICODE_SURROGATE,
    JSON_PARSE_MISS_COMMA_OR_SQUARE_BARCKET,
    JSON_PARSE_MISS_KEY,
    JSON_PARSE_MISS_COLON,
    JSON_PARSE_MISS_COMMA_OR_CURLY_BARCKET,

    JSON_STRINGIFY_OK
};

#define json_init(v) do{ (v)->type = JSON_NULL; }while(0)
#define json_set_null(v) json_free(v)

// 解析json字符串
int json_parse(json_value *v, const char *json);

int json_stringify(const json_value *v, char **json, size_t *length);

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

size_t json_get_array_size(const json_value *v);

json_value *json_get_array_element(const json_value *v, size_t index);

size_t json_get_object_size(const json_value *v);

const char *json_get_object_key(const json_value *v, size_t index);

size_t json_get_object_key_length(const json_value *v, size_t index);

json_value *json_get_object_value(const json_value *v, size_t index);

#endif //CJSON_CJSON_H


