#include <iostream>
#include <stdio.h>

int fact(int n)
{
  if (n <= 1)
      return 1;
  else 
      return n*fact(n-1);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int n;
	cout << "n = "; 
	cin >> n;
	cout << "n! = " << fact(n) << "\n";
	return 0;
}
