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
#include "php_uselib.h"
#include <stdio.h>
#include "hello.h"
#include "wt.h"

/* If you declare any globals in php_uselib.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(uselib)
*/

/* True global resources - no need for thread safety here */
static int le_uselib;

zend_class_entry *uselib_ce;
zend_object_handlers uselib_object_handlers;
typedef struct _uselib_object
{
	char * uselib_ptr;
	zend_object std;
} uselib_object;

//用于从标准的zend_object转换获取uselib_object地址
static inline uselib_object *uselib_fetch_object(zend_object *obj) /* {{{ */ {
        return (uselib_object *)((char*)(obj) - XtOffsetOf(uselib_object, std));
}

//创建类对象
static zend_object * uselib_object_create(zend_class_entry * type TSRMLS_DC)
{
	uselib_object *obj = (uselib_object *)ecalloc(1, sizeof(uselib_object) + zend_object_properties_size(type));
	zend_object_std_init(&obj->std, type);
	object_properties_init(&obj->std, type);
	obj->std.handlers = &uselib_object_handlers;
	return &obj->std;
}

//用户销毁类对象
void uselib_object_free_storage(zend_object *object)
{
	uselib_object *intern = uselib_fetch_object(object);
	zend_object_std_dtor(&intern->std);
}

//声明类都有哪些方法
PHP_METHOD(uselib, __construct);
PHP_METHOD(uselib, __destruct);
PHP_METHOD(uselib, get);
const zend_function_entry uselib_methods[] = {
            PHP_ME(uselib, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
            PHP_ME(uselib, __destruct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_DTOR)
            PHP_ME(uselib, get, NULL, ZEND_ACC_PUBLIC)
            {NULL, NULL, NULL}  /* Must be the last line in hello_methods[] */
};

PHP_METHOD(uselib, __construct)
{
	zval *self = getThis();
	uselib_object *obj = uselib_fetch_object(Z_OBJ_P((self)));
	obj->uselib_ptr = show_site();
	RETURN_TRUE;
}

PHP_METHOD(uselib, __destruct)
{
	zval *self = getThis();
	uselib_object *obj = uselib_fetch_object(Z_OBJ_P((self)));
	free(obj->uselib_ptr);
	RETURN_TRUE;
}

PHP_METHOD(uselib, get)
{
	zval *self = getThis();
	uselib_object *obj = uselib_fetch_object(Z_OBJ_P((self)));
	RETURN_STRING(obj->uselib_ptr);
}

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("uselib.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_uselib_globals, uselib_globals)
    STD_PHP_INI_ENTRY("uselib.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_uselib_globals, uselib_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_uselib_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_uselib_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "uselib", arg);

	RETURN_STR(strg);
}

PHP_FUNCTION(custom_show_site)
{
	char *site = show_site();
	RETVAL_STRING(site);
	free(site);
	return;
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_uselib_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_uselib_init_globals(zend_uselib_globals *uselib_globals)
{
	uselib_globals->global_value = 0;
	uselib_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(uselib)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/

	//把声明和定义的函数结合起来
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, "uselib", uselib_methods);
	uselib_ce = zend_register_internal_class(&ce);
	uselib_ce->create_object = uselib_object_create;
	memcpy(&uselib_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	uselib_object_handlers.clone_obj = NULL;
	uselib_object_handlers.offset = XtOffsetOf(uselib_object, std);
	uselib_object_handlers.free_obj = uselib_object_free_storage;
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(uselib)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(uselib)
{
#if defined(COMPILE_DL_USELIB) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(uselib)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(uselib)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "uselib support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ uselib_functions[]
 *
 * Every user visible function must have an entry in uselib_functions[].
 */
const zend_function_entry uselib_functions[] = {
	PHP_FE(confirm_uselib_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(custom_show_site, NULL)
	PHP_FE_END	/* Must be the last line in uselib_functions[] */
};
/* }}} */

/* {{{ uselib_module_entry
 */
zend_module_entry uselib_module_entry = {
	STANDARD_MODULE_HEADER,
	"uselib",
	uselib_functions,
	PHP_MINIT(uselib),
	PHP_MSHUTDOWN(uselib),
	PHP_RINIT(uselib),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(uselib),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(uselib),
	PHP_USELIB_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_USELIB
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(uselib)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
