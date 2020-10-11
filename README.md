# ext-libdeflate
[![Build Status](https://travis-ci.com/pmmp/ext-libdeflate.svg?branch=master)](https://travis-ci.com/pmmp/ext-libdeflate)

PHP bindings for [libdeflate](https://github.com/ebiggers/libdeflate), a zlib replacement with significantly better performance.

## Features
At the time of writing, this extension only exposes libdeflate's compression APIs, since these are the simplest to implement.

Since libdeflate doesn't support stream decompression, the decompression APIs are less useful unless you know the decompressed size of the data before decompressing it.

## Performance
Compared to `zlib_encode()`, a 40% performance improvement can be observed at level 1, rising to 50-70% at level 6 (default), for approximately the same compression ratios. Also, `libdeflate_deflate_compress()` was observed to sometimes be faster at level 6 compression than `zlib_encode()` at level 1 compression.

## API
```php
<?php

/**
 * Equivalent to zlib_encode($data, ZLIB_ENCODING_RAW, $level)
 * @throws \RuntimeException
 */
function libdeflate_deflate_compress(string $data, int $level = 6) : string;

/**
 * Equivalent to zlib_encode($data, ZLIB_ENCODING_DEFLATE, $level)
 * @throws \RuntimeException
 */
function libdeflate_zlib_compress(string $data, int $level = 6) : string;

/**
 * Equivalent to zlib_encode($data, ZLIB_ENCODING_GZIP, $level)
 * @throws \RuntimeException
 */
function libdeflate_gzip_compress(string $data, int $level = 6) : string;
```
