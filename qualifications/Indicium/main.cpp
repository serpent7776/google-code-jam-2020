#include <iostream>
#include <cstdio>
#include <vector>

class Mat
{
public:
	Mat(size_t sz) : sz{sz}, data {new size_t[sz * sz]}
	{}

	~Mat()
	{
		delete [] data;
	}

	size_t& operator()(size_t x, size_t y)
	{
		return data[x + y * sz];
	}

	size_t operator()(size_t x, size_t y) const
	{
		return data[x + y * sz];
	}

	size_t sz;
private:
	size_t *data;
};

std::ostream& operator<<(std::ostream& s, const Mat& m)
{
	auto size = m.sz;
	for (size_t x = 0; x < size; ++x)
		for (size_t y = 0; y < size; ++y)
		{
			std::cout << m(x, y);
			if (y != size - 1)
			{
				std::cout << ' ';
			}
			else
			{
				std::cout << '\n';
			}
		}
	return s;
}

enum Type
{
	One_to_n = -1,
	Impossible = 0,
};

size_t sum_1_n(size_t size)
{
	size_t sum = 0;
	for (size_t i = 1; i <= size; ++i)
	{
		sum += i;
	}
	return sum;
}

size_t sum_n_sz(size_t size, size_t n)
{
	return size * n;
}

bool odd(size_t val)
{
	return val % 2 == 1;
}

Type get_type(size_t size, size_t trace)
{
	if (odd(size) and sum_1_n(size) == trace)
	{
		return One_to_n;
	}
	for (size_t n = 1; n <= size; ++n)
	{
		if (sum_n_sz(size, n) == trace)
		{
			return Type(n);
		}
	}
	return Impossible;
}

Mat gen_one_to_n(size_t size)
{
	Mat m {size};
	for (size_t x = 0; x < size; ++x)
		for (size_t y = 0; y < size; ++y)
		{
			size_t offset = x;
			m(x, y) = (offset + y) % size + 1;
		}
	return m;
}

Mat gen_n_cp(size_t size, size_t n)
{
	Mat m {size};
	for (size_t x = 0; x < size; ++x)
		for (size_t y = 0; y < size; ++y)
		{
			m(x, y) = (size + n - y + x - 1) % size + 1;
		}
	return m;
}

struct Result
{
	Mat m;
	bool possible;
};

Result generate(size_t size, size_t trace)
{
	auto type = get_type(size, trace);
	if (type == One_to_n)
	{
		return {gen_one_to_n(size), true};
	}
	if (type > 0)
	{
		return {gen_n_cp(size, type), true};
	}
	else
	{
		return {{size}, false};
	}
}

template <typename Callable>
void repeat(unsigned n, Callable f)
{
	for (unsigned i = 0; i < n; ++i)
	{
		f(i);
	}
}

const char* pos_s(bool b)
{
	return b ? "POSSIBLE" : "IMPOSSIBLE";
}

int main()
{
	size_t n;
	std::cin >> n;
	repeat(n, [](size_t k)
	{
		size_t size, trace;
		std::cin >> size >> trace;
		auto r = generate(size, trace);
		std::cout << "Case #" << (k+1) << ": " << pos_s(r.possible);
		if (r.possible)
		{
			std::cout << "\n" << r.m;
		}
		std::cout << "\n";
	});
}
