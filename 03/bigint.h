#include<iostream>
#include<algorithm>
#include<cmath>
class BigInt {
public:
	BigInt() {
		this->sign = true;
		this->size_ = 1;
		this->data_ = new char[size_];
		this->data_[0] = '0';
	}
	BigInt(const BigInt& copied)
		:size_(copied.size_)
		, data_(new char[copied.size_])
		, sign(copied.sign)
	{
		std::copy(copied.data_, copied.data_ + size_, data_);
	}
	BigInt(const int64_t& num) {
		size_t k = 0;
		int64_t number = num;
		if (number < 0) {
			sign = false;
			number *= -1;
		}
		else sign = true;

		while (number) {
			k++;
			number /= 10;
		}
		size_ = k;
		number = num;
		char* ptr = new char[size_];
		//delete[] data_;
		data_ = ptr;
		for (size_t i = 0; i < size_; i++) {
			data_[i] = abs(number) % 10 + '0';
			number /= 10;
		}
	}
	~BigInt() {
		sign = true;
		size_ = 0;
		delete[] data_;
	}
	BigInt& operator=(const BigInt& copied)
	{
		if (this == &copied)
			return *this;
		char* ptr = new char[copied.size_];
		delete[] data_;
		data_ = ptr;
		size_ = copied.size_;
		sign = copied.sign;
		std::copy(copied.data_, copied.data_ + size_, data_);
		return *this;
	}
	BigInt& operator=(const int64_t& num)
	{
		size_t k = 0;
		int64_t number = num;
		if (number < 0) {
			sign = false;
			number *= -1;
		}
		else sign = true;
		while (number) {
			k++;
			number /= 10;
		}
		size_ = k;
		number = num;
		char* ptr = new char[size_];
		delete[] data_;
		data_ = ptr;
		for (size_t i = 0; i < size_; i++) {
			data_[i] = abs(number) % 10 + '0';
			number /= 10;
		}
		return *this;
	}
	friend std::ostream& operator<<(std::ostream &out, const BigInt &BigInt) {
		if (!BigInt.sign)
			out << "-";
		for (size_t i = BigInt.size_; i > 0; i--)
			out << BigInt.data_[i - 1];
		return out;
	}
	BigInt operator-() const
	{
		BigInt tmp(*this);
		if (this->data_[0] == '0'  && this->size_ == 1) 
			return tmp;
		tmp.sign = !sign;
		return tmp;
	}
	bool operator>(const BigInt& other) const{
		if (this == &other)
			return false;
			if (this->sign > other.sign || this->size_ > other.size_)
				return true;
			if (this->sign < other.sign || this->size_ < other.size_)
				return false;
			for (size_t i = this->size_; i > 0; i--) {
				{
					if (this->data_[i - 1] < other.data_[i - 1])
					{
						if (this->sign == false) return true;
						else return false;
					}
					else if (this->data_[i - 1] > other.data_[i - 1])
					{
						if (this->sign == false) return false;
						else return true;
					}
				}
			}
			return false;
	}
	bool operator==(const BigInt& other) const
	{
		if (this == &other)
			return true;
		if (this->sign != other.sign || this->size_ != other.size_)
			return false;
		for (size_t i = 0; i < size_; ++i) {
			if (data_[i] != other.data_[i])
				return false;
		}
		return true;
	}
	bool operator!=(const BigInt& other) const {
		return !(*this == other);
	}
	bool operator<(const BigInt& other) const {
		if (this == &other)
			return false;
		return !(*this > other && *this == other);
	}
	bool operator<=(const BigInt& other) const {
		return *this < other || *this == other;
	}
	bool operator>=(const BigInt& other) const {
		return *this > other || *this == other;
	}

	bool operator>(const int64_t& num) const
	{
		BigInt other = num;
		if (this == &other)
			return false;
		if (this->sign > other.sign || this->size_ > other.size_)
			return true;
		if (this->sign < other.sign || this->size_ < other.size_)
			return false;
		for (size_t i = this->size_; i > 0; i--) {
			{
				if (this->data_[i - 1] < other.data_[i - 1])
				{
					if (this->sign == false) return true;
					else return false;
				}
				else if (this->data_[i - 1] > other.data_[i - 1])
				{
					if (this->sign == false) return false;
					else return true;
				}
			}
		}
		return false;

	}
	bool operator==(const int64_t& num) const
	{
		BigInt other = num;
		if (this == &other)
			return true;
		if (this->sign != other.sign)
			return false;
		for (size_t i = 0; i < size_; ++i)
			if (data_[i] != other.data_[i])
				return false;

		return true;
	}
	bool operator!=(const int64_t& num) const {
		BigInt other = num;
		return !(*this == other);
	}
	bool operator<(const int64_t& num) const {
		BigInt other = num;
		return !(*this > other && *this == other);
	}
	bool operator<=(const int64_t& num) const {
		BigInt other = num;
		return *this < other || *this == other;
	}
	bool operator>=(const int64_t& num) const {
		BigInt other = num;
		return *this > other || *this == other;
	}
	BigInt absBig() const {
		BigInt tmp(*this);
		tmp.sign = true;
		return tmp;
	}
	BigInt operator+(const BigInt& other) const {
		BigInt sum;
		size_t newsize_ = std::max(this->size_, other.size_) + 1;
		char* sum1 = new char[newsize_];
		for (size_t i = 0; i < newsize_; i++) {
			sum1[i] = '0';
		}
		char* newthis = new char[newsize_ - 1];
		for (size_t i = 0; i < this->size_; i++) {
			newthis[i] = this->data_[i];
		}
		for (size_t i = this->size_; i < newsize_ - 1; i++) {
			newthis[i] = '0';
		}
		char* newother = new char[newsize_ - 1];
		for (size_t i = 0; i < other.size_; i++) {
			newother[i] = other.data_[i];
		}
		for (size_t i = other.size_; i < newsize_ - 1; i++) {
			newother[i] = '0';
		}
		size_t p = 0;
		for (size_t i = newsize_ - 1; i > 0; i--) {
			if (this->data_[i] > other.data_[i]) {
				p = 1;
				sum.sign = this->sign;
				break;
			}
			else if (this->data_[i] < other.data_[i]) {
				p = 2;
				sum.sign = other.sign;
				break;
			}
		}
		if (this->sign != other.sign && *this == -other) {
			newsize_ = 1;
			sum1[0] = 0 + '0';
			sum.sign = true;
			sum.size_ = newsize_;
			sum.data_ = new char[newsize_];
			sum.data_[0] = sum1[0];
			delete[] sum1;
			return sum;
		}
		char tmp;
		if (this->sign == other.sign) {
			sum.sign = this->sign;

			for (size_t i = 0; i < newsize_ - 1; i++) {
				tmp = (newthis[i] - '0') + (newother[i]);
				sum1[i] = (sum1[i] - '0' + (tmp - '0')) % 10 + '0';
				sum1[i + 1] += (tmp - '0') / 10;
			}
			size_t s = 0;
			while (sum1[newsize_ - s - 1] == '0')
				s++;
			newsize_ = newsize_ - s;
			sum.size_ = newsize_;
			sum.data_ = new char[newsize_];
			for (size_t i = 0; i < newsize_; i++) {
				sum.data_[i] = sum1[i];
			}
			delete[] sum1;
			return sum;
		}
		else {
				if (absBig() > other.absBig()) {
					sum.sign = this->sign;
					for (size_t i = 0; i < this->size_; i++) {
						newthis[i] = '9' - newthis[i] + '0';
					}
				}
				else {
					sum.sign = other.sign;
					for (size_t i = 0; i < other.size_; i++) {
						newother[i] = '9' - newother[i] + '0';
					}
				}
			for (size_t i = 0; i < newsize_ - 1; i++) {
					tmp = (newthis[i] - '0') + (newother[i]);
					sum1[i] = (sum1[i] - '0' + (tmp - '0')) % 10 + '0';
					sum1[i + 1] += (tmp - '0') / 10;
				}
			size_t s = 0;
			while (sum1[newsize_ - s - 1] == '0')
				s++;
			for (size_t i = 0; i < newsize_-s; i++) {
				sum1[i] = '9' - sum1[i] + '0';
				}
			newsize_ = newsize_ - s;
			}
			size_t s = 0;
			while (sum1[newsize_ - s - 1] == '0')
				s++;
			newsize_ = newsize_ - s;
			sum.size_ = newsize_;
			sum.data_ = new char[newsize_];
			for (size_t i = 0; i < newsize_; i++) {
				sum.data_[i] = sum1[i];
			}
			delete[]newother;
			delete[]newthis;
			delete[] sum1;
			return sum;
		}
		BigInt operator+(const int& num) const {
			BigInt other = num;
			return this->operator+(other);
		}
		BigInt operator-(const BigInt& other) const {
			return this->operator+(-(other));
		}
		BigInt operator-(const int& num) const {
			BigInt other = num;
			return this->operator-(-(other));
		}
	private:
		char* data_ ;
		size_t size_;
		bool sign;
};
