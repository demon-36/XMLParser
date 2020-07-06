std::string lasttag(std::string &tasktag){
    std::string ans="";
    bool b=0;
    for(int i=0;i<tasktag.length();i++)if(tasktag[i]=='.'){b=1;break;}
    if(b==1){
        int i=tasktag.length()-1;
        while(i){
            if(tasktag[i]=='.'){
                reverse(ans.begin(),ans.end());
                return ans;
            }
            while(i && tasktag[i]!='[')i--;
            i--;
            while(i && tasktag[i]!='.'){ans+=tasktag[i];i--;}
        }
    }
    else{
        int i=0;
        while(i<tasktag.length()){
            if(tasktag[i]=='[')return ans;
            while(i<tasktag.length() && tasktag[i]!='['){ans+=tasktag[i];i++;}
            if(tasktag[i]=='[')return ans;
        }
    }
    return ans;
}

int lastindex(std::string &tasktag){
    int ind;
    int i=tasktag.length()-2;
    std::string tmp="";
    while(i && tasktag[i]!='['){
        tmp+=tasktag[i];
        i--;
    }
    reverse(tmp.begin(),tmp.end());
    ind=stoi(tmp);
    return ind;
}

std::vector<std::string> tagsdata(std::string &xmldata, std::string &tag){
    std::vector<std::string>vs;
    getData(xmldata, tag, vs);
    return vs;
}

std::string searchquery(std::string &xmldata, std::vector<std::string> &alltags, std::string &tasktag){
    int i=0;
    std::string s=xmldata;
    std::string tagname="";
    int x=0;
    std::vector<std::string>v;
    std::string tmp="";
    while(i<tasktag.length()){
        while(i<tasktag.length() && tasktag[i]!='[' && tasktag[i]!=']' && tasktag[i]!='.'){
            tagname+=tasktag[i];
            i++;
        }
        if(tasktag[i]=='['){
            v=tagsdata(s,tagname);
            i++;
            while(i<tasktag.length() && tasktag[i]!=']'){
                tmp+=tasktag[i];
                i++;
            }
        }
        else if(tasktag[i]==']'){
            x=stoi(tmp);
            i++;
            tmp="";
        }
        else if(tasktag[i]=='.'){
            s=v[x];
            tagname="";
            i++;
            x=0;
            v.clear();
        }
    }
    return s;
}

int updatequery(std::string &s, std::vector<std::string> &alltags, std::string &tasktag){
    int i=0;
    std::string tagname="";
    int x=0;
    int index=0;
    std::vector<std::string>v;
    std::string tmp="";
    std::vector<std::vector<std::string> > vt;
    while(i<tasktag.length()){
        while(i<tasktag.length() && tasktag[i]!='[' && tasktag[i]!=']' && tasktag[i]!='.'){
            tagname+=tasktag[i];
            i++;
        }
        if(tasktag[i]=='['){
            v=tagsdata(s,tagname);
            i++;
            while(i<tasktag.length() && tasktag[i]!=']'){
                tmp+=tasktag[i];
                i++;
            }
            v.insert(v.begin(),tagname);
            v.insert(v.begin(),tmp);
        }
        else if(tasktag[i]==']'){
            x=stoi(tmp);
            i++;
            tmp="";
        }
        else if(tasktag[i]=='.'){
            vt.push_back(v);
            x+=2;
            s=v[x];
            tagname="";
            i++;
            v.clear();
        }
    }
    for(int i=vt.size()-1;i>=0;i--){
        for(int j=2;j<vt[i].size();j++){
            if((j-2)<stoi(vt[i][0])){
                index+=vt[i][j].length();
                index+=2*(vt[i][1].length())+5;
            }
            else if((j-2)==stoi(vt[i][0]))index+=vt[i][1].length()+2;
        }
    }
    return index;
}
