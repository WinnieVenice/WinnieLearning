# 约翰逊法-Johnson法则

## 题目

$$
有n件物品,每件物品需要现在工厂A加工a_i时间，完再在工厂B加工b_i时间。
\\每个工厂每次只能加工一件物品，问加工完所有物品的总时间的最小值是多少。
$$

## Johnson法则


$$
\\\begin{align}
\\&令N_1=\{i|a_i<b_i,a_i<a_{i+1}\},N_2=\{i|a_i\geq b_i,b_i>b_{i+1}\}
\\&ans=N_1\rightarrow N_2
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
\\\Rightarrow&\begin{cases} B_{x\rightarrow y}&=max(A_k+a_x+a_y+b_y,A_k+a_x+b_x+b_y)
\\B_{y\rightarrow x}&=max(A_k+a_y+a_x+b_x,A_k+a_y+b_y+b_x)\end{cases}
\\\Rightarrow&\begin{cases} B_{x\rightarrow y}&=A_k+a_x+b_y+max(a_y,b_x)
\\B_{y\rightarrow x}&=A_k+a_y+b_x+max(a_x,b_y)\end{cases} 
\\\end{align}
\\假设B_{x\rightarrow y}>B_{y\rightarrow x},则:
\\B_{x\rightarrow y}>B_{y\rightarrow x}
\\A_k+a_x+b_y+max(a_y,b_x)>A_k+a_y+b_x+max(a_x,b_y)
\\a_x+b_y+max(a_y,b_x)>a_y+b_x+max(a_x,b_y)
\\a_x+b_y-max(a_x,b_y)>a_y+b_x-max(a_y,b_x)
\\min(a_x,b_y)>min(a_y,b_x)
\\(注意)事实上当min(a_x,b_y)=min(a_y,b_x)的时候并不等价,
$$

