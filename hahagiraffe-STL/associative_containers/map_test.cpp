#include <iostream>
#include <map>
#include <string>
using namespace std;

void show(map<string,int> &name_year_map)
{
map<string,int>::iterator iter=name_year_map.begin();
    for(;iter!=name_year_map.end();iter++){
        cout<<iter->first<<" "<<iter->second<<endl; //cha 21
                                                    //chb 22
                                                    //chs 20
    }
}
int main(){
    map<string,int> name_year_map;
    name_year_map["chs"]=20;
    name_year_map["cha"]=21;
    pair<string,int> pa("chb",22);
    name_year_map.insert(pa);
    //map的迭代器
    show(name_year_map);
    map<string,int>::iterator itr1=name_year_map.find("chs");
    if(itr1==name_year_map.end()){
        cout<<"not find\n";
    }
    else{
        cout<<"find "<<itr1->second<<endl;
    }
    cout<<"change key chs "<<endl;
    itr1->second=22;
    show(name_year_map);
    return 0;
}