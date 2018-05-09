dnl $Id$
dnl config.m4 for extension uselib

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(uselib, for uselib support,
dnl Make sure that the comment is aligned:
dnl [  --with-uselib             Include uselib support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(uselib, whether to enable uselib support,
Make sure that the comment is aligned:
[  --enable-uselib           Enable uselib support])

if test "$PHP_USELIB" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-uselib -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/uselib.h"  # you most likely want to change this
  dnl if test -r $PHP_USELIB/$SEARCH_FOR; then # path given as parameter
  dnl   USELIB_DIR=$PHP_USELIB
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for uselib files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       USELIB_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$USELIB_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the uselib distribution])
  dnl fi

  dnl # --with-uselib -> add include path
  dnl PHP_ADD_INCLUDE($USELIB_DIR/include)

  dnl # --with-uselib -> check for lib and symbol presence
  dnl LIBNAME=uselib # you may want to change this
  dnl LIBSYMBOL=uselib # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $USELIB_DIR/$PHP_LIBDIR, USELIB_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_USELIBLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong uselib lib version or lib not found])
  dnl ],[
  dnl   -L$USELIB_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(USELIB_SHARED_LIBADD)

  PHP_ADD_LIBRARY_WITH_PATH(hello, /usr/local/lib, SAY_SHARED_LIBADD)
  PHP_SUBST(SAY_SHARED_LIBADD)

  PHP_ADD_LIBRARY_WITH_PATH(wt, /usr/local/lib, WT_SHARED_LIBADD)
  PHP_SUBST(WT_SHARED_LIBADD)

  PHP_NEW_EXTENSION(uselib, uselib.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
  PHP_INSTALL_HEADERS(ext/uselib, [php_uselib.h])
fi
