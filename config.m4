PHP_ARG_WITH([libdeflate],
  [whether to enable libdeflate support],
  [AS_HELP_STRING([--with-libdeflate],
    [Enable libdeflate support])],
  [no])

if test "$PHP_LIBDEFLATE" != "no"; then
  dnl --with-libdeflate -> check with-path
  SEARCH_PATH="/usr/local /usr"
  SEARCH_FOR="include/libdeflate.h"
  if test -r $PHP_LIBDEFLATE/$SEARCH_FOR; then
     LIBDEFLATE_DIR=$PHP_LIBDEFLATE
  else
     AC_MSG_CHECKING([for libdeflate files in default path])
     for i in $SEARCH_PATH ; do
       if test -r $i/$SEARCH_FOR; then
         LIBDEFLATE_DIR=$i
         AC_MSG_RESULT(found in $i)
       fi
     done
  fi
  
  if test -z "$LIBDEFLATE_DIR"; then
     AC_MSG_RESULT([not found])
     AC_MSG_ERROR([Please reinstall the libdeflate distribution])
  fi

  PHP_ADD_INCLUDE($LIBDEFLATE_DIR/include)

  PHP_ADD_LIBRARY_WITH_PATH(deflate, $LIBDEFLATE_DIR/$PHP_LIBDIR, LIBDEFLATE_SHARED_LIBADD)
  PHP_SUBST(LIBDEFLATE_SHARED_LIBADD)

  AC_DEFINE(HAVE_LIBDEFLATE, 1, [ Have libdeflate support ])

  PHP_NEW_EXTENSION(libdeflate, libdeflate.c, $ext_shared)
fi
