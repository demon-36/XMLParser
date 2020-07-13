std::string validTag(std::string s, std::string &x){
    if(s[0]!='<')return "-1";
    std::string tag="";
    for(int i=1;i<s.length();i++){
        if(s[i]=='<')return "-1";
        if(s[i]=='>')return tag;
        if(s[i]==' '){
            while(i<s.length() && s[i]!='/' && s[i]!='>'){x+=s[i];i++;}
            if((s[i]=='/' && s[i+1]=='>') || (s[i]=='>' && s[i-1]=='/')){
                tag+="/";
                return tag;
            }
            if(s[i]=='>')return tag;
        }
        else tag+=s[i];
    }
}

bool isValid(std::string s){
    if(s[0]!='<')return 0;
    int i=0;
    if(s[0]=='<' && s[1]=='?'){
        i+=2;
        while(s[i]!='?')i++;
        i+=2;
    }
    std::stack<std::string>st;
    while(i<s.length()){
        if(s[i]=='<'){
            int xl=0;
            std::string x="";
            std::string tag=validTag(s.substr(i),x);
            if(tag[tag.length()-1]=='/'){i+=tag.length()+x.length()+1+2;continue;}
            if(x.length()>0)xl=x.length()+1;
            if(tag=="-1" || tag=="" || tag=="/" || tag==" ")return 0;
            if(tag[0]=='/'){
                if(st.empty())return 0;
                if(st.top()!=tag.substr(1))return 0;
                st.pop();
            }
            else {st.push(tag);}
            i+=tag.length()+2+xl;
        }
        else if(s[i]=='>')return 0;
        else i++;
    }
    if(!st.empty())return 0;
    return 1;
}

std::string getFile(std::string filename){
    std::string xmldata;
    char c;
    std::ifstream in(filename);
    if(!in){std::cout<<filename<<" not found"; exit(1);}
    while(in.get(c))xmldata+=c;
    in.close();
    return xmldata;
}
