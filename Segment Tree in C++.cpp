#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

class ST{
public:
    vector<int> st,lazy;
        ST(int n){
            st.resize(4*n);
            lazy.resize(4*n);
        }

        void build(int ind,int low, int high, int arr[]){
            if(low==high){
                st[ind]=arr[low];
                return ;
            }
            int mid=(low+high)>>1;
            build(2*ind+1,low,mid,arr);
            build(2*ind+2,mid+1,high,arr);

            st[ind]=st[2*ind+1]+st[2*ind+2];
        }

        
    	void update(int ind,int low, int high, int l, int r, int val){
            if(lazy[ind]!=0){
                st[ind]+=(high-low+1)*lazy[ind];

                if(low!=high){
                    lazy[2*ind+1]+=lazy[ind];
                    lazy[2*ind+2]+=lazy[ind];
                }
                lazy[ind]=0;
            }

            // no overlap
            // don't do anything return
            if(high<l || r<low){
                return;
            }

            // complete overlap
            // l low  high r
            if(low>=l && high<=r){
                st[ind] +=(high-low+1)*val;
                if(low!=high){
                    lazy[2*ind+1]+=val;
                    lazy[2*ind+2]+=val;
                }
                return;
            }
            int mid=(low+high)>>1;
            update(2*ind+1,low,mid,l,r,val);
            update(2*ind+2,mid+1,high,l,r,val);
            st[ind]=st[2*ind+1]+st[2*ind+2];
        }

        int query(int ind, int low, int high, int l, int r){
            if(lazy[ind]!=0){
                st[ind]+=(high-low+1)*lazy[ind];

                if(low!=high){
                    lazy[2*ind+1]+=lazy[ind];
                    lazy[2*ind+2]+=lazy[ind];
                }
                lazy[ind]=0;
            }

            if(high<l || r<low){
                return 0;
            }

            if(low>=l && high<=r) return st[ind];

            int mid=(low+high)>>1;
            int left=query(2*ind+1,low,mid,l,r);
            int right=query(2*ind+2,mid+1,high,l,r);
            return left+right;
        }
};

int main() {
	cout << "Hello Friends\n";
	
	// Sample Array 
	int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int n = sizeof(arr)/sizeof(arr[0]);
	
	ST obj(n);
	
	// The Segment Tree is built for our given array. 
	obj.build(0, 0, 10, arr);
	
	// The Segment Tree Array is prnted.
	for(int i=0; i<2*n; i++) cout<< obj.st[i]<< " ";
	cout<< endl;
	
	// The Segment Tree is updated with  a value in a given range.
	obj.update(0, 0, 10, 3, 4, 3);
	
	// The Segment Tree Array is prnted.
	for(int i=0; i<2*n; i++) cout<< obj.st[i]<< " ";
	cout<< endl;
	
	// A Query with a given range is called.
	obj.query(0, 0, 10, 3, 4);
	
	// The Segment Tree Array is prnted.
	for(int i=0; i<2*n; i++) cout<< obj.st[i]<< " ";
	cout<< endl;
	
	return 0;
}
