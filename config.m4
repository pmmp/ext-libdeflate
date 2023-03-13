PHP_ARG_WITH([libdeflate],
  [whether to enable libdeflate support],
  [AS_HELP_STRING([--with-libdeflate],
    [Enable libdeflate support])],
  [no])

if test "$PHP_LIBDEFLATE" != "no"; then
  PKG_CHECK_MODULES(LIBDEFLATE, [libdeflate])

  PHP_EVAL_LIBLINE($LIBDEFLATE_LIBS, LIBDEFLATE_SHARED_LIBADD)
  PHP_EVAL_INCLINE($LIBDEFLATE_CFLAGS)

  PHP_SUBST(LIBDEFLATE_SHARED_LIBADD)

  AC_DEFINE(HAVE_LIBDEFLATE, 1, [ Have libdeflate support ])

  PHP_NEW_EXTENSION(libdeflate, libdeflate.c, $ext_shared)
fi
