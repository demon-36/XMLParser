void getData(const std::string &text, std::string tag, std::vector<std::string> &all){
   int pos=0, start;
   while(true){
      start=text.find("<"+tag, pos);
      if(start==std::string::npos)return;
      start=text.find(">", start);
      start++;
      pos=text.find("</"+tag, start);
      if(pos==std::string::npos)return;
      all.push_back(text.substr(start, pos-start));
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
