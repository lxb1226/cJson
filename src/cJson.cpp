/**
 *  @DATE: 2021/11/30 10:00
 *  @author: heyjude
 *  @email: 1944303766@qq.com
 */
//
// Created by heyjude on 2021/11/30.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h> // NULL
#include <errno.h>  // errno
#include <math.h>   // HUGE_VAL
#include <string.h>

#include "cJson.h"

#define EXPECT(c, ch)             \
    do                            \
    {                             \
        assert(*c->json == (ch)); \
        c->json++;                \
    } while (0)
#define ISDIGIT(ch) ((ch >= '0' && (ch) <= '9'))
#define ISDIGIT1TO9(ch) ((ch >= '1' && (ch) <= '9'))
#define STRING_ERROR(ret) \
    do                    \
    {                     \
        c->top = head;    \
        return ret;       \
    } while (0)

#define PUTC(c, ch)                                         \
    do                                                      \
    {                                                       \
        *(char *)json_context_push(c, sizeof(char)) = (ch); \
    } while (0)

#ifndef JSON_PARSE_STACK_INIT_SIZE
#define JSON_PARSE_STACK_INIT_SIZE 256
#endif

typedef struct
{
    const char *json;
    char *stack;      // 指示栈底
    size_t size, top; // top指示栈顶
} json_context;

static void *json_context_push(json_context *c, size_t size)
{
    void *ret;
    assert(size > 0);
    if (c->top + size >= c->size)
    {
        if (c->size == 0)
            c->size = JSON_PARSE_STACK_INIT_SIZE;
        while (c->top + size >= c->size)
            c->size += c->size >> 1; // 扩大1.5倍
        c->stack = (char *)realloc(c->stack, c->size);
    }

    ret = c->stack + c->top;
    c->top += size;
    return ret;
}

static void *json_context_pop(json_context *c, size_t size)
{
    assert(c->top >= size);
    return c->stack + (c->top -= size);
}

// 解析空格
static void json_parse_whitespace(json_context *c)
{
    const char *p = c->json;
    while (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t')
        p++;
    c->json = p;
}

// 解析值
static int json_parse_value(json_context *c, json_value *v);

// 释放内存
void json_free(json_value *v)
{
    assert(v != NULL);
    size_t i;
    switch (v->type)
    {
    case JSON_ARRAY:
        for (i = 0; i < v->u.a.size; i++)
            json_free(&v->u.a.e[i]);
        free(v->u.a.e);
        break;
    case JSON_STRING:
        free(v->u.s.s);
        break;
    case JSON_OBJECT:
        for (i = 0; i < v->u.o.size; i++)
        {
            json_member m = v->u.o.m[i];
            free(m.k);
            json_free(&m.v);
        }
        free(v->u.o.m);
        break;
    default:
        break;
    }
    v->type = JSON_NULL;
}

void json_set_string(json_value *v, const char *s, size_t len)
{
    assert(v != NULL && (s != NULL || len == 0));
    json_free(v);
    v->u.s.s = (char *)malloc(len + 1);
    memcpy(v->u.s.s, s, len);
    v->u.s.s[len] = '\0';
    v->u.s.len = len;
    v->type = JSON_STRING;
}

const char *json_parse_hex4(const char *p, unsigned *u)
{
    size_t i;
    *u = 0;
    for (i = 0; i < 4; i++)
    {
        char ch = *p++;
        *u <<= 4;
        if (ch >= '0' && ch <= '9')
            *u |= ch - '0';
        else if (ch >= 'a' && ch <= 'f')
            *u |= ch - ('a' - 10);
        else if (ch >= 'A' && ch <= 'F')
            *u |= ch - ('A' - 10);
        else
            return NULL;
    }
    return p;
}

void json_encode_utf8(json_context *c, unsigned u)
{
        if (u <= 0x7F) 
        PUTC(c, u & 0xFF);
    else if (u <= 0x7FF) {
        PUTC(c, 0xC0 | ((u >> 6) & 0xFF));
        PUTC(c, 0x80 | ( u       & 0x3F));
    }
    else if (u <= 0xFFFF) {
        PUTC(c, 0xE0 | ((u >> 12) & 0xFF));
        PUTC(c, 0x80 | ((u >>  6) & 0x3F));
        PUTC(c, 0x80 | ( u        & 0x3F));
    }
    else {
        assert(u <= 0x10FFFF);
        PUTC(c, 0xF0 | ((u >> 18) & 0xFF));
        PUTC(c, 0x80 | ((u >> 12) & 0x3F));
        PUTC(c, 0x80 | ((u >>  6) & 0x3F));
        PUTC(c, 0x80 | ( u        & 0x3F));
    }
}

// 解析字面量 null true false
static int json_parse_literal(json_context *c, json_value *v, const char *literal, json_type type)
{
    size_t i;
    EXPECT(c, literal[0]);
    for (i = 0; literal[i + 1]; i++)
    {
        if (c->json[i] != literal[i + 1])
        {
            return JSON_PARSE_INVALID_VALUE;
        }
    }
    c->json += i;
    v->type = type;
    return JSON_PARSE_OK;
}

// 解析原始字符串
static int json_parse_string_raw(json_context *c, char **str, size_t *len)
{
    size_t head = c->top;
    unsigned u, u1;
    const char *p;
    EXPECT(c, '\"');
    p = c->json;
    for (;;)
    {
        char ch = *p++;
        switch (ch)
        {
        case '\"':
            *len = c->top - head;
            *str = static_cast<char *>(json_context_pop(c, *len));
            c->json = p;
            return JSON_PARSE_OK;
        case '\\': // 解析转义字符
            switch (*p++)
            {
            case '\"':
                PUTC(c, '\"');
                break;
            case '\\':
                PUTC(c, '\\');
                break;
            case '/':
                PUTC(c, '/');
                break;
            case 'b':
                PUTC(c, '\b');
                break;
            case 'f':
                PUTC(c, '\f');
                break;
            case 'n':
                PUTC(c, '\n');
                break;
            case 'r':
                PUTC(c, '\r');
                break;
            case 't':
                PUTC(c, '\t');
                break;
            case 'u': // 解析
                if (!(p = json_parse_hex4(p, &u)))
                    STRING_ERROR(JSON_PARSE_INVALID_UNICODE_HEX);
                if (u >= 0xD800 && u <= 0xDBFF)
                {
                    // 低代理对
                    if (*p++ != '\\')
                        STRING_ERROR(JSON_PARSE_INVALID_UNICODE_SURROGATE);
                    if (*p++ != 'u')
                        STRING_ERROR(JSON_PARSE_INVALID_UNICODE_SURROGATE);
                    if (!(p = json_parse_hex4(p, &u1)))
                    {
                        STRING_ERROR(JSON_PARSE_INVALID_UNICODE_HEX);
                    }
                    if (u1 < 0xDC00 || u1 > 0xDFFF)
                        STRING_ERROR(JSON_PARSE_INVALID_UNICODE_SURROGATE);
                    u = (((u - 0xD800) << 10) | (u1 - 0xDC00)) + 0x10000;
                }
                json_encode_utf8(c, u);
                break;
            default:
                STRING_ERROR(JSON_PARSE_INVALID_STRING_ESCAPE);
            }
            break;
        case '\0':
            STRING_ERROR(JSON_PARSE_MISS_QUOTATION_MARK);
        default:
            if ((unsigned char)ch < 0x20)
            {
                STRING_ERROR(JSON_PARSE_INVALID_STRING_CHAR);
            }
            PUTC(c, ch);
        }
    }
}

// 解析字符串
static int json_parse_string(json_context *c, json_value *v)
{
    int ret;
    char *s;
    size_t len;
    if ((ret = json_parse_string_raw(c, &s, &len)) == JSON_PARSE_OK)
        json_set_string(v, s, len);
    return ret;
}

// 解析数字
static int json_parse_number(json_context *c, json_value *v)
{
    const char *p = c->json;
    if (*p == '-')
        p++;
    if (*p == '0')
        p++;
    else
    {
        if (!ISDIGIT1TO9(*p))
            return JSON_PARSE_INVALID_VALUE;
        for (p++; ISDIGIT(*p); p++)
            ;
    }
    if (*p == '.')
    {
        p++;
        if (!ISDIGIT(*p))
            return JSON_PARSE_INVALID_VALUE;
        for (p++; ISDIGIT(*p); p++)
            ;
    }
    if (*p == 'e' || *p == 'E')
    {
        p++;
        if (*p == '+' || *p == '-')
        {
            p++;
        }
        if (!ISDIGIT(*p))
            return JSON_PARSE_INVALID_VALUE;
        for (p++; ISDIGIT(*p); p++)
            ;
    }
    errno = 0;
    v->u.n = strtod(c->json, NULL);
    if (errno == ERANGE && (v->u.n == HUGE_VAL || v->u.n == -HUGE_VAL))
        return JSON_PARSE_NUMBER_TOO_BIG;
    c->json = p;
    v->type = JSON_NUMBER;
    return JSON_PARSE_OK;
}

// 解析数组
static int json_parse_array(json_context *c, json_value *v)
{
    size_t size = 0, i;
    int ret;
    EXPECT(c, '[');
    json_parse_whitespace(c);
    if (*c->json == ']')
    {
        c->json++;
        v->type = JSON_ARRAY;
        v->u.a.size = 0;
        v->u.a.e = NULL;
        return JSON_PARSE_OK;
    }
    for (;;)
    {
        json_value e;
        json_init(&e);
        json_parse_whitespace(c);
        if ((ret = json_parse_value(c, &e)) != JSON_PARSE_OK)
        {
            break;
        }
        memcpy(json_context_push(c, sizeof(json_value)), &e, sizeof(json_value));
        size++;
        json_parse_whitespace(c);
        if (*c->json == ',')
        {
            c->json++;
            json_parse_whitespace(c);
        }
        else if (*c->json == ']')
        {
            c->json++;
            v->type = JSON_ARRAY;
            v->u.a.size = size;
            size *= sizeof(json_value);
            memcpy(v->u.a.e = (json_value *)malloc(size), json_context_pop(c, size), size);
            return JSON_PARSE_OK;
        }
        else
        {
            ret = JSON_PARSE_MISS_COMMA_OR_SQUARE_BARCKET;
            break;
        }
    }
    for (i = 0; i < size; i++)
        json_free((json_value *)json_context_pop(c, sizeof(json_value)));
    return ret;
}

// 解析对象
static int json_parse_object(json_context *c, json_value *v)
{
    size_t size, i;
    json_member m;
    int ret;
    EXPECT(c, '{');
    json_parse_whitespace(c);
    if (*c->json == '}')
    {
        c->json++;
        v->type = JSON_OBJECT;
        v->u.o.m = 0;
        v->u.o.size = 0;
        return JSON_PARSE_OK;
    }
    m.k = NULL;
    size = 0;
    for (;;)
    {
        char *str;
        json_init(&m.v);

        if (*c->json != '"')
        {
            ret = JSON_PARSE_MISS_KEY;
            break;
        }
        json_parse_whitespace(c);
        if ((ret = json_parse_string_raw(c, &str, &m.klen)) != JSON_PARSE_OK)
        {
            break;
        }
        memcpy(m.k = (char *)malloc(m.klen + 1), str, m.klen);
        m.k[m.klen] = '\0';
        json_parse_whitespace(c);
        if (*c->json != ':')
        {
            ret = JSON_PARSE_MISS_COLON;
            break;
        }
        c->json++;
        json_parse_whitespace(c);
        if ((ret = json_parse_value(c, &m.v)) != JSON_PARSE_OK)
            break;
        memcpy(json_context_push(c, sizeof(json_member)), &m, sizeof(json_member));
        size++;
        m.k = NULL;
        json_parse_whitespace(c);
        if (*c->json == ',')
        {
            c->json++;
            json_parse_whitespace(c);
        }
        else if (*c->json == '}')
        {
            size_t s = sizeof(json_member) * size;
            c->json++;
            v->type = JSON_OBJECT;
            v->u.o.size = size;
            memcpy(v->u.o.m = (json_member *)malloc(s), json_context_pop(c, s), s);
            return JSON_PARSE_OK;
        }
        else
        {
            ret = JSON_PARSE_MISS_COMMA_OR_CURLY_BARCKET;
            break;
        }
    }
    free(m.k);
    for (i = 0; i < size; i++)
    {
        json_member *m = (json_member *)json_context_pop(c, sizeof(json_member));
        free(m->k);
        json_free(&m->v);
    }
    v->type = JSON_NULL;
    return ret;
}

static int json_parse_value(json_context *c, json_value *v)
{
    switch (*c->json)
    {
    case 'n':
        return json_parse_literal(c, v, "null", JSON_NULL);
    case 'f':
        return json_parse_literal(c, v, "false", JSON_FALSE);
    case 't':
        return json_parse_literal(c, v, "true", JSON_TRUE);
    case '\0':
        return JSON_PARSE_EXPECT_VALUE;
    case '"':
        return json_parse_string(c, v);
    case '[':
        return json_parse_array(c, v);
    case '{':
        return json_parse_object(c, v);
    default:
        return json_parse_number(c, v);
    }
}

// 解析json字符串 主函数
int json_parse(json_value *v, const char *json)
{
    json_context c;
    int ret;
    assert(v != NULL);
    c.json = json;
    c.stack = NULL;
    c.size = c.top = 0;
    json_init(v);
    json_parse_whitespace(&c);
    if ((ret = json_parse_value(&c, v)) == JSON_PARSE_OK)
    {
        json_parse_whitespace(&c);
        if (*c.json != '\0')
        {
            v->type = JSON_NULL;
            ret = JSON_PARSE_ROOT_NOT_SINGULAR;
        }
    }
    assert(c.top == 0);
    free(c.stack);
    return ret;
}

#define PUTS(c, s, len) memcpy(json_context_push(c, len), s, len)

static void json_stringify_string(json_context *c, const char *s, size_t len)
{
    size_t i;
    assert(s != NULL);
    PUTC(c, '"');
    for (i = 0; i < len; i++)
    {
        unsigned char ch = (unsigned char)s[i];
        switch (ch)
        {
        case '\"':
            PUTS(c, "\\\"", 2);
            break;
        case '\\':
            PUTS(c, "\\\\", 2);
            break;
        case '\b':
            PUTS(c, "\\b", 2);
            break;
        case '\f':
            PUTS(c, "\\f", 2);
            break;
        case '\n':
            PUTS(c, "\\n", 2);
            break;
        case '\r':
            PUTS(c, "\\r", 2);
            break;
        case '\t':
            PUTS(c, "\\t", 2);
            break;
        default:
            if (ch < 0x20)
            {
                char buffer[7];
                sprintf(buffer, "\\u%04X", ch);
                PUTS(c, buffer, 6);
            }
            else
                PUTC(c, s[i]);
        }
    }
    PUTC(c, '"');
}

static void json_stringify_value(json_context *c, const json_value *v)
{
    size_t i;
    
    switch (v->type)
    {
    case JSON_NULL:
        PUTS(c, "null", 4);
        break;
    case JSON_FALSE:
        PUTS(c, "false", 5);
        break;
    case JSON_TRUE:
        PUTS(c, "true", 4);
        break;
    case JSON_NUMBER:
    {
        c->top -= 32 - sprintf(static_cast<char*>(json_context_push(c, 32)), "%.17g", v->u.n);
        break;
    }
    case JSON_ARRAY:
    {
        PUTC(c, '[');
        for (i = 0; i < v->u.a.size; i++)
        {
            if(i > 0)
                PUTC(c, ',');
            json_stringify_value(c, &v->u.a.e[i]);
            
        }
        PUTC(c, ']');
        break;
    }
    case JSON_OBJECT:
    {
        PUTC(c, '{');
        for (i = 0; i < v->u.o.size; i++)
        {   
            if(i > 0)
                PUTC(c, ',');
            json_stringify_string(c, v->u.o.m[i].k, v->u.o.m[i].klen);
            PUTC(c, ':');
            json_stringify_value(c, &v->u.o.m[i].v);
        }
        PUTC(c, '}');
        break;
    }
    case JSON_STRING:
    {
        json_stringify_string(c, v->u.s.s, v->u.s.len);
        break;
    }
    default:
        assert(0 && "invalid type");
    }
    
}

// 字符串化json 主函数
char* json_stringify(const json_value *v,  size_t *length)
{
    json_context c;
    assert(v != NULL);

    c.stack = (char *)malloc(c.size = JSON_PARSE_STACK_INIT_SIZE);
    c.top = 0;
    json_stringify_value(&c, v);
    if (length)
    {
        *length = c.top;
    }
    PUTC(&c, '\0');
    
    return c.stack;
}

// 获取json类型
json_type json_get_type(const json_value *v)
{
    assert(v != NULL);
    return v->type;
}

// 获取数字
double json_get_number(const json_value *v)
{
    assert(v != NULL && v->type == JSON_NUMBER);
    return v->u.n;
}

int json_get_boolean(const json_value *v)
{
    assert(v != NULL && (v->type == JSON_TRUE || v->type == JSON_FALSE));
    return v->type == JSON_TRUE;
}

void json_set_boolean(json_value *v, int b)
{
    json_free(v);
    v->type = b ? JSON_TRUE : JSON_FALSE;
}

void json_set_number(json_value *v, double n)
{
    json_free(v);
    v->u.n = n;
    v->type = JSON_NUMBER;
}

const char *json_get_string(const json_value *v)
{
    assert(v != NULL && v->type == JSON_STRING);
    return v->u.s.s;
}

size_t json_get_string_length(const json_value *v)
{
    assert(v != NULL && v->type == JSON_STRING);
    return v->u.s.len;
}

size_t json_get_array_size(const json_value *v)
{
    assert(v != NULL && v->type == JSON_ARRAY);
    return v->u.a.size;
}

json_value *json_get_array_element(const json_value *v, size_t index)
{
    assert(v != NULL && v->type == JSON_ARRAY);
    assert(index < v->u.a.size);
    return &v->u.a.e[index];
}

size_t json_get_object_size(const json_value *v)
{
    assert(v != NULL && v->type == JSON_OBJECT);
    return v->u.o.size;
}

const char *json_get_object_key(const json_value *v, size_t index)
{
    assert(v != NULL && v->type == JSON_OBJECT);
    assert(index < v->u.o.size);
    return v->u.o.m[index].k;
}

size_t json_get_object_key_length(const json_value *v, size_t index)
{
    assert(v != NULL && v->type == JSON_OBJECT);
    assert(index < v->u.o.size);
    return v->u.o.m[index].klen;
}

json_value *json_get_object_value(const json_value *v, size_t index)
{
    assert(v != NULL && v->type == JSON_OBJECT);
    assert(index < v->u.o.size);
    return &v->u.o.m[index].v;
}