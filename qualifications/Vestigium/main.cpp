#include <iostream>
#include <cstdio>

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

void read_mat(Mat* m)
{
	for (size_t x = 0; x < m->sz; ++x)
		for (size_t y = 0; y < m->sz; ++y)
		{
			std::cin >> (*m)(x, y);
		}
}

size_t calc_trace(const Mat& m)
{
	size_t trace = 0;
	for (size_t n = 0; n < m.sz; ++n)
	{
		trace += m(n, n);
	}
	return trace;
}

size_t row_repeats(const Mat& m, size_t row)
{
	for (size_t i = 0; i < m.sz; ++i)
		for (size_t j = i + 1; j < m.sz; ++j)
		{
			if (m(row, i) == m(row, j))
			{
				return 1;
			}
		}
	return 0;
}

size_t col_repeats(const Mat& m, size_t col)
{
	for (size_t i = 0; i < m.sz; ++i)
		for (size_t j = i + 1; j < m.sz; ++j)
		{
			if (m(i, col) == m(j, col))
			{
				return 1;
			}
		}
	return 0;
}

std::pair<size_t, size_t> calc_repeats(const Mat& m)
{
	size_t rows = 0;
	size_t cols = 0;
	for (size_t r = 0; r < m.sz; ++r)
	{
		rows += row_repeats(m, r);
	}
	for (size_t c = 0; c < m.sz; ++c)
	{
		cols += col_repeats(m, c);
	}
	return {rows, cols};
}

template <typename Callable>
void repeat(unsigned n, Callable f)
{
	for (unsigned i = 0; i < n; ++i)
	{
		f(i);
	}
}

int main()
{
	size_t n;
	std::cin >> n;
	repeat(n, [](size_t n)
	{
		size_t size;
		std::cin >> size;
		Mat m{size};
		read_mat(&m);
		const size_t trace = calc_trace(m);
		auto reps = calc_repeats(m);
		std::printf("Case #%zu: %zu %zu %zu\n", n+1, trace, reps.first, reps.second);
	});
}
