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

      cout<<"Choose desired option : "<<endl;
      cout<<"\t\t\t1. Get all tags of XML file "<<endl;
      cout<<"\t\t\t2. Search for a particular tag "<<endl;
      cout<<"\t\t\t3. Perform some query operation "<<endl;

      int opt;
      cin>>opt;

      vector<string> alltagsname=getalltagsname(xmldata);

      cin.ignore();
      if(opt==1){
         cout<<"\nAll tags in XML file are : ";
         for(int i=0;i!=alltagsname.size();i++){
            cout<<alltagsname[i]<<" ";
         }
         cout<<endl;
      }
      else if(opt==2){
         cout<<"\nEnter tag name : ";
         string tag;
         cin>>tag;
         bool b=0;
         for(auto st:alltagsname)if(st==tag){b=1;break;}
         if(b==0)cout<<"\nTag not found, try again !"<<endl;
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
      else{
         cout<<"\nSupported queries are : ";
         cout<<"SELECT * : to select all tags available in XML file "<<endl;
         cout<<"\t\t\tSELECT tagname : to search particular tag from XML "<<endl;
         cout<<"\t\t\tSEARCH query : to search query, Ex. : tag[0].tag[1].tag[2] "<<endl;
         cout<<"\t\t\tUPDATE query : to update data, Ex. : tag[0].tag[1].tag[2]=newdata "<<endl;
         cout<<"\t\t\tINSERT query : to add new entry, Ex. : INSERT tag[0].tag[1].tag[2] newtagname newtagvalue "<<endl;

         cout<<"\nEnter query : ";
         string q;
         getline(cin,q);

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
               bool b=0;
               for(int i=0;i<alltagsname.size();i++){
                  if(alltagsname[i]==tasktag)b=1;
               }
               if(b==0)cout<<"\nTag not found, try again !"<<endl;
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
            string last=lasttag(tasktag);
            int ind=lastindex(tasktag);
            string finaltag=searchquery(tagstring, alltagsname, tasktag);
            vector<string>final;
            getData(finaltag,last,final);
            stripTags(final[ind]);
            cout<<"\nValue of "<<last<<" is : "<<final[ind]<<endl;
         }

         else if(head=="UPDATE"){
            string searchtag="";
            string updatetag="";
            int i=0;
            while(i<tasktag.length()){
               if(tasktag[i]==' ')i++;
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
               if(tasktag[i]==' ')i++;
               while(i<tasktag.length()){
                  updatetag+=tasktag[i];
                  i++;
               }
            }
            string tmpdata=xmldata;
            string last=lasttag(searchtag);
            int lastind=lastindex(searchtag);
            int indexofquery=updatequery(tmpdata, alltagsname, searchtag);
            vector<string>final;
            getData(tmpdata,last,final);
            stripTags(final[lastind]);
            string orgvalue=final[lastind];
            string updatedstring="";
            for(int j=0;j<indexofquery;j++)updatedstring+=xmldata[j];
            string subdata=xmldata.substr(indexofquery);
            int found=subdata.find(last);
            if(found!=string::npos){
               for(int j=0;j<found;j++)updatedstring+=subdata[j];
               string subsubdata=subdata.substr(found);
               int f=subsubdata.find(orgvalue);
               subsubdata.erase(f,orgvalue.length());
               subsubdata.insert(f,updatetag);
               updatedstring+=subsubdata;
               cout<<updatedstring<<endl;
               std::ofstream out("updated"+filename);
               out << updatedstring;
               out.close();
            }
            else cout<<"Tag not found, try again !"<<endl;
         }

         else if(head=="INSERT"){
            string searchtag="";
            string newtagname="";
            string newtagvalue="";
            separatetags(searchtag, newtagname, newtagvalue, tasktag);

            string tmpdata=xmldata;
            string last=lasttag(searchtag);
            int lastind=lastindex(searchtag);
            int ii=updatequery(tmpdata, alltagsname, searchtag);
            vector<string>final;
            getData(tmpdata,last,final);
            string tagleftout=final[lastind];

            string subdata=xmldata.substr(ii);
            string updatedstring="";
            for(int i=0;i<ii;i++)updatedstring+=xmldata[i];
            int j=0;
            for(;j<tagleftout.length();j++){
                if(isalnum(tagleftout[j]))break;
            }
            j--;
            string tmp="";
            tmp+=tagleftout[j];
            j++;
            tmp+=tagleftout[j];
            int found=subdata.find(tmp);
            if(found!=string::npos){
               string newtagstring=buildtagstring(newtagname,newtagvalue);
               subdata.insert(found, newtagstring);
               updatedstring+=subdata;
               cout<<updatedstring<<endl;
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
   else cout<<"Invalid XML file"<<endl;
}
