#include <iostream>
#include <vector>

using namespace std;

int main()
{

    vector<long long int> in;
    in.push_back(4);
    in.push_back(4);
    long long int os=1000000000;

    int ii=2;
    while(in[ii-1]<os)
    {
        in.push_back(in[ii-2]+in[ii-1]);
        ii++;
    }

    int ind=in.size()-1;
    while(ind>10)
    {
        long long int asd=in[ind-2];
		if(asd<=os)
		{
			os-=asd;
			ind--;
		}
		else
		{
			ind-=2;
		}
    }


    vector<char> c2;
    vector<char> c1;
    vector<char> cn;
    cn.resize(0);

    c2.push_back('b');
    c2.push_back('u');
    c2.push_back('g');

    c1.push_back('f');
    c1.push_back('e');
    c1.push_back('a');
    c1.push_back('t');
    c1.push_back('u');
    c1.push_back('r');
    c1.push_back('e');

	int szam=0;
    while(szam<ind-1)
    {
        cn=c2;
        for(int i=0;i<c1.size();i++)
        {
            cn.push_back(c1[i]);
        }
        c2=c1;
        c1=cn;

		szam++;
    }

    cout << cn[os-1] << endl;

    return 0;
}
