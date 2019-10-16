#include <iostream>
using namespace std;

void hash(int *c)
{
int val=263,mod=73,i;
for(i=0;i<3;i++)
  c[i]=(c[i]*263)%73;
}

int main()
{
  int x[3],y[3];
  cout<<"Enter the number\n";
  for(int i=0;i<n;i++)
      cin>>x[i];
  hash(&x);
  cout<<"Enter the number\n";
  for(int i=0;i<n;i++)
      cin>>y[i];
  hash(&y);
  cout<<x<<y<<endl;
  return 0;

}
