<?php
$useLib = new uselib();
$result = $useLib->get();
print_r($result);
echo "\r\n";
$result = custom_show_site();
print_r($result);