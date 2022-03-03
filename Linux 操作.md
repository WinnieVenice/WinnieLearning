# Linux 操作

## 基础指令

-   (指令) &

    在后台运行

-   ls	

    显示当前目录列表

-   cd dir	

    到达目录dir

-   mkdir dir	

    创建目录dir

-   vim name 

    打开文件name

-   set nu 

    显示行号（在文件内使用）

-   touch name	

    创建文件name

-   rm name	

    删除文件name

-   ll	

    查看文件及目录详情

-   cp [options] source dest	

    将source复制到dest，options是具体复制操作的选项

-   mv [options] source dest	

    将source移动到dest，options是具体移动操作的选项

-   *.xxx	

    相当于对所有.xxx后缀的对象进行操作

-   ..	

    上级目录

-   .	

    当前目录

-   env	

    显示当前用户的环境变量	

-   export [-f/-n/-p] [name] = [val]	

    设置或显示环境变量name的值为val，可以新增、修改、删除环境变量。-f 代表[name]中为函数名称；-n 删除指定的变量（实际上并未删除，只是不输出到后续值令的执行环境中）；-p 列出所有shell赋予程序的环境变量。这种方式事实上不会真的修改，只是会改变当前终端的后续执行环境。

-   $name	

    获取变量name或环境变量name的值

-   pwd	

    （print work directory）用于显示工作目录，得到当前所在目录的绝对路径名称

-   echo xxx	

    将xxx打印显示出来，xxx可以是变量

-   source filename	

    在当前bash环境下读取并执行filename中的命令（也可以使用 . filename ）

-   cd ~	

    家目录

## 编辑操作

shift + g	下拉到最下面

o	插入

wq	保存并退出

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

-fPIC/fpic	生成与位置无关（内存位置）的代码

-shared	生成共享目标文件，通常用在建立共享库时

-std	指定c语言，如：-std=99，gcc默认的方言是GNU C

# 库

## 工作原理

静态库：gcc进行链接时，会把静态库中代码打包到可执行程序中

动态库：gcc进行链接时，动态库的代码不会被打包到可执行程序中

程序启动之后，动态库会被动态加载到内存中，通过ldd（list dynamic dependencies）命令检查动态库依赖关系

Linux定位共享库文件：当系统加载可执行代码时，能够知道其所依赖的库的文件，但是还需要知道绝对路径。此时需要系统的动态载入器来获取该绝对路径。对于elf格式的可执行程序，是由ld-linux.so来完成的，它先后搜索elf文件的DT_RPATH段->环境变量LD_LIBRARY_PATH->/etc/ld.so.cache文件列表->/lib/,/usr/lib目录找到库文件后将其载入内存（不建议使用最后一种方法，因为预置了系统的库文件）

### 修改环境变量的方法

不同目录之间用 : 分隔开

方法一（终端级）：修改当前bash（终端）的环境变量，直接在当前bash中export环境变量

方法二（用户级）：在用户根目录的隐藏文件.bashrc中修改环境变量，在根目录的.bashrc中export环境变量，然后source生效export指令

方法三（系统级）：在系统/etc/profile文件中修改环境变量，export然后再source

### 修改/etc/ld.so.cache

无法直接修改，间接修改通过/etc/ld.so.conf，直接在里面添加环境变量的路径，然后ldconfig。（都在sudo下执行）

## 静态库和动态库的区别

静态库在程序的链接阶段被复制到了程序中；动态库在链接阶段没有被复制到程序中，而实程序在运行时由系统动态加载到内存中供程序调用。

具体而言：

在链接阶段，静态库将被需要的代码链接进去，而动态库只会将一些动态库的信息（比如：名称、地址）链接进去，当程序运行需要的时候再寻找动态库的文件，并把动态库加载到内存中，这样才能使用动态库中的代码。

## 库的好处

1、代码保密；

2、方便部署和分发

## 静态库

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

编译的时候要指定头文件目录和库文件目录、

### 静态库的优缺点

- 优点

  静态库被打包到应用程序中加载速度快

  发布程序无需提供静态库，移植方便

- 缺点

  消耗系统资源，浪费内存

  更新、部署、发布麻烦

  

## 动态库（共享库）

### 命名规则

Linux：libxxx.so	lib：固定前缀	xxx：库的名字	.so：固定后缀	在linux下是一个可执行文件

Windows：libxxx.dll

### 动态库的制作

步骤一：gcc/g++ 编译得到.o文件，得到和位置无关的代码	

gcc -c -fpic/-fPIC xxx.c xxx.c

步骤二：gcc得到动态库

gcc -shared xxx.o xxx.o -o libxxx.so

### 动态库的使用

在程序的源代码中inclue 头文件和调用里面的函数/变量

编译的时候要指定头文件目录和库文件目录

### 动态库优缺点

- 优点

  可以实现进程间资源共享（共享库）

  更新、部署、发布简单

  可以控制何时加载动态库

- 缺点

  加载速度比静态库慢

  发布程序时需要提供依赖的动态库

# Makefile

一个工程中的源文件不计其数，其按类型、功能、模块分别放在若干个目录中，Makefile文件定义了一系列的规则来指定哪些文件需要先编译，哪些文件需要后编译，哪些文件需要重新编译，甚至于进行更复杂的功能操作，因为Makefile文件像一个shell脚本一样，也可以执行操作系统的命令。

## 好处

自动化编译。Makefile一旦写好，只需要一个make命令，整个工程完全自动编译，极大的提高了软件开发的效率。make是一个命令工具，是一个解释Makefile文件中指令的命令工具，一般来说大多数IDE都要这个命令。（Visual C++ : nmake；Linux GNU：make）

## 编写

### 文件命名

makefile 或者Makefile

### 规则

-   一个Makefile文件中可以有一个或者多个规则

    目标…: 依赖…

    ​		命令(shell命令)

    ​		…

    （目标：最终要生成的文件（伪目标除外）；依赖：生成目标所需要的文件或是目标；命令：通过执行命令对依赖操作生成目标（命令前必须tab缩进））

-   其他规则一般都是为第一条规则服务

## 工作原理

-   命令在执行之前，需要检查规则中的依赖是否存在

    如果存在，执行命令

    如果不存在，向下检查其他规则，检查有没有一个规则是用来生成这个依赖的，如果找到了，则执行该规则中的命令

-   检测更新，在执行规则中的命令时，会比较目标和依赖文件的时间

    如果依赖的时间比目标的时间晚，需要重新生成目标

    如果依赖的时间比目标的时间早，目标不需要更新，对应规则中的命令不需要被执行

## 变量

-   自定义变量

    变量名 = 变量值

-   预定义变量

    AR ：归档维护程序的名称，默认值为 ar

    CC ：C编译器的名称，默认值为 cc

    CXX ：C++编译器名称，默认值为 g++

    $自动变量(只能在规则的命令中使用)\begin{cases}\ \$@ ：目标的完整名称 \\ \$< ：第一个依赖文件的名称\\ \$^ ：所有的依赖文件 \end{cases}$

-   获取变量的值

    $(变量名)

## 模式匹配

%：通配符，匹配一个字符串

两个%匹配的是同一个字符串

## 函数

格式：

$(函数名 函数参数…)

例如：

-   $(wildcard PATTERN…)

    功能：获取指定目录下指定类型的文件列表

    参数：PATTERN指的是某个或多个目录下的对应的某种类型的文件，如果有多个目录，一般使用空格间隔

    返回：得到的若干个文件的列表，文件名之间使用空格间隔

    示例：

    $(wildcard \*.c ./sub/\*.c)

    返回格式：a.c b.c c.c d.c e.c f.c

-   $(patsubst \<pattern\>, \<replacement\>,\<text\>)

    功能：查找\<text\>中的单词（单词以“空格”、“tab”或“回车””换行“分隔）是否符合模式\<pattern\>，如果匹配，则以\<replacement\>替换

    \<pattern\>可以包括通配符’%‘，表示任意长度的字符串。如果\<replacement\>中也包含‘%’，那么，\<replacement\>中的这个‘%’将是\<pattern\>中的那个%所代表的字符串。（可以用‘\’来转义，来表示真实含义的‘%’字符)

    返回：函数返回被替换过后的字符串

    示例：

    $(patsubst %.c, %.o, x.c bar.c)

    返回值格式：x.o bar.o

## 伪目标

当不需要生成目标文件时，可将目标文件变成伪目标即可

格式：

.PHONY: 目标

# GDB调试

## GDB

GDB是由GNU软件系统社区提供的调试工具，同GCC配套组成了一套完整的开发环境，GDB是Linux和许多类Unix系统中的标准开发环境

## 功能

1.启动程序，可以按照自定义的要求运行程序

2.可让被调试的程序在所指定的调置的断点处停住（断点可以是条件表达式）

3.当程序被停住时，可以检查此时程序中所发生的事

4.可以改变程序，将一个bug产生的影响修成从而测试其他bug

## 准备工作

通常，在为调试而编译时，我们会关掉编译器的优化选项（‘-o’），并打开调试选项（’-g’）。另外，

‘-wall’在尽量不影响程序行为的情况下选项打开所有warning，也可以发现许多问题，避免不必要的bug。

示例：

gcc -g -Wall progam.c -o progam

‘-g’选项的作用是在可执行文件中加入源代码的信息，比如可执行文件中第几条机器指令对应源代码的第几行，但并不是把整个源文件嵌入到可执行文件中，所以在调试时必须保证gdb能找到源文件

## GDB 命令

-   启动和退出

    gdb 可执行程序

    quit

-   给程序设置参数/获取设置参数

    set args 10 20

    show args

-   查看当前文件代码

    list/l (从默认位置显示)

    list/l 行号 (从指定的行显示)

    list/l 函数名 (从指定的函数显示)

-   查看非当前文件代码

    list/l 文件名：行号

    list/l 文件名：函数名

-   设置显示的行数

    show list/listsize

    set list/listsize 行数

-   gdb使用帮助

    help

-   设置断点

    b/break 行号
    b/break 函数名

    b/break 文件名：行号

    b/break 文件名：函数

-   查看断点

    i/info b/break

-   删除断点

    d/del/delete 断点编号

-   设置断点无效

    dis/disable 断点编号

-   设置断点生效

    ena/enable 断点编号

-   设置条件断点（一般用在循环的位置）

    b/break 断点编号 条件

    示例：

    b/break 10 if i == 5

-   运行GDB程序

    start（程序停在第一行）

    run（遇到断点才停）

-   继续运行，到下一个断电停

    c/continue

-   向下执行一行代码（不会进入函数体）

    n/next

-   变量操作

    p/print 变量名（打印变量值）

    ptype 变量名（打印变量类型）

-   向下单步调试（遇到函数进入函数体）

    s/step

    finish(跳出函数体)

-   自动变量操作

    display num（自动打印指定变量的值）

    i/info display 

    undisplay 编号

-   其他操作

    set var 变量名=变量值

    until（跳出循环）

## 多进程调试

gdb默认只能跟踪一个进程

-   set follow-fork-mode [parent(默认) | child]

    设置调试父进程或者子进程

-   set detach-on-fork [on(默认) | off]

    设置调试模式. on:表示调试当前进程时,其他进程继续运行; off: 其他进程被gdb挂起

-   info inferiors

    查看调试的进程

-   inferiors id

    切换当前调试的进程

-   detach inferiors id

    使进程脱离gdb调试

# C函数

## 文件属性操作函数

-   int access(const char *pathname, int mode)

    判断文件权限或文件是否存在

-   int chmod(const char *filename, int mode)

    修改文件权限

-   int chown(const char *path, uid_t owner, gid_t group)

    修改文件的所有者或者所在组

-   int truncate(const char *path, off_t length)

    缩减或拓展文件的大小

## 目录操作函数

-   int mkdir(const char *pathname, mode_t mode)

    创建目录

-   int rmdir(const char *pathname)

    删除空目录

-   int rename(const char *oldpath, const char *newpath)

    重命名目录

-   int chdir(const char *path)

    修改当前目录的当前路径

-   char *getcwd(char *buf, size_t size)

    获取当前的路径

## 目录遍历函数

-   DIR *opendir(const char *name)

    打开目录

-   struct dirent *readdir(DIR *dirp)

    读取目录

-   int closedir(DIR *dirp)

    关闭目录

## 文件操作符相关函数

-   int dup(int oldfd)

    复制文件描述符

-   int dup2(int oldfd, int newfd)

    重定向文件描述符，即：将newfd重定向至oldfd的指向，该函数的返回值与newfd相同

-   int fcntl(int fd, int cmd, …/\*arg\*/)

    复制文件描述符

    设置/获取文件的状态标志

    cmd：该函数内定义的一些命令宏

    …：可选参数

## exec函数族

(函数族:一系列具有相同或类似功能的函数的统称)

### 作用

根据指定的文件名找到可执行文件,并用它来取代调用进程的内容.

即:在调用进程内部执行一个可执行文件.

exec函数执行成功后不会返回,因为调用进程的实体,包括代码段,数据段,堆栈都被新内容替代(用户数据区),只留下进程ID等一些表面信息保持原样.只有调用失败了,才会返回-1,从原程序的调用点接着往下执行.

-   int execl(const char *path, const char *arg, …/\*(char \*) NULL\*/)

    path:需要指定的执行的文件的路径或者名称

    arg:是可执行文件所需要的参数列表

    ​	第一个参数没什么作用,一般写可执行程序的名称

    ​	第二个参数开始就是程序执行所需要的参数列表

    ​	参数最后需要以NULL结束

    返回值:

    ​	只有调用失败才会返回-1,否则没有返回值

-   int execlp(const char *file, const char *arg, …/\*(char *) NULL\*/)

    [会到环境变量中查找指定的可执行文件,如果找到了就执行,找不到就执行不成功]

    path:需要指定的执行的文件的文件名

    arg:是可执行文件所需要的参数列表

    ​	第一个参数没什么作用,一般写可执行程序的名称

    ​	第二个参数开始就是程序执行所需要的参数列表

    ​	参数最后需要以NULL结束

    返回值:

    ​	只有调用失败才会返回-1,否则没有返回值

-   int execle(const char *path, const char *arg,…/\*(char *) NULL, char *const envp[]\*/)

-   int execv(const char *path, char *const argv[])

-   int execvp(const char *file, char *const argv[])

-   int execvpe(const char *file, char *const argv[], char *const envp[])

-   int execve(const char *filename, char *const argv[], char *const enp[])

    前6个是标准C库的,最后一个是Linux的

    l(list)	参数地址列表,以空指针结尾

    v(vector)	存有各参数地址的指针数组的地址

    p(path)	按PATH环境变量指定的目录搜索可执行文件

    e(environment)	存有环境变量字符串地址的指针数组的地址

# 进程



## 显示进程

-   ps aux / ajx

    查看进程

    a :  显示终端上的所有进程, 包括其他用户进程

    u : 显示进程的详细信息

    x : 显示没有控制终端的进程

    j : 列出与作业控制相关的信息

-   top

    实时显示进程动态

    -d 设置刷新间隔时间

-   kill 

    杀死进程

    kill [-signal] pid	杀死进程

    kill -l 列出所有信号

    kill -9 / -SIGKILL  进程ID	强制杀死进程

    killall name 根据进程名杀死进程

## 显示进程

-   pid_t getpid(void)

    获取当前进程ID

-   pid_t getppid(void)

    获取当前进程的父进程ID

## 进程创建

-   pid_t fork(void)

    创建当前子进程

    返回值: 成功:子进程中返回0,父进程返回子进程ID;失败返回-1

    失败原因:当前系统进程数达到上限(errno:EAGAIN);系统内存不足(errno:ENOMEM)
    
    通过fork()复制当前进程创建出的子进程除了pid不同外,(虚拟地址的)用户区数据和内核区都一样,具体来说(fork是写时拷贝):一开始fork完,用户区资源是共享的(共享同一个空间地址),内核区还是要独立的,但是部分内核区数据一样,只要是只读状态那么用户区资源都是共享的,只有在写入修改的情况下才会开始复制数据(分配新的内存)
    
-   父子进程的区别

    1.fork()的函数返回值不同

    ​	父进程中:>0 返回的子进程ID

    ​	子进程中:=0

    2.pcb中的一些数据不同

    ​	当前进程ID pid

    ​	当前进程的父进程ID pid

    ​	信号集

-   父子进程的共同点

    某些状态下:子进程刚被创建出来,还没执行任何写数据的操作

    ​	用户区数据一样

    ​	文件描述符表一样

    父子进程对变量的共享情况:

    ​	刚开始时,是一样的,共享的.如果修改了数据,不共享了

    ​	(读时共享(没有进行任何写的操作),写时拷贝)

## 进程退出

-   void exit(int status)

    #include<stdlib.h>

    status: 退出时的状态.父进程回收子进程时可以获取

-   void _exit(int status)

    #include<unistd.h>

![image-20220303200239408](https://raw.githubusercontent.com/WinnieVenice/PicBed/main/202203032002638.png)

## 孤儿进程

父进程结束运行,但子进程还在运行(未运行结束),这样的子进程就叫孤儿进程

每当出现一个孤儿进程时,内核就把孤儿进程的父进程设置为init, 而init进程会循环地wait()它的已经退出的子进程.当孤儿进程结束其生命周期时,init进程会回收.

孤儿进程没什么危害

## 僵尸进程

每个进程结束之后,都会释放自己地址空间中的用户区数据,内核区的PCB没有办法自己释放,需要父进程释放.

进程终止时,父进程尚未回收,子进程残留资源(PCB)存放于内核中,变成僵尸进程.

僵尸进程无法被kill -9杀死

-   危害:

    如果父进程不调用wait()或waitpid()的话,那么残留的信息将不会释放,其进程号会一直被占用,但系统的进程号是有限的,如果产生大量的僵尸进程,将因为没有可用的进程号而导致系统不能产生新的进程

