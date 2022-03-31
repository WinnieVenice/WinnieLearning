# Max Min Query

## Description

SemonCC有一个整数数组$\{ a_1, a_2, \cdots, a_n \}$，他想知道下面的式子的结果是多少：

$ \sum_{i=l}^{r}\sum_{j=i}^{r} \min(a_i, a_{i+1}, \cdots, a_j)\cdot{\max(a_i, a_{i+1},\cdots,a_j)} $

是的，懒鬼SemonCC并不想自己做，于是他把问题丢给了你。

## Input Format

第一行为一个整数$n, m$，表示数组长度和SemonCC的问题个数。
第二行为数组${ a_1, a_2, \cdots, a_n }$
接下来$m$行，每行两个整数$l_i, r_i$，即SemonCC的问题。

## Output Format

共$m$行，每行一个整数，为问题的答案。
考虑到答案可能非常大，你需要输出答案模$998244353$的结果。

## Limits

TL: 2s(?), ML: ?
$$ 1 \leq n \leq 5\cdot{10^{5}}, 0 \leq a_i < 998244353 $$
$$ 1 \leq q \leq 5\cdot{10^{5}}, 1 \leq l \leq r \leq n $$

