#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <algorithm>

struct Pattern
{
	std::string pre;
	std::string suf;
};

template <typename Index, typename Callable>
void repeat(Index n, Callable f)
{
	for (Index i = 0; i < n; ++i)
	{
		f(i);
	}
}

Pattern make_pat(const std::string& s)
{
	auto star = std::find(std::begin(s), std::end(s), '*');
	std::string pre {std::begin(s), star};
	std::string suf {star + 1, std::end(s)};
	return {pre, suf};
}

std::vector<Pattern> read_patterns(size_t count)
{
	std::vector<Pattern> pats;
	repeat(count, [&pats](auto n) mutable
	{
		std::string s;
		std::cin >> s;
		pats.push_back(make_pat(s));
	});
	return pats;
}

bool ends(const std::string& fullString, const std::string& ending)
{
	if (fullString.length() >= ending.length())
	{
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else
	{
		return false;
	}
}

bool starts(const std::string& fullString, const std::string& beg)
{
	if (fullString.length() >= beg.length())
	{
		return (0 == fullString.compare(0, beg.length(), beg));
	}
	else
	{
		return false;
	}
}

Pattern common(const std::vector<Pattern>& pats)
{
	Pattern common;
	for (auto& p : pats)
	{
		if (p.pre.length() > common.pre.length())
		{
			common.pre = p.pre;
		}
		if (p.suf.length() > common.suf.length())
		{
			common.suf = p.suf;
		}
	}
	return common;
}

std::string solve(size_t k, const std::vector<Pattern>& pats)
{
	Pattern longest = common(pats);
	for (auto p : pats)
	{
		if (not ends(longest.suf, p.suf) or not starts(longest.pre, p.pre))
		{
			return "*";
		}
	}
	std::string s = longest.pre;
	s += longest.suf;
	return s;
}

int main()
{
	size_t n;
	std::cin >> n;
	repeat(n, [](size_t k)
	{
		size_t count;
		std::cin >> count;
		auto pats = read_patterns(count);
		auto ans = solve(k, pats);
		std::cout << "Case #" << (k+1) << ": " << ans << '\n';
	});
}
