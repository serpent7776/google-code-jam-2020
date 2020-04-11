#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <algorithm>

template <typename Index, typename Callable>
void repeat(Index n, Callable f)
{
	for (Index i = 0; i < n; ++i)
	{
		f(i);
	}
}

auto read_patterns(size_t count)
{
	std::vector<std::string> pats;
	repeat(count, [&pats](auto n) mutable
	{
		std::string s;
		std::cin >> s;
		pats.push_back(s);
	});
	return pats;
}

auto len(const std::string& l, const std::string& r)
{
	return l.size() < r.size();
}

bool ends(std::string const &fullString, std::string const &ending)
{
	if (fullString.length() >= ending.length())
	{
		return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
	}
	else
	{
		return false;
	}
}

std::string solve(size_t k, const std::vector<std::string>& pats)
{
	auto ans = *std::max_element(std::begin(pats), std::end(pats), len);
	std::string longest = {ans.begin() + 1, ans.end()};
	for (auto s : pats)
	{
		std::string s2 = {s.begin() + 1, s.end()};
		if (not ends(longest, s2))
		{
			return "*";
		}
	}
	return longest;
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
