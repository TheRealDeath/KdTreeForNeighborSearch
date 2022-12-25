#include <bits/stdc++.h>
using namespace std;


struct resource {
    string name;
    int value;
};

typedef struct coordinate {
    double x;
    double y;
    vector<resource> v;
} coordinate;
bool operator<(coordinate const& compare, coordinate const& c) {
        if(compare.x > c.x) return false;
        if(compare.x < c.x) return true;
        if(compare.y > c.y) return false;
        if(compare.y < c.y) return true;
        return false;
}
bool contains(coordinate const& v,string name) {
        for(auto &x : v.v) 
            if(x.name == name)
                return true;
        return false;
    }
const char* w = " \t\n\r\f\v";
inline std::string& rtrim(std::string& s, const char* t = w)
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}
inline std::string& ltrim(std::string& s, const char* t = w)
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}
inline std::string& trim(std::string& s, const char* t = w)
{
    return ltrim(rtrim(s, t), t);
}
ofstream & operator<<(ofstream &out, coordinate const& x) {
    out << x.x <<  " " << x.y << " ";
    out << "[";
    for(auto &l : x.v) {
        out << "{" << l.name << ", " << l.value << "}";
        out << " "; 
    }
    out << "]";
    return out;
}
ostream& operator<<(ostream &out, coordinate const& x) {
    out << x.x <<  " " << x.y << " ";
    out << "[";
    for(auto &l : x.v) {
        out << "{" << l.name << ", " << l.value << "}";
        out << " "; 
    }
    out << "]";
    return out;
}
bool compare(coordinate const& x, coordinate const& y) {
    int sum1 = 0;
    int sum2 = 0;
    for(auto &z : x.v) sum1 += z.value;
    for(auto &z : y.v) sum2 += z.value;
    return sum1 < sum2;
}
vector<string> tokenize(string s, string del = " ")
{
    vector<string> temp;
    int start, end = -1*del.size();
    do {
        start = end + del.size();
        end = s.find(del, start);
        temp.push_back(s.substr(start, end - start));
    } while (end != -1);
    return temp;
}
coordinate max(set<coordinate> const& v) {
    coordinate temp = *v.begin();
    for(auto i = v.begin()++;i!=v.end();i++)
        if(compare(temp,*i))
            temp = *i;
    return temp;
}
set<coordinate> filter(set<coordinate> const& v, string type) {
    set<coordinate> p;
    for(auto & x : v) 
        if(contains(x,type)) 
            p.insert(x);
    return p;
}

static const string dat[17] = {"Black Pearls","Cactus","Clay","Crystal Deposit","Metal Deposit","Obsidian Deposit","Oil Rock","Oil Vein","Rare Flowers","Rich Metal Deposit","Rockarrot","Salt Deposit","Savoroot","Silica Deposit","Sulfur Deposit","Underwater Metal Deposit","Water Vein"};
static const int value[17] = {100,5,5,25,25,25,25,50,5,100,1,5,1,25,5,25,1};
int main() {
    // system("easyBat.bat");
    /*
        do dijkstras but think of the values as lessened weights so the formula for calculating
        weight is manhattan_distance/value_of_coord
    */
    ifstream fin;
    fin.open("coords.txt");
    map<string, int> values;
    for(int i = 0;i<17;i++) {
        values.insert(make_pair(dat[i],value[i]));
    }
    ofstream fout("out.txt");
    map<pair<double,double>,coordinate> m;
    string temp;
    while(getline(fin,temp,'\n')) {
        // v.push_back(temp);
        string name = tokenize(temp,"title=\"")[1];
        getline(fin,temp);
        vector<string> t = tokenize(temp,", ");
        double x = stof(tokenize(t[0])[1]);
        double y = stof(tokenize(t[1])[1]);
        if(m.find(make_pair(x,y)) == m.end()) {
            vector<resource> te;
            coordinate l = {x,y,te};
            m.insert({make_pair(x,y),l});
        }
        // printf("%s %d\n",name.c_str(),values[trim(name)]);
        resource j = {trim(name),values[trim(name)]};
        m[make_pair(x,y)].v.push_back(j);
    }
    fin.close();
    set<coordinate> s;
    for(auto const& x : m) {
        // fout << x.second << endl;
        s.insert(x.second);
    }
    // cout << s.size(); 2834
    string instruct;
    set<coordinate> filtered = s;
    coordinate player;
    set<coordinate>::iterator iter;
    while(true) {
        cout << "enter input: ";
        getline(cin, instruct);
        vector<string> arr = tokenize(instruct);
        if(arr[0] == "get_max") {
            cout << max(filtered) << endl;
        }
        if(arr[0] == "filter") {
            string query;
            for(auto &x : arr) 
            {
                if(x == "filter") continue;
                query += x +" ";
            }
            filtered = filter(s,trim(query));
        }
        if(arr[0] == "closest") {
            player.x = stof(arr[1]);
            player.y = stof(arr[2]);
            filtered.insert(player);
            iter = filtered.find(player);
        }
        if(arr[0] == "original") {filtered = s;}
        if(arr[0] == "print") {
            for(auto &x : filtered) {
                fout << x << endl;
            }
        }
        if(arr[0] == "next") {
            iter++;
            fout << (*iter) << endl;
        }
        if(arr[0] == "previous") {
            iter--;
            fout << (*iter) << endl;
        }
        if(arr[0] == "delete") {
            filtered.erase(player);
        }
        if(arr[0] == "end") {
            return 0;
        }
    }
}