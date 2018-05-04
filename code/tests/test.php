<?php
//PHP7扩展开发之传参与返回值
	// function default_value($type, $value=null)
	// {
	// 	if ($type == "int") {
	// 		return $value ?? 0;
	// 	} else if ($type == "bool") {
	// 		return $value ?? false;
	// 	} else if ($type == "str") {
	// 		return is_null($value) ? "" : $value;
	// 	}

	// 	return null;
	// }
	echo "PHP7扩展开发之传参与返回值\r\n";
	var_dump(default_value("int"));
	var_dump(default_value("int", 1));
	var_dump(default_value("bool"));
	var_dump(default_value("bool", true));
	var_dump(default_value("str"));
	var_dump(default_value("str", "a"));
	var_dump(default_value("array"));

//PHP7扩展开发之类型处理

	// function get_size($value)
	// {
	// 	if (is_string($value)) {
	// 		return "string size is ". strlen($value);
	// 	} else if (is_array($value)){
	// 		return "array size is ". sizeof($value);
	// 	} else {
	// 		return "can not support";
	// 	}
	// }

	echo "PHP7扩展开发之类型处理\r\n";
	var_dump(get_size("abc"));
	var_dump(get_size(array(1,2,3)));

//PHP7扩展开发之创建变量
	echo "PHP7扩展开发之创建变量\r\n";
	class demo {}
	// $lng = 2;
	// $str = "abc";
	// $arr = array(1,'a' => 'b');
	// $obj = new demo();

	define_var();
	 
	var_dump($str);
	var_dump($arr);
	var_dump($obj);

//PHP7扩展开发之字符串处理
	echo "PHP7扩展开发之字符串处理\r\n";
	// function str_concat($prefix, $string)
	// {
	// 	$len = strlen($prefix);
	// 	$substr = substr($string, 0, $len);
	// 	if ($substr != $prefix) {
	// 		return $prefix." ".$string;
	// 	} else {
	// 		return $string;
	// 	}
	// }

	echo str_concat("hello", "world");
	echo "\n";
	echo str_concat("hello", "hello wjc");
	echo "\n";

//PHP7扩展开发之数组处理
	echo "PHP7扩展开发之数组处理\r\n";
	// function array_concat($arr, $prefix)
	// {
	// 	foreach ($arr as $key => $value) {
	// 		if (isset($prefix[$key]) && is_string($value) && is_string($prefix[$key])) {
	// 			$arr[$key] = $prefix[$key].$value;
	// 		}
	// 	}

	// 	return $arr;
	// }

		 
	$arr = array(
	    0 => '0',
	    1 => '123',
	    'a' => 'abc',
	);  
	$prefix = array(
	    1 => '456',
	    'a' => 'def',
	);  
	var_dump(array_concat($arr, $prefix));


//PHP7扩展开发之常量定义
	echo "PHP7扩展开发之常量定义\r\n";
	// define("__ARR__", [2, 'site'=>"www.wjc.com"]);
	// define('__SITE__', 'www.wjc.com');
	// define("say\__SITE__", "wjc.com");
	var_dump(__ARR__);
	var_dump(__site__);
	var_dump(say\__SITE__);


//PHP7扩展开发之创建对象
	echo "PHP7扩展开发之创建对象\r\n";
	$children = new children();
	var_dump($children->memory);
	$children->learn('love');
	var_dump($children->memory);


//PHP7扩展开发之函数调用
	echo "PHP7扩展开发之函数调用\r\n";
	class FuncCall{	
	    public function get_site_name ($prefix) {
	        return $prefix."信海龙的博客\n";
	    }
	}
	function get_site_url ($prefix) {
	    return $prefix."www.bo56.com\n";
	}
	 
	// function call_function ($obj, $fun, $param) {
	//     if ($obj == null) {
	//         $result = $fun($param);
	//     } else {
	//         $result = $obj->$fun($param);
	//     }
	//     return $result;
	// }
	$demo = new FuncCall();
	echo call_function($demo, "get_site_name", "site name:");
	echo call_function(null, "get_site_url", "site url:");