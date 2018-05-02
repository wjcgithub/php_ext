### 1. 常见的扩展可以在以下几个方面有所作为
- `介入PHP的编译，执行阶段`：　可以介入PHP框架执行的`5个阶段`,　比如opcache, 就是重定义了编译函数
- `提供内部函数：`可以定义内部函数扩充PHP的函数功能，比如array, date等操作
- `提供内部类：`
- `实现RPC客户端：`实现与外部服务的交互，比如redis, mysql等
- `提升执行性能：`PHP是解析型语言，在性能方面远不及C语言，可以将`耗cpu的操作`以c语言替代
- `等等．．．．`

### 2. php中的扩展分为两类
- PHP扩展
- Zend扩展
> 对于内核而言这两个分别称之为：模块（module）, 扩展（extension）

### 3. 扩展实现的原理
> PHP中扩展通过`zend_module_entry`这个结构来表示，此结构定义了扩展的全部信息：扩展名，　扩展版本，扩展提供的函数列表以及php四个执行阶段的Hook函数等，每一个扩展都需要定义一个次结构的变量，而且这个变量的名称格式必现是：`{module_name}_module_entry`, 内核正是通过这个结构获取到扩展提供的功能的．

1. dlopen()打开so库文件
2. dlsym()获取动态库中`get_module`函数的地址，`get_module`是每个扩展都必须提供的一个接口，用于返回扩展`zend_module_entry`结构的地址
3. 调用扩展的`get_module`，获取扩展的`zend_module_entry`结构
4. zend api版本号检查，比如php的扩展在php5下是无法使用的
5. 注册扩展，将扩展添加到`module_registry`中，这是一个全局`HashTable`, 用于全部扩展的`zend_module_entry`结构
6. 如果扩展提供了内部函数则将这些函数注册到`EG(funcction_table)`中

> 完成以上的扩展注册后．PHP将在不同的执行阶段依此调用每个扩展注册的当前阶段的`hook函数`

### 4. 扩展的构成及编译

#### 1. zend_module_entry
```powershell
//zend_modules.h
struct	_zend_module_entry	{
	unsigned	short	size;	//sizeof(zend_module_entry)
	unsigned	int	zend_api;	//ZEND_MODULE_API_NO
	unsigned	char	zend_debug;	//是否开启debug
	unsigned	char	zts;	//是否开启线程安全
	const	struct	_zend_ini_entry	*ini_entry;
	const	struct	_zend_module_dep	*deps;
	const	char	*name;	//扩展名称,不能重复
	const	struct	_zend_function_entry	*functions;	//扩展提供的内部函数列表
	int	(*module_startup_func)(INIT_FUNC_ARGS);	//扩展初始化回调函数,PHP_MI
NIT_FUNCTION或ZEND_MINIT_FUNCTION定义的函数
	int	(*module_shutdown_func)(SHUTDOWN_FUNC_ARGS);	//扩展关闭时回调函数
	int	(*request_startup_func)(INIT_FUNC_ARGS);	//请求开始前回调函数
	int	(*request_shutdown_func)(SHUTDOWN_FUNC_ARGS);	//请求结束时回调函数
	void	(*info_func)(ZEND_MODULE_INFO_FUNC_ARGS);	//php_info展示的扩展信息处理函数
	const	char	*version;	//版本
	...
	unsigned	char	type;
	void	*handle;
	int	module_number;	//扩展的唯一编号
	const	char	*build_id;
};
```

> 这个结构包含很多成员,但并不是所有的都需要自己定义,经常用到的主要有下面几个:

- name:	扩展名称,不能重复
- functions:	扩展定义的内部函数entry
- module_startup_func:	PHP在模块初始化时回调的hook函数,可以使扩展介入modulestartup阶段
- module_shutdown_func:	在模块关闭阶段回调的函数
- request_startup_func:	在请求初始化阶段回调的函数
- request_shutdown_func:	在请求结束阶段回调的函数
- __info_func:__	php_info()函数时调用,用于展示一些配置、运行信息
- version:	扩展版本

#### 2. phpize的执行过程
> 这个脚本主要是操作复杂的autoconf/automake/autoheader/autolocal等系列命令,用于生成configure文件,GNU	auto系列的工具众多

1. (1)autoscan:	在源码目录下扫描,生成configure.scan,然后把这个文件重名为为configure.in,可以在这个文件里对依赖的文件、库进行检查以及配置一些编译参数等。
2. (2)aclocal:	automake中有很多宏可以在configure.in或其它.m4配置中使用,这些宏必须定义在aclocal.m4中,否则将无法被autoconf识别,aclocal可以根据configure.in自动生成aclocal.m4,另外,autoconf提供的特性不可能满足所有的需求,所以autoconf还支持自定义宏,用户可以在acinclude.m4中定义自己的宏,然后在执行aclocal生成aclocal.m4时也会将acinclude.m4加载进去。
3. (3)autoheader:	它可以根据configure.in、aclocal.m4生成一个C语言"define"声明的头文件模板(config.h.in)供configure执行时使用,比如很多程序会通过configure提供一些enable/disable的参数,然后根据不同的参数决定是否开启某些选项,这种就可以根据编译参数的值生成一个define宏,比如: --enabled-xxx 生成 #define	ENABLED_XXX	1,否则默认生成 #define	ENABLED_XXX	0 ,代码里直接使用这个宏即可。
```cmake
AC_PREREQ([2.63])
AC_INIT([FULL-PACKAGE-NAME],	[VERSION],	[BUG-REPORT-ADDRESS])
AC_CONFIG_HEADERS([config.h])
AC_ARG_ENABLE(xxx,	"--enable-xxx	if	enable	xxx",[
				AC_DEFINE([ENABLED_XXX],	[1],	[enabled	xxx])
],
[
				AC_DEFINE([ENABLED_XXX],	[0],	[disabled	xxx])
])
AC_OUTPUT
```
比如执行autoheader后将生成一个config.h.in的文件,里面包含 #undef	ENABLED_XXX ,最终执行 ./configure	--enable-xxx 后将生成一个config.h文件,包含#define	ENABLED_XXX	1
4. (4)autoconf:	将configure.in中的宏展开生成configure、config.h,此过程会用到aclocal.m4中定义的宏。
5. (5)automake:	将Makefile.am中定义的结构建立Makefile.in,然后configure脚本将生成的Makefile.in文件转换为Makefile。

> 各步骤之间的转化关系如下图:
![Alt text](./1524571113965.png)

#### 3. 编写扩展的基本步骤
1. 通过ext目录下ext_skel脚本生成扩展的基本框架: ./ext_skel	--extname ;
2. 修改config.m4配置:设置编译配置参数、设置扩展的源文件、依赖库/函数检查等等;
3. 编写扩展要实现的功能:按照PHP扩展的格式以及PHP提供的API编写功能;
4. 生成configure:扩展编写完成后执行phpize脚本生成configure及其它配置文件;
5. 编译&安装:./configure、make、make	install,然后将扩展的.so路径添加到php.ini中。

### 5. 钩子函数
1. module startup
2. requrst startup
3. 编译，执行
4. request shutdown
5. post deactivate
	6. 这个函数比较特殊,一般很少会用到,实际它也是在请求结束之后调用的,它比request_shutdown_func更晚执行
6. module shutdown



## 扩展返回值
> 方法的返回值是使用`RETURN_`开头的宏方法进行返回的。常用的宏方法有：

1. RETURN_NULL()	返回null
2. RETURN_LONG(l)	返回整型
3. RETURN_DOUBLE(d) 返回浮点型
4. RETURN_STR(s)	返回一个字符串。参数是一个zend_string * 指针
5. RETURN_STRING(s)	返回一个字符串。参数是一个char * 指针
6. RETURN_STRINGL(s, l) 返回一个字符串。第二个参数是字符串长度。
7. RETURN_EMPTY_STRING()	返回一个空字符串。
8. RETURN_ARR(r)	返回一个数组。参数是zend_array *指针。
9. RETURN_OBJ(r) 返回一个对象。参数是zend_object *指针。
10. RETURN_ZVAL(zv, copy, dtor) 返回任意类型。参数是 zval *指针。
11. RETURN_FALSE	返回false
12. RETURN_TRUE	返回true

### 1. 简单分析一个返回值的宏展开式
`RETURN_LONG` ->   `{ RETVAL_LONG(l); return; }`  ->   `ZVAL_LONG(return_value, l)`  ->  ......  -> `(zval).u1.type_info   &&7   `
