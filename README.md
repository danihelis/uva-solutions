# UVa Solutions

An archive of personal solutions for competitive programming contests from [UVa
Online Judge](https://onlinejudge.org/). You can check my progress on
[uHunt](https://uhunt.onlinejudge.org/id/401345), under the pseudonym account
`schreiber`.

While studying how to solve these programming challenges, I created some notes
with reusable code and solutions to general problems. You can check these notes
along with some explanation in [my repository of
algorithms](https://danihelis.github.io/algorithms/).


### Compiling the code

All code is written in ANSI C, with very rare exceptions when I needed a higher
precision register for math operations. They were all compiled using `gcc` with
the following parameters:

```
gcc -pipe -ansi -pedantic -Wall -O2 {input} -o {output} -lm -lcrypt
```

(When I submit a solution to UVa Online Judge, however, I choose a C++ 11
compiler, since it produces better optimized and faster executables. It seems to
be a peculiarity of the submission system.)
