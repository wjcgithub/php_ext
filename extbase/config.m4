dnl $Id$
dnl config.m4 for extension wjctest

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(wjctest, for wjctest support,
dnl Make sure that the comment is aligned:
dnl [  --with-wjctest             Include wjctest support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(wjctest, whether to enable wjctest support,
Make sure that the comment is aligned:
[  --enable-wjctest           Enable wjctest support])

if test "$PHP_WJCTEST" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-wjctest -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/wjctest.h"  # you most likely want to change this
  dnl if test -r $PHP_WJCTEST/$SEARCH_FOR; then # path given as parameter
  dnl   WJCTEST_DIR=$PHP_WJCTEST
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for wjctest files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       WJCTEST_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$WJCTEST_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the wjctest distribution])
  dnl fi

  dnl # --with-wjctest -> add include path
  dnl PHP_ADD_INCLUDE($WJCTEST_DIR/include)

  dnl # --with-wjctest -> check for lib and symbol presence
  dnl LIBNAME=wjctest # you may want to change this
  dnl LIBSYMBOL=wjctest # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $WJCTEST_DIR/$PHP_LIBDIR, WJCTEST_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_WJCTESTLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong wjctest lib version or lib not found])
  dnl ],[
  dnl   -L$WJCTEST_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(WJCTEST_SHARED_LIBADD)

  PHP_NEW_EXTENSION(wjctest, wjctest.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
