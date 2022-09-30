//Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts

class Solution {
public:
    int maxArea(int h, int w, vector<int>& hc, vector<int>& vc) {
        sort(hc.begin(), hc.end());
        sort(vc.begin(), vc.end());
        int hm, vm, i;
        if(hc.size() == 1) hm = max(hc[0], h-hc[0]);
        else{
            hm = hc[0];
            for(i=1;i<hc.size();i++){
                hm = max(hm, hc[i]-hc[i-1]);
            }
            hm = max(hm, h-hc[hc.size()-1]);
        }
        if(vc.size() == 1) vm = max(vc[0], w-vc[0]);
        else{
            vm = vc[0];
            for(i=1;i<vc.size();i++){
                vm = max(vm, vc[i]-vc[i-1]);
            }
            vm = max(vm, w-vc[vc.size()-1]);
        }
        return (long)hm*vm%1000000007;
    }
};
