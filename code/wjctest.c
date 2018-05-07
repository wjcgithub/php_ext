/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_wjctest.h"

/* If you declare any globals in php_wjctest.h uncomment this:*/
ZEND_DECLARE_MODULE_GLOBALS(wjctest)


/* True global resources - no need for thread safety here */
static int le_wjctest;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini*/
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("wjctest.number", "100", PHP_INI_ALL, OnUpdateLong, global_number, zend_wjctest_globals, wjctest_globals)
    STD_PHP_INI_ENTRY("wjctest.string", "ab", PHP_INI_ALL, OnUpdateString, global_string, zend_wjctest_globals, wjctest_globals)
    STD_PHP_INI_ENTRY("wjctest.boolean", "0", PHP_INI_ALL, OnUpdateBool, global_boolean, zend_wjctest_globals, wjctest_globals)
PHP_INI_END()
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_wjctest_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(wjctest)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "wjctest", arg);

	RETURN_STR(strg);
}

PHP_FUNCTION(default_value)
{
	zend_string *type;
	zval             *value = NULL;

#ifndef FAST_ZPP
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "S|z", &type, &value) == FAILURE) {
		return ;
	}
#else
	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(type)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_EX(value,0,1)
	ZEND_PARSE_PARAMETERS_END();
#endif

	if (ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type), "int", 3) == 0 && value == NULL) {
	    RETURN_LONG(0);
	} else if (ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type), "int", 3) == 0 && value != NULL) {
	    RETURN_ZVAL(value, 0, 1); 
	} else if (ZSTR_LEN(type) == 4 && strncmp(ZSTR_VAL(type), "bool", 4) == 0 && value == NULL) {
	    RETURN_FALSE;
	} else if (ZSTR_LEN(type) == 4 && strncmp(ZSTR_VAL(type), "bool", 4) == 0 && value != NULL) {
	    RETURN_ZVAL(value, 0, 1); 
	} else if (ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type), "str", 3) == 0 && value == NULL) {
	    RETURN_EMPTY_STRING();
	} else if (ZSTR_LEN(type) == 3 && strncmp(ZSTR_VAL(type), "str", 3) == 0 && value != NULL) {
	    RETURN_ZVAL(value, 0, 1); 
	} 
	RETURN_NULL();
}

PHP_FUNCTION(get_size)
{
	zval *val;
	size_t size;
	zend_string *result;
	HashTable *myht;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "z", &val))
	{
		return;
	}

	if (Z_TYPE_P(val) == IS_STRING) {
	    result = strpprintf(0, "string size is %d", Z_STRLEN_P(val));
	} else if (Z_TYPE_P(val) == IS_ARRAY) {
	    myht = Z_ARRVAL_P(val);
	    result = strpprintf(0, "array size is %d", zend_array_count(myht));
	} else {
	    result = strpprintf(0, "can not support");
	}   
	     
	RETURN_STR(result);
}

PHP_FUNCTION(define_var)
{
	//变量的值
	zval var_value;
	//变量名称
	zend_string *var_name = NULL;

	//创建整形变量
	ZVAL_LONG(&var_value, 2);
	//设置本地变量
	zend_set_local_var_str("lng", 3, &var_value, 0);
	ZVAL_NULL(&var_value);

	//创建字符串变量
	zend_string *str = NULL;
	char content[4] = "abc";
	var_name = zend_string_init("str", 3, 0);
	str = zend_string_init(content, sizeof(content)-1, 0);
	//设置变量值
	ZVAL_STR(&var_value, str);
	//设置本地变量
	zend_set_local_var(var_name, &var_value, 0);
	//清除变量
	zend_string_release(var_name);
	ZVAL_NULL(&var_value);

	//创建数组变量
	//设置变量名称
	var_name = zend_string_init("arr", 3, 0);
	array_init(&var_value);
	add_index_long(&var_value, 0, 1);
	add_assoc_stringl_ex(&var_value, "a", 1, "b", 1);
	zend_set_local_var(var_name, &var_value, 0);
	zend_string_release(var_name);
	ZVAL_NULL(&var_value);

	//创建对象变量
	zend_class_entry *ce;
	zend_string *class_name;
	class_name = zend_string_init("demo", 4, 0);
	//获取类
	ce = zend_fetch_class(class_name, ZEND_FETCH_CLASS_AUTO);
	zend_string_release(class_name);
	object_init_ex(&var_value, ce);
	//设置本地变量
	zend_set_local_var_str("obj", 3, &var_value, 0);
	ZVAL_NULL(&var_value);
}

//字符串链接
PHP_FUNCTION(str_concat)
{
	zend_string *prefix, *subject, *result;
	zval *string;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "Sz", &prefix, &string) == FAILURE)
	{
		return;
	}

	subject = zval_get_string(string);
	if (zend_binary_strncmp(ZSTR_VAL(prefix), ZSTR_LEN(prefix), ZSTR_VAL(subject),ZSTR_LEN(subject),ZSTR_LEN(prefix)) == 0)
	{
		RETURN_STR(subject);
	}
	result = strpprintf(0, "%s %s", ZSTR_VAL(prefix), ZSTR_VAL(subject));
	RETURN_STR(result);
}

PHP_FUNCTION(array_concat)
{
	zval *arr, *prefix, *entry, *prefix_entry, value;
	zend_string *string_key, *result;
	zend_ulong num_key;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "aa", &arr, &prefix) == FAILURE)
	{
		return;
	}

	array_init_size(return_value, zend_hash_num_elements(Z_ARRVAL_P(arr)));

	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(arr), num_key, string_key, entry){
		if (string_key && zend_hash_exists(Z_ARRVAL_P(prefix), string_key))
		{
			prefix_entry = zend_hash_find(Z_ARRVAL_P(arr), string_key);
			if (Z_TYPE_P(entry) == IS_STRING && prefix_entry != NULL 
				&& Z_TYPE_P(prefix_entry) == IS_STRING)
			{
				result = strpprintf(0, "%s%s", Z_STRVAL_P(prefix_entry), Z_STRVAL_P(entry));
				ZVAL_STR(&value, result);
				zend_hash_update(Z_ARRVAL_P(return_value), string_key, &value);
			}
		} else if(string_key == NULL && zend_hash_index_exists(Z_ARRVAL_P(prefix), num_key)){
			prefix_entry = zend_hash_index_find(Z_ARRVAL_P(prefix), num_key);
			if (Z_TYPE_P(entry) == IS_STRING && prefix_entry != NULL && Z_TYPE_P(prefix_entry) == IS_STRING)
			{
				result = strpprintf(0, "%s%s", Z_STRVAL_P(prefix_entry), Z_STRVAL_P(entry));
				ZVAL_STR(&value, result);
				zend_hash_index_update(Z_ARRVAL_P(return_value), num_key, &value);
			}
		} else if (string_key){
			zend_hash_update(Z_ARRVAL_P(return_value), string_key, entry);
			zval_add_ref(entry);
		} else {
			zend_hash_index_update(Z_ARRVAL_P(return_value), num_key, entry);
			zval_add_ref(entry);
		}
	}ZEND_HASH_FOREACH_END();
}

//释放hash
static void wjctest_hash_destroy(HashTable *ht)
{
	zend_string *key;
	zval *element;
	if ( (ht)->u.flags & HASH_FLAG_INITIALIZED )
	{
		ZEND_HASH_FOREACH_STR_KEY_VAL(ht, key, element) {
			if (key)
			{
				free(key);
			}
			switch(Z_TYPE_P(element)) {
				case IS_STRING:
					free(Z_PTR_P(element));
					break;
				case IS_ARRAY:
					wjctest_hash_destroy(Z_ARRVAL_P(element));
					break;
			}
		} ZEND_HASH_FOREACH_END();
		free(HT_GET_DATA_ADDR(ht));
	}
	free(ht);
}

//释放数组和字符串
static void wjctest_entry_dtor_persisten(zval *zvalue)
{
	if (Z_TYPE_P(zvalue) == IS_ARRAY)
	{
		wjctest_hash_destroy(Z_ARRVAL_P(zvalue));
	} else if (Z_TYPE_P(zvalue) == IS_STRING) {
		zend_string_release(Z_STR_P(zvalue));
	}
}

//PHP7扩展开发之类的创建
zend_class_entry *children_ce;
PHP_METHOD(children, learn);

ZEND_BEGIN_ARG_INFO_EX(arginfo_children_learn, 0, 0, 1)
	ZEND_ARG_INFO(0, love)
ZEND_END_ARG_INFO()

const zend_function_entry children_methods[] = {
	PHP_ME(children, learn, arginfo_children_learn, ZEND_ACC_PUBLIC)
	{NULL, NULL, NULL}
};

//PHP7扩展开发之函数调用
PHP_FUNCTION(call_function)
{
	zval *obj = NULL;
	zval *fun = NULL;
	zval *param = NULL;
	zval retval;
	zval args[1];

#ifndef FAST_ZPP
	//Get function parameters and do error-checking.
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "zzz", &obj, &fun, &param) == FAILURE)
	{
		return;
	}
#else
	ZEND_PARSE_PARAMETERS_START(3, 3)
	        Z_PARAM_ZVAL(obj)
	        Z_PARAM_ZVAL(fun)
	        Z_PARAM_ZVAL(param)
    	ZEND_PARSE_PARAMETERS_END();
#endif

    	args[0] = *param;
    	if (obj == NULL || Z_TYPE_P(obj) == IS_NULL)
    	{
    		call_user_function_ex(EG(function_table), NULL, fun, &retval, 1, args, 0, NULL);
    	} else {
    		call_user_function_ex(EG(function_table), obj, fun, &retval, 1, args, 0, NULL);
    	}
    	RETURN_ZVAL(&retval, 0, 1);
}

//php7扩展开发之配置项
PHP_FUNCTION(show_ini)
{
	zval arr;
	array_init(&arr);
	add_assoc_long_ex(&arr, "wjctest.number", 14, WJCTEST_G(global_number));
	add_assoc_string_ex(&arr, "wjctest.string", 14, WJCTEST_G(global_string));
	add_assoc_bool_ex(&arr, "wjctest.boolean", 15, WJCTEST_G(global_boolean));
	RETURN_ZVAL(&arr, 0, 1);
}

/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_wjctest_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_wjctest_init_globals(zend_wjctest_globals *wjctest_globals)
{
	wjctest_globals->global_value = 0;
	wjctest_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(wjctest)
{
	/* If you have INI entries, uncomment these lines*/
	REGISTER_INI_ENTRIES();
	
	//PHP7扩展开发之常量的创建
	zend_constant c;
	zend_string *key;
	zval value;
	ZVAL_NEW_PERSISTENT_ARR(&c.value);
	zend_hash_init(Z_ARRVAL(c.value), 0, NULL,
		(dtor_func_t)wjctest_entry_dtor_persisten, 1);
	add_index_long(&c.value, 0, 2);
	key = zend_string_init("site", 4, 1);
	ZVAL_STR(&value, zend_string_init("www.wjc.com", 12, 1));
	zend_hash_update(Z_ARRVAL(c.value), key, &value);
	c.flags = CONST_CS|CONST_PERSISTENT;
	c.name = zend_string_init("__ARR__", 7, 1);
	c.module_number = module_number;
	zend_register_constant(&c);

	REGISTER_STRINGL_CONSTANT("__SITE__", "www.wjc.com", 11, CONST_PERSISTENT);
	REGISTER_NS_STRINGL_CONSTANT("say", "__SITE__", "wjc.com", 7, CONST_CS|CONST_PERSISTENT);


	//PHP7扩展开发之类的创建
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "children", children_methods);

	children_ce = zend_register_internal_class(&ce);

	zend_declare_property_null(children_ce, "memory", sizeof("memory")-1, ZEND_ACC_PUBLIC);

	return SUCCESS;
}


PHP_METHOD(children, learn)
{
	char *love;
	size_t love_len;

	if(zend_parse_parameters(ZEND_NUM_ARGS(), "s", &love, &love_len) == FAILURE ){
		return;
	}

	zend_update_property_string(children_ce, getThis(), "memory", sizeof("memory")-1, love);
}

/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(wjctest)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	zval *val;
	val = zend_get_constant_str("__ARR__", 7);
	wjctest_hash_destroy(Z_ARRVAL_P(val));
	ZVAL_NULL(val);
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(wjctest)
{
#if defined(COMPILE_DL_WJCTEST) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(wjctest)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(wjctest)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "wjctest support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ wjctest_functions[]
 *
 * Every user visible function must have an entry in wjctest_functions[].
 */
const zend_function_entry wjctest_functions[] = {
	PHP_FE(wjctest, NULL)
	PHP_FE(default_value, NULL)
	PHP_FE(get_size, NULL)
	PHP_FE(define_var, NULL)
	PHP_FE(str_concat, NULL)
	PHP_FE(array_concat, NULL)
	PHP_FE(call_function, NULL)
	PHP_FE(show_ini, NULL)
	// #define ZEND_FE(name, arg_info)						ZEND_FENTRY(name, ZEND_FN(name), arg_info, 0)
	// #define ZEND_FENTRY(zend_name, name, arg_info, flags)	{ #zend_name, name, arg_info, (uint32_t) (sizeof(arg_info)/sizeof(struct _zend_internal_arg_info)-1), flags },
	// #define ZEND_FN(name) zif_##name
	// #define ZEND_FE_END            { NULL, NULL, NULL, 0, 0 }
	PHP_FE_END	/* Must be the last line in wjctest_functions[] */
	
};
/* }}} */

/* {{{ wjctest_module_entry
 */
zend_module_entry wjctest_module_entry = {
	STANDARD_MODULE_HEADER,
	"wjctest",
	wjctest_functions,
	PHP_MINIT(wjctest),
	PHP_MSHUTDOWN(wjctest),
	PHP_RINIT(wjctest),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(wjctest),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(wjctest),
	PHP_WJCTEST_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_WJCTEST
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(wjctest)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
