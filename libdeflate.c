#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/spl/spl_exceptions.h"
#include "ext/standard/info.h"
#include "Zend/zend_exceptions.h"

#include "php_libdeflate.h"
#include "libdeflate.h"

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(libdeflate)
{
#if defined(ZTS) && defined(COMPILE_DL_LIBDEFLATE)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(libdeflate)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "libdeflate support", "enabled");
	php_info_print_table_header(2, "libdeflate library version", LIBDEFLATE_VERSION_STRING);
	php_info_print_table_end();
}
/* }}} */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_libdeflate_compress, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, level, IS_LONG, 0)
ZEND_END_ARG_INFO()

typedef size_t (*php_libdeflate_compress_bound_func)(struct libdeflate_compressor*, size_t);
typedef size_t (*php_libdeflate_compress_func)(struct libdeflate_compressor*, const void*, size_t, void*, size_t);

static inline zend_string* php_libdeflate_compress(zend_string *data, zend_long level, php_libdeflate_compress_bound_func compressBoundFunc, php_libdeflate_compress_func compressFunc) {
	struct libdeflate_compressor* compressor = libdeflate_alloc_compressor(level);
	if (compressor == NULL) {
		zend_throw_exception_ex(spl_ce_RuntimeException, 0, "Unable to allocate libdeflate compressor");
		return NULL;
	}

	size_t compressBound = compressBoundFunc(compressor, ZSTR_LEN(data));
	void* output = emalloc(compressBound);
	size_t actualSize = compressFunc(compressor, ZSTR_VAL(data), ZSTR_LEN(data), output, compressBound);

	if (actualSize == 0){
		zend_throw_exception_ex(spl_ce_RuntimeException, 0, "Too small buffer provided (this is a bug)");
		return NULL;
	}

	zend_string* result = zend_string_init(output, actualSize, 0);
	efree(output);
	libdeflate_free_compressor(compressor);
	return result;
}

#define PHP_LIBDEFLATE_FUNC(compressFunc, compressBoundFunc) \
PHP_FUNCTION(compressFunc) { \
	zend_string *data; \
	zend_long level = 6; \
\
	ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 2) \
		Z_PARAM_STR(data) \
		Z_PARAM_OPTIONAL \
		Z_PARAM_LONG(level) \
	ZEND_PARSE_PARAMETERS_END(); \
\
	zend_string *result = php_libdeflate_compress(data, level, compressBoundFunc, compressFunc); \
	if (result == NULL) { \
		return; \
	} \
	RETURN_STR(result); \
}

/* {{{ proto string libdeflate_deflate_compress(string $data [, int $level = 6]) */
PHP_LIBDEFLATE_FUNC(libdeflate_deflate_compress, libdeflate_deflate_compress_bound) /* }}} */

/* {{{ proto string libdeflate_zlib_compress(string $data [, int $level = 6]) */
PHP_LIBDEFLATE_FUNC(libdeflate_zlib_compress, libdeflate_zlib_compress_bound) /* }}} */

/* {{{ proto string libdeflate_gzip_compress(string $data [, int $level = 6]) */
PHP_LIBDEFLATE_FUNC(libdeflate_gzip_compress, libdeflate_gzip_compress_bound) /* }}} */

/* {{{ libdeflate_functions[]
 */
static const zend_function_entry libdeflate_functions[] = {
	PHP_FE(libdeflate_deflate_compress, arginfo_libdeflate_compress)
	PHP_FE(libdeflate_zlib_compress, arginfo_libdeflate_compress)
	PHP_FE(libdeflate_gzip_compress, arginfo_libdeflate_compress)
	PHP_FE_END
};
/* }}} */

/* {{{ libdeflate_module_entry
 */
zend_module_entry libdeflate_module_entry = {
	STANDARD_MODULE_HEADER,
	"libdeflate",
	libdeflate_functions,
	NULL, /* PHP_MINIT */
	NULL, /* PHP_MSHUTDOWN */
	PHP_RINIT(libdeflate), /* PHP_RINIT */
	NULL, /* PHP_RSHUTDOWN */
	PHP_MINFO(libdeflate),
	PHP_LIBDEFLATE_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_LIBDEFLATE
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(libdeflate)
#endif
