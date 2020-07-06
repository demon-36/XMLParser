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
                i++;
                while(i<s.length() && s[i]!='>'){
                    tagn+=s[i];
                    i++;
                }
                if(s[i]=='>'){
                    tagn="";
                    i++;
                }
            }
            else{
                while(i<s.length() && (s[i]!=' '&& s[i]!='/' && s[i]!='>')){
                    tagn+=s[i];
                    i++;
                }
                if((s[i]=='/' && s[i+1]=='>') || s[i]=='>'){
                    if(alltags.find(tagn)==alltags.end()){alltags.insert(tagn);tagsvector.push_back(tagn);}
                    tagn="";
                    i++;
                }
            }
        }
        else{
            while(i<s.length() && s[i]!='<'){
                i++;
            }
        }
    }
    return tagsvector;
}
