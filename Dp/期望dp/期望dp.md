# 期望dp

## 全期望公式：$E[E(X|Y)]=E(X)$

$$
\begin{align}
E(E(X|Y))&=\sum_{y}{p(Y=y)*E(X|Y=y)}
\\&=\sum_{y}{p(Y=y)*E(X|Y=y))}
\\&=\sum_{y}{p(Y=y)*\left[\sum_{x}{p(X=x|Y=y)*x}\right]}
\\&=\sum_{y}\sum_{x}{p(Y=y)*P(X=x|Y=y)*x}
\\\because条件概率公式:p(X=x,Y=y)&=p(X=x|Y=y)*p(Y=y)=p(Y=y|X=x)*p(X=x)
\\\therefore上式&=\sum_{y}\sum_{x}{p(X=x)*p(Y=y|X=x)*x}
\\&=\sum_{x}{p(X=x)*x*\left[\sum_{y}{p(Y=y|X=x)*1}\right]}
\\&=\sum_{x}{p(X=x)*x}
\\&=E(X)
\end{align}
$$

因此当我们确定某些状态的期望后可以求出别的期望（或者通过某些条件求出概率）



## 期望dp常用方法

