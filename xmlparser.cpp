#include <bits/stdc++.h>
#include<\headers\headxmlvalid.h>
#include<\headers\headxmlparser.h>
#include<\headers\getalltagsname.h>
#include<\headers\headquery.h>
using namespace std;

int main(){
   cout<<"\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
   cout<<"\t\t\tWelcome to XMLParser "<<endl;
   cout<<"\t\t_________________________________"<<endl;

   string filename;
   cout<<"Enter XML file name : ";
   cin>>filename;

   string xmldata=getFile(filename);

   if(isValid(xmldata)){
      cout<<endl;
      cout<<"XML file is Valid"<<endl<<endl;
      cout<<"type exit to quit !"<<endl<<endl;

      while(1){
         cout<<"Choose desired option : "<<endl;
         cout<<"\t\t\t1. Get all tags of XML file "<<endl;
         cout<<"\t\t\t2. Search for a particular tag "<<endl;
         cout<<"\t\t\t3. Perform some query operation "<<endl;

         string opt;
         cin>>opt;

         vector<string> alltagsname=getalltagsname(xmldata);

         cin.ignore();
         if(opt=="quit" || opt=="exit"){
            exit(0);
         }
         else if(opt=="1"){
            cout<<"\nAll tags in XML file are : ";
            for(int i=0;i!=alltagsname.size();i++){
               cout<<alltagsname[i]<<" ";
            }
            cout<<endl;
         }
         else if(opt=="2"){
            cout<<"\nEnter tag name : ";
            string tag;
            cin>>tag;
            if(!isExist(tag,alltagsname))cout<<"\nTag not found, try again !"<<endl;
            else{
               vector<string>all;
               getData(xmldata, tag, all);
               cout<<"\nData of "<<tag<<" is : ";
               for(string &s:all){
                  stripTags(s);
                  cout<<s<<" ";
               }
               cout<<endl;
            }
         }
         else if(opt=="3"){
            cout<<"\nSupported queries are : ";
            cout<<"Queries are case sensitive, keep that is mind :) "<<endl;
            cout<<"\t\t\tSELECT * : select all tags available in XML file "<<endl;
            cout<<"\t\t\tSELECT tagname : search particular tag from XML "<<endl;
            cout<<"\t\t\tSEARCH query : search any query, Ex query : tag[0].tag[1].tag[2] "<<endl;
            cout<<"\t\t\t\t\t\t\t Ex query : tag[0].tag[1].tag[2][attr] "<<endl;
            cout<<"\t\t\tUPDATE TAG query : update tag data, Ex query : tag[0].tag[1].tag[2]=newdata "<<endl;
            cout<<"\t\t\tUPDATE ATTR query : update attr data, Ex query : tag[0].tag[1].tag[2][attr]=newdata "<<endl;
            cout<<"\t\t\tINSERT TAG query : add new tag, Ex. query : tag[0].tag[1].tag[2] newname newvalue "<<endl;
            cout<<"\t\t\tINSERT ATTR query : add new attr, Ex. query : tag[0].tag[1].tag[2] newattrname newattrvalue "<<endl;

            while(1){
               cout<<"\nEnter query : ";
               string q;
               getline(cin,q);

               if(q=="exit" || q=="quit")break;

               string head=q.substr(0,6);
               string tasktag=q.substr(7);

               if(head=="SELECT"){

                  if(tasktag=="*"){
                     cout<<"\nAll tags in XML file are : ";
                     for(int i=0;i<alltagsname.size();i++){
                        cout<<alltagsname[i]<<" ";
                     }
                     cout<<endl;
                  }

                  else{
                     if(!isExist(tasktag,alltagsname))cout<<"\nTag not found, try again !"<<endl;
                     else{
                        vector<string>all;
                        getData(xmldata, tasktag, all);
                        cout<<"\nData of "<<tasktag<<" is : ";
                        for(string &s:all){
                           stripTags(s);
                           cout<<s<<" ";
                        }
                        cout<<endl;
                     }
                  }
               }

               else if(head=="SEARCH"){
                  string tagstring=xmldata;
                  string attr="";
                  int f=tasktag.find("][");
                  string ttag="";
                  if(f!=string::npos){
                     for(int i=0;i<=f;i++)ttag+=tasktag[i];
                     for(int i=f+2;i<tasktag.length()-1;i++)attr+=tasktag[i];
                  }
                  else{ttag=tasktag;}
                  string last=lasttag(ttag);                  
                  if(!isExist(last,alltagsname)){
                     cout<<"Tag not found, try again ! "<<endl;
                  }
                  else{
                     int ind=lastindex(ttag);
                     string finaltag=searchquery(tagstring, alltagsname, ttag);
                     vector<string>final;
                     if(attr!=""){
                        getDataAttr(finaltag,last,final,attr);
                        if(final.size()==0 || isalnum(finaltag[finaltag.find(attr)+attr.length()]))cout<<"Attribute not found, try again !"<<endl;
                        else{
                           string finalstr=final[ind];
                           if(finalstr.find("konyamilyo")!=string::npos)cout<<"Attribute not found, try again !"<<endl;
                           else{
                              string attrvalue=getattrvalue(final[ind]);
                              if(attrvalue.find("<")!=string::npos && 
                                 ((attrvalue.find("/>")!=string::npos) || 
                                 ((attrvalue.find(">")!=string::npos) && (attrvalue.find("</")!=string::npos)))){
                                    cout<<"Invalid attribute value, value can't have tag inside !"<<endl;
                              }
                              else {
                                 cout<<"Value of "<<last<<"["<<ind<<"]"<<"["<<attr<<"]"<<" is : "<<attrvalue<<endl;
                              }
                           }
                        }
                     }
                     else{
                        string laststr="</"+last+">";
                        if(finaltag.find(laststr)==string::npos)cout<<"Tag not found, try again !"<<endl;
                        else{
                           getData(finaltag,last,final);
                           if(final.size()==0)cout<<"Tag entry not found, try again !"<<endl;
                           else{
                              stripTags(final[ind]);
                              cout<<"\nValue of "<<last<<" is : "<<final[ind]<<endl;
                           }
                        }
                     }
                  }
               }

               else if(head=="UPDATE"){
                  string searchtag="";
                  string updatetag="";
                  string task="";
                  int i=0;
                  while(i<tasktag.length()){
                     if(tasktag[i]==' '){
                        while(tasktag[i]==' ')i++;
                     }
                     while(i<tasktag.length() && tasktag[i]!=' '){
                        task+=tasktag[i];
                        i++;
                        if(tasktag[i]==' '){while(tasktag[i]==' ')i++;break;}
                     }
                     while(i<tasktag.length() && tasktag[i]!='='){
                        searchtag+=tasktag[i];
                        i++;
                        while(tasktag[i]==' ')i++;
                        if(tasktag[i]=='='){
                           i++;
                           break;
                        }
                     }
                     if(tasktag[i]=='=')i++;
                     //if(tasktag[i]==' ')i++;
                     while(i<tasktag.length()){
                        updatetag+=tasktag[i];
                        i++;
                     }
                  }
                  string tmpdata=xmldata;
                  if(task=="TAG"){
                     string last=lasttag(searchtag);
                     if(!isExist(last,alltagsname))cout<<"Tag not found, try again !"<<endl;
                     else{
                        int lastind=lastindex(searchtag);
                        int indexofquery=updatequery(tmpdata, alltagsname, searchtag);
                        while(tmpdata[tmpdata.length()-1]!='+'){
                           tmpdata.pop_back();
                        }
                        tmpdata.pop_back();
                        vector<string>final;
                        getData(tmpdata,last,final);
                        string orgvalue=final[lastind];
                        string findtag=findtagstring(last,orgvalue);
                        string updatedstring="";
                        for(int j=0;j<indexofquery;j++)updatedstring+=xmldata[j];
                        string subdata=xmldata.substr(indexofquery);
                        int found=subdata.find(tmpdata);
                        if(found!=string::npos){
                           for(int j=0;j<found;j++)updatedstring+=subdata[j];
                           string subsubdata=subdata.substr(found);
                           int f=subsubdata.find(findtag);
                           if(f==string::npos)cout<<"Tag not found, try again !"<<endl;
                           else{
                              for(int j=0;j<f;j++)updatedstring+=subsubdata[j];
                              string substrdata=subsubdata.substr(f);
                              int ff=substrdata.find(orgvalue);
                              substrdata.erase(ff,orgvalue.length());
                              substrdata.insert(ff,updatetag);
                              updatedstring+=substrdata;
                              std::ofstream out("updated"+filename);
                              out << updatedstring;
                              out.close();
                              cout<<"File updated successfully"<<endl;
                           }
                        }
                        else cout<<"Tag not found, try again !"<<endl;
                     }
                  }
                  else if(task=="ATTR"){
                     string attr="";
                     int f=searchtag.find("][");
                     string stag="";
                     if(f==string::npos){
                        cout<<"Attribute not found, try again !"<<endl;
                     }
                     else{
                        for(int i=0;i<=f;i++)stag+=searchtag[i];
                        for(int i=f+2;i<searchtag.length()-1;i++)attr+=searchtag[i];
                        string last=lasttag(stag);
                        if(!isExist(last,alltagsname)){
                           cout<<"Tag not found, try again ! "<<endl;
                        }
                        else{
                           string strdata=xmldata;
                           string tmpdata=xmldata;
                           int ind=lastindex(stag);
                           int upindex=updatequery(tmpdata, alltagsname, stag);
                           while(tmpdata[tmpdata.length()-1]!='+'){
                              tmpdata.pop_back();
                           }
                           tmpdata.pop_back();
                           string finaltag=searchquery(strdata, alltagsname, stag);
                           vector<string>final;
                           if(attr!=""){
                              getDataAttr(finaltag,last,final,attr);
                              string finalstr=final[ind];
                              while(finalstr[finalstr.length()-1]!='+'){
                                 finalstr.pop_back();
                              }
                              finalstr.pop_back();
                              if(finalstr.find("konyamilyo")!=string::npos)cout<<"Attribute not found, try again !"<<endl;
                              else{
                                 string attrvalue=getattrvalue(final[ind]);
                                 string updated="";
                                 for(int i=0;i<upindex;i++)updated+=xmldata[i];
                                 string subst=xmldata.substr(upindex);
                                 int fa=subst.find(attr);
                                 for(int i=0;i<fa;i++)updated+=subst[i];
                                 string substa=subst.substr(fa);
                                 int fav=substa.find(attrvalue);
                                 substa.erase(fav,attrvalue.length());
                                 substa.insert(fav,updatetag);
                                 updated+=substa;
                                 std::ofstream out("updated"+filename);
                                 out << updated;
                                 out.close();
                                 cout<<"File updated successfully"<<endl;
                              }
                           }
                           else{
                              cout<<"Attribute not found, try again !"<<endl;
                           }
                        }
                     }
                  }
                  else{
                     cout<<"Invalid query, check and try again !"<<endl;
                  }
               }

               else if(head=="INSERT"){
                  string searchtag="";
                  string newname="";
                  string newvalue="";
                  string task="";
                  separatetags(searchtag, newname, newvalue, tasktag, task);
                  string tmpdata=xmldata;
                  string last=lasttag(searchtag);
                  int lastind=lastindex(searchtag);
                  int ii=insertquery(tmpdata, alltagsname, searchtag);
                  while(tmpdata[tmpdata.length()-1]!='+'){
                     tmpdata.pop_back();
                  }
                  tmpdata.pop_back();
                  string subdata=xmldata.substr(ii);
                  string updatedstring="";
                  for(int i=0;i<ii;i++)updatedstring+=xmldata[i];
                  int found=subdata.find(tmpdata);
                  if(found!=string::npos){
                     if(task=="TAG"){
                        string newtagstring=buildtagstring(newname,newvalue);
                        subdata.insert(found+tmpdata.length(), newtagstring+"\n"+"\t");
                        updatedstring+=subdata;
                        updatedstring+='\n';
                        std::ofstream out("updated"+filename);
                        out << updatedstring;
                        out.close();
                        cout<<"Entry added and file updated successfully"<<endl;
                     }
                     else if(task=="ATTR"){
                        string newattrstring=buildattrstring(newname, newvalue);
                        if(tmpdata.find(last)!=string::npos){
                           subdata.insert(found+tmpdata.length(), newattrstring);
                        }
                        else {subdata.insert(found-1, newattrstring);}
                        updatedstring+=subdata;
                        std::ofstream out("updated"+filename);
                        out << updatedstring;
                        out.close();
                        cout<<"Entry added and file updated successfully"<<endl;
                     }
                     else{
                        cout<<"Invalid query, try again !"<<endl;
                     }
                  }
                  else{
                     cout<<"Oops, something went wrong, try again !"<<endl;
                  }
               }

               else{
                  cout<<"\nInvalid query, check supported queries and try again !"<<endl;
               }
            }
         }
         else {cout<<"Invalid option, try again !"<<endl;}
      }
   }
   else cout<<"Invalid XML file"<<endl;
}
