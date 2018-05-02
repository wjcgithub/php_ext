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

/* If you declare any globals in php_wjctest.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(wjctest)
*/

/* True global resources - no need for thread safety here */
static int le_wjctest;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("wjctest.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_wjctest_globals, wjctest_globals)
    STD_PHP_INI_ENTRY("wjctest.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_wjctest_globals, wjctest_globals)
PHP_INI_END()
*/
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

//传递参数与返回值
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
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(wjctest)
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
