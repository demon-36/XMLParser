void getData(const std::string &text, std::string tag, std::vector<std::string> &all){
   int pos=0, start;
   int x;
   while(true){
      start=text.find("<"+tag, pos);
      x=start;
      if(start==std::string::npos)return;
      start=text.find(">", start);
      start++;
      pos=text.find("</"+tag, start);
      if(pos==std::string::npos)return;
      all.push_back(text.substr(start, pos-start));
   }
}

void getDataUpIn(const std::string &text, std::string &tag, std::vector<std::string> &all){
   int pos=0, start, x;
   while(true){
      start=text.find("<"+tag, pos);
      if(start==std::string::npos)break;
      x=start;
      int sc=text.find("/>",start);
      int c=text.find(">", start);
      if(sc!=std::string::npos){
         if(sc<c){
            pos=sc;
            int l=pos-start+2;
            all.push_back(text.substr(start, pos-start)+"+"+std::to_string(l));
         }
         else{
            start=c;
            int l=start-x+1;
            start++;
            pos=text.find("</"+tag, start);
            if(pos==std::string::npos)break;
            all.push_back(text.substr(start, pos-start)+"+"+std::to_string(l));
         }
      }
      else{
         start=c;
         int l=start-x+1;
         start++;
         pos=text.find("</"+tag, start);
         if(pos==std::string::npos)break;
         all.push_back(text.substr(start, pos-start)+"+"+std::to_string(l));
      }
   }
}

void getDataAttr(const std::string &text, std::string tag, std::vector<std::string> &all, std::string &attr){
   int pos=0, start;
   while(true){
      std::string tmpattr="";
      int spaces=0;
      start=text.find("<"+tag, pos);
      spaces=start;
      if(start==std::string::npos)break;
      std::string subst=text.substr(start);
      int f=subst.find(attr);
      if(f!=std::string::npos){
         int in=f+attr.length()-1;
         while(in<subst.length() && subst[in]!='`' && subst[in]!='"')in++;
         if(subst[in]=='`' || subst[in]=='"'){
            tmpattr+=subst[in];
            in++;
            while(in<subst.length() && subst[in]!='`' && subst[in]!='"'){
               tmpattr+=subst[in];
               in++;
            }
            if(subst[in]=='`' || subst[in]=='"'){tmpattr+=subst[in];in++;}
         }
         while(subst[in]!='>' && subst[in]!='/')in++;
         spaces+=in;
      }
      else return;
      pos=text.find("/>",start);
      if(pos!=std::string::npos && pos==spaces){
         if(tmpattr=="")tmpattr="konyamilyo";
         all.push_back(text.substr(start, pos-start)+"+"+tmpattr);
         pos=spaces;
      }
      else{
         pos=0;
         start=text.find(">", start);
         start++;
         pos=text.find("</"+tag, start);
         if(pos==std::string::npos)break;
         if(tmpattr=="")tmpattr="konyamilyo";
         all.push_back(text.substr(start, pos-start)+"+"+tmpattr);
      }
   }
}

void stripTags(std::string &text){
   int start=0,pos;
   while(start<text.size()){
      start=text.find("<", start);
      if(start==std::string::npos)break;
      pos=text.find(">", start);
      if(pos==std::string::npos)break;
      text.erase(start, pos-start+1);
   }
}

std::string getattrvalue(std::string &finalstr){
   std::string ans="";
   ans+='"';
   for(int i=finalstr.length()-2;i>=0;i--){
      if(finalstr[i]=='"'){
         ans+=finalstr[i];
         reverse(ans.begin(),ans.end());
         return ans;
      }
      else ans+=finalstr[i];
    }
   return ans;
}
