#include <iostream>
#include <cstdio>
#include <vector>
#include <functional>
#include <numeric>
#include <algorithm>

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
			if (y == 0)
			{
				std::cout << '\n';
			}
			std::cout << m(x, y);
			if (y != size - 1)
			{
				std::cout << ' ';
			}
		}
	return s;
}

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

size_t sum(const std::vector<size_t>& v)
{
	return std::accumulate(v.begin(), v.end(), 0);
}

bool check_parity(const std::vector<size_t>& v, size_t n)
{
	const bool nodd = odd(n);
	return std::all_of(v.begin(), v.end(), [&](size_t val)
	{
		auto count = std::count(v.begin(), v.end(), val);
		return odd(count) == nodd;
	});
}

bool full(const std::vector<size_t>& v)
{
	return std::all_of(v.begin(), v.end(), [size=v.size()](size_t val){return val == size;});
}

bool inc(std::vector<size_t>& v)
{
	if (full(v))
	{
		return false;
	}
	for (size_t i = v.size() - 1; ; --i)
	{
		v[i] = v[i] % v.size() + 1;
		if (v[i] != 1 or i == 0)
		{
			break;
		}
	}
	return true;
}

std::vector<size_t> find_diagonal(size_t size, size_t trace)
{
	std::vector<size_t> diag(size, 1);
	while (true)
	{
		if (sum(diag) == trace and check_parity(diag, size))
		{
			return diag;
		}
		const bool b = inc(diag);
		if (not b)
		{
			return {};
		}
	}
}

bool row_conflicts(const Mat& m, size_t r, const std::vector<size_t>& row)
{
	for (size_t i = 0; i < row.size(); ++i)
	{
		if (m(r, i) == row[i])
		{
			return true;
		}
	}
	return false;
}

bool row_doesnt_conflict(const Mat& m, size_t r, const std::vector<size_t>& row)
{
	for (size_t n = 0; n < r; ++n)
	{
		if (row_conflicts(m, n, row))
		{
			return false;
		}
	}
	return true;
}

bool eqn(size_t x, size_t y, bool b)
{
	return b ? x == y : x != y;
}

bool row_matches_diag(const std::vector<size_t>& row, size_t r, const std::vector<size_t>& diag)
{
	for (size_t i = 0; i < diag.size(); ++i)
	{
		if (not eqn(row[i], diag[i], i == r))
		{
			return false;
		}
	}
	return true;
}

std::vector<size_t> gen_row(const Mat& m, size_t r, const std::vector<size_t> diag)
{
	std::vector<size_t> row(diag.size());
	std::iota(row.begin(), row.end(), 1);
	while (true)
	{
		if (row_doesnt_conflict(m, r, row) and row_matches_diag(row, r, diag))
		{
			return row;
		}
		const bool cont = std::next_permutation(row.begin(), row.end());
		if (not cont)
		{
			return {};
		}
	}
}

void set_row(Mat* m, size_t r, const std::vector<size_t>& row)
{
	for (size_t i = 0; i < row.size(); ++i)
	{
		(*m)(r, i) = row[i];
	}
}

Mat gen_diag(const std::vector<size_t>& diag)
{
	auto size = diag.size();
	Mat m {size};
	for (size_t r = 0; r < size; ++r)
	{
		auto row = gen_row(m, r, diag);
		if (row.size())
		{
			set_row(&m, r, row);
		}
	}
	return m;
}

std::function<Mat()> get_gen(size_t size, size_t trace)
{
	if (odd(size) and sum_1_n(size) == trace)
	{
		return [=]()
		{
			return gen_one_to_n(size);
		};
	}
	for (size_t n = 1; n <= size; ++n)
	{
		if (sum_n_sz(size, n) == trace)
		{
			return [=]()
			{
				return gen_n_cp(size, n);
			};
		}
	}
	if (size >= 4)
	{
		auto diag = find_diagonal(size, trace);
		if (diag.size())
		{
			return [diag=std::move(diag)]()
			{
				return gen_diag(diag);
			};
		}
	}
	return {};
}

struct Result
{
	Mat m;
	bool possible;
};

Result generate(size_t size, size_t trace)
{
	auto gen = get_gen(size, trace);
	if (gen)
	{
		return {gen(), true};
	}
	else
	{
		return {Mat {0}, false};
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
			std::cout << r.m;
		}
		std::cout << "\n";
	});
}
