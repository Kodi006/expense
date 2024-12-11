#include<iostream>
#include<cstring>
#include<unistd.h>
#include<vector>
#include<ctime>
using namespace std;
class history{
    char* time;
    int type;
    double amount;
    double available;
public:
    history(char* str,double amo,double avail,int type):time(str),amount(amo),available(avail),type(type){};
    friend ostream& operator<<(ostream& out,history*);
};



class expense{
    double balence=0;
    vector<history*> memorise;
public:
    expense(){};
    void open(){
        int k=1,var;
        while(k){
            cout<<"1)Please enter 1 if you want to views you history\n2)Please enter 2 if you want to add amount\n3)Please enter 3 if want too remove amount\n4)Please enter 4 to view balance\n5)Please enter 5 to exit\n Please enter your choice: ";
            cin>>var;
            switch(var){
                case 1:{
                    if(this->memorise.size()==0||this->memorise.size()==-1){
                        cout<<"\n\nYour account dont have any history so please add an amount\n\n";
                       

                    }
                    else{
                        for(auto i : memorise){
                            cout<<i<<"\n";

                        }
                        
                    }
                    break;}
                case 2:{
                    double amo;int var1=1;
                        while(var1){
                            cout<<"\n\nEnter the amount you want to add: ";
                        cin>>amo;
                        if(amo<0) cout <<"\n Invalid ,please enter positive value to be added :";
                        else var1=0;
                        }
                        
                        time_t now=time(0);
                        char*dt=ctime(&now);
                        this->balence=this->balence+amo;
                        history *var2=new history(dt,amo,this->balence,1);
                        memorise.emplace_back(var2);
                        cout<<var2<<"\n";     
                    
                    break;}
                case 3:{
                    double amo;int var1=1;
                        while(var1){
                            cout<<"\n\nEnter the amount you want to remove: ";
                        cin>>amo;
                        if(amo<0) cout <<"\n Invalid ,please enter positive value which you want to remove:";
                        else break;
                        }
                        time_t now=time(0);
                        char*dt=ctime(&now);
                        if(this->balence-amo<0) {cout<<"\n\nentered amount is greated than avaiable balance \n\n";break;}
                        this->balence=this->balence-amo;
                        history *var2=new history(dt,amo,this->balence,0);
                        memorise.emplace_back(var2);
                        cout<<var2;     
                    
                    break;}
                case 4:{
                cout<<"\n\n Available balance is :"<<this->balence<<"\n\n";break;
                }
                case 5:{k=0;break;}

            }
        }
    }


};

class User{
    expense * userexpense=NULL;
    string username;
    string password;
public:
    static vector<User*> users;

    User(string name,string pass):username(name),password(pass){User::users.emplace_back(this);};
    bool checkname(string var){
        if(var==this->username) return 1;
    else return 0;

    }
    bool checkpass(string var){
    if(var==this->password) {
        if(this->userexpense==NULL){
            expense *obj=new expense;
            this->userexpense=obj;
            return 1;
        }
        else{
            return 1;
        }
        }
    else return 0;
    }
    void details(){
        if(this->userexpense==NULL){
            expense *obj=new expense;
            this->userexpense=obj;}
        (this->userexpense)->open();
    }
};




ostream& operator<<(ostream& out,history* his){
    if(his->type==1){
out<<" \nadded amount was : "<<his->amount<<" (on "<<his->time<<") and avaiable balaence was "<<his->available<<endl;return out;};

if(his->type==0){
out<<" \n used amount was : "<<his->amount<<" (on "<<his->time<< " ) and avaiable balaence was "<<his->available<<endl;return out;};

return out;
}
vector<User*> User::users; // Define the static member

int main(){
int k=1,var;
while(k){
    cout<<"\n1)enter 1 if you want to register\n2)enter 2 if you want to login\n3)Enter 3 to exit\nEnter the value";
    cin>>var;
switch(var){
    case 1:{
        string name,pass,pass1;
        cout<<"Enter the user name: ";
        cin>>name;
        int kk=1;
        while(kk){
            cout<<"Enter the password: ";
            cin>>pass;
            cout<<"please re enter the password: ";
            cin>>pass1;
            if(pass==pass1) kk=0;
            else{cout<<"\nPassword Not matched please re-enter password\n\n";}
            }
            cout<<"\n\n";
        User* us=new User(name,pass);
        us->details();
        
        break;
        }
    case 2:{
        string name,pass,pass1;
        User *l1=0;
        cout<<"Enter the the user name :";
        cin>>name;
        for(auto i: User::users){
            if(i->checkname(name)){l1=i;break;};
        }
        if(l1!=0){
            while(1){
            cout<<"\nplease enter password: ";
            cin>>pass;
            if(l1->checkpass(pass)) {l1->details();break;}
            else cout<<"\nInvalid Password,please re enter the password.\n\n";
        }
        }
                else {cout<<"Invalid Username.";}

        break;}
    case 3:{k=0;break;}

}
}
    return 0;
}
