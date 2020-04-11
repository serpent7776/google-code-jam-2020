#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <algorithm>

struct XY
{
	size_t x;
	size_t y;
};

class Mat
{
public:
	Mat(size_t w, size_t h) : w{w}, h{h}, data(w * h, 0)
	{}

	size_t& operator()(size_t x, size_t y)
	{
		return data[x + y * w];
	}

	size_t operator()(size_t x, size_t y) const
	{
		return data[x + y * w];
	}

	bool at(size_t x, size_t y) const
	{
		return (*this)(x, y) > 0;
	}

	void mark(size_t x, size_t y)
	{
		marks.push_back({x, y});
	}

	void eliminate()
	{
		for (auto m : marks)
		{
			(*this)(m.x, m.y) = 0;
		}
		marks.clear();
	}

	size_t width() const
	{
		return w;
	}

	size_t height() const
	{
		return h;
	}

private:
	size_t w;
	size_t h;
	std::vector<size_t> data;
	std::vector<XY> marks;
};

std::vector<size_t> neighs(4, 0);

const std::vector<size_t>& get_neighbours(const Mat& m, size_t r, size_t c)
{
	neighs.clear();
	// left
	for (long i = r - 1; i >= 0; --i)
	{
		if (m.at(i, c))
		{
			neighs.push_back(m(i, c));
			break;
		}
	}
	// right
	for (long i = r + 1; i < m.width(); ++i)
	{
		if (m.at(i, c))
		{
			neighs.push_back(m(i, c));
			break;
		}
	}
	// top
	for (long j = c - 1; j >= 0; --j)
	{
		if (m.at(r, j))
		{
			neighs.push_back(m(r, j));
			break;
		}
	}
	// bottom
	for (long j = c + 1; j < m.height(); ++j)
	{
		if (m.at(r, j))
		{
			neighs.push_back(m(r, j));
			break;
		}
	}
	return neighs;
}

float skill(const std::vector<size_t>& n)
{
	if (n.size() == 0)
	{
		return 0;
	}
	return std::accumulate(std::begin(n), std::end(n), 0.0f) / n.size();
}

template <typename Index, typename Callable>
void repeat(Index n, Callable f)
{
	for (Index i = 0; i < n; ++i)
	{
		f(i);
	}
}

auto read_board()
{
	size_t r, c;
	std::cin >> r >> c;
	Mat m {r, c};
	for (size_t i = 0; i < r; ++i)
		for (size_t j = 0; j < c; ++j)
		{
			std::cin >> m(i, j);
		}
	return m;
}

auto get_score(const Mat& m)
{
	size_t score = 0;
	for (size_t i = 0; i < m.width(); ++i)
		for (size_t j = 0; j < m.height(); ++j)
		{
			if (m.at(i, j))
			{
				score += m(i, j);
			}
		}
	return score;
}

bool eliminate(Mat& m)
{
	bool cont = false;
	for (size_t i = 0; i < m.width(); ++i)
		for (size_t j = 0; j < m.height(); ++j)
		{
			if (not m.at(i, j))
			{
				continue;
			}
			auto neighbours = get_neighbours(m, i, j);
			auto avg_skill = skill(neighbours);
			if (avg_skill > m(i, j))
			{
				m.mark(i, j);
				cont = true;
			}
		}
	m.eliminate();
	return cont;
}

auto solve(size_t k, Mat& m)
{
	size_t score = 0;
	// size_t round = 1;
	while (true)
	{
		auto s = get_score(m);
		score += s;
		bool cont = eliminate(m);
		if (not cont)
		{
			break;
		}
	}
	return score;
}

int main()
{
	size_t n;
	std::cin >> n;
	repeat(n, [](size_t k)
	{
		auto m = read_board();
		auto ans = solve(k, m);
		std::cout << "Case #" << (k+1) << ": " << ans << '\n';
	});
}
