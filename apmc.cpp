#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
COORD coord = {0, 0};
void gotoxy (int x, int y)	
{
    coord.X = x;
    coord.Y = y; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
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
        role ="1";
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
        string tax;

        void gov_menu();
        void add_crop();
        void update_msp();
        void update_tax();
        void create_apmc();
        void pack(string cname,string msp,string id);
        void load_crop();
};

class data
{
    public:
     string n;
     string m;
};

class userdata
{
    public:
   string datapos;
   string indexpos;
};

class apmcs
{
    public:
        void apmc_menu();
        void buycrop();
};

class displayuser
{
    public:
    string phoneno;
    string name;
    string address;
    string total_kg;
    string no_crop;
    string total_tax;
    string income;

    void user_menu(string);
    void report(string);
    void get_msp();
    void load_user();

};

class userin
{
    public:
      string kg;
      string tax;
      string income;

      void userin_unpack(int);
      void user_delete(int);

};

class transaction
{
    public:
    string date;
    string crop_name;
    string price;
    string crop_kg;
    string income_tax;
    string tax;
    string income;


};

void trans_unpack(string id);

void hedder()
{
    cout<<"\n\t\t\t\t\t***************************************************";
	cout<<"\n\t\t\t\t\t*             APMC MANAGEMENT SYSTEM              *";
	cout<<"\n\t\t\t\t\t***************************************************";   
    cout<<endl;
    cout<<endl;

}

void menu(string str)
{
		cout<<"\n\t\t\t\t\t\t++++++++++++ "<<str<<" ++++++++++++\n";

}


map<string,string> cropnamemap;
map<string,string> cropidmap;
map<string,data> totalcrop;
map<string,userdata>trans_user;
map<string,transaction>trans_crop;

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

            cout<<role<<endl;

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
    system("cls");
    hedder();
    menu("LOGIN MENU");
    string ph,pass;
  cout<<"\n\n\t\t\t\t\t\t\tEnter the phone number:\n";
   cout<<"\n\t\t\t\t\t\t\t   ";
  getline(cin,ph);
  cout<<"\n\t\t\t\t\t\t\tEnter the Password:\n";
  cout<<"\n\t\t\t\t\t\t\t      ";
  getline(cin,pass);

  int isregisrter = search(ph);

  if(!isregisrter)
  {
          system("cls");
    hedder();
    menu("LOGIN MENU");
      cout<<"\n\n\t\t\t\t\t\t       User is Not registred Yet";
      cout<<"\n\n\t\t\t\t\t\t       Press enter to register....!";
      getchar();
  }
 int res = isuser(ph,pass);

 if(res)
 {
     gov g;
     apmcs a;
     displayuser d;
     cout<<"signin successfull\n";
     switch(res)
     {
         case 3 : g.gov_menu();
                    break;
         case 2: a.apmc_menu();
                    break;
         case 1: d.user_menu(ph);
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
system("cls");
}



/*  funactions of goverment */

void gov::load_crop()
{
    data d;

    cropidmap.clear();
    totalcrop.clear();
    cropnamemap.clear();
    fstream file("msp.txt",ios::binary|ios::in);
    string name,msp,id,position,buffer;
     int q,i=0;
     cout<<"in"<<endl;

    while(file.good())
    {
     q = file.tellg();
     position = to_string(q);
     getline(file,buffer);
     if(buffer.length()>0 && buffer[i]!='*')
     {
         while(buffer[i]!='|')
            id+=buffer[i++];
         i++;

         while(buffer[i]!='|')
             name+=buffer[i++];
         i++;

         while(buffer[i]!='$')
             msp+=buffer[i++];

             cout<<id<<"   "<<name<<"   "<<msp<<"    "<<position<<endl;

        d.n=name;
        d.m=msp;

        cropidmap[id]=position;
        cropnamemap[name]=msp;
        totalcrop[id]=d;

     }
     name.erase();
     msp.erase();
     id.erase();
     position.erase();
     buffer.erase();
     i=0;
    }
/*
   for(auto x=cropidmap.cbegin(),y=cropidmap.cend(),m=cropnamemap.crbegin(),n =cropnamemap.cend(); x!=y||m!=n;)
        {
                if(x!=y){
                cout<<x->first<<x->second;
                ++x;
                }
                if(m!=n){
                cout<<m->first<<m->second;
                ++m;
                }
        }
   */

/*
    for(auto x: cropidmap)
    {
        cout<<x.first<<"    "<<x.second<<endl;

    }
    for(auto x: cropnamemap)
    {
        cout<<x.first<<"    "<<x.second<<endl;

    }
*/
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
    string b =id +"|"+ cname + "|" + msp +"$"+"\n";
    int pos = file.tellp();
    file<<b;
    file.close();
}

void gov::add_crop(){
    cout<<"Enter the Crop ID:\n";
    getline(cin,cropid);
    cout<<"Enter the Crop name:\n";
    getline(cin,cropname);
    cout<<"Enter the MSP\n";
    getline(cin,cropmsp);

    if(!(cropnamemap.find(cropname) == cropnamemap.end())) 
    {
        cout<<"\n\t\t\t Crop already in the list of MSP\n";
    }
    else{
      pack(cropname,cropmsp,cropid);
    }

}
void gov::update_msp(){
      
      for(auto x: totalcrop)
        cout<<x.first<<"\t\t"<<x.second.n<<"\t\t"<<x.second.m<<endl;

    fstream file("mspindex.txt",ios::out|ios::in);

    string id,newmsp;

    cout<<"Enter the id of the Crop thats msp to be updated"<<endl;
    getline(cin,id);

    if(cropidmap.find(id)==cropidmap.end())
    {
        cout<<"Crop is not Present in the MSP list";
    }else{
        cout<<"Enter the new MSP"<<endl;
        getline(cin,newmsp);

        string newcrop = totalcrop[id].n;
        int oldpos = stoi(cropidmap[id]);

        file.seekp(oldpos,ios::beg);
        file.put('*');

        pack(newcrop,newmsp,id);

        file.close();
    }
    
}
void gov::update_tax(){

}


/* funcations of the Apmc */

void apmcs::apmc_menu ()
{
    gov g;
    apmcs a;
    user u("1");
    displayuser j;
    j.load_user();
    
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
        cout<<"\n\n\n\t\t\t1.Buy Crop";
		cout<<"\n\t\t\t2.Create User";
		cout<<"\n\t\t\t3.Exit";
		cout<<"\n\t\t\t\t";
        getline(cin,choice);
        int c = stoi(choice);
        switch(c)
        {
            case 1: a.buycrop();
                    j.load_user();
                        break;
            case 2: u.signup();
                        break;
            case 3: return;

            default:
                    {
                      cout<<"\n\n\t\t\tWrong choice.....!!!";
					  cout<<"\n\t\t\tPress enter to continue....!!";
					  getchar();
                    }
        }
    } 

}

void userin::userin_unpack(int pos)
{
     fstream file("userdetile.txt", ios::in |ios::out);
     string buffer,fid;
     file.seekp(pos,ios::beg);

     getline(file,buffer);

    int i=0;
     fid.clear();
     while(buffer[i]!='|')
        fid+=buffer[i++];
    i++;
     kg.clear();
    while(buffer[i]!='|')
        kg+=buffer[i++];

    i++;
     tax.clear();
      while(buffer[i]!='|')
        tax+=buffer[i++];
    i++;
    income.clear();
    while(buffer[i]!='$')
        income+=buffer[i++];
   file.close();
}

void userin::user_delete(int pos)
{
    fstream file("userdetileindex.txt",ios::out|ios::in);
    file.seekp(pos,ios::beg);
    file.put('*');
    file.close();

}

   void apmcs::buycrop (){
       ofstream file,file1,file2;
       file.open("apmctrans.txt",ios::app);
       file1.open("userdetile.txt",ios::app | ios::ate);
       file2.open("userdetileindex.txt",ios::app | ios::ate);
       user u1;
       string fid,cropid;
       cout<<"Enter the Farmer ID\n";
       getline(cin,fid);

       int res = u1.search(fid);

       if(!res)
       {
        cout<<"\n\t\t\tFarmer is not registred yet Please Register Farmer"<<endl;
         cout<<"\n\t\t\tPress enter to continue....!!";
		getchar();
       }
       else
       {
                 for(auto x: totalcrop)
                    cout<<"\n\t\t\t"<<x.first<<"\t\t"<<x.second.n<<"\t\t"<<x.second.m<<endl;
                
                cout<<"\n\t\t\tEnter the Crop Id that is you want to buy\n";
                getline(cin,cropid);

                res = stoi(cropidmap[cropid]);

                if(!res)
                    cout<<"\n\t\t\tCrop entred is not bought here\n";
                else{
                    int cropmsp = stoi(totalcrop[cropid].m);
                    int apmcprice,cropkg;

                    string apprice,kgstring;
                    cout<<"Enter the Local price of the crop (for quintal)\n";
                    getline(cin,apprice);
                    apmcprice = stoi(apprice);
                    while(apmcprice<cropmsp)
                    {
                        cout<<"APMC price is less than MSP\n";
                        cout<<"Plase enter to give APMC price\n";
                        getchar();
                        cout<<"Enter the Local price of the crop\n";
                        getline(cin,apprice);
                        apmcprice = stoi(apprice);
                    }
                    cout<<"Enter the wight of the crop that farmer sold(in quintal)\n";
                    getline(cin,kgstring);
                    cropkg = stoi(kgstring);
                    int pq = cropkg/100;
                    int total_crop_price = pq * apmcprice;

                    float total_tax = total_crop_price*0.03;

                    float after_tax = total_crop_price-total_tax;

                    time_t t = time(NULL);
                    tm* tPtr = localtime(&t);
                    string today = to_string(tPtr->tm_mday)+"/"+to_string((tPtr->tm_mon)+1)+"/"+to_string((tPtr->tm_year)+1900) ;

                    string addtrans = fid+"|"+today+"|"+totalcrop[cropid].n+"|"+apprice+"|"+kgstring+"|"+to_string(total_crop_price)+"|"+to_string(total_tax)+"|"+to_string(after_tax)+"$"+"\n";
                    file<<addtrans;
                    
                    if(trans_user.find(fid)==trans_user.end())
                    {
                        int pos = file1.tellp();
                        string o =fid+"|"+kgstring+"|"+to_string(total_tax)+"|"+to_string(after_tax)+"$"+"\n";
                        file1<<o;
                        string i = fid+"|"+to_string(pos)+"$"+"\n";
                        file2<<i;    
                    
                    }
                    else{
                        userin z;
                        int datapos = stoi(trans_user[fid].datapos);
                        int indexpos = stoi(trans_user[fid].indexpos);
                        z.userin_unpack(datapos);
                        z.user_delete(indexpos);
                         
                         int k = cropkg+stoi(z.kg);
                         int t =total_tax+stoi(z.tax);
                         int f =after_tax+stoi(z.income);

                        int pos = file1.tellp();
                        string o =fid+"|"+to_string(k)+"|"+to_string(t)+"|"+to_string(f)+"$"+"\n";
                        file1<<o;
                        string i = fid+"|"+to_string(pos)+"$"+"\n";
                        file2<<i; 
                        
                    }

                    file.close();
                    file1.close();
                    file2.close();


                            cout<<"\n\t\t************************************************************";
		                    cout<<"\n\t\t\t\t**************** BILL DETILES ****************";
		                    cout<<"\n\t\t*************************************************************\n";

                            cout<<"Farmer ID:  "<<fid<<endl;
                            cout << "Current Date: " <<(tPtr->tm_mday)<<"/"<< (tPtr->tm_mon)+1 <<"/"<< (tPtr->tm_year)+1900<< endl;
                            cout<<"Crop Id that to be Sold:  "<<cropid<<endl;
                            cout<<"Crop Name that to be Sold: "<<totalcrop[cropid].n<<endl;
                            cout<<"MSP of the Crop:  "<<cropmsp<<endl;
                            cout<<"APMC Price of the Crop:  "<<apmcprice<<endl;
                            cout<<"Total Kg that is sold  "<<cropkg<<endl;
                            cout<<"Total amount without APMC tax  "<<total_crop_price<<endl;
                            cout<<"APMC Tax for the Crop  "<<total_tax<<endl;
                            cout<<"--------------------------------------------------------  "<<endl;
                            cout<<"\t\tGarand total:  "<<after_tax<<endl;


                 cout<<"Tahank you for Visiting\n Please press enter to continue\n";
                 getchar();



                }

       }

    }

                    /*Display user funcations*/

  void trans_unpack(string id)
  {
      fstream file("apmctrans.txt",ios::in);
      transaction t;
      string buffer,fid;
      int i=0;
      while(file.good())
      {
          getline(file,buffer);
          if(buffer.length()>0 && buffer[i]!='*')
          {
              fid.clear();
              while(buffer[i]!='|')
                fid+=buffer[i++];
              if(!(fid==id))
                continue;
              else{
                  i++;
                  t.date.clear();
                while(buffer[i]!='|')
                    t.date+=buffer[i++];
                i++;
                t.crop_name.clear();
                while(buffer[i]!='|')
                    t.crop_name+=buffer[i++];
                i++;
                t.price.clear();
                while(buffer[i]!='|')
                    t.price+=buffer[i++];
                i++;
                t.crop_kg.clear();
                while(buffer[i]!='|')
                    t.crop_kg+=buffer[i++];
                i++;
                t.income_tax.clear();
                while(buffer[i]!='|')
                    t.income_tax+=buffer[i++];
                i++;
                t.tax.clear();
                while(buffer[i]!='|')
                    t.tax+=buffer[i++];
                i++;
                t.income.clear();
                while(buffer[i]!='$')
                    t.income+=buffer[i++];

                    trans_crop[fid]=t;
              }
                    i=0;
          }

      }
      
  }

  void displayuser::load_user()
  {
      userdata q;
      trans_user.clear();
    fstream file("userdetileindex.txt",ios::binary|ios::in);
    string buffer,farmerid,posindex,posdata;
    int p,i=0,m;

    while(file.good())
    {
      m = file.tellg();
      posindex = to_string(m);
      getline(file,buffer);
     if(buffer.length()>0 && buffer[i]!='*')
      {
             while(buffer[i]!='|')
              farmerid+=buffer[i++];
                i++;
            while(buffer[i]!='$')
              posdata+=buffer[i++];

              q.datapos = posdata;
              q.indexpos = posindex;

              trans_user[farmerid]=q;
      }
      buffer.clear();
      posdata.clear();
      posindex.clear();
      farmerid.clear();
      i=0;
    }

  }

  void displayuser::user_menu(string id)
  {
       gov g;
      apmcs a;
    
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
        cout<<"\n\n\n\t\t\t1. Your Report";
		cout<<"\n\t\t\t2.Know the MSP";
		cout<<"\n\t\t\t3.Exit";
		cout<<"\n\t\t\t\t";
        getline(cin,choice);
        int c = stoi(choice);
        switch(c)
        {
            case 1: report(id);
                        break;
            case 2:  get_msp();
                        break;
            case 3: return;

            default:
                    {
                      cout<<"\n\n\t\t\tWrong choice.....!!!";
					  cout<<"\n\t\t\tPress enter to continue....!!";
					  getchar();
                    }
        }
    } 

  }

  void displayuser::report(string id)
  {
      user u;
      int res = u.search(id);
      userin v;
      transaction t;
      gov g;
      g.load_crop();

      if(res)
      {

              cout<<"\n\t\t\t***************************************************";
	          cout<<"\n\t\t\t*             APMC MANAGEMENT SYSTEM              *";
	          cout<<"\n\t\t\t***************************************************";
              cout<<"\n\t\t\t\t***************************************";
		      cout<<"\n\t\t\t\t************** Your Complete Report *************";
		      cout<<"\n\t\t\t\t**************************************";


		      cout<<"\n\t\t\t\t Farmaer ID:   "<<u.phoneno<<endl;
		      cout<<"\n\t\t\t\t Farmaer Name:   "<<u.name<<endl;
		      cout<<"\n\t\t\t\t Farmaer Address:   "<<u.address<<endl;

              if(trans_user.find(id)==trans_user.end())
              {
		      cout<<"\n\t\t\t\t Total Crop sold(in quintal):   "<<0<<endl;
		      cout<<"\n\t\t\t\t Total Tax Paid to APMC:   "<<0<<endl;
		      cout<<"\n\t\t\t\t Total Income :   "<<0<<endl;
		      cout<<"\n\t\t\t\t You didnot Sold Any Crop in APMC"<<endl;
		      cout<<"\n\t\t\t\t Press Enter to continue\n"<<endl;
              getchar();

                  
              }else{
                  int y =stoi(trans_user[id].datapos);
                  v.userin_unpack(y);
              cout<<"\n\t\t\t\t Total Crop sold(in quintal):   "<<v.kg<<endl;
		      cout<<"\n\t\t\t\t Total Tax Paid to APMC:   "<<v.tax<<endl;
		      cout<<"\n\t\t\t\t Total Income :   "<<v.income<<endl;
               trans_unpack(u.phoneno);
              cout<<"\n\t\t\t\tYour Selling Detiles\n";

              for(auto x: trans_crop)
                cout<<t.date<<"\t\t"<<t.crop_name<<"\t\t"<<t.price<<"\t\t"<<t.crop_kg<<"\t\t"<<t.income_tax<<"\t\t"<<t.tax<<"\t\t"<<t.income<<endl;

              cout<<"Please press enter to exit this Screen"<<endl;
              getchar();

              }

      }
  }

  void displayuser::get_msp(){
      for(auto x: totalcrop)
        cout<<x.first<<"\t\t"<<x.second.n<<"\t\t"<<x.second.m<<endl;

  }

  



int main()
{
    user u;
   system("cls");
 
    string choice;
    while(choice!="3")
    {
               hedder();

        cout<<"\n";
        menu("MAIN MENU");
        cout<<"\n\n\n\t\t\t\t\t\t\t     1.Login";
		cout<<"\n\t\t\t\t\t\t\t     2.Register";
		cout<<"\n\t\t\t\t\t\t\t     3.Exit";
		cout<<"\n\n\t\t\t\t\t\t\t\t";
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
                      cout<<"\n\n\t\t\t\t\t\tWrong choice.....!!!";
					  cout<<"\n\t\t\t\t\t\tPress enter to continue....!!";
					  getchar();
                      system("cls");
                    }
        }
    }
    return 0;
}