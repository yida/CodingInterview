#include <iostream>
#include <deque>
#include <vector>
#include <stdint.h>
#include <cmath>
#include <ctime>

using namespace std;

class BigInt {
  public:
    BigInt();
    explicit BigInt(const int input);
    explicit BigInt(const string intput_str);
    explicit BigInt(const double input);
    virtual ~BigInt() {} 

    const size_t max_size() const { return max_length; }
    const size_t size() const { return digits.size(); }
    const bool empty() const { return digits.empty(); }
    const bool equal_to(const BigInt& big_int) const;
    const bool equal_to(const BigInt& big_int, const size_t length) const;
    const bool less_than(const BigInt& big_int) const;
    const bool abs_less_than(const BigInt& big_int) const;
    size_t same_digits_front(const BigInt& big_int) const;
    
    void abs();
    void negative();
    void add(const BigInt& big_int);
    void multiply_by(const BigInt& big_int);
    void multiply_by(const uint8_t small_int);
    void divide_by(const BigInt& divisor);
    void divide_by_long(const BigInt& divisor);
    void divide_by_newton(const BigInt& divisor);
    void shift_left(const size_t shift_num);
    void shift_right(const size_t shift_num);

    double to_double(const size_t first, const size_t last) const;
    size_t to_uint(const size_t first, const size_t last) const;

    void assign(const size_t number);
    void assign(const BigInt& big_int, const size_t length);
    void zap_heading_zeros();
    void print();
  private:
    friend ostream& operator<<(ostream& out, const BigInt& num);

    int8_t sign; 
    static const size_t max_length;
    deque<uint8_t> digits;
};

const size_t BigInt::max_length = 64;

ostream& operator<<(ostream& out, const BigInt& num) {
  if (num.empty()) return out;
  
  if (num.sign < 0) out << '-';
  for (deque<uint8_t>::const_iterator it = num.digits.begin(); 
                                it != num.digits.end(); it ++)
    out << static_cast<unsigned int>(*it);
  return out;
}

void BigInt::print() {
  if (sign < 0) cout << '-';
  for (deque<uint8_t>::iterator it = digits.begin(); 
                                it != digits.end(); it ++)
    cout << static_cast<unsigned int>(*it);
}

BigInt::BigInt(): sign(1) {
  digits.push_back(0);  
}

BigInt::BigInt(const string input_str) : sign(1) {
  string::const_iterator it = input_str.begin();   
  if ((*it) == '-') {
    sign = -1;
    it ++;
  }
  for (; it != input_str.end(); it ++) {
    if ((*it) <= '9' && (*it) >= '0') {
      digits.push_back(static_cast<uint8_t>(*it) - 48);
    }
  }
}

BigInt::BigInt(const int input): sign(1) {
  int div = input;
  if (input < 0) {
    sign = -1;
    div = -div;  
  }
  int mod = 0;    
  while (div > 0) {
    mod = div % 10;
    div = div / 10;
    digits.push_front(static_cast<uint8_t>(mod));
  }
}

BigInt::BigInt(const double input): sign(1) {
  double fractpart, intpart;
  fractpart = modf(input, &intpart);
//  cout << intpart << endl;

  int64_t div = static_cast<int64_t>(intpart);
  if (input < 0) {
    sign = -1;
    div = -div;  
  }
  int64_t mod = 0;    
  while (div > 0) {
    mod = div % 10;
    div = div / 10;
    digits.push_front(static_cast<uint8_t>(mod));
  }
}

size_t BigInt::same_digits_front(const BigInt& big_int) const {
  size_t min_size = min(this->size(), big_int.size());
  size_t same_digits = 0;
  for (size_t index = 0; index < min_size; index ++) {
    if (this->digits[index] == big_int.digits[index]) {
      same_digits ++;
    } else
      break;
  }
  return same_digits;
}

const bool BigInt::equal_to(const BigInt& big_int) const {
  if (big_int.sign != this->sign) return false;
  if (big_int.size() != this->size()) return false;  
  for (size_t counter = 0; counter < this->size(); counter ++) {
    if (big_int.digits[counter] != this->digits[counter])
      return false;
  }
  return true;
}

const bool BigInt::equal_to(const BigInt& big_int, const size_t length) const {
  if (big_int.sign != this->sign) return false;
  for (size_t counter = 0; counter < length; counter ++) {
    if (big_int.digits[counter] != this->digits[counter])
      return false;
  }
  return true;
}

const bool BigInt::less_than(const BigInt& big_int) const {
  if (this->sign < big_int.sign) {
//    cout << "sign less" << endl;
    return true;
  }
  else if (this->sign == big_int.sign) {
    return this->abs_less_than(big_int);
//    if (this->size() < big_int.size()) { 
////      cout << "size less" << endl;
//      return true;
//    } else if (this->size() == big_int.size()) {
//      for (size_t counter = 0; counter < this->size(); counter ++) {
//        if (this->digits[counter] < big_int.digits[counter]) {
////          cout << "number less" << endl;
//          return true;
//        }
//      }
//    }
  }
  return false;
}

const bool BigInt::abs_less_than(const BigInt& big_int) const {
  if (this->size() < big_int.size()) { 
//    cout << "size less" << endl;
    return true;
  } else if (this->size() == big_int.size()) {
    for (size_t counter = 0; counter < this->size(); counter ++) {
      if (this->digits[counter] < big_int.digits[counter]) {
//        cout << "number less" << endl;
        return true;
      }
    }
  }
  return false;
}

// << times 10
void BigInt::shift_left(const size_t shift_num) {
  for (int counter = 0; counter < shift_num; counter ++)
    digits.push_back(0);
}

// >> divides 10
void BigInt::shift_right(const size_t shift_num) {
  if (shift_num >= this->size()) {
    this->digits.erase(this->digits.begin(), this->digits.end());
    this->digits.push_back(0);
    this->sign = 1; 
  } else {
    uint8_t current_digit = 0;
    uint8_t carrier = 0;
    uint8_t sum = 0;
    for (int counter = 0; counter < shift_num; counter ++) {
      this->digits.back() += carrier;
      current_digit = this->digits.back();
      if (current_digit >= 5) {
        carrier = 1;
      } else {
        carrier = 0;
      }
      this->digits.pop_back();
    }
    deque<uint8_t>::reverse_iterator it = this->digits.rbegin();     
    while (it != this->digits.rend() && carrier > 0) {
      sum = *it + carrier; 
      *it = sum % 10;
      carrier = sum / 10; 
      it ++;
    }
    if (carrier > 0) 
      this->digits.push_front(carrier);
  }
}

double BigInt::to_double(size_t first, size_t last) const {
  double result = 0;
  if (last > this->size()) return 0; 

  for (size_t index = first; index <= last; index ++) {
    result = result * 10 + this->digits[index];
  }
  if (this->sign == -1) result = - result;
  
  return result;
}

size_t BigInt::to_uint(const size_t first, const size_t last) const {
  size_t result = 0;
  if (last > this->size()) return 0; 

  for (size_t index = first; index <= last; index ++) {
    result = result * 10 + this->digits[index];
  }
  if (this->sign == -1) result = - result;
  
  return result;
}

void BigInt::zap_heading_zeros() {
  while (this->digits.front() == 0) {
    this->digits.pop_front();
  }
}

void BigInt::assign(const BigInt& big_int, const size_t length) {
  size_t input_size = big_int.size();
  while (input_size < length) {
    this->digits.push_back(0); 
    input_size ++;
  }
  for (size_t counter = 0; counter < big_int.size(); counter ++) {
    this->digits.push_back(big_int.digits[counter]);
  }
}

void BigInt::assign(const size_t number) {
  size_t div = number;
  
  if (div == 0) {
    this->digits.push_back(0);
    return;
  }

  int mod = 0;    
  vector<uint8_t> digit_stack;
  while (div > 0) {
    mod = div % 10;
    div = div / 10;
    digit_stack.push_back(static_cast<uint8_t>(mod));
  }  
  while (!digit_stack.empty()) {
    this->digits.push_back(digit_stack.back());
    digit_stack.pop_back();
  }
}

void BigInt::abs() {
  this->sign = 1;
}

void BigInt::negative() {
  this->sign = -this->sign;
}

void BigInt::add(const BigInt& addend) {
  uint8_t carrier = 0;
  uint8_t sum = 0;
  int8_t new_sign = 0;
  if (this->sign == addend.sign) {
//    cout << "sum" << endl;
    while (this->size() < addend.size()) {
      this->digits.push_front(0);
    }
    deque<uint8_t>::reverse_iterator addend_it = this->digits.rbegin(); 
    for (int index = 0; index < addend.digits.size(); index ++) {
      sum = *addend_it + addend.digits[addend.size() - index - 1] + carrier; 
//      cout << static_cast<int>(*addend_it) << ' ' 
//           << static_cast<int>(addend.digits[addend.size() - index - 1]) << ' ' << static_cast<int>(carrier) << endl;
      *addend_it = sum % 10;
      carrier = sum / 10;
      addend_it ++;
    }
    while (addend_it != this->digits.rend()) {
      sum = *addend_it + carrier; 
      *addend_it = sum % 10;
      carrier = sum / 10; 
      addend_it ++;
    }
    if (carrier > 0) digits.push_front(carrier); 

  } else {
//    cout << "substract" << endl;
    BigInt minuend = addend; 
    if (this->abs_less_than(minuend)) {
      new_sign = minuend.sign;
    } else {
      new_sign = this->sign;
    }
    this->abs();
    minuend.abs();
    BigInt subtrahend;
//    print(); cout << endl;
//    cout << minuend << endl;
    if (this->less_than(minuend)) {
      subtrahend = *this; 
    } else {
      subtrahend = minuend;
      minuend = *this;
    } 

//    cout << static_cast<int>(new_sign) << endl; 
//    cout << "minuend " << minuend << ' ' << "subtrahend " << subtrahend << endl;

    deque<uint8_t>::reverse_iterator minuend_it = minuend.digits.rbegin(); 
    for (int index = 0; index < subtrahend.digits.size(); index ++) {

//      cout << static_cast<int>(*(minuend_it + index)) << ' ' 
//           << static_cast<int>(subtrahend.digits[subtrahend.size() - index - 1]) << endl;

      if (*(minuend_it + index) < subtrahend.digits[subtrahend.size() - index - 1]) {
        *(minuend_it + index) += 10; 
        int add_index = 1;
        while (*(minuend_it + index + add_index) < 1) {
          *(minuend_it + index + add_index) = 9;
          add_index ++;
        }
        *(minuend_it + index + add_index) -= 1;
      }
      *(minuend_it + index) -= subtrahend.digits[subtrahend.size() - index - 1];
    }
//    cout << "minuend " << minuend << endl; 
    minuend.sign = new_sign;
    *this = minuend;
  }
}

void BigInt::multiply_by(const uint8_t small_int) {
  uint8_t carrier = 0;
  uint8_t product = 0;
  if (small_int == 0) {
    this->digits.erase(this->digits.begin(), this->digits.end());
    digits.push_back(0);
  }
  for (int counter = digits.size() - 1; counter >= 0; counter --) {
    product = digits[counter] * small_int + carrier;
    digits[counter] = product % 10;
    carrier = product / 10;
  }
  if (carrier > 0) digits.push_front(carrier);
}

void BigInt::multiply_by(const BigInt& big_int) {
  BigInt base; 
  BigInt product;
  for (int counter = 0; counter < big_int.size(); counter ++) {
    base = *this; 
    base.shift_left(big_int.size() - counter - 1);
    base.multiply_by(big_int.digits[counter]);
//    cout << "sum " << product << ' ' << base << endl;
    product.add(base);
//    cout << "sum result " << product << endl;
  } 
  int8_t new_sign = this->sign * big_int.sign;
  *this = product;
  this->sign = new_sign;
}

void BigInt::divide_by(const BigInt& divisor) {
//    clock_t t1, t2;
  if (divisor.size() <= 16) {
//    t1 = clock();
    this->divide_by_long(divisor);
//    t2 = clock();
//    cout << "time " << (static_cast<double>(t2) - static_cast<double>(t1)) / CLOCKS_PER_SEC << endl;
  } else {
//    t1 = clock();
    this->divide_by_newton(divisor);
//    t2 = clock();
//    cout << "time " << (static_cast<double>(t2) - static_cast<double>(t1)) / CLOCKS_PER_SEC << endl;
  }
}

void BigInt::divide_by_long(const BigInt& divisor) {
//  print(); cout << endl;
  BigInt number = divisor;
//  cout << number << endl;
  int8_t new_sign = number.sign * this->sign;
  number.abs(); 
  this->abs();
  
  size_t ui_dividend = 0, ui_divisor = 0;
  size_t ui_quotient = 0, ui_remainder = 0;
  BigInt quotient;
  size_t dividend_size = this->size();
  size_t divisor_size = number.size();
  size_t dividend_length = this->size();
  size_t dividend_length_remain = this->size();
  ui_divisor = number.to_uint(0, number.size() - 1);
  size_t dividend_index = 0;

  while (dividend_index < dividend_length) {
    dividend_size = min(divisor_size, dividend_length_remain);

    ui_dividend = this->to_uint(dividend_index, dividend_index + dividend_size - 1);
    ui_dividend += ui_remainder * static_cast<size_t>(pow(10.0, static_cast<int>(dividend_size)));
    //    cout << "ui " << dividend_size << ' ' 
    //         << ui_dividend << ' ' << ui_divisor << endl;
    ui_quotient = ui_dividend / ui_divisor;
    ui_remainder = ui_dividend % ui_divisor;
    //    cout << "quotient " << ui_quotient << endl;
    //    cout << "remainder " << ui_remainder << endl;
    //    cout << "assign " << ui_quotient << endl;
    quotient.assign(BigInt(static_cast<int>(ui_quotient)), dividend_size);
    
    
    //    cout << quotient << endl;
    dividend_length_remain -= dividend_size;
    dividend_index += dividend_size;
    //    cout << dividend_index << ' ' << dividend_length << endl;
  }
  quotient.zap_heading_zeros();
  
  *this = quotient;
  this->sign = new_sign;
  
}

void BigInt::divide_by_newton(const BigInt& divisor) {
  //  print(); cout << endl;

  BigInt number = divisor;
  int8_t new_sign = divisor.sign * this->sign;
  number.abs(); 
  BigInt two(2);
  int magnitude = number.size();
  two.shift_left(magnitude); 
  
  BigInt reciprocal(1); 
  BigInt prev_reciprocal;

  BigInt prev_quotient = *this;
  BigInt quotient = *this;
  
  size_t iter_time = 0; 
  //  for (int iter = 0; iter < 6; iter ++) {
  //  while (prev_reciprocal.same_digits_front(reciprocal) < this->size()) {
  do {
    prev_quotient = quotient;
    iter_time ++;
    prev_reciprocal = reciprocal;
    //    cout << "start X " << reciprocal << endl;
    reciprocal.multiply_by(number);
    //    cout << "bX " << reciprocal << endl;
    reciprocal.negative();
    //    cout << "two " << two << endl;
    //    cout << "this add " << endl;
    reciprocal.add(two);  
    //    cout << prev_reciprocal << endl;
    reciprocal.multiply_by(prev_reciprocal);
    //    cout << "iter " << magnitude << ' ' << reciprocal << endl;
    two.shift_left(magnitude); 
    magnitude += magnitude;

    quotient = *this;
    quotient.multiply_by(reciprocal);
    quotient.shift_right(magnitude);
    //    cout << "sec result " << quotient << endl;

  } while (!quotient.equal_to(prev_quotient));
  //  cout << "reciprocal " << reciprocal << endl;
  
  //  cout << iter_time << endl; 
  
  *this = quotient;
  
  //  this->multiply_by(reciprocal);
  //  cout << "before shift ";
  //  print(); 
  //  cout << endl;
   
  //  this->shift_right(magnitude);
  //  cout << "after shift ";
  //  print(); 
  //  cout << endl;
  this->sign = new_sign;
}

int main(int argc, char ** argv) {
  int N = 0;
  cin >> N; 

  //  vector<int64_t> num_array;
  //  double product = 1;
  //  int64_t input;
  //  for (int counter = 0; counter < N; counter ++) {
  //    cin >> input;
  //    num_array.push_back(input);
  //    product *= input;
  //  }
  //  
  //  for (int counter = 0; counter < N; counter ++) {
  //    cout << static_cast<int64_t>(product / num_array[counter]) << endl;
  //  }

  string input_str;
  long long input;
  vector<BigInt> num_array;
  BigInt product(1);

  //  clock_t t1, t2;
  //  t1 = clock();
  for (int counter = 0; counter < N; counter ++) {
    cin >> input_str;
    num_array.push_back(BigInt(input_str));
    //    cout << "prev " << product << endl;
    //    cout << "* " << num_array.back() << endl;
    product.multiply_by(num_array.back());
    //    cout << "* result " << product << endl;
    //    cout << "next " << endl;
  }
  //  t2 = clock();
  //  cout << "input time " << (static_cast<double>(t2) - 
  //                            static_cast<double>(t1)) / CLOCKS_PER_SEC << endl;
  //  cout << "product " << product << endl;
  BigInt product_without_one;

  for (int counter = 0; counter < N; counter ++) {
  //  for (int counter = 0; counter < 1; counter ++) {
    product_without_one = product;
    //    cout << "prev " << product_without_one << endl;
    //    t1 = clock();
    product_without_one.divide_by(num_array[counter]);
    //    t2 = clock();
    //    cout << "time " << (static_cast<double>(t2) - 
    //                        static_cast<double>(t1)) / CLOCKS_PER_SEC << endl;
    //    cout << "after " << product_without_one << endl;
    cout << product_without_one << endl;
  }

  return 0;
}

