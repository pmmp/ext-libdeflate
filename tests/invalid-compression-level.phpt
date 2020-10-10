--TEST--
Test that libdeflate_deflate_compress() doesn't segfault when given an invalid compression level
--SKIPIF--
<?php if(!extension_loaded("libdeflate)) die("skip: extension not loaded"); ?>
--FILE--
<?php

try{
	libdeflate_deflate_compress("aaaaaa", -1);
}catch(\RuntimeException $e){
	var_dump("ok");
}

try{
	libdeflate_deflate_compress("aaaaaa", 13);
}catch(\RuntimeException $e){
	var_dump("ok");
}
?>
--EXPECT--
string(2) "ok"
string(2) "ok"
