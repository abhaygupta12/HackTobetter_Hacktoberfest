int lengthOfLongestSubstring(string s) {
        set<char> st;
        int x=0,y=0,mx=0;
        int n=s.size();
        while(x<n){
            if(st.find(s[x])==st.end()){
                st.insert(s[x++]);
                mx=max(mx,(int)st.size());
            }
            else{
                while(s[y]!=s[x]){
                    st.erase(s[y++]);
                }
                x++;
                y++;
            }
        }
        return mx;
    }
