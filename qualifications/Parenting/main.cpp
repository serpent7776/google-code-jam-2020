#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

struct Range
{
	size_t start;
	size_t end;	
};

bool independent(const Range& lhs, const Range& rhs)
{
	const bool rhs_is_later = rhs.start >= lhs.end;
	const bool rhs_is_earlier = rhs.end <= lhs.start;
	return rhs_is_later or
		rhs_is_earlier;
}

bool overlaps(const Range& lhs, const Range& rhs)
{
	return !independent(lhs, rhs);
}

struct Peep
{
	bool can(const Range& r)
	{
		return std::all_of(std::begin(jobs), std::end(jobs), [&](const Range& j)
		{
			return independent(r, j);
		});
	}

	void add(Range r)
	{
		jobs.push_back(std::move(r));
	}

	std::vector<Range> jobs;
};

template <typename Callable>
void repeat(unsigned n, Callable f)
{
	for (unsigned i = 0u; i < n; ++i)
	{
		const bool cont = f(i);
		if (not cont)
		{
			break;
		}
	}
}

struct Job
{
	unsigned idx;
	Range r;
};

size_t length(const Range& r)
{
	return r.end - r.start;
}

bool operator<(const Job& lhs, const Job& rhs)
{
	return length(lhs.r) > length(rhs.r);
}

using Jobs = std::multiset<Job>;

Jobs read_jobs()
{
	Jobs jobs;
	size_t no;
	std::cin >> no;
	repeat(no, [&](unsigned n)
	{
		size_t start, end;
		std::cin >> start >> end;
		Range r {start, end};
		jobs.insert({n, r});
		return true;
	});
	return jobs;
}

int main()
{
	size_t n;
	std::cin >> n;
	repeat(n, [](unsigned k)
	{
		Jobs jobs = read_jobs();
		Peep C, J;
		std::string ans = "";
		ans.resize(jobs.size());
		for (const auto job : jobs)
		{
			auto r = job.r;
			auto idx = job.idx;
			if (C.can(r))
			{
				C.add(r);
				ans[idx] = 'C';
			}
			else if (J.can(r))
			{
				J.add(r);
				ans[idx] = 'J';
			}
			else
			{
				ans = "IMPOSSIBLE";
				break;
			}
		}
		std::printf("Case #%u: %s\n", k+1, ans.c_str());
		return true;
	});
}
