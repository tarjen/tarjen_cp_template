/*
every pair of pair<int,int> will not intersect
if i is true then it will be in the set
*/
struct SegmentSet{
    set<pair<int,int>>s;
    void write(){
        for(auto [x,y]:s)cout<<x<<"/"<<y<<" ";;cout<<"\n";
    }
    //make l...r to be true
    void insert(int l,int r)
    {
        int L=l,R=r;
        auto it=s.lower_bound(make_pair(L,(int)-2e9));
        while(it!=s.end()&&it->first<=R+1){
            R=max(it->second,R);
            it=s.erase(it);
        }
        if(it!=s.begin()){
            it--;
            if(it->second+1>=L){
                L=min(L,it->first);
                R=max(R,it->second);
                s.erase(it);
            }
        }
        s.insert(make_pair(L,R));
    }
    // if l...r all true return false
    bool query_no_full(int l,int r){
        auto it=s.lower_bound(make_pair(l,(int)-2e9));
        if(it!=s.end()){
            if(l==it->first&&r<=it->second)return false;
        }
        if(it!=s.begin()){
            it--;
            if(it->second>=r)return false;
        }
        return true;
    }
    //make l...r to be false
    void del(int l,int r){
        auto it=s.lower_bound(make_pair(l,(int)-2e9));
        while(it!=s.end()&&it->first<=r){
            if(it->second<=r){
                it=s.erase(it);continue;
            }
            int R=it->second;
            s.erase(it);
            s.insert(make_pair(r+1,R));
            break;
        }
        it=s.lower_bound(make_pair(l,(int)-2e9));
        if(it!=s.begin()){
            it--;
            int L=it->first,R=it->second;
            if(R>=l){
                s.erase(it);
                if(L<=l-1)s.insert(make_pair(L,l-1));
                if(R>=r+1)s.insert(make_pair(r+1,R));
            }
        }
    }
    // if l...r all false return false
    bool query_at_least_one(int l,int r){
        auto it=s.lower_bound(make_pair(l,(int)-2e9));
        if(it!=s.end()){
            if(it->first<=r)return true;
        }
        if(it!=s.begin()){
            it--;
            if(it->second>=l)return true;
        }
        return false;
    }
};