std::vector<std::string> getalltagsname(std::string &s){
    std::string tagn="";
    int i=0;
    std::set<std::string>alltags;
    std::vector<std::string>tagsvector;
    if(s[0]=='<' && s[1]=='?'){
        i+=2;
        while(i<s.length() && s[i]!='?')i++;
        i+=2;
    }
    while(i<s.length()){
        if(s[i]=='<'){
            i++;
            if(s[i]=='/'){
                while(i<s.length() && s[i]!='>')i++;
                i++;
            }
            else{
                while(i<s.length() && s[i]!=' ' && s[i]!='/' && s[i]!='>'){
                    tagn+=s[i];
                    i++;
                }
                if(s[i]=='>'){
                    if(alltags.find(tagn)==alltags.end()){alltags.insert(tagn);tagsvector.push_back(tagn);}
                    tagn="";
                    i++;
                }
                else if(s[i]=='/' && s[i+1]=='>'){
                    if(alltags.find(tagn)==alltags.end()){alltags.insert(tagn);tagsvector.push_back(tagn);}
                    tagn="";
                    i+=2;
                }
                else if(s[i]==' '){
                    if(alltags.find(tagn)==alltags.end()){alltags.insert(tagn);tagsvector.push_back(tagn);}
                    tagn="";
                    while(i<s.length() && s[i]!='/' && s[i]!='>')i++;
                    if(s[i]=='/')i+=2;
                    else i++;
                }
            }
        }
        else{
            while(i<s.length() && s[i]!='<')i++;
        }
    }
    return tagsvector;
}

bool isExist(std::string &tag, std::vector<std::string> &alltagsname){
    for(auto s:alltagsname)if(s==tag)return 1;
    return 0;
}
