#include<iostream>
#include<vector>
#include<algorithm>

int count = 0;

bool canBeExtendedToSolution(std::vector<int>perm)
{
	int i = perm.size()-1;
	for(int j=0;j<i;j++)
	{
		if(i-j == abs(perm[i] - perm[j]))
		{
			return false;
		}
	}
	return true;
}
void extend(std::vector<int>&perm,int n)
{
	if(perm.size() == n)
	{
		// for(int iter = 0;iter<perm.size();++iter)
		// {
		// 	std::cout<<perm[iter]<<" ";
		// }
		std::cout<< ++count << "\n";
		// exit(0);
	}

	for(int iter = 0;iter<n;++iter)
	{
		if(std::find(perm.begin(),perm.end(),iter)==perm.end())
		{
			perm.push_back(iter);
			if(canBeExtendedToSolution(perm))
				extend(perm,n);
			perm.pop_back();
		}
	}
}

int main() 
{ 
	int N = 8;		//Side of ChessBox
	std::vector<int>permutations;
	extend(permutations,N);
}
