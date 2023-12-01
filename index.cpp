#include<iostream>
#include<string.h>
#include<fstream>
#include<unistd.h>
#include<windows.h>
#include<conio.h>
#if defined(_WIN32)
    #define CLR system("cls");
#else
    #define CLR system("clear");
#endif
using namespace std;

class college {
    private:
        char name[100];
        char address[200];
        int strength;
    public:
        int no_of_branches;
        char branch[10][100];
        int br_strg[10];
        college() { for(int i=0 ; i<10 ; i++) br_strg[i] = 0; } 
        college(char nm[], char addr[], int strg, int br = 0) {
            strcpy(name, nm);
            strcpy(address, addr);
            strength = strg;
            no_of_branches = br;
            for(int i=0 ; i<10 ; i++) br_strg[i] = 0;
        }
        void input(char nm[], char addr[], int strg, int br = 0) {
            strcpy(name, nm);
            strcpy(address, addr);
            strength = strg;
            no_of_branches = br;
        }
        bool append_branch(char brch[], int b_strg) {
            int sum = 0;
            for(int i=0 ; i<10 ; i++) sum = sum + br_strg[i];
            if((sum + b_strg) > strength) return false;
            strcpy(branch[no_of_branches], brch);
            br_strg[no_of_branches] = b_strg; 
            no_of_branches++;
            return true;
        }
        void new_strength(int strg) {
            strength = strg;
        }
        char* ret_name() {
            return name;
        }
        char* ret_addr() {
            return address;
        }
        int ret_str() {
            return strength;
        }
};

void menuUI(){ 
    cout.fill('-');
    cout.width(100);
    cout << "" << endl;
    cout << "           | G9 |           COLLEGE ADMISSION SYSTEM                                                " << endl;
    cout << "           | -- |           powered by c++                                                          " << endl;
    cout.width(100);
    cout << "" << endl;
    cout.fill(' ');
}

void line(){
        cout << "----------------------------------------------------------------------------------------------------" << endl;
}
void nav(){ 
    cout << "\t   | " << endl;
    cout << "\t   |---[ 1 ] Register a New College               " << endl;
    cout << "\t   |---[ 2 ] Edit Strength of a College           " << endl;
    cout << "\t   |---[ 3 ] To Add New Branch to a College       " << endl;
    cout << "\t   |---[ 4 ] To view Details of a College         " << endl;
    cout << "\t   |---[ 5 ] To Exit                              " << endl;
    cout << "\t   |" << endl;
    cout << "\t   |---[Enter Code] : ";
}
void thanks_page() { 
    cout<<"LOADING THANK YOU PAGE ..."<<endl;
    sleep(2);
    system("Color 0B");
    cout<<"############################################################"<<endl;
    cout<<"#                                                          #"<<endl;
    cout<<"#     ####### #  # #### ##  # # #    # # #### #  #         #"<<endl;
    cout<<"#        #    #### #  # # # # ##      #  #  # #  #         #"<<endl;
    cout<<"#        #    #  # #### #  ## ##      #  #  # #  #         #"<<endl;
    cout<<"#        #    #  # #  # #   # # #     #  #### ####         #"<<endl;
    cout<<"#                                                          #"<<endl;
    cout<<"#                                                          #"<<endl;
    cout<<"#                                                          #"<<endl;
    cout<<"############################################################"<<endl;

    cout<<"HAVE A GREAT DAY"<<endl;
    sleep(3);
}

void invalid_page(){ 
    cout<<"OOPS.."<<endl;
    sleep(1);
    cout<<"############################################"<<endl;
    cout<<"#                                          #"<<endl;
    cout<<"#    # ## # #   # #   #   # ##             #"<<endl;
    cout<<"#    # # ##  # # ###  #   # # #            #"<<endl;
    cout<<"#    # #  #   # #   # ### # ##             #"<<endl;
    cout<<"#                                          #"<<endl;
    cout<<"#     ## # # ### #  ## ###                 #"<<endl;
    cout<<"#    #   ### # # # #   ##                  #"<<endl;
    cout<<"#     ## # # ### #  ## ###                 #"<<endl;
    cout<<"#                                          #"<<endl;
    cout<<"############################################"<<endl<<endl;

    cout<<"TRY AGAIN .."<<endl;
    sleep (3);
}
bool create_college(char cname[100], char addr[100], int strg) { 
    college *cp = new college(cname, addr, strg);
    if(cp == NULL) return false;
    else {
        ifstream fin; fin.open(cname, ios::binary | ios::in);
        if(fin) {
            fin.close();
            return false; 
        }
        fin.close();
        ofstream fout;
        fout.open(cname, ios::out | ios::binary);
        fout.write((char*) &(*cp), sizeof(college));
        if(fout.bad()){
            delete cp;
         return false;
          }
        else {
            delete cp; 
            return true; 
        }
    }
}
void register_clg(){
    char name[100],address[100];
    int strength;
    CLR;
    menuUI();
    cout << " Main Menu > Register New College" << endl;
    line();
    cout << "\n\n";
    cout<<"\t\t Enter College Name     : ";
    cin.ignore();
    cin.getline(name,100); 
    cout<<"\t\t Enter College Address  : ";
    cin.getline(address,100);
    cout<<"\t\t Enter College Strength : ";
    cin>>strength;
    cout << "\tNote :- Once you Register you cannot change college name or address\n";
    cout << "\n\tDo you want to edit info added above ? \n";
    cout << "\t   1. Yes, I want to edit \n";
    cout << "\t   2. No, Proceed to Registration\n"; 
    cout << "\t   Enter your choice: ";
    int choice;
    cin >> choice;
    if(choice == 1){
        register_clg();
    }
    else if(choice == 2){
        bool create=create_college(name,address,strength);
        if(create){
            for(int i=0;i<5;i++){
                CLR;
                menuUI();
                cout << " Main Menu > Register New College > Registration Status" << endl;
                line();
                cout << "\n\n";
                cout << "                               Registration Successfull ! ! !" << endl;
                cout << "\n";
                cout << "                               College Name     : " << name << endl;
                cout << "                               College Address  : " << address << endl;
                cout << "                               College Strength : " << strength << endl;
                cout << "\n";
                cout<<"you'll be redirected to Main Menu in"<<5-i<<"secs\n";
                sleep(1);
            }
        }
        else{
            for(int i=0;i<5;i++){
            CLR;
            menuUI();
            cout << " Main Menu > Register New College > Registration Status" << endl;
            line();
            cout<<"                             College Registration Failed"<<endl;
            cout<<"                             Please try again."<<endl;
            cout<<"     you'll be redirected to Main Menu in"<<5-i<<"secs"<<endl;
            sleep(1);
           
        }
}
    }
}

void view_details(){ 
    CLR
    char cname[100];
    menuUI();
    cout << " Main Menu > View Details " << endl;
    line();
    cout << "\n\n";
    cout << "\t\tEnter Name Of College : "; cin.ignore(); cin.getline(cname, 100);
    college *cp = new college;
    if(cp == NULL){
        CLR
        for(int i=0 ; i<7 ; i++) {
            CLR
            menuUI();
            cout << " Main Menu > View Details > error" << endl;
            line();
            cout << "\n\n";
            cout << "                              OOPS !!! " << endl;
            cout << "                      Something went Wrong !!! " << endl;
            cout << "\n\n";
            cout << "      Redirecting to Main Menu in " << 7-i << " s" << endl;
            sleep(1);
        }
        delete cp;
    }
    else {
        ifstream fin;
        fin.open(cname, ios::in | ios::binary);
        fin.read((char*)&(*cp), sizeof(college));
        if(!fin) {
            CLR
            for(int i=0 ; i<7 ; i++) {
                CLR
                menuUI();
                cout << " Main Menu > View Details > error" << endl;
                line();
                cout << "\n\n";
                cout << "                              OOPS !!! " << endl;
                cout << "            College Not Found Please Enter valid name !!! " << endl;
                cout << "\n\n";
                cout << "      Redirecting to Main Menu in " << 7-i << " s" << endl;
                sleep(1);
            }
            delete cp;
        }
        else {
            CLR
            menuUI();
            cout << " Main Menu > View Details > " << cname << endl;
            line();
            cout << "\n\n";
            cout << "\t\tCollege Name     : " << cp->ret_name() << endl;
            cout << "\t\tCollege Address  : " << cp->ret_addr() << endl;
            cout << "\t\tCollege Strength : " << cp->ret_str() << endl;
            cout << "------------------------------------------------------------" << endl;
            for(int i=0 ; i<cp->no_of_branches ; i++) {
                if(i == 0) {
                    cout.width(40);
                    cout.setf(ios::left, ios::adjustfield);
                    cout << "Branches Offered ";
                    cout.width(40);
                    cout.setf(ios::left, ios::adjustfield);
                    cout << "Strength " << endl;
                }
                cout.width(40);
                cout << cp->branch[i];
                cout.width(40);
                cout << cp->br_strg[i] << endl;
            }
            cout << "\n\n";
            cout << "------------------------------------------------------------" << endl;
            cout << "\n";
            cout << "\t Press any key to exit to Main Menu... " << endl;
            char c; cin >> c;
        }
    }
}

void append_branch(){
    CLR
    char cname[100];
    char bname[100];
    int b_strg;
    menuUI();
    cout << " Main Menu > Append Branch " << endl;
    line();
    cout << "\n\n";
    cout << "\t Enter College Name         : "; cin.ignore(); cin.getline(cname, 100);
    ifstream fin;
    fin.open(cname, ios::in | ios::binary);
    college *cp = new college;
    if(fin) {
        cout << "\t Enter Branch to be appnded : "; cin.getline(bname, 100);
        cout << "\t Enter Strength of Branch   : "; cin >> b_strg;
        fin.read((char*)&(*cp), sizeof(college));
        bool app_br = cp->append_branch(bname, b_strg);
        fin.close();
        if(app_br) {
            ofstream fout;
            fout.open(cname, ios::out | ios::binary);
            fout.write((char*)&(*cp), sizeof(college));
            fout.close();
            fin.open(cname, ios::in | ios::binary);
            fin.read((char*)&(*cp), sizeof(college));
            for(int i=0 ; i<7 ; i++) {
                CLR
                menuUI();
                cout << " Main Menu > Append Branch > " << cname << endl;
                line();
                cout << "\n\n";
                cout << "\t\tCollege Name     : " << cp->ret_name() << endl;
                cout << "\t\tCollege Address  : " << cp->ret_addr() << endl;
                cout << "\t\tCollege Strength : " << cp->ret_str() << endl;
                cout << "------------------------------------------------------------" << endl;
                for(int i=0 ; i<cp->no_of_branches ; i++) {
                if(i == 0) {
                    cout.width(40);
                    cout.setf(ios::left, ios::adjustfield);
                    cout << "Branches Offered ";
                    cout.width(40);
                    cout.setf(ios::left, ios::adjustfield);
                    cout << "Strength " << endl;
                }
                cout.width(40);
                cout << cp->branch[i];
                cout.width(40);
                cout << cp->br_strg[i] << endl;
                }
                cout << "\n\n";
                cout << "------------------------------------------------------------" << endl;
                cout << "\n";
                cout << "  Redirecting to Main Menu " << 7-i << endl;
                sleep(1);
            }
        }
        else {
            CLR
            for(int i=0 ; i<7 ; i++) {
                CLR
                menuUI();
                cout << " Main Menu > View Details > error" << endl;
                line();
                cout << "\n\n";
                cout << "                              OOPS !!! " << endl;
                cout << "                   College Strength Exceeded !!! " << endl;
                cout << "\n\n";
                cout << "      Redirecting to Main Menu in " << 7-i << " s" << endl;
                sleep(1);
            }
        }
        delete cp;
    } 
    else {
        CLR
        for(int i=0 ; i<7 ; i++) {
            CLR
            menuUI();
            cout << " Main Menu > View Details > error" << endl;
            line();
            cout << "\n\n";
            cout << "                              OOPS !!! " << endl;
            cout << "            College Not Found Please Enter valid name !!! " << endl;
            cout << "\n\n";
            cout << "      Redirecting to Main Menu in " << 7-i << " s" << endl;
            sleep(1);
        }
        delete cp;
    } 
}
void edit_strength(){
    CLR
    char cname[100];
    int strg;
    menuUI();
    cout << " Main Menu -> Edit Strength" << endl;
    line();
    cout << "\n\n";
    cout << "\t Enter College Name: "; cin.ignore(); cin.getline(cname, 100);
    ifstream fin;
    fin.open(cname, ios::in | ios::binary);
    college *cp = new college;
    if(fin) {
        cout << "\t Enter new strength         : "; cin >> strg;
        fin.read((char*)&(*cp), sizeof(college));
        cp->new_strength(strg);
        fin.close();
        ofstream fout;
        fout.open(cname, ios::binary|ios::out);
        fout.write((char*)&(*cp), sizeof(college));
        fout.close();
        fin.open(cname, ios::in | ios::binary);
        fin.read((char*)&(*cp), sizeof(college));
            CLR
            menuUI();
            cout << " Main Menu -> Edit Strength -> " << cname << endl;
            line();
            cout << "\n\n";
            cout << "\t\tCollege Name     : " << cp->ret_name() << endl;
            cout << "\t\tCollege Address  : " << cp->ret_addr() << endl;
            cout << "\t\tCollege Strength : " << cp->ret_str() << endl;
            cout << "------------------------------------------------------------" << endl;
            for(int i=0 ; i<cp->no_of_branches ; i++) {
                if(i == 0) {
                    cout.width(40);
                    cout.setf(ios::left, ios::adjustfield);
                    cout << "Branches Offered ";
                    cout.width(40);
                    cout.setf(ios::left, ios::adjustfield);
                    cout << "Strength " << endl;
                }
                cout.width(40);
                cout << cp->branch[i];
                cout.width(40);
                cout << cp->br_strg[i] << endl;
            }
            cout << "\n\n";
            cout << "------------------------------------------------------------" << endl;
            cout << "\n";
            cout << " Press any key to return to Main Menu \n" <<  endl;
            getch();
            delete cp;
    }
    else {
        {
            CLR
            menuUI();
            cout << " Main Menu -> View Details -> error" << endl;
            line();
            cout << "\n\n";
            cout << "Entered College Not Found."<<endl;
            cout<<"Please Enter valid name !" << endl;
            cout<<"\n \n ";
            cout << "Press any key to return to Main Menu "<< endl;
            getch();
        }
        delete cp;
    }
}

int main() { 
    bool run_prg = true;
    int choice;
    while(run_prg) {
        CLR
        menuUI();
        cout << " Main Menu " << endl;
        line();
        nav();
        cin >> choice;
        switch(choice) {
            case 1:
                register_clg();
                break;
            case 2:
                edit_strength();
                break;
            case 3:
                append_branch();
                break;
            case 4:
                view_details();
                break;
            case 5:
                thanks_page();
                run_prg = false;
                break;
            default:
                invalid_page();
                break;
        }
    }
    return 0;
}
