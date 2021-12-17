# Linux 操作

ls	显示当前目录列表

cd dir	到达目录dir

mkdir dir	创建目录dir

vim name	打开文件name

touch name	创建文件name

rm name	删除文件name

ll	查看文件及目录详情

cp [options] source dest	将source复制到dest，options是具体复制操作的选项

mv [options] source dest	将source移动到dest，options是具体移动操作的选项

*.xxx	相当于对所有.xxx后缀的对象进行操作

..	上级目录

.	当前目录



# GCC操作

## gcc/g++编译选项

-E	预处理指定源文件，不进行编译

-S	编译指定源文件，但是不进行汇编

-c	编译、汇编指定源文件，但是不进行链接

-o [file1] [file2] / [file2] -o [file1]	将文件file2编译成可执行文件file1

-I(大写的i) dir	指定include包含文件的搜索目录dir

-g	在编译的时候，生成调试信息，该程序可以被调试器调试

-D name	编译的时候指定宏name

-w	不生成任何警告信息

-Wall	生成所有警告信息

-On	“吸氧”，n的取值范围：0~3。编译器的优化选项的4个级别：-O0没有优化，-O1为缺省值（默认），-O3优化级别最高 

-l(小写的L)	在程序编译的时候，指定使用的库

-L	指定编译的时候，搜索库的路径

-fPIC/fpic	生成与位置无关的代码

-shared	生成共享目标文件，通常用在建立共享库时

-std	指定c语言，如：-std=99，gcc默认的方言是GNU C

# 库

## 静态库和动态库的区别

静态库在程序的链接阶段被复制到了程序中；动态库在链接阶段没有被复制到程序中，而实程序在运行时由系统动态加载到内存中供程序调用。

## 库的好处

1、代码保密；

2、方便部署和分发

## 静态库的制作和

### 命名规则

Linux：libxxx.a	lib固定前缀，xxx库的名字，.a固定后缀

Windows：libxxx.lib	lib固定前缀，xxx库额名字，.lib固定后缀

### 静态库的制作

步骤一：gcc获得.o文件，将库文件编译，要在头文件下，或者指定头文件

gcc/g++ -c

步骤二：将.o文件打包，使用ar工具（archive)	

ar rcs libxxx.a xxx.o xxx.o	

r - 将文件插入备存文件中 

c - 建立备存文件 

s - 索引

### 静态库的使用

在程序的源代码中inclue 头文件和调用里面的函数/变量

编译的时候要指定头文件目录和库文件目录

