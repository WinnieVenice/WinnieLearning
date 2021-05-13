# 约翰逊法-Johnson法则

## 题目

$$
有n件物品,每件物品需要现在工厂A加工a_i时间，完再在工厂B加工b_i时间。
\\每个工厂每次只能加工一件物品，问加工完所有物品的总时间的最小值是多少。
$$

## Johnson法则


$$
\\\begin{align}
\\&记总物品集合S=\{1,2,\dots,n\}。
\\&令N_1=\{i|i\in S,min(a_i,b_{i+1})<min(a_{i+1},b_i)\},N_2=\{i|i\in S,i\notin N_1,a_i<a_{i+1}\}
\\&ans=\rightarrow N_1\rightarrow N_2
\\\end{align}
$$

## 证明

$$
采用交换论证法。
\\假设当前最优解为S=\{s_1,s_2,\dots,s_x,\dots,s_y,\dots,s_n\}。
\\记A_j=\sum_{i=1}^j{a_i}为工厂A加工完前i件物品所花的时间,B_j=max(A_j,B_{j-1})+b_j为工厂B加工完前i间物品所花的时间。
\\假设x<y:
\\先加工s_x：B_x=max(A_k+a_x,B_k)+b_x;先加工s_y:B_y=max(A_k+a_y,B_k)+b_y,则:
\\\begin{align}
\\&\begin{cases} B_{x\rightarrow y}&=max(A_k+a_x+a_y,max(A_k+a_x,B_k)+b_x)+b_y
\\B_{y\rightarrow x}&=max(A_k+a_y+a_x,max(A_k+a_y,B_k)+b_y)+b_x
\\\end{cases}
\\\Rightarrow&\begin{cases} B_{x\rightarrow y}&=max(A_k+a_x+a_y+b_y,A_k+a_x+b_x+b_y,B_k+b_x+b_y)
\\B_{y\rightarrow x}&=max(A_k+a_y+a_x+b_x,A_k+a_y+b_y+b_x,B_k+b_y+b_x)\end{cases}
\\\Rightarrow&\begin{cases} B_{x\rightarrow y}&=max(A_k+a_x+a_y+b_y,A_k+a_x+b_x+b_y,B_k+b_y+b_x)
\\B_{y\rightarrow x}&=max(A_k+a_y+a_x+b_x,A_k+a_y+b_y+b_x,B_k+b_y+b_x)\end{cases}
\\\Rightarrow&\begin{cases} B_{x\rightarrow y}&=max(A_k+a_x+b_y+max(a_y,b_x),B_k+b_x+b_y)
\\B_{y\rightarrow x}&=max(A_k+a_y+b_x+max(a_x,b_y),B_k+b_x+b_y)\end{cases} 
\\\end{align}
\\假设B_{x\rightarrow y}>B_{y\rightarrow x},则:
\\B_{x\rightarrow y}>B_{y\rightarrow x}
\\A_k+a_x+b_y+max(a_y,b_x)>A_k+a_y+b_x+max(a_x,b_y)
\\a_x+b_y+max(a_y,b_x)>a_y+b_x+max(a_x,b_y)
\\a_x+b_y-max(a_x,b_y)>a_y+b_x-max(a_y,b_x)
\\min(a_x,b_y)>min(a_y,b_x)
\\(注意)事实上当B_{x\rightarrow y}=B_{y\rightarrow x}时,min(a_x,b_y)=min(a_y,b_x)或B_{x\rightarrow y}=B_{y\rightarrow x}=B_k+b_x+b_y。
\\当时取等是情况2的时候:
\\因为B_{y\rightarrow x}=max(A_k+a_x+a_y+b_x,A_k+a_y+b_y+b_x,B_k+b_x+b_y)
\\所以有B_k\geq A_k+max(a_y,a_x),b_y\geq a_x,b_x\geq a_y
\\故min(a_y,b_x)=a_y,min(a_x,b_y)=a_x
\\此时若不考虑B_k+b_x+b_y对B_{x\rightarrow y},B_{y\rightarrow x}的影响,则x,y的先后序取决于a_x,a_y
\\又因为B_i=max(A_i,B_{i-1})+b_i有传递性,所以取等时要考虑a_x,a_y。
\\具体来说,两次贪心,分别考虑s_x,s_y,s_k
\\若s_x,s_y在a_x<a_y时不交换,则第二次贪心是s_y,s_k;若交换了则是s_x,s_k
\\不难知道可以构造一组数据来hack掉不交换的情况
\\故当两者相等时还要按a_x,a_y从小到大排序
$$

## 结论

$$
若min(a_x,b_y)<(>)min(a_y,b_x),则:x\rightarrow(\leftarrow) y
\\取等时,若a_x<(>)a_y,则:x\rightarrow(\leftarrow) y
$$

