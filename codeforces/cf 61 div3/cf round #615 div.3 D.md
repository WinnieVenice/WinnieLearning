# cf round #615 div.3-D:数论 

## 题意

维护一个序列当前的最小未出现的非负整数(记为MEX),该序列一开始为
空有q次访问,每次访问向当前序列添加一个元素Yj,每次访问都需要输出当前
的MEX,现在你有一种操作,对于给定的整数x,你可以选择序列中任意元素ai使
其ai=ai-x或ai=ai+x,如果你有无限次操作,那么请问每次访问时最大的MEX是
多少.

## 分析

由于,对于每个元素我们有无限次操作,$a_i\geq a_i+k*x$ (k为整数,$a_i+k*x\geq0$).也就是说,$a_i$的个数允许的时候$a_i\leftrightarrow a_i+k*x$,逆向思维一下,也满足$a_i+k*x\leftrightarrow a_i$
也就是说我们可以把$a_i+k*x$记为一个集合$\{a_i\}$,那么$|a_i|$就是$a_i$这种类型的数
的次数.那么我们应该如何考虑记录怎么样的ai呢?显然,当$k<0,a_i+k*x$变小,
我们可以选择记录最小的数类似于定义原始数(即:最靠近0的$a_i+k*x$),而其他
数都是由它衍生出来的.如何快速得到一个数的原始数呢,显然我们会考虑到%x.即:一个数p,p%x就是它的原始数(这里显然其实就是x的完全剩余系).根据MEX的定义,实际上MEX的值就在x的完全剩余系里循环,直到某个值的次数为0则就是当前的MEX值. 



