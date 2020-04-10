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

struct Peep
{
	bool can(const Range& r)
	{
		return r.start >= free_at;
	}

	void add(Range r)
	{
		free_at = r.end;
	}

	size_t free_at = 0u;
};

template <typename Callable>
void repeat(unsigned n, Callable f)
{
	for (unsigned i = 0u; i < n; ++i)
	{
		f(i);
	}
}

struct Job
{
	unsigned idx;
	Range r;
};

bool operator<(const Job& lhs, const Job& rhs)
{
	return (lhs.r.start) < (rhs.r.start);
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
	});
}
