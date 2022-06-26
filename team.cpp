// fuck C++98
#include <stddef.h>
#include <stdint.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using std::max;

using std::cin;
using std::cout;
using std::endl;
using std::ostream;

using std::vector;

class BigInt {
  // 0 if positive or zero, and 1 if negative
  bool sign;
  // `32*mag.size()` bit unsigned integer, splitted into 32-bit chunks.
  // Lower chunks are in the front, i.e. little endian.
  // Make sure there is not any leading chunk of 0's.
  // When the value is 0, the vector is empty.
  vector<uint32_t> mag;

  typedef vector<uint32_t> vec;
  typedef vector<uint32_t>::iterator iter;
  typedef vector<uint32_t>::reverse_iterator rev_iter;

public:
  inline BigInt(bool sign, vector<uint32_t> mag) : sign(sign), mag(mag) {}
  inline BigInt(int32_t value = 0) : sign(value < 0) {
    if (value != 0) mag.push_back(sign ? uint32_t(-value) : uint32_t(value));
  }

  inline bool get_sign() const { return sign; }
  inline const vector<uint32_t>& get_mag() const { return mag; }
  inline bool is_zero() const { return mag.empty(); }

// *** add & minus

private:
  // require `rhs > 0`
  void mag_add(const BigInt &rhs) {
    mag.resize(max(mag.size(), rhs.mag.size()) + 1);
    size_t i = 0;
    while (rhs.mag[i] == 0) i++;
    uint32_t carry = 0;
    uint32_t tmp;
    for (; i < rhs.mag.size(); i++) {
      mag[i] += rhs.mag[i];
      tmp = mag[i] < rhs.mag[i];
      mag[i] += carry;
      carry = tmp || mag[i] < carry;
    }
    // the mag must have at least 1 zero chunk at back
    // so no need to check `i < size()`
    if (carry) {
      for (; mag[i] == 0xffffffff; i++) mag[i] = 0;
      mag[i]++;
    }
    if (mag.back() == 0) mag.pop_back();
  }
  // requires `lhs >= rhs > 0`
  void mag_minus(const BigInt &rhs) {
    size_t i = 0;
    while (rhs.mag[i] == 0) i++;
    uint32_t borrow = 0;
    uint32_t tmp;
    for (; i < rhs.mag.size(); i++) {
      tmp = mag[i];
      mag[i] -= rhs.mag[i];
      tmp = mag[i] > tmp;
      mag[i] -= borrow;
      borrow = tmp || (borrow && mag[i] == 0xffffffff);
    }
    if (borrow) {
      for (; mag[i] == 0; i++) mag[i] = 0xffffffff;
      mag[i]--;
    }
    while (mag.back() == 0) mag.pop_back();
  }
  // requires `0 < lhs <= rhs`
  void mag_rev_minus(const BigInt &rhs) {
    const size_t size = mag.size();
    mag.resize(rhs.mag.size());
    size_t i = 0;
    while (mag[i] == 0) i++;
    uint32_t borrow = 0;
    uint32_t tmp;
    for (; i < size; i++) {
      mag[i] = rhs.mag[i] - mag[i];
      tmp = mag[i] > rhs.mag[i];
      mag[i] -= borrow;
      borrow = tmp || (borrow && mag[i] == 0xffffffff);
    }
    if (borrow) {
      for (; rhs.mag[i] == 0; i++) mag[i] = 0xffffffff;
      mag[i] = rhs.mag[i] - 1;
      i++;
    }
    for (; i < rhs.mag.size(); i++) mag[i] = rhs.mag[i];
    sign = !sign;
    while (!mag.empty() && mag.back() == 0) mag.pop_back();
    if (mag.empty()) sign = false;
  }
  // requires not both are 0
  bool mag_gt(const BigInt &rhs) {
    if (mag.size() > rhs.mag.size()) return true;
    if (mag.size() < rhs.mag.size()) return false;
    for (size_t i = mag.size() - 1; i != 0; i--)
      if (mag[i] > rhs.mag[i]) return true;
      else if (mag[i] < rhs.mag[i]) return false;
    return mag[0] > rhs.mag[0];
  }

public:
  inline BigInt& negate() {
    sign = !sign;
    return *this;
  }

  inline BigInt& operator+=(const BigInt &rhs) {
    if (rhs.is_zero()) return *this;
    if (is_zero()) return *this = rhs;
    if (sign == rhs.sign) mag_add(rhs);
    else if (mag_gt(rhs)) mag_minus(rhs);
    else mag_rev_minus(rhs);
    return *this;
  }
  inline BigInt& operator-=(const BigInt &rhs) {
    if (rhs.is_zero()) return *this;
    if (is_zero()) { *this = rhs; return negate(); }
    if (sign != rhs.sign) mag_add(rhs);
    else if (mag_gt(rhs)) mag_minus(rhs);
    else mag_rev_minus(rhs);
    return *this;
  }

  inline BigInt operator+(const BigInt &rhs) const {
    BigInt res(*this);
    return res += rhs;
  }
  inline BigInt operator-(const BigInt &rhs) const {
    BigInt res(*this);
    return res -= rhs;
  }
  inline BigInt operator-() const {
    BigInt res(*this);
    return res.negate();
  }

// *** multiply

  template<typename T>
  BigInt& operator*=(T rhs) {
    if (is_zero()) return *this;
    if (rhs == 0) return *this = BigInt(0);
    if (rhs < 0) {
      rhs = -rhs;
      sign = !sign;
    }
    uint64_t tmp1;
    uint32_t tmp2;
    uint32_t high = 0;
    uint32_t carry = 0;
    for (iter p = mag.begin(); p < mag.end(); p++) {
      tmp1 = uint64_t(*p) * uint64_t(rhs);
      *p = uint32_t(tmp1) + high;
      tmp2 = *p < high;
      high = uint32_t(tmp1 >> 32);
      *p += carry;
      carry = tmp2 || *p < carry;
    }
    mag.push_back(high + carry);
    if (mag.back() == 0) mag.pop_back();
    return *this;
  }
  template<typename T>
  inline BigInt operator*(const T rhs) const {
    BigInt res(*this);
    return res *= rhs;
  }

  BigInt operator*(const BigInt &rhs) const {
    if (is_zero()) return BigInt(0);
    if (rhs.is_zero()) return BigInt(0);
    BigInt res(sign ^ rhs.sign, vec(mag.size() + rhs.mag.size()));
    for (size_t i = 0; i < rhs.mag.size(); i++) {
      uint64_t tmp1;
      uint32_t tmp2;
      uint32_t carry = 0;
      uint32_t* p = res.mag.data() + i;
      for (size_t j = 0; j < mag.size(); j++) {
        tmp1 = uint64_t(mag[j]) * uint64_t(rhs.mag[i]);
        // res.mag[i + j .. i + j + 1] += tmp1 + (carry << 32)
        *(uint64_t*)p += tmp1; // assume little-endian
        tmp2 = *(uint64_t*)p < tmp1;
        p++;
        *p += carry;
        carry = tmp2 + (*p < carry);
      }
    }
    while (res.mag.back() == 0) res.mag.pop_back();
    return res;
  }
  inline BigInt& operator*=(const BigInt &rhs) {
    return *this = *this * rhs;
  }

// *** divide

  typedef struct {} divide_by_zero;

  // @returns remainder
  int32_t divmod(int32_t rhs) throw(divide_by_zero) {
    if (is_zero()) return 0;
    if (rhs == 0) throw divide_by_zero();
    bool rhs_sign = false;
    if (rhs < 0) {
      rhs_sign = true;
      rhs = -rhs;
      sign = !sign;
    }
    int32_t rem = 0;
    uint64_t tmp;
    for (rev_iter p = mag.rbegin(); p != mag.rend(); p++) {
      tmp = uint64_t(*p) | (uint64_t(rem) << 32);
      *p = uint32_t(tmp / uint32_t(rhs));
      rem = int32_t(tmp % uint32_t(rhs));
    }
    while (!mag.empty() && mag.back() == 0) mag.pop_back();
    if (mag.empty()) sign = false;
    return rhs_sign ? -rem : rem;
  }
  inline BigInt& operator/=(const int32_t rhs) {
    divmod(rhs);
    return *this;
  }
  inline BigInt operator/(const int32_t rhs) const {
    BigInt res(*this);
    return res /= rhs;
  }

private:
  void mag_minus(const BigInt &rhs, size_t offset) {
    size_t i = 0;
    while (rhs.mag[i] == 0) i++;
    uint32_t borrow = 0;
    uint32_t tmp;
    for (; i < rhs.mag.size(); i++) {
      tmp = mag[i + offset];
      mag[i + offset] -= rhs.mag[i];
      tmp = mag[i + offset] > tmp;
      mag[i + offset] -= borrow;
      borrow = tmp || (borrow && mag[i + offset] == 0xffffffff);
    }
    if (borrow) {
      for (; mag[i + offset] == 0; i++) mag[i + offset] = 0xffffffff;
      mag[i + offset]--;
    }
  }
  bool mag_geq(const BigInt &rhs, size_t offset = 0) {
    for (size_t i = rhs.mag.size() - 1; i != 0; i--)
      if (mag[i + offset] > rhs.mag[i]) return true;
      else if (mag[i + offset] < rhs.mag[i]) return false;
    return mag[offset] >= rhs.mag[0];
  }

public:
  // @returns quotient
  BigInt moddiv(const BigInt& rhs) throw(divide_by_zero) {
    if (is_zero()) return BigInt(0);
    if (rhs.is_zero()) throw divide_by_zero();
    mag.push_back(0);
    BigInt quot(sign ^ rhs.sign, vec(mag.size() - rhs.mag.size()));
    sign = sign ^ rhs.sign;
    const double rhs_approx =
      rhs.mag.size() == 1 ? double(rhs.mag[rhs.mag.size() - 1])
      : rhs.mag.size() == 2
        ? double(*(uint64_t*)rhs.mag.data()) / 0x100000000
        : double(*(uint64_t*)(rhs.mag.data() + rhs.mag.size() - 2) + 1)
          / 0x100000000;
      // assume little-endian
    size_t offset = mag.size() - rhs.mag.size() - 1;
    uint32_t tmp;
    while (mag.size() > rhs.mag.size()) {
      tmp = uint32_t((*(uint64_t*)(mag.data() + mag.size() - 2)) / rhs_approx);
      if (tmp != 0) mag_minus(rhs * tmp, offset);
      while (mag_geq(rhs, offset)) {
        mag_minus(rhs, offset);
        tmp++;
      }
      quot.mag[mag.size() - rhs.mag.size() - 1] = tmp;
      mag.pop_back(); // asserts `mag.back() == 0`
      offset--;
    }
    while (!mag.empty() && mag.back() == 0) mag.pop_back();
    if (mag.empty()) sign = false;
    if (quot.mag.back() == 0) quot.mag.pop_back();
    if (quot.mag.empty()) quot.sign = false;
    return quot;
  }
  inline BigInt& operator/=(const BigInt& rhs) {
    return *this = moddiv(rhs);
  }
  inline BigInt operator/(const BigInt& rhs) const {
    return BigInt(*this).moddiv(rhs);
  }
// *** end
};

ostream& operator<<(ostream& out, const BigInt& num) {
  if (num.is_zero()) return out << '0';
  switch (out.flags() & std::ios::basefield) {
  case std::ios::hex: {
    size_t i = num.get_mag().size();
    std::ios::fmtflags flags = out.flags();
    std::ios::char_type fill = out.fill();
    out << std::hex << std::setfill('0');
    i--;
    if (num.get_sign()) out << '-';
    out << num.get_mag()[i];
    if (i > 0) do {
      i--;
      out << std::setw(8) << num.get_mag()[i];
    } while (i > 0);
    out.flags(flags);
    out.fill(fill);
    break;
  }
  case std::ios::oct:
    typedef struct {} unimplemented;
    throw unimplemented();
  default: {
    vector<int32_t> dec;
    dec.reserve(num.get_mag().size() * 10 / 9 + 1);
    BigInt self(num);
    while (!self.is_zero())
      dec.push_back(self.divmod(1000000000));

    std::ios::char_type fill = out.fill();
    out << std::setfill('0');
    if (num.get_sign()) out << '-';
    out << dec.back();
    dec.pop_back();
    while (!dec.empty()) {
      out << std::setw(9) << dec.back();
      dec.pop_back();
    }
    out.fill(fill);
  }
  }
  return out;
}

BigInt pow(const BigInt& base, int32_t exp) {
  if (exp == 0) return BigInt(1);
  BigInt aux(base);
  BigInt res(1);
  for (; exp != 0; exp >>= 1) {
    if (exp & 1) res *= aux;
    aux *= aux;
  }
  return res;
}

//*

typedef BigInt TeamWorkBigInt;

//StudybarCommentBegin
int main() {
  int i, N;
  TeamWorkBigInt n = 10, b, x1, x2, s, t, pi;

  cin >> N;
  N--;
  b = pow(n, N + 10);

  x1 = b * 4 / 5;
  x2 = b / -239;
  s = x1 + x2;

  for (i = 3; i <= N * 2; i += 2) {
    x1 /= -25;
    x2 /= -57121;
    t = (x1 + x2) / i;
    s += t;
  }
  pi = s * 4;
  cout << (pi / pow(n, 10)) << endl;
  return 0;
}
//StudybarCommentEnd

/*/

int main() {
  // mag_add
  cout << BigInt(100) + BigInt(101) << endl;
  cout << BigInt(0, vector<uint32_t>(1, 0xffffffff))
    + BigInt(0, vector<uint32_t>(1, 0xffffffff)) << endl;
  cout << BigInt(-100) + BigInt(-101) << endl;
  cout << BigInt(1, vector<uint32_t>(1, 0xffffffff))
    + BigInt(1, vector<uint32_t>(1, 0xffffffff)) << endl;
  // mag_minus
  cout << (BigInt(101) + BigInt(-100)) << endl;
  cout << (BigInt(101) - BigInt(100)) << endl;
  cout << (BigInt(-101) + BigInt(100)) << endl;
  cout << (BigInt(-101) - BigInt(-100)) << endl;
  // mag_rev_minus
  cout << (BigInt(100) + BigInt(-101)) << endl;
  cout << (BigInt(100) - BigInt(101)) << endl;
  cout << (BigInt(-100) + BigInt(101)) << endl;
  cout << (BigInt(-100) - BigInt(-101)) << endl;
  // operator*(int32_t)
  cout << (BigInt(100) * 100) << endl;
  cout << (BigInt(100) * -100) << endl;
  cout << (BigInt(0x60000000) * 0x60000000) << endl;
  cout << (BigInt(100) * 0) << endl;
  cout << (BigInt(0) * 100) << endl;
  // operator*(const BigInt &)
  cout << (BigInt(100) * BigInt(100)) << endl;
  cout << (BigInt(0x60000000) * BigInt(0x60000000)) << endl;
  BigInt a(0x11111111);
  a = (a * a) * (a * a);
  cout << a << endl;
  cout << BigInt(0x1111) * BigInt(0x1111) << endl;
  // operator/(int32_t)
  cout << BigInt(100) / 10 << endl;
  cout << a / 0x11111111 << endl;
  // operator/(const BigInt &)
  cout << BigInt(100) / BigInt(10) << endl;
  cout << BigInt(0, vector<uint32_t>(4, 0xffffffff))
    / BigInt(0, vector<uint32_t>(2, 0xffffffff)) << endl;
  cout << a / BigInt(0x11111111) << endl;
  return 0;
}

/**/
