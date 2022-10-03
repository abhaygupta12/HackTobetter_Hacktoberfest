class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int a=0;
        int b=numbers.size()-1;
        while(a<b){
            if((numbers[a]+numbers[b])==target){
                a=a+1;
                b=b+1;
                return {a,b};
            }
            else if((numbers[a]+numbers[b])<target){
                a=a+1;
            }
            else{
                b=b-1;
            }
        }
        return {a,b};
    }
};