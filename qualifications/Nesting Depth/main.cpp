#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

template <typename Callable>
void repeat(size_t n, Callable f)
{
	for (size_t i = 0u; i < n; ++i)
	{
		f(i);
	}
}

template <typename Callable>
void repeat(int n, Callable f)
{
	for (int i = 0u; i < n; ++i)
	{
		f(i);
	}
}

void brace(int diff, std::string* s)
{
	if (diff > 0)
	{
		repeat(diff, [=](int) {s->push_back('(');});
	}
	if (diff < 0)
	{
		repeat(-diff, [=](int) {s->push_back(')');});
	}
}

std::string nest(const std::string& s)
{
	std::string ret;
	int nesting = 0;
	for (const char c : s)
	{
		const int n = c - '0';
		const int diff = n - nesting;
		nesting = n;
		brace(diff, &ret);
		ret.push_back(c);
	}
	brace(-nesting, &ret);
	return ret;
}

int main()
{
	size_t n;
	std::cin >> n;
	repeat(n, [](unsigned k)
	{
		std::string s;
		std::cin >> s;
		std::string ans = nest(s);
		std::printf("Case #%u: %s\n", k+1, ans.c_str());
	});
}
