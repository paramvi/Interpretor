#include<iostream>
//#include<conio.h>
#include<string.h>
#include<stdio.h>

using namespace std;
char *c;
int i;

class GenListNode{      
      public :
             int flag;
             GenListNode *right;
             GenListNode *down;
             char ch[10];
             GenListNode *makeList();
};
 
 class Value
{
      public:
      int tag;
      int s;
      float f;
      GenListNode *ptr;
};

class Env {            
public:
Value* a[26];
Env* parent;

Env() {
for(int i=0; i<26; i++)
a[i]=NULL;
parent=NULL;
}
};

Value evalNode(GenListNode *p,Env& e);
Value evalList(GenListNode *p,Env& e);
Value funct(GenListNode *p,Value v,Env& e);

  GenListNode *makeList(int k)  
 {             
               i=k;
               GenListNode *curr=new GenListNode;
               GenListNode *head;
               head=curr;
               while(1){
               
               if(c[i]=='('){
                             curr->flag=1;  
                             curr->down=makeList(i+2);
                             if(c[i]!=')'){
                             GenListNode *temp=new GenListNode;
                             curr->right=temp;
                             curr=temp;} 
                             continue;
                            }
                            
               if(c[i]==')'){
                             i=i+2;
                             curr->right=NULL;
                             return head;
                            }
               
               else {
                    int t=0;int j=0;
                    while(c[i]!=' '){
                    
                    curr->ch[j]=c[i];
                    curr->flag=0;
                    j++;
                    t=j;
                     i++;
                    curr->down=NULL;
                                    }
                    curr->ch[t]='\0';
                    i++;
                   }
               
               if(c[i]!=')'){
               GenListNode *temp=new GenListNode;
               curr->right=temp;
               curr=temp;   }
                   
                                }
               
 }

void addToEnv(char x,Value val,Env& e)
{
     Value *va=new Value;
     va->tag=val.tag;
     va->f=val.f;
     va->ptr=val.ptr;
     e.a[x-'a']=va;   
}

Value findInEnv(char x,Env& e)
{
         if(e.a[x-'a']!=NULL)
         return *(e.a[x-'a']);
         
         else{
              if(e.parent==NULL){
              cout<<"Error no match Answer may be wrong "<<endl;
              Value v; v.s=1; 
              return v;         }
              
              else{
                   return findInEnv(x,*(e.parent));
                  }
             }
}                 

Value evalList(GenListNode *p,Env& e)
{     
      if(strcmp(p->ch,"+")==0){   
      Value v1,v2;
      v1=evalNode(p->right,e);
      v2=evalNode(p->right->right,e);
      Value v;
      v.f=v1.f+v2.f;
      v.tag=0; 
      return v;
                    }
                    
      if(strcmp(p->ch,"-")==0){   
      Value v1,v2;
      v1=evalNode(p->right,e);
      v2=evalNode(p->right->right,e);
      Value v;
      v.f=v1.f-v2.f;
      v.tag=0; 
      return v;
                    }
                    
      if(strcmp(p->ch,"*")==0){             
      Value v1,v2;
      v1=evalNode(p->right,e);
      v2=evalNode(p->right->right,e);
      Value v;
      v.f=v1.f*v2.f;
      v.tag=0; 
      return v;
                    }
                    
      if(strcmp(p->ch,"/")==0){              
      Value v1,v2;
      v1=evalNode(p->right,e);
      v2=evalNode(p->right->right,e);
      Value v;
      v.f=(float)(v1.f/v2.f);
      v.tag=0; 
      return v;
                    }
                    
      if(strcmp(p->ch,"%")==0){
      Value v1,v2;
      v1=evalNode(p->right,e);
      v2=evalNode(p->right->right,e);
      Value v;
      int a=v1.f;
      int b=v2.f;
      v.f=(a%b);
      v.tag=0; 
      return v;
                    }
                    
      if(strcmp(p->ch,"==")==0){         
      Value v1,v2;
      v1=evalNode(p->right,e);
      v2=evalNode(p->right->right,e);
      Value v;
      if(v1.f==v2.f)
      v.f=1;
      else
      v.f=0;
      v.tag=0; 
      return v;
                    }
                    
      if(strcmp(p->ch,">=")==0){         
      Value v1,v2;
      v1=evalNode(p->right,e);
      v2=evalNode(p->right->right,e);
      Value v;
      if(v1.f>=v2.f)
      v.f=1;     
      else
      v.f=0;
      v.tag=0; 
      return v;
                    }
                    
      if(strcmp(p->ch,"<")==0){         
      Value v1,v2;
      v1=evalNode(p->right,e);
      v2=evalNode(p->right->right,e);
      Value v;
      if(v1.f<v2.f)
      v.f=1;
      else
      v.f=0;
      v.tag=0; 
      return v;
                    }
                    
      if(strcmp(p->ch,">")==0){        
      Value v1,v2;
      v1=evalNode(p->right,e);
      v2=evalNode(p->right->right,e);
      Value v;
      if(v1.f>v2.f)
      v.f=1;
      else
      v.f=0;
      v.tag=0; 
      return v;
                    }
                    
      if(strcmp(p->ch,"<=")==0){        
      Value v1,v2;
      v1=evalNode(p->right,e);
      v2=evalNode(p->right->right,e);
      Value v;
      if(v1.f<=v2.f)
      v.f=1;
      else
      v.f=0;
      v.tag=0; 
      return v;
                    }
                    
      if(strcmp(p->ch,"if")==0){        
      Value v=evalNode(p->right,e);  
      p=p->right;  
      if(v.f==1)
      return evalNode(p->right,e);
      else
      return evalNode(p->right->right,e);
                     }
       
      if(strcmp(p->ch,"define")==0){     
      Value v=evalNode(p->right->right,e);
      addToEnv(p->right->ch[0],v,e);
      return v;  }
                        
      if(strcmp(p->ch,"while")==0){        
      Value v=evalNode(p->right,e);
      Value v1;
      while(v.f==1){
                    v1=evalNode(p->right->right,e);
                    v=evalNode(p->right,e);
                   }
      return v1;
                                  }
                        
      if(strcmp(p->ch,"set")==0){
      Value v1=findInEnv(p->right->ch[0],e);
      if(v1.s==1)
      return v1;
      
      else{
       Value v=evalNode(p->right->right,e);
      addToEnv(p->right->ch[0],v,e);
      return v;}
                                }
                      
      if(strcmp(p->ch,"begin")==0){   
      p=p->right;
      Value v;                            
      while(p->right!=NULL){
                        evalNode(p,e);
                        p=p->right;    
                           }
      return evalNode(p,e);
                           }
						   
      if(strcmp(p->ch,"lambda")==0){
      Value v;
      v.tag=1;
      v.ptr=p;
      return v;
                                   }
                                   
      if((p->ch[0]-'a')<=26&&(p->ch[0]-'a')>=0&&p->ch[1]=='\0'){
            Value v=findInEnv(p->ch[0],e);
      if(v.tag==1){
                   Value v1=funct(p,v,e); 
                     return v1;
                  }
                                                               }
                  
      if(p->flag==1&&strcmp(p->down->ch,"lambda")==0) {   
      Value v=evalList(p->down,e);
      Value v1=funct(p,v,e);
      return v1;                          }
}

Value evalNode(GenListNode *p,Env& e)
{
      if(p->flag==0){   // it is a atom
                     if((p->ch[0]-'a')<=26&&(p->ch[0]-'a')>=0&&p->ch[1]=='\0'){
                     return findInEnv(p->ch[0],e);             }  
                     
                     else{
                     Value v;
                     v.f=atof(p->ch);
                     v.tag=0;
                     return v;
                         }
                    }
                    
      else   // it is a list
      return evalList(p->down,e);
}

/* void print(GenListNode *p)
{
     if(p!=NULL)
     {
     if(p->flag==0)
     cout<<p->ch<<" ";
     print(p->down);
     print(p->right);           
     }
}
 */
Value funct(GenListNode *p,Value v,Env& e)
{
      Env e1;
      e1.parent=&e;
      GenListNode *k=v.ptr;    // here k is pointing to the keyword "lambda"
      GenListNode *p1=p->right; 
      GenListNode *j=k->right; 
      k=k->right->down;  // first argument of the lambda fucntion
      while(k!=NULL){
                            addToEnv(k->ch[0],evalNode(p1,e),e1);
                            k=k->right;
                            p1=p1->right;
                    }
     
      return evalNode(j->right,e1);   // this is for body evaluation
}
      
int main()
{
    GenListNode *head;
    int n=0;
    c=(char*)malloc(600);
    //strcpy(c,"( begin ( define i 1 ) ( define n 10 ) ( define a 0 ) ( define b 1 ) ( while ( <= i n ) ( begin ( define t ( + a b ) ) ( set a b ) ( set b t ) ( set i ( + i 1 ) ) ) ) a )"); //important test case
    //strcpy(c,"( ( lambda ( z ) ( ( lambda ( x ) ( ( lambda ( y ) ( + 3 y ) ) x ) ) z ) ) 7 )");
    cin.getline(c,600);  
    head=makeList(2);
    Env e;
    //printf("head->ch=%c",c[2]);
    //print(head);
    printf("%s\n",c);
    if(c[2]=='('){
    Value v=evalNode(head,e);
    Value v1=funct(head,v,e);
    cout<<v1.f;
                 }    
     
     else{       
    Value v=evalList(head,e);
    cout<<v.f;
         }
    //getch();
}
