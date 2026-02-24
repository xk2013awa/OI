#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>

long long int n, x, max, dp[100010];

int main(void)
{
	scanf("%lld", &n);
	
	for (int i = 1; i <= n; i++)
	{
		dp[i] = LLONG_MIN;
	}
	
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &x);
		
		for (int j = i; j > 0; j--)
		{
			dp[j] = std::max(dp[j], dp[j - 1] + j * x); 
		}
	}
	
	for (int i = 1; i <= n; i++)
	{
		max = std::max(max, dp[i]);
	}
	
	printf("%lld", max);
	return 0;
}
