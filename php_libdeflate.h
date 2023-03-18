/* libdeflate extension for PHP */

#ifndef PHP_LIBDEFLATE_H
# define PHP_LIBDEFLATE_H

extern zend_module_entry libdeflate_module_entry;
# define phpext_libdeflate_ptr &libdeflate_module_entry

# define PHP_LIBDEFLATE_VERSION "0.2.1"

# if defined(ZTS) && defined(COMPILE_DL_LIBDEFLATE)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_LIBDEFLATE_H */
