#include<bits/stdc++.h>
using namespace std;

class user
{
public:
    string phoneno;
    string name;
    string address;
    string password;
    string buffer;
    string role;
    string temprole;

    user()
    {
        role ="3";
        temprole=role;
    }

    user(string r)
    {
        role = r;
        temprole=role;

    }

    void signup();
    void signin();
    int search(string key);
    int isuser(string key1,string key2);
    void unpack();
    void pack();
    void user_menu();
};

class gov
{
    public:
        string cropname;
        string cropmsp;
        string cropid;

        void gov_menu();
        void add_crop();
        void update_msp();
        void update_tax();
        void create_apmc();
        void pack(string cname,string msp,string id);
        void load_crop();
};

class pos
{
    public:
    string datapos;
    string indexpath;
};

map<string,pos> crop;

/* funcations of the use */
void user::pack()
{
    buffer.erase();
    buffer = phoneno + "|" + name + "|" + address + "|" + password +"|"+role+"$"+"\n";
}

void user:: unpack()
{
   int i=0;
   phoneno.erase();
   while(buffer[i]!='|')
        phoneno+=buffer[i++];
    i++;
    name.erase();
    while(buffer[i]!='|')
        name+=buffer[i++];
    i++;
    address.erase();
    while(buffer[i]!='|')
        address+=buffer[i++];
    i++;
    password.erase();
    while(buffer[i]!='|')
        password+=buffer[i++];
    i++;
    role.erase();
    while(buffer[i]!='$')
        role+=buffer[i++];
}
int user::search(string key)
{
    int i=0;
    ifstream file("user.txt",ios::in);
    while (file.good())
    {
        buffer.erase();
        getline(file,buffer);
        if(buffer.length()>0)
        {
            unpack();
        }
        else
        {
            file.close();
            return 0;

        }
        if(key == phoneno)
        {
            file.close();
            return 1;

        }
    }
    file.close();
    return 0;
}
int user::isuser(string key1,string key2)
{
    int i=0;
    ifstream file("user.txt",ios::in);
    while (file.good())
    {
        buffer.erase();
        getline(file,buffer);
        if(buffer.length()>0)
        {
            unpack();
            int p = (key1==phoneno);
            int q = (key2==password);

            if(p=q==1)
                return stoi(role);

        }
        else
        {
            file.close();
            return 0;

        }


    }
            file.close();
    return 0;
}

void user::signup()
{
    string ph,na,add,pass;
    ofstream file;
    file.open("user.txt",ios::app);
  cout<<"Enter the phone number\n";
  getline(cin,ph);
  cout<<"Enter the name\n";
  getline(cin,na);
  cout<<"Enter the Address\n";
  getline(cin,add);
  cout<<"Enter the Password\n";
  getline(cin,pass);
  int res = search(ph) ;
  cout<<res<<endl;

  if(res)
  {
      cout<<"\n\t\t\t Signup is unsuccessful";
      cout<<"\n\t\t\t User already exsits";

  }
  else
  {
      phoneno=ph;
      name=na;
      address=add;
      password=pass;
      role=temprole;
      pack();
      file<<buffer;
      buffer.erase();
      file.close();
      cout<<"\n\t\t\t Signup is successful";
      cout<<"\n\n\t\t\t Press enter to login";
      getchar();
  }
}

void user::signin()
{
    string ph,pass;
  cout<<"Enter the phone number\n";
  getline(cin,ph);
  cout<<"Enter the Password\n";
  getline(cin,pass);

  int isregisrter = search(ph);

  if(!isregisrter)
  {
      cout<<"\n\n\t\t\t User is Not registred Yet";
      cout<<"\n\n\t\t\t Press enter to register";
      getchar();
  }
 int res = isuser(ph,pass);

 if(res)
 {
     gov g;
     cout<<"signin successfull\n";
     switch(res)
     {
         case 3 : g.gov_menu();
                    break;
        /* case 2: apmc_menu();
                    break;*/
         case 1: user_menu();
                    break;
        default:
                {
                    cout<<"\n\n\t\t\tError while processing";
                    cout<<"\n\n\t\t\t Press enter to login";
                    getchar();

                }
     }
 }else{
     cout<<"signin not successfull";

 }

}

void user::user_menu()
{

}

/*  funactions of goverment */

void gov::load_crop()
{
    pos p;
    crop.clear();
    ifstream file("mspindex.txt",ios::in);
    string buf,posbuf;
    string cname,cpos;
    while(file.good())
    {
      int q = file.tellg();
      p.indexpath = to_string(q);
      getline(file,buf);

      int i=0;
      if(buf.length()>0 && buf[i]!='*')
      {
        while(buf[i]!='|')
        cname+=buf[i++];
      i++;
         while(buf[i]!='$')
        posbuf += buf[i++];

        p.datapos = posbuf;

        cout<<cname<<"   ";

        crop[cname]=p;
      }
        posbuf.erase();
        cname.erase();
        buf.erase();

    }
    for(auto x: crop)
        cout<<x.first<<"  "<<x.second.indexpath<<endl;
    file.close();

}

void gov::gov_menu()
{

    gov g;
    user u("2");
                    g.load_crop();


    cout<<"\n\t\t\t***************************************************";
	cout<<"\n\t\t\t*             APMC MANAGEMENT SYSTEM              *";
	cout<<"\n\t\t\t***************************************************";

     string choice;
    while(choice!="3")
    {
        cout<<"\n\t\t\t\t***************************************";
		cout<<"\n\t\t\t\t************** MAIN MENU *************";
		cout<<"\n\t\t\t\t**************************************";
        cout<<"\n\n\n\t\t\t1.Add Crop";
		cout<<"\n\t\t\t2.Upadte MSP";
		cout<<"\n\t\t\t3.Update Tax";
		cout<<"\n\t\t\t4.Create APMC";
		cout<<"\n\t\t\t5.Exit";
		cout<<"\n\t\t\t\t";
        getline(cin,choice);
        int c = stoi(choice);
        switch(c)
        {
            case 1: g.add_crop();
                    g.load_crop();
                        break;
            case 2: g.update_msp();
                    g.load_crop();
                        break;
            case 3: g.update_tax();
                        break;
            case 4: u.signup();
                        break;
            case 5: return;

            default:
                    {
                      cout<<"\n\n\t\t\tWrong choice.....!!!";
					  cout<<"\n\t\t\tPress enter to continue....!!";
					  getchar();
                    }
        }
    } 

}

void gov::pack(string cname,string msp,string id )
{
    ofstream file,file1;
    file.open("msp.txt",ios::app | ios::ate);
    file1.open("mspindex.txt",ios::app);
    string b =cname + "|" + msp +"$"+"\n";
    int pos = file.tellp();
    file<<b;
    string smsp = cname+"|" + to_string(pos)+"$"+"\n";
    file1<<smsp;
    file.close();
    file1.close();
}

void gov::add_crop(){
    cout<<"Enter the Crop ID:\n";
    getline(cin,cropid);
    cout<<"Enter the Crop name:\n";
    getline(cin,cropname);
    cout<<"Enter the MSP\n";
    getline(cin,cropmsp);

    if(!(crop.find(cropname) == crop.end())) 
    {
        cout<<"\n\t\t\t Crop already in the list of MSP\n";
    }
    else{
      pack(cropname,cropmsp);
    }

}
void gov::update_msp(){
    fstream file1("mspindex.txt",ios::out|ios::in);
    string name,msp;
    for(auto x:crop)
    {
        cout<<"\n\t\t"<<x.first;
    }
    cout<<endl;
    cout<<"enter the crop name thats MSP to be Updated\n";
    getline(cin,name);

    if((crop.find(name) == crop.end())) 
    {
        cout<<"\n\t\t\t Crop not present in MSP\n";
    }else{
     
     string dps = crop[name].datapos;
     string ips = crop[name].indexpath;
     int dp = stoi(dps);
     int ip = stoi(ips);

     //cout<<file.tellp()<<endl;
     //file.seekp(dp,ios::beg);
     //cout<<file.tellp()<<endl;
     //file.put('*');
     //cout<<file1.tellp()<<endl;
     file1.seekp(ip,ios::beg);
     //cout<<file1.tellp()<<endl;

     file1.put('*');
     file1.seekp(0,ios::beg);
    //cout<<file1.tellp()<<endl;
    cout<<"\n\t\t\t Enter the New MSP\n";
     getline(cin,msp);
     pack(name,msp);
     file1.close();

    }
    
}
void gov::update_tax(){}



int main()
{
    user u;

    cout<<"\n\t\t\t***************************************************";
	cout<<"\n\t\t\t*             APMC MANAGEMENT SYSTEM              *";
	cout<<"\n\t\t\t***************************************************";
 
    string choice;
    while(choice!="3")
    {
        cout<<"\n\t\t\t\t*************************************************";
		cout<<"\n\t\t\t\t******************* MAIN MENU *******************";
		cout<<"\n\t\t\t\t*************************************************";
        cout<<"\n\n\n\t\t\t1.Login";
		cout<<"\n\t\t\t2.Register";
		cout<<"\n\t\t\t3.Exit";
		cout<<"\n\t\t\t\t";
        getline(cin,choice);
        int c = stoi(choice);
        switch(c)
        {
            case 1: u.signin();
                        break;
            case 2: u.signup();
                        break;
            case 3: break;

            default:
                    {
                      cout<<"\n\n\t\t\tWrong choice.....!!!";
					  cout<<"\n\t\t\tPress enter to continue....!!";
					  getchar();
                    }
        }
    }
    return 0;
}