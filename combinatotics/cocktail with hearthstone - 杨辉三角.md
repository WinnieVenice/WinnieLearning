# cocktail with hearthstone - 杨辉三角

## 题意

$$
\\\begin{align}
\\&有2^{n + m}个人参加比赛,每个人都有输赢状态(a,b),即:当前赢了a场,输了b场，初始状态都为(0, 0).
\\&每场比赛由两个具有相同(a,b)状态的人组成,每场比赛没有平局,即:有一个变成(a+1, b),另一个变成(a, b + 1).
\\&每个人退出参赛的条件是其a = n或b = m.
\\&q次询问,每次询问以(a,b)退出参赛的人有多少个,其中a = n 或 b = m.
\\& n, m, q\in[1, 2 * 10^5],确保每个未退赛的人都有比赛参加
\\\end{align}
$$

## 分析

$$
\\\begin{align}
\\&不难知道对于f(a, b) = f(a - 1, b) / 2 + f(a, b - 1) / 2	
\\&但是因为2^{n + m}太大了,所以dp不了,尝试下找规律.
\\&先画图模拟一下:
\\
\\\end{align}
$$

![image-20210611163422711](C:\Users\WinnieVenice\AppData\Roaming\Typora\typora-user-images\image-20210611163422711.png)
$$
\\\begin{align}
\\&显然每次询问就是询问这个图上的某个节点.
\\&不难联想到这图和杨辉三角很像,尝试把杨辉三角运用进来,因为杨辉三角我们显然能直接求出每个节点的值
\\&考虑下杨辉三角的定义：
\\\end{align}
$$
![image-20210611171856341](C:\Users\WinnieVenice\AppData\Roaming\Typora\typora-user-images\image-20210611171856341.png)
$$
\\\begin{align}
\\&不难发现,a、b的幂次就是对应的状态(x,y),即:选择x场赢,选择y场输,a^x*b^y\Leftrightarrow (x,y)
\\&则:每个节点的含义不难理解为,比赛了x+y场,输x场的贡献有C_{x + y}^x,那么如果有\lambda个人参加,则该节点的答案就是=\lambda*C_{x + y}^x
\\&或者说不考虑参与人数的情况下,那么题目的图等价于杨辉三角的图
\\&因此我们可以直接求出题目的图莉的每个节点,具体而言,对于f(a + b) = C_{a + b}^a*2^{n + m - (a + b)}
\\&注意到询问是(n, b)或者(a, m), 因为状态转移的时候f(n, b) \leftarrow f(n - 1, b) + f(n, b - 1),根据题目条件发现,f(n, b - 1)已经结束了,所以对f(n, b)没有贡献。
\\&所以求f(n, b) = f(n - 1, b) / 2, f(a, m) = f(a, m - 1) / 2
\\\end{align}
$$
