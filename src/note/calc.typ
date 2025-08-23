= 导数积分
#box(
  height: auto,
  [
    #set par(spacing: 0.5em)
    #set text(size: 0.9em)
    #columns(
      3,
      [
        $ (u / v)' = (u' v - u v') / v^2 $
        $ (a^x)' = (ln a) a^x $
        $ (tan x)' = sec^2 x $
        $ (cot x)' = csc^2 x $
        $ (sec x)' = tan x sec x $
        $ (csc x)' = - cot x csc x $
        $ (arcsin x)' = 1 / sqrt(1-x^2) $
        $ (arccos x)' = - 1 / sqrt(1-x^2) $
        #colbreak()
        $ (arctan x)' = 1 / (1+x^2) $
        $ (op("arccot") x)' = - 1 / (1+x^2) $
        $ (op("arccsc") x)' = -1 / (x sqrt(1-x^2)) $
        $ (op("arcsec") x)' = 1 / (x sqrt(1-x^2)) $
        $ (tanh x)' = sech^2 x $
        $ (coth x)' = -csch^2 x $
        $(sech x)' = -sech x tanh x$
        $(csch x)' = -csch x coth x$
        #colbreak()
        $ (op("arcsinh") x)' = 1 / sqrt(1+x^2) $
        $ (op("arccosh") x)' = 1 / sqrt(x^2-1) $
        $ (op("arctanh") x)' = 1 / (1-x^2) $
        $ (op("arccoth") x)' = 1 / (x^2-1) $
        $ (op("arccsch") x)' = -1 / (|x| sqrt(1+x^2)) $
        $ (op("arcsech") x)' = -1 / (x sqrt(1-x^2)) $

      ],
    )
  ],
)

#show math.cases: it => {
  math.display(it)
}

== $a x^2 + b x + c$ ($a > 0$)
+ $integral frac(dif x, a x^2 + b x + c) = cases(
    2 / sqrt(4 a c - b^2) arctan frac(2 a x + b, sqrt(4 a c - b^2)) + C & (b^2 < 4 a c),
    1 / sqrt(b^2 - 4 a c) ln lr(|frac(2 a x + b - sqrt(b^2 - 4 a c), 2 a x + b + sqrt(b^2 - 4 a c))|) + C & (b^2 > 4 a c)
  )$
+ $integral frac(x, a x^2 + b x + c) dif x = frac(1, 2 a) ln | a x^2 + b x + c | - frac(b, 2 a) integral frac(dif x, a x^2 + b x + c)$

== $sqrt(plus.minus a x^2 + b x + c)$ ($a > 0$)
+ $integral frac(dif x, sqrt(a x^2 + b x + c)) = 1 / sqrt(a) ln | 2 a x + b + 2 sqrt(a) sqrt(a x^2 + b x + c) | + C$
+ $integral sqrt(a x^2 + b x + c) dif x = frac(2 a x + b, 4 a) sqrt(a x^2 + b x + c) + frac(4 a c - b^2, 8 sqrt(a^3)) ln | 2 a x + b + 2 sqrt(a) sqrt(a x^2 + b x + c) | + C$
+ $integral x / sqrt(a x^2 + b x + c) dif x = 1 / a sqrt(a x^2 + b x + c) - frac(b, 2 sqrt(a^3)) ln | 2 a x + b + 2 sqrt(a) sqrt(a x^2 + b x + c) | + C$
+ $integral frac(dif x, sqrt(c + b x - a x^2)) = - 1 / sqrt(a) arcsin frac(2 a x - b, sqrt(b^2 + 4 a c)) + C$
+ $integral sqrt(c + b x - a x^2) dif x = frac(2 a x - b, 4 a) sqrt(c + b x - a x^2) + frac(b^2 + 4 a c, 8 sqrt(a^3)) arcsin frac(2 a x - b, sqrt(b^2 + 4 a c)) + C$
+ $integral x / sqrt(c + b x - a x^2) dif x = - 1 / a sqrt(c + b x - a x^2) + frac(b, 2 sqrt(a^3)) arcsin frac(2 a x - b, sqrt(b^2 + 4 a c)) + C$

== $sqrt(plus.minus frac(x - a, x - b))$ 或 $sqrt((x - a) (x - b))$
+ $integral frac(dif x, sqrt((x - a) (b - x))) = 2 arcsin √frac(x - a, b - x) + C$
  ($a < b$)
+ $integral sqrt((x - a) (b - x)) dif x = frac(2 x - a - b, 4) sqrt((x - a) (b - x)) + frac((b - a)^2, 4) arcsin √frac(x - a, b - x) + C , (a < b)$

== 三角函数的积分
+ $integral tan x dif x = - ln | cos x | + C$
+ $integral cot x dif x = ln | sin x | + C$
+ $integral sec x dif x = ln lr(|tan (pi / 4 + x / 2)|) + C = ln | sec x + tan x | + C$
+ $integral csc x dif x = ln lr(|tan x / 2|) + C = ln | csc x - cot x | + C$
+ $integral sec^2 x dif x = tan x + C$
+ $integral csc^2 x dif x = - cot x + C$
+ $integral sec x tan x dif x = sec x + C$
+ $integral csc x cot x dif x = - csc x + C$
+ $integral sin^2 x dif x = x / 2 - 1 / 4 sin 2 x + C$
+ $integral cos^2 x dif x = x / 2 + 1 / 4 sin 2 x + C$
+ $integral sin^n x dif x = - 1 / n sin^(n - 1) x cos x + frac(n - 1, n) integral sin^(n - 2) x dif x$
+ $integral cos^n x dif x = 1 / n cos^(n - 1) x sin x + frac(n - 1, n) integral cos^(n - 2) x dif x$
+ $integral frac(dif x, sin^n x) = - frac(1, n - 1) frac(cos x, sin^(n - 1) x) + frac(n - 2, n - 1) integral frac(dif x, sin^(n - 2) x)$
+ $integral frac(dif x, cos^n x) = frac(1, n - 1) frac(sin x, cos^(n - 1) x) + frac(n - 2, n - 1) integral frac(dif x, cos^(n - 2) x)$
+ $&integral cos^m x sin^n x dif x \
    & = frac(1, m + n) cos^(m - 1) x sin^(n + 1) x + frac(m - 1, m + n) integral cos^(m - 2) x sin^n x dif x \
    & = - frac(1, m + n) cos^(m + 1) x sin^(n - 1) x + frac(n - 1, m + 1) integral cos^m x sin^(n - 2) x dif x$
+ $integral frac(dif x, a + b sin x) = cases(
    2 / sqrt(a^2 - b^2) arctan frac(a tan x / 2 + b, sqrt(a^2 - b^2)) + C & (a^2 > b^2 ),
    1 / sqrt(b^2 - a^2) ln lr(|frac(a tan x / 2 + b - sqrt(b^2 - a^2), a tan x / 2 + b + sqrt(b^2 - a^2))|) + C & (a^2 < b^2 )
  )$
+ $integral frac(dif x, a + b cos x) = cases(
    frac(2, a + b) √frac(a + b, a - b) arctan (√frac(a - b, a + b) tan x / 2) + C & (a^2 > b^2 ),
    frac(1, a + b) √frac(a + b, a - b) ln lr(|frac(tan x / 2 + √frac(a + b, b - a), tan x / 2 - √frac(a + b, b - a))|) + C & (a^2 < b^2 )
  )$
+ $integral frac(dif x, a^2 cos^2 x + b^2 sin^2 x) = frac(1, a b) arctan (b / a tan x) + C$
+ $integral frac(dif x, a^2 cos^2 x - b^2 sin^2 x) = frac(1, 2 a b) ln lr(|frac(b tan x + a, b tan x - a)|) + C$
+ $integral x sin a x dif x = 1 / a^2 sin a x - 1 / a x cos a x + C$
+ $integral x^2 sin a x dif x = - 1 / a x^2 cos a x + 2 / a^2 x sin a x + 2 / a^3 cos a x + C$
+ $integral x cos a x dif x = 1 / a^2 cos a x + 1 / a x sin a x + C$
+ $integral x^2 cos a x dif x = 1 / a x^2 sin a x + 2 / a^2 x cos a x - 2 / a^3 sin a x + C$

== 反三角函数的积分 (其中 $a > 0$ )
+ $integral arcsin x / a dif x = x arcsin x / a + sqrt(a^2 - x^2) + C$
+ $integral x arcsin x / a dif x = (x^2 / 2 - a^2 / 4) arcsin x / a + x / 4 sqrt(x^2 - x^2) + C$
+ $integral x^2 arcsin x / a dif x = x^3 / 3 arcsin x / a + 1 / 9 (x^2 + 2 a^2) sqrt(a^2 - x^2) + C$
+ $integral arccos x / a dif x = x med a r c c o s x / a - sqrt(a^2 - x^2) + C$
+ $integral x arccos x / a dif x = (x^2 / 2 - a^2 / 4) arccos x / a - x / 4 sqrt(a^2 - x^2) + C$
+ $integral x^2 arccos x / a dif x = x^3 / 3 arccos x / a - 1 / 9 (x^2 + 2 a^2) sqrt(a^2 - x^2) + C$
+ $integral arctan x / a dif x = x arctan x / a - a / 2 ln (a^2 + x^2) + C$
+ $integral x arctan x / a dif x = 1 / 2 (a^2 + x^2) arctan x / a - a / 2 x + C$
+ $integral x^2 arctan x / a dif x = x^3 / 3 arctan x / a - a / 6 x^2 + a^3 / 6 ln (a^2 + x^2) + C$

== 指数函数的积分
+ $integral a^x dif x = frac(1, ln a) a^x + C$
+ $integral e^(a x) dif x = 1 / a a^(a x) + C$
+ $integral x e^(a x) dif x = 1 / a^2 (a x - 1) a^(a x) + C$
+ $integral x^n e^(a x) dif x = 1 / a x^n e^(a x) - n / a integral x^(n - 1) e^(a x) dif x$
+ $integral x a^x dif x = frac(x, ln a) a^x - frac(1, (ln a)^2) a^x + C$
+ $integral x^n a^x dif x = frac(1, ln a) x^n a^x - frac(n, ln a) integral x^(n - 1) a^x dif x$
+ $integral e^(a x) sin b x dif x = frac(1, a^2 + b^2) e^(a x) (a sin b x - b cos b x) + C$
+ $integral e^(a x) cos b x dif x = frac(1, a^2 + b^2) e^(a x) (b sin b x + a cos b x) + C$
+ $integral e^(a x) sin^n b x dif x = frac(1, a^2 + b^2 n^2) e^(a x) sin^(n - 1) b x (a sin b x - n b cos b x) + frac(n (n - 1) b^2, a^2 + b^2 n^2) integral e^(a x) sin^(n - 2) b x dif x$
+ $integral e^(a x) cos^n b x dif x = frac(1, a^2 + b^2 n^2) e^(a x) cos^(n - 1) b x (a cos b x + n b sin b x) + frac(n (n - 1) b^2, a^2 + b^2 n^2) integral e^(a x) cos^(n - 2) b x dif x$

== 对数函数的积分
+ $integral ln x dif x = x ln x - x + C$
+ $integral frac(dif x, x ln x) = ln | ln x | + C$
+ $integral x^n ln x dif x = frac(1, n + 1) x^(n + 1) (ln x - frac(1, n + 1)) + C$
+ $integral (ln x)^n dif x = x (ln x)^n - n integral (ln x)^(n - 1) dif x$
+ $integral x^m (ln x)^n dif x = frac(1, m + 1) x^(m + 1) (ln x)^n - frac(n, m + 1) integral x^m (ln x)^(n - 1) dif x$

== STL 积分/求和 (need `std::`)
+ $integral_0^1 t^(x - 1) (1 - t)^(y - 1) dif t = mono("beta(x, y)") = frac(Gamma (x) Gamma (y), Gamma (x + y))$
+ $integral_0^(+ oo) t^("num" - 1) e^(- t) dif t = mono("tgamma(num)") = e^(mono("lgamma(num)")) = Gamma ("num")$
+ $integral_0^(phi) frac(dif theta, sqrt(1 - k^2 sin^2 theta)) = mono("ellint_1(k, phi)")$
+ $integral_0^(phi) sqrt(1 - k^2 sin^2 theta) dif theta = mono("ellint_ 2(k , phi)")$
+ $integral_("num")^(+ oo) e^(- t) / t dif t = - mono("expint(-num)")$
+ $sum_(n = 1)^(+ oo) n^(- "num") = mono("riemann_zeta(num)")$
+ $2 / sqrt(pi) integral_0^("arg") e^(- t^2) dif t = mono("erf(arg)")$
