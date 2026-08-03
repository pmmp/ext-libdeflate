--TEST--
Test that extension throws errors if given invalid parameters
--SKIPIF--
<?php if(!extension_loaded("libdeflate")) die("skip: extension not loaded"); ?>
--FILE--
<?php

try{
	libdeflate_deflate_compress();
}catch(\ArgumentCountError $e){
	var_dump("ok");
}

try{
	libdeflate_deflate_compress(new stdclass);
}catch(\TypeError $e){
	var_dump("ok");
}

try{
	libdeflate_deflate_compress(str_repeat("abcdefghijklmnopqrstuvwxyz", 1000), 1, 'this_does_not_belong_here');
}catch(\TypeError $e){
	var_dump("ok");
}
?>
--EXPECT--
string(2) "ok"
string(2) "ok"
string(2) "ok"
