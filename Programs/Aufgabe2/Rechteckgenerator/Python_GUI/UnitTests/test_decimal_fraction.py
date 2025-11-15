"""
    Some unit tests for decimal_fraction.
    Start the test using calling python test_decimal_fraction.py
"""
import unittest
import sys
sys.path.append("../basics")
from decimal_fraction import DecimalFraction


# This function scales a float string, such that it can be compared to an
# DecimalFraction value
def scale(s):
    float(s)  # Basic syntactical check
    s.replace(' ', '').replace('\t', '')
    s = s + ".0" if -1 == s.find('.') else s
    s = s + "0" if s[-1:] == '.' else s
    s = "0" + s if s[0:1] == '.' else s
    s = "-0" + s[1:] if s[0:2] == "-." else s
    s = "0.0" if s == "-0.0" else s
    while len(s) >= 2 and s[-1] == '0' and s[-2] != '.':
        s = s[0:-1]
    return s


class TestDecimalFraction(unittest.TestCase):
    def test_simple_numbers(self):
        for (test, v, erg) in {(1, "0.0", "0.0"), (2, "    0.1   ", "0.1"), (3, "-35", "-35.0"),
                               (4, "0001234567891234567899.12343217689000", "1234567891234567899.12343217689"),
                               (5, "-0001234567891234567899.12343217689000", "-1234567891234567899.12343217689"),
                               (6, ".6", "0.6"), (7, "3.", "3.0"), (8, "-.65", "-0.65"),
                               (9, "4.300", "4.3"), (10, "-0.9", "-0.9"),
                               (11, "4.300e0", "4.3"), (12, "4.300e-0", "4.3"),
                               (13, "-4.300e0", "-4.3"), (14, "-4.300e-0", "-4.3"),
                               (15, "4.300e1", "43.0"), (16, "4.300e-1", "0.43"),
                               (17, "-4.300e1", "-43.0"), (18, "-4.300e-1", "-0.43"),
                               (19, ".300e1", "3.0"), (20, ".300e-1", "0.03"),
                               (21, "-.300e1", "-3.0"), (22, "-.300e-1", "-0.03"),
                               (23, "4.56789123456e18", "4567891234560000000.0"),
                               (24, "4.56789123456e-10", "0.000000000456789123456"),
                               (25, "-4.56789123456e18", "-4567891234560000000.0"),
                               (26, "-4.56789123456e-10", "-0.000000000456789123456")}:
            v1 = DecimalFraction(v)
            self.assertEqual(str(v1), erg, "Test " + str(test) + " failed. Value should be " + erg)
            self.assertEqual(str(v1), erg, "Test " + str(test) + " failed. Value should be " + erg)

    def test_eq(self):
        for (e1, e2, erg) in {("0.0", "0.0", True), ("0.1", "-0.1", False), ("-35.3", "-35.3", True),
                              ("1234567891234567899.12343217689", "1234567891234567899.12343217689", True),
                              ("345678", "34567.8", False),
                              ("-12345123", "-12345123", True), ("3.", "3.0", True), ("-.65", "-0.65", True)}:
            v1, v2 = DecimalFraction(e1), DecimalFraction(e2)
            self.assertEqual(v1 == v2, erg, "Result should be " + str(erg))
            self.assertEqual(v1 == v2, erg, "Result should be " + str(erg))
            self.assertEqual(str(v1), scale(e1), "Result should be " + scale(e1))
            self.assertEqual(str(v2), scale(e2), "Result should be " + scale(e1))

    def test_lt(self):
        for (e1, e2, erg) in {("0.0", "0.0", False), ("-3.1", "3.1", True), ("35.3", "-35.3", False),
                              ("1234567891234567899.12343217689", "1234567891234567899.12343217689", False),
                              ("3456.78", "34567.8", True),
                              ("-12345123.1", "-12345123", True), ("0.2", "0.3", True), ("-.65", "0.65", True)}:
            v1, v2 = DecimalFraction(e1), DecimalFraction(e2)
            self.assertEqual(v1 < v2, erg, "Result should be " + str(erg))
            self.assertEqual(v1 < v2, erg, "Result should be " + str(erg))
            self.assertEqual(str(v1), scale(e1), "Result should be " + scale(e1))
            self.assertEqual(str(v2), scale(e2), "Result should be " + scale(e1))

    def test_other_comp_pos(self):
        e1, e2 = "123.23", "123.23"
        v1, v2 = DecimalFraction(e1), DecimalFraction(e2)
        self.assertEqual(v1 > v2, False, "Result should be False")
        self.assertEqual(v1 >= v2, True, "Result should be True")
        self.assertEqual(v1 <= v2, True, "Result should be True")
        self.assertEqual(str(v1), scale(e1), "Result should be " + scale(e1))
        self.assertEqual(str(v2), scale(e2), "Result should be " + scale(e1))

        e1, e2 = "-123.23", "123.23"
        v1, v2 = DecimalFraction(e1), DecimalFraction(e2)
        self.assertEqual(v1 > v2, False, "Result should be False")
        self.assertEqual(v1 >= v2, False, "Result should be False")
        self.assertEqual(v1 <= v2, True, "Result should be True")
        self.assertEqual(str(v1), scale(e1), "Result should be " + scale(e1))
        self.assertEqual(str(v2), scale(e2), "Result should be " + scale(e1))

        e1, e2 = "-1", "-23.23"
        v1, v2 = DecimalFraction(e1), DecimalFraction(e2)
        self.assertEqual(v1 > v2, True, "Result should be True")
        self.assertEqual(v1 >= v2, True, "Result should be True")
        self.assertEqual(v1 <= v2, False, "Result should be False")
        self.assertEqual(str(v1), scale(e1), "Result should be " + scale(e1))
        self.assertEqual(str(v2), scale(e2), "Result should be " + scale(e1))

    def test_abs(self):
        for (e, erg) in {("0.0", "0.0"), ("-0.1", "0.1"), ("-35.3", "35.3"), ("0", "0.0"), ("-0", "0.0"),
                         ("1234567891234567899.12343217689", "1234567891234567899.12343217689"), ("34567.8", "34567.8"),
                         ("-12345123", "12345123.0"), ("-3.", "3.0"), ("-.65", "0.65"), (".65", "0.65")}:
            v = DecimalFraction(e)
            self.assertEqual(str(abs(v)), erg, "Result should be " + erg)
            self.assertEqual(str(abs(v)), erg, "Result should be " + erg)
            self.assertEqual(str(v), scale(e), "Result should be " + scale(e))

    def test_is_integer(self):
        for (e, erg) in {("0.0", True), ("-0.1", False), ("-35.3", False), ("1323123123123123130", True),
                         ("1234567891234567899.12343217689", False), ("34567.0", True),
                         ("-12345123", True), ("-3.", True), ("-.65", False), ("-23123", True)}:
            v = DecimalFraction(e)
            self.assertEqual(v.is_integer(), erg, "Result should be " + str(erg))
            self.assertEqual(v.is_integer(), erg, "Result should be " + str(erg))
            self.assertEqual(str(v), scale(e), "Result should be " + scale(e))

    def test_add(self):
        for (e1, e2, erg) in {("0.0", "0", "0.0"), ("-0.1", "2", "1.9"), ("3.2", "-4.1", "-0.9"),
                              ("1234567891234567899.12343217689", "-9",  "1234567891234567890.12343217689"),
                              ("34567.0", "0", "34567.0"), ("34567.56", "-0", "34567.56"),  ("-0", "345.56", "345.56"),
                              ("-12345123", "12345123", "0.0"), ("-5", "-0.04", "-5.04"),
                              ("-3.", "0.00004", "-2.99996"), ("65", "35", "100.0")}:
            v1, v2 = DecimalFraction(e1), DecimalFraction(e2)
            self.assertEqual(str(v1 + v2), erg, "Result should be " + str(erg))
            self.assertEqual(str(v2 + v1), erg, "Result should be " + str(erg))
            self.assertEqual(str(v1), scale(e1), "Result should be " + scale(e1))
            self.assertEqual(str(v2), scale(e2), "Result should be " + scale(e1))

    def test_sub(self):
        for (e1, e2, erg) in {("0.0", "3", "-3.0"), ("0.1", "-2", "2.1"), ("3.2", "4.1", "-0.9"),
                              ("1234567891234567899.12343217680", "-9",  "1234567891234567908.1234321768"),
                              ("-88887777567.0", "0", "-88887777567.0"), ("34567.56", "0", "34567.56"),
                              ("-0", "345.56", "-345.56"), ("0", "-0", "0.0"), ("1.25", "0.2", "1.05"),
                              ("-3.", "0.00004", "-3.00004"), ("65", "35", "30.0")}:
            v1, v2 = DecimalFraction(e1), DecimalFraction(e2)
            self.assertEqual(str(v1 - v2), erg, "Result should be " + str(erg))
            self.assertEqual(str(v1 - v2), erg, "Result should be " + str(erg))
            self.assertEqual(str(v1), scale(e1), "Result should be " + scale(e1))
            self.assertEqual(str(v2), scale(e2), "Result should be " + scale(e1))

    def test_mult(self):
        for (no, e1, e2, erg) in {(1, "0.0", "3", "0.0"), (2, "-0.1", "0", "0.0"), (2, "3.2", "-4.1", "-13.12"),
                                  (3, "-3.2", "-4.1", "13.12"), (4, "-3.2", "4.1", "-13.12"),
                                  (5, "1234567891234567899.12343217680", "10", "12345678912345678991.234321768"),
                                  (6, "1234567891234567899.12343217680", "0.01", "12345678912345678.991234321768"),
                                  (7, "123443210091234.1234", "20.0", "2468864201824682.468"),
                                  (8, "0.99", "2.12", "2.0988")}:
            v1, v2 = DecimalFraction(e1), DecimalFraction(e2)
            self.assertEqual(str(v1 * v2), erg, "Test " + str(no) + "a: Result should be " + str(erg))
            self.assertEqual(str(v2 * v1), erg, "Test " + str(no) + "b: Result should be " + str(erg))
            self.assertEqual(str(v1), scale(e1), "Result should be " + scale(e1))
            self.assertEqual(str(v2), scale(e2), "Result should be " + scale(e1))

    def test_mod(self):
        for (no, e1, e2, erg) in {(1, "0.0", "3", "0.0"), (2, "12", "5", "2.0"), (3, "10", "5", "0.0"),
                                  (3, "12345934234234234545", "100", "45.0")}:
            v1, v2 = DecimalFraction(e1), DecimalFraction(e2)
            self.assertEqual(str(v1 % v2), erg, "Test " + str(no) + "a: Result should be " + str(erg))
            self.assertEqual(str(v1 % v2), erg, "Test " + str(no) + "b: Result should be " + str(erg))
            self.assertEqual(str(v1), scale(e1), "Result should be " + scale(e1))
            self.assertEqual(str(v2), scale(e2), "Result should be " + scale(e1))

    def test_truediv(self):
        for (no, e1, e2, erg) in {(1, "0.0", "10", "0.0"), (2, "2.2", "100", "0.022"),
                                  (3, "-332.2", "100", "-3.322"), (4, "-2345.643", "-100", "23.45643"),
                                  (5, "0.349860", "124.95", "0.0028"), (6, "900", "0.9", "1000.0")}:
            v1, v2 = DecimalFraction(e1), DecimalFraction(e2)
            self.assertEqual(str(v1 / v2), erg, "Test " + str(no) + "a: Result should be " + str(erg))
            self.assertEqual(str(v1 / v2), erg, "Test " + str(no) + "b: Result should be " + str(erg))
            self.assertEqual(str(v1), scale(e1), "Result should be " + scale(e1))
            self.assertEqual(str(v2), scale(e2), "Result should be " + scale(e1))

    def test_floor(self):
        for (no, e, erg) in {(1, "0.0", "0.0"), (2, "12.0", "12.0"), (2, "10", "10.0"),
                             (3, "-0.0", "0.0"), (4, "-12.0", "-12.0"), (5, "-100", "-100.0"),
                             (6, "123459342342342345.45",  "123459342342342345.0"),
                             (7, "-123459342342342345.45", "-123459342342342346.0")}:
            v = DecimalFraction(e)
            self.assertEqual(str(v.floor()), erg, "Test " + str(no) + "a: Result should be " + str(erg))
            self.assertEqual(str(v.floor()), erg, "Test " + str(no) + "a: Result should be " + str(erg))
            self.assertEqual(str(v), scale(e), "Result should be " + scale(e))


if __name__ == '__main__':
    unittest.main()
