--TEST--
Test that compression works normally
--FILE--
<?php

$buffer = str_repeat("abcdefghijklmnopqrstuvwxyz", 1000);

foreach([
    'libdeflate_deflate_compress',
    'libdeflate_zlib_compress',
    'libdeflate_gzip_compress'
] as $function){
    $compressedBuffers = [];
    for($i = 1; $i <= 10; $i++){
        for($level = 0; $level <= 12; $level++){
            $compressed = libdeflate_deflate_compress($buffer, $level);

            if(isset($compressedBuffers[$level]) && $compressedBuffers[$level] !== $compressed){
                throw new \Error("Different output for compression on level $level on run $i");
            }
            $compressedBuffers[$level] = $compressed;
        }
    }

    var_dump(count($compressedBuffers));
    foreach($compressedBuffers as $level => $compressed){
        if($level === 0){
            if(strpos($compressed, $buffer) === false){
                var_dump($compressed);
                throw new \Error("Output for level 0 doesn't contain recognizable data");
            }
        }elseif(strlen($compressed) >= strlen($buffer)){
            //this string is definitely compressible
            throw new \Error("Level $level didn't compress anything");
        }
    }
}
?>
--EXPECT--
int(13)
int(13)
int(13)
