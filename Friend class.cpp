#include<iostream>
using namespace std;

class Alpha
{
	private:
		int a1;
	public:
      Alpha(int arg =0)    
        {
        	a1=arg;
        }
        friend class Beta;  //beta class can access the feature of Alpha class bcox we can created beta class as friend of alpha
};
class Beta
{
	private:
		int b1;
	public:
     Beta(int arg =0)    
        {
        	b1=arg;
		}
		 int sum()
		 {
		 	Alpha alpha_obj(3);
		 	int sum = alpha_obj.a1+b1;
		 	return sum;
		 }
};
int main()
{
	Beta beta_obj(7);
	int b=beta_obj.sum();
	cout<<b;
}


// all member function of Beta class can access the private data of alpha,
