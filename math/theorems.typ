=== Combinatoria

==== General
- $sum_(k=0)^n binom(n-k, k) = "Fib"_(n+1)$
- $binom(n, k) = binom(n, n-k)$
- $binom(n, k) + binom(n, k+1) = binom(n+1, k+1)$
- $k binom(n, k) = n binom(n-1, k-1)$
- $sum_(i=0)^n binom(n, i) = 2^n$

*Identidad de Vandermonde:*
$ sum_(k=0)^r binom(m, k) binom(n, r-k) = binom(m+n, r) $

*Identidad del Palo de Hockey (Hockey-Stick):*
$ sum_(i=r)^n binom(i, r) = binom(n+1, r+1) $

==== Triángulo de Pascal
- En una fila $p$ donde $p$ es un número primo, todos los términos en esa fila excepto los unos son múltiplos de $p$.
- *Teorema de Kummer*: Para enteros $n >= m >= 0$ y un número primo $p$, la mayor potencia de $p$ que divide a $binom(n, m)$ es igual al número de acarreos cuando $m$ se suma a $n-m$ en base $p$.

==== Números de Catalan
- Fórmula general: $C_n = 1/(n+1) binom(2n, n)$
- Recurrencia: $C_0 = 1, C_1 = 1$ y $C_n = sum_(k=0)^(n-1) C_k C_(n-1-k)$
Representa, entre otras cosas, el número de secuencias de paréntesis balanceadas o triangulaciones de un polígono convexo.

==== Números de Stirling (Primera y Segunda Especie)
- *Primera especie* (número de permutaciones con $k$ ciclos disjuntos): \
  $S(n, k) = (n-1) dot S(n-1, k) + S(n-1, k-1)$
- *Segunda especie* (maneras de particionar un conjunto de $n$ objetos en $k$ subconjuntos no vacíos): \
  $S(n, k) = k dot S(n-1, k) + S(n-1, k-1)$

==== Números de Bell
Cuenta el número total de particiones posibles de un conjunto.
$ B_(n+1) = sum_(k=0)^n binom(n, k) dot B_k $


=== Matemáticas

==== Fórmulas Generales
- $a^k - b^k = (a-b) dot (a^(k-1)b^0 + a^(k-2)b^1 + ... + a^0 b^(k-1))$
- $|a-b| + |b-c| + |c-a| = 2(max(a, b, c) - min(a, b, c))$

*Identidad de Lagrange:*
$ (sum_(k=1)^n a_k^2)(sum_(k=1)^n b_k^2) - (sum_(k=1)^n a_k b_k)^2 = \
   1/2 sum_(i=1)^n sum_(j=1)^n (a_i b_j - a_j b_i)^2 $

==== Fórmulas de Vieta
Para un polinomio de grado $n$: $p(x) = a_n x^n + a_(n-1) x^(n-1) + ... + a_0$ con raíces $r_1, r_2, ..., r_n$:
- $r_1 + r_2 + ... + r_n = - a_(n-1) / a_n$
- $r_1 r_2 ... r_n = (-1)^n a_0 / a_n$

==== Sucesión de Fibonacci
- $F_n = sum_(k=0)^floor((n-1)/2) binom(n-k-1, k)$
- *Fórmula de Binet:* $F_n = 1/sqrt(5) (((1+sqrt(5))/2)^n - ((1-sqrt(5))/2)^n)$
- $sum_(i=1)^n F_i = F_(n+2) - 1$
- $gcd(F_m, F_n) = F_(gcd(m, n))$

==== Ternas Pitagóricas
Fórmula de Euclides para generar ternas donde $a^2 + b^2 = c^2$:
Para $m > n > 0$:
$ a = m^2 - n^2, quad b = 2m n, quad c = m^2 + n^2 $


=== Teoría de Números

==== Función Totiente de Euler ($phi$)
- $phi(n) = n product_(p | n) (1 - 1/p)$ donde $p$ son factores primos distintos.
- Si $a$ y $b$ son coprimos, entonces $phi(a dot b) = phi(a) dot phi(b)$
- $sum_(d | n) phi(d) = n$

==== Función e Inversión de Möbius
$mu(n)$ toma valores en $\{-1, 0, 1\}$:
- $1$ si es libre de cuadrados con cantidad par de factores primos.
- $-1$ si es libre de cuadrados con cantidad impar de factores primos.
- $0$ si contiene algún factor primo al cuadrado.

*Teorema de inversión de Möbius:* Si $g(n) = sum_(d | n) f(d)$, entonces:
$ f(n) = sum_(d | n) mu(d) g(n/d) $

==== MCD (GCD) y MCM (LCM)
- $gcd(a, b) dot "lcm"(a, b) = |a dot b|$
- $gcd(a, "lcm"(b, c)) = "lcm"(gcd(a, b), gcd(a, c))$
- $sum_(k=1)^n gcd(k, n) = sum_(d | n) d dot phi(n/d)$


=== Operaciones de Bits (Bitwise) y Miscelánea
- $a + b = (a plus.circle b) + 2(a "AND" b)$
- $a + b = (a | b) + (a "AND" b)$
- El $k$-ésimo bit está encendido en $x$ si y solo si $x mod 2^k >= 2^(k-1)$.
- $1 plus.circle 2 plus.circle 3 plus.circle ... plus.circle (4k-1) = 0$ para todo $k >= 0$.

==== Teorema de Erdős–Gallai
Una secuencia descendente de grados $d_1 >= d_2 >= ... >= d_n$ puede representar un grafo simple finito si la suma total de grados es par y:
$ sum_(i=1)^k d_i <= k(k-1) + sum_(i=k+1)^n min(d_i, k) \
  quad text("para cada ") 1 <= k <= n $