dnl $Id$
dnl config.m4 for extension demo_dep

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(demo_dep, for demo_dep support,
dnl Make sure that the comment is aligned:
dnl [  --with-demo_dep             Include demo_dep support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(demo_dep, whether to enable demo_dep support,
Make sure that the comment is aligned:
[  --enable-demo_dep           Enable demo_dep support])

if test "$PHP_DEMO_DEP" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-demo_dep -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/demo_dep.h"  # you most likely want to change this
  dnl if test -r $PHP_DEMO_DEP/$SEARCH_FOR; then # path given as parameter
  dnl   DEMO_DEP_DIR=$PHP_DEMO_DEP
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for demo_dep files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       DEMO_DEP_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$DEMO_DEP_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the demo_dep distribution])
  dnl fi

  dnl # --with-demo_dep -> add include path
  dnl PHP_ADD_INCLUDE($DEMO_DEP_DIR/include)

  dnl # --with-demo_dep -> check for lib and symbol presence
  dnl LIBNAME=demo_dep # you may want to change this
  dnl LIBSYMBOL=demo_dep # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $DEMO_DEP_DIR/$PHP_LIBDIR, DEMO_DEP_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_DEMO_DEPLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong demo_dep lib version or lib not found])
  dnl ],[
  dnl   -L$DEMO_DEP_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(DEMO_DEP_SHARED_LIBADD)

  PHP_NEW_EXTENSION(demo_dep, demo_dep.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)

  PHP_ADD_EXTENSION_DEP(demo_dep, wjctest)
fi
