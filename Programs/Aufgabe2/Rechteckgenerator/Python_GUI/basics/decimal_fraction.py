"""
    This class implements a very simple decimal fraction, that only contains
    the functionality required in this project.
    This class is implemented since float128 is only implemented in a
    64 bit representation on Windows systems. Hence, 2^64 bit floating numbers
    with one decimal place are not displayed exactly.
"""

from __future__ import annotations
import copy
import math


class DecimalFraction:
    @staticmethod
    def __prime_factors(num):
        if num < 0:
            raise ValueError
        prims, factor = [], 2
        while num >= 2:
            if num % factor == 0:
                prims.append(factor)
                num = num // factor
            else:
                factor += 1
        return prims

    def __set(self, numerator, denominator):
        (self._numerator, self._denominator) = (numerator, denominator)
        return self

    # test if self is a valid DecimalFraction
    def __test(self):
        # check valid denominator - must be positive and a power of 10
        tmp = abs(self._denominator)
        while tmp != 0 and tmp % 10 == 0:
            tmp = tmp // 10
        if tmp != 1 or self._denominator <= 0:
            raise ValueError

    def __reduce(self):
        if self._denominator < 0:
            self._numerator, self._denominator,  = self._numerator * -1, self._denominator * -1
        # reduce to decimal fraction
        prims = DecimalFraction.__prime_factors(self._denominator)
        # due to decimal factor : delete 2 * 5 pairs out of prims
        for x in [e for e in [2, 5] for _ in range(min(prims.count(2), prims.count(5)))]:
            prims.remove(x)
        # Each element of prims must be a prime factor of numerator
        div = math.prod(prims)
        if self._numerator % div != 0:
            raise ValueError
        self._numerator, self._denominator = self._numerator // div, self._denominator // div
        self.__test()
        # Shorten to decimal fraction
        sign = -1 if self._numerator < 0 else 1
        self._numerator = abs(self._numerator)
        while self._numerator % 10 == 0 and self._denominator % 10 == 0:
            self.__set(self._numerator // 10, self._denominator // 10)
        self._numerator = sign * self._numerator
        return self

    def __init__(self, float_str):
        float(float_str)  # Checks whether the function is a float
        # extract exponent
        [float_str, expo] = [float_str, "0"] if -1 == float_str.find('e') else float_str.split('e',1)
        [float_str, expo] = [float_str, expo] if -1 == float_str.find('E') else float_str.split('E',1)
        self.__set(0, 1)
        sign = 1 if -1 == float_str.find('-') else -1
        try:
            self._numerator = abs(int(float_str.split('.', 1)[0]))
        except ValueError:
            self._numerator = 0
        frac_part = '' if -1 == float_str.find('.') else float_str.split('.', 1)[1]
        while frac_part != '':
            c, frac_part = frac_part[:1], frac_part[1:]
            if c in set('0123456789'):
                self._denominator = self._denominator * 10
                self._numerator = self._numerator * 10 + (ord(c) - ord('0'))
        self._numerator = sign * self._numerator
        # handle exponent
        expo = int(expo)
        for _ in range(abs(expo)):
            self._numerator = self._numerator * (10 if expo >= 0 else 1)
            self._denominator = self._denominator * (10 if expo < 0 else 1)
        self.__reduce()

    def __str__(self):
        self.__reduce()
        frac, d, tmp = '', 1, abs(self._numerator)
        while d != self._denominator:
            frac = chr(ord('0') + tmp % 10) + frac
            d, tmp = d * 10, tmp // 10
        frac = '.0' if frac == '' else '.' + frac
        sign = '-' if self._numerator < 0 else ''
        return sign + str(abs(self._numerator)//self._denominator) + frac

    def is_integer(self):
        return 1 == self.__reduce()._denominator

    def __eq__(self, other: DecimalFraction):
        self.__test(), other.__test()
        lcm = math.lcm(self._denominator, other._denominator)
        return self._numerator * (lcm//self._denominator) == other._numerator * (lcm//other._denominator)

    def __ne__(self, other):
        return not self.__eq__(other)

    def __lt__(self, other: DecimalFraction):
        self.__test(), other.__test()
        lcm = math.lcm(self._denominator, other._denominator)
        return self._numerator * (lcm // self._denominator) < other._numerator * (lcm // other._denominator)

    def __gt__(self, other: DecimalFraction):
        return self.__ne__(other) and not self.__lt__(other)

    def __le__(self, other: DecimalFraction):
        return self.__eq__(other) or self.__lt__(other)

    def __ge__(self, other: DecimalFraction):
        return self.__eq__(other) or self.__gt__(other)

    def __abs__(self):
        erg = copy.deepcopy(self).__reduce()
        erg._numerator = abs(erg._numerator)
        return erg

    def floor(self):
        erg = copy.deepcopy(self).__reduce()
        if erg.is_integer():
            return erg
        sign = -1 if self._numerator < 0 else 1
        erg._numerator = abs(erg._numerator)
        while erg._denominator != 1:
            erg._numerator = erg._numerator // 10
            erg._denominator = erg._denominator // 10
        erg._numerator = erg._numerator * sign
        if erg._numerator < 0:
            erg._numerator = erg._numerator - 1
        return erg

    def __mul__(self, other: DecimalFraction):
        return copy.deepcopy(self).__set(self._numerator * other._numerator, self._denominator * other._denominator)\
            .__reduce()

    def __truediv__(self, other: DecimalFraction):
        return copy.deepcopy(self).__set(self._numerator * other._denominator, self._denominator * other._numerator)\
            .__reduce()

    def __add__(self, other: DecimalFraction):
        lcm = math.lcm(self._denominator, other._denominator)
        return copy.deepcopy(self).\
            __set(self._numerator * (lcm // self._denominator) + other._numerator * (lcm // other._denominator), lcm).\
            __reduce()

    def __sub__(self, other: DecimalFraction):
        return self + DecimalFraction("-1") * other

    def __mod__(self, other: DecimalFraction):
        if not self.is_integer() or not other.is_integer():
            raise ValueError
        return copy.deepcopy(self).__set(self._numerator % other._numerator, 1)
