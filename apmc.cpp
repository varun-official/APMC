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

void setline(int num){
  for(int i = 0; i < num; i++)
    cout << endl;
}

void putSpace(int num){
   for(int i = 0; i < num; i++)
          cout << " ";
}
void paddedOutput(string s,int padding,int underline = 0){
    putSpace(padding);
    cout << s;
}


map<string,string> cropnamemap;
map<string,string> cropidmap;
map<string,data> totalcrop;
map<string,userdata>trans_user;
//map<string,transaction>trans_crop;
vector<transaction> trans_crop;

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

    system("cls");
    hedder();
    menu("SignUp Page");

    string ph,na,add,pass;
    ofstream file;
    file.open("user.txt",ios::app);
    setline(3);
    putSpace(55);
  cout<<"Enter the phone number:";
  putSpace(2);
  getline(cin,ph);
      setline(2);
    putSpace(55);
  cout<<"Enter the name:";
  putSpace(2);
  getline(cin,na);
        setline(2);
    putSpace(55);
  cout<<"Enter the Address:";
  putSpace(2);
  getline(cin,add);
        setline(2);
    putSpace(55);
  cout<<"Enter the Password:";
  putSpace(2);
  getline(cin,pass);
  int res = search(ph) ;

    system("cls");
    hedder();
    menu("SignUp Page");

  if(res)
  {
          setline(3);
    putSpace(55);
      cout<<"SignUp is unsuccessful";
          setline(1);
    putSpace(55);
      cout<<"User already exits";
      Sleep(2000);

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
       setline(3);
      putSpace(57);

      cout<<"SignUp is successful\n";
            putSpace(57);
      cout<<"Press enter to login";
            putSpace(2);

      getchar();
      system("cls");
  }
}

void user::signin()
{
    system("cls");
    hedder();
    menu("LOGIN Page");
    string ph,pass;
    setline(3);
    putSpace(55);
  cout<<"Enter the phone number:";
  putSpace(2);
  getline(cin,ph);
  setline(2);
  putSpace(55);
  cout<<"Enter the Password:";
  putSpace(2);
  getline(cin,pass);

  int isregisrter = search(ph);

  if(!isregisrter)
  {
    system("cls");
    hedder();
    menu("LOGIN MENU");
    setline(3);
    putSpace(50);
    cout<<"User is Not registred Yet";
    setline(2);
    putSpace(50);
    cout<<"Press enter to register....!";
    getchar();
  }
 int res = isuser(ph,pass);

 if(res)
 {
     gov g;
     apmcs a;
     displayuser d;
    system("cls");
    hedder();
    menu("LOGIN MENU");
    setline(3);
     putSpace(57);
     cout<<"SignIn successfull\n";
     Sleep(3000);
     switch(res)
     {
         case 3 : system("cls");
                  g.gov_menu();
                    break;
         case 2:   system("cls");
                    a.apmc_menu();
                    break;
         case 1:    system("cls");
                    d.user_menu(ph);
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

     string choice;
    while(choice!="3")
    {
        system("cls");
        hedder();
        cout<<"\n\t\t\t\t\t     +++++++++++Government DashBoard +++++++++++\n";
        setline(3);
        putSpace(60);
        cout<<"1.Add Crop";
        setline(1);
        putSpace(60);
		cout<<"2.Upadte MSP";
                setline(1);
        putSpace(60);
		cout<<"3.Update Tax";
                setline(1);
        putSpace(60);
		cout<<"4.Create APMC";
                setline(1);
        putSpace(60);
		cout<<"5.SignOut";
                setline(2);
        putSpace(60);
		  cout<<"Enter the choice:";
          putSpace(2);
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
            case 5: system("cls");
                    return;

            default:
                    {
                      cout<<"\n\n\t\t\tWrong choice.....!!!";
					  cout<<"\n\t\t\tPress enter to continue....!!";
					  getchar();
                    }
        }
    } 
    system("cls");

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
      system("cls");
      hedder();
      cout<<"\n\t\t\t\t\t     +++++++++++Add Crop Details +++++++++++\n";

    setline(3);
    putSpace(55);
    cout<<"Enter the Crop ID:";
    putSpace(2);
    getline(cin,cropid);

    setline(2);
    putSpace(55);
    cout<<"Enter the Crop name:";
    putSpace(2);
    getline(cin,cropname);

    setline(2);
    putSpace(55);
    cout<<"Enter the MSP:";
    putSpace(2);
    getline(cin,cropmsp);

      system("cls");
      hedder();
      cout<<"\n\t\t\t\t\t     +++++++++++Add Crop Details +++++++++++\n";

    if(!(cropnamemap.find(cropname) == cropnamemap.end())) 
    {
        setline(3);
        putSpace(52);
        cout<<"Crop already in the list of MSP\n";
        Sleep(2000);
    }
    else{
      pack(cropname,cropmsp,cropid);
      setline(3);
      putSpace(52);
      cout<<"Crop Added to the list of MSP\n";
      Sleep(2000);
    }

}
void gov::update_msp(){
        system("cls");
        hedder();
        cout<<"\n\t\t\t\t\t     +++++++++++Update MSP Price +++++++++++\n";

        setline(2);
      
      for(auto x: totalcrop)
      {
        putSpace(42);
        cout<<x.first<<"\t\t"<<x.second.n<<"\t\t"<<x.second.m;
        setline(1);

      }

    fstream file("mspindex.txt",ios::out|ios::in);

    string id,newmsp;
     setline(3);
     putSpace(19);
     cout<<"\n\n\t\t\t\t\t Enter the id of the Crop thats msp to be updated:";
     putSpace(2);
     getline(cin,id);

    if(cropidmap.find(id)==cropidmap.end())
    {
        system("cls");
        hedder();
        cout<<"\n\t\t\t\t\t     +++++++++++Update MSP Price +++++++++++\n";

        setline(3);
         putSpace(30);
        cout<<"Crop is not Present in the MSP list:";
        Sleep(2000);
    }
    else
    {
         setline(3);
         putSpace(55);
         cout<<"Enter the new MSP:";
         putSpace(2);
         getline(cin,newmsp);

        string newcrop = totalcrop[id].n;
        int oldpos = stoi(cropidmap[id]);

        file.seekp(oldpos,ios::beg);
        file.put('*');

        pack(newcrop,newmsp,id);

        file.close();

        system("cls");
        hedder();
        cout<<"\n\t\t\t\t\t     +++++++++++Update MSP Price +++++++++++\n";

        setline(3);
        putSpace(57);
        cout<<"MSP is Updated"<<endl;
        Sleep(2000);

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



     string choice;
    while(choice!="3")
    {
        system("cls");
        hedder();
        putSpace(5);
        menu("APMC MENU");
        setline(3);
        putSpace(60);
        cout<<"1.Buy Crop";
        setline(2);
        putSpace(60);
		cout<<"2.Create User";
        setline(2);
        putSpace(60);
		cout<<"3.Exit";
        setline(2);
        putSpace(60);
		cout<<"Enter the Choice:";
        putSpace(2);
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

        system("cls");
        hedder();
        putSpace(5);
        menu("Buy Crop");

       ofstream file,file1,file2;
       file.open("apmctrans.txt",ios::app);
       file1.open("userdetile.txt",ios::app | ios::ate);
       file2.open("userdetileindex.txt",ios::app | ios::ate);
       user u1;
       string fid,cropid;
       setline(3);
       putSpace(55);
       cout<<"Enter the Farmer ID:";
       putSpace(2);
       getline(cin,fid);

       int res = u1.search(fid);

       if(!res)
       {
                system("cls");
                hedder();
                putSpace(5);
                menu("Buy Crop");

                setline(3);
                putSpace(30);

        cout<<"Farmer is not registred yet Please Register Farmer\n"<<endl;
         cout<<"Press enter to continue....!!";
		getchar();
       }
       else
       {
                system("cls");
                hedder();
                putSpace(5);
                menu("Buy Crop");

                setline(3);
                 for(auto x: totalcrop)
                 {
                    putSpace(50);
                    cout<<x.first<<"\t\t"<<x.second.n<<"\t\t"<<x.second.m<<endl;

                 }

                 setline(3);
                    putSpace(40);
                
                cout<<"Enter the Crop Id that is you want to buy: ";
                putSpace(1);
                getline(cin,cropid);

                res = stoi(cropidmap[cropid]);

                if(!res)
                {
                    setline(3);
                    putSpace(40);
                    cout<<"Crop entred is not bought here\n";

                }
                else{
                    int cropmsp = stoi(totalcrop[cropid].m);
                    int apmcprice,cropkg;

                    string apprice,kgstring;
                     setline(1);
                    putSpace(40);
                    cout<<"Enter the APMC price of the crop (for quintal): ";
                    putSpace(2);
                    getline(cin,apprice);
                    apmcprice = stoi(apprice);
                    while(apmcprice<cropmsp)
                    {
                        system("cls");
                        hedder();
                        putSpace(5);
                        menu("Buy Crop");
                        setline(3);
                       putSpace(40);
                        cout<<"APMC price is less than MSP,";
                        setline(1);
                       putSpace(40);
                        cout<<"Enter the price greter than or equal to MSP";
                        setline(1);
                       putSpace(40);
                        cout<<"Enter the APMC price of the crop";
                        putSpace(1);
                        getline(cin,apprice);
                        apmcprice = stoi(apprice);

                        system("cls");
                        hedder();
                        putSpace(5);
                        menu("Buy Crop");
                        setline(3);

                 for(auto x: totalcrop)
                 {
                    putSpace(50);
                    cout<<x.first<<"\t\t"<<x.second.n<<"\t\t"<<x.second.m<<endl;

                 }
                    }
                        setline(1);
                       putSpace(40);
                    cout<<"Enter the wight of the crop that farmer sold(in quintal): ";
                    putSpace(2);
                    getline(cin,kgstring);
                    cropkg = stoi(kgstring);
                    int total_crop_price = cropkg * apmcprice;

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

                        system("cls");
                        hedder();
                        putSpace(5);
                        menu("Bill Details");

                            setline(3);
                            putSpace(48);
                            cout<<"Farmer ID:  ";
                            putSpace(20);
                            cout<<fid<<endl;
                            putSpace(48);
                            cout << "Bill Date: ";
                            putSpace(21);
                            cout<<(tPtr->tm_mday)<<"/"<< (tPtr->tm_mon)+1 <<"/"<< (tPtr->tm_year)+1900<< endl;
                            putSpace(48);
                            cout<<"Crop Id that to be Sold:  ";
                            putSpace(6);
                            cout<<cropid<<endl;
                            putSpace(48);
                            cout<<"Crop Name that to be Sold: ";
                            putSpace(5);
                            cout<<totalcrop[cropid].n<<endl;
                            putSpace(48);
                            cout<<"MSP of the Crop:  ";
                            putSpace(14);
                            cout<<cropmsp<<endl;
                            putSpace(48);
                            cout<<"APMC Price of the Crop:  ";
                            putSpace(7);
                            cout<<apmcprice<<endl;
                            putSpace(48);
                            cout<<"Total Kg that is sold:  ";
                            putSpace(8);
                            cout<<cropkg<<endl;
                            putSpace(48);
                            cout<<"Total amount without APMC tax:  ";
                            cout<<total_crop_price<<endl;
                            putSpace(48);
                            cout<<"APMC Tax for the Crop:  ";
                            putSpace(8);
                            cout<<total_tax<<endl;
                            putSpace(38);
                            cout<<"---------------------------------------------------------  "<<endl;
                            putSpace(50);
                            cout<<"Garand total:  ";
                            putSpace(15);
                            cout<<after_tax<<endl;

                            setline(3);
                            putSpace(50);
                            cout<<"Thank you for Visiting\n";
                            setline(2);
                            putSpace(50);
                            cout<< "Please press enter to continue\n";
                            getchar();



                }

       }

    }

                    /*Display user funcations*/

  void trans_unpack(string id)
  {
      fstream file("apmctrans.txt",ios::binary|ios::in);
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

                    if(fid==id){
                        trans_crop.push_back(t);
                    }

              }
                    i=0;
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

     string choice;
    while(choice!="3")
    {
        system("cls");
        hedder();
        menu("User Menu");
        setline(3);
        putSpace(60);
        cout<<"1.Your Report";
        setline(2);
        putSpace(60);
		cout<<"2.Know the MSP";
        setline(2);
        putSpace(60);
		cout<<"3.Exit";
        setline(2);
        putSpace(60);
		cout<<"Enter the choice:";
        putSpace(3);
        getline(cin,choice);
        int c = stoi(choice);
        switch(c)
        {
            case 1: report(id);
                        break;
            case 2:  get_msp();
                        break;
            case 3: system("cls");
                    return;

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
      load_user();

      if(res)
      {
              system("cls");
              hedder();
              menu("Your Transcation");

              setline(3);
              putSpace(55);
		      cout<<"Farmer ID:   ";
              putSpace(18);
              cout<<u.phoneno<<endl;
              putSpace(55);
		      cout<<"Farmer Name:   ";
              putSpace(16);
              cout<<u.name<<endl;
              putSpace(55);
		      cout<<"Farmer Address:   ";
              putSpace(13);

              cout<<u.address<<endl;

              if(trans_user.find(id)==trans_user.end())
              {
		      setline(1);
                     putSpace(55);
                    cout<<"Total Crop sold(in quintal):   ";
                    cout<<0<<endl;
                     putSpace(55);
                    cout<<"Total Tax Paid to APMC:   ";
                    putSpace(6);
                    cout<<0<<endl;
                     putSpace(55);
                    cout<<"Total Income :   ";
                    putSpace(14);
                    cout<<0.000<<endl;

                setline(3);
                putSpace(55);
		      cout<<"You didnot Sold Any Crop in APMC"<<endl;
              setline(1);
                putSpace(55);
		      cout<<"Press Enter to continue";
              putSpace(3);
              getchar();

                  
              }else{
                    int y =stoi(trans_user[id].datapos);
                    v.userin_unpack(y);
                     putSpace(55);
                    cout<<"Total Crop sold(in quintal):   ";
                    cout<<v.kg<<endl;
                     putSpace(55);
                    cout<<"Total Tax Paid to APMC:   ";
                    putSpace(5);
                    cout<<v.tax<<endl;
                     putSpace(55);
                    cout<<"Total Income :   ";
                    putSpace(14);
                    cout<<v.income<<endl;

               trans_unpack(u.phoneno);
               setline(3);
               putSpace(50);
              menu("Your Transcation Detaies");

              setline(2);
              for(auto x: trans_crop)
                cout<<x.date<<"\t"<<x.crop_name<<"\t"<<x.price<<"\t"<<x.crop_kg<<"\t"<<x.income_tax<<"\t"<<x.tax<<"\t"<<x.income<<endl;

               setline(3);
               putSpace(55);
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
        setline(2);
         putSpace(58);
        cout<<"Enter the choice:";
         putSpace(2);
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