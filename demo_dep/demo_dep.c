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
#include "php_demo_dep.h"
#include "ext/wjctest/php_wjctest.h"

/* If you declare any globals in php_demo_dep.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(demo_dep)
*/

/* True global resources - no need for thread safety here */
static int le_demo_dep;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("demo_dep.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_demo_dep_globals, demo_dep_globals)
    STD_PHP_INI_ENTRY("demo_dep.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_demo_dep_globals, demo_dep_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_demo_dep_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_demo_dep_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "demo_dep", arg);

	RETURN_STR(strg);
}

PHP_FUNCTION(demo_say)
{
	zif_wjctest(INTERNAL_FUNCTION_PARAM_PASSTHRU);
}

/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_demo_dep_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_demo_dep_init_globals(zend_demo_dep_globals *demo_dep_globals)
{
	demo_dep_globals->global_value = 0;
	demo_dep_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(demo_dep)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(demo_dep)
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
PHP_RINIT_FUNCTION(demo_dep)
{
#if defined(COMPILE_DL_DEMO_DEP) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(demo_dep)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(demo_dep)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "demo_dep support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ demo_dep_functions[]
 *
 * Every user visible function must have an entry in demo_dep_functions[].
 */
const zend_function_entry demo_dep_functions[] = {
	PHP_FE(confirm_demo_dep_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(demo_say, NULL)
	PHP_FE_END	/* Must be the last line in demo_dep_functions[] */
};
/* }}} */

static const zend_module_dep demo_dep_deps[] = {
	ZEND_MOD_REQUIRED("wjctest")
	ZEND_MOD_END	
};

/* {{{ demo_dep_module_entry
 */
zend_module_entry demo_dep_module_entry = {
	STANDARD_MODULE_HEADER_EX, NULL,
	demo_dep_deps,
	"demo_dep",
	demo_dep_functions,
	PHP_MINIT(demo_dep),
	PHP_MSHUTDOWN(demo_dep),
	PHP_RINIT(demo_dep),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(demo_dep),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(demo_dep),
	PHP_DEMO_DEP_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_DEMO_DEP
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(demo_dep)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
