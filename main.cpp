/// IP CALCULATOR - C++
/// NICOI ALEXANDRU
/// https://github.com/tr0yyy/IP-CALCULATOR-CPP
/// FACULTY OF MATHEMATICS AND COMPUTER SCIENCE, UNIVERSITY OF BUCHAREST

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdlib>

#define INT_MAX 8

using namespace std;

void write_ip(ostream& out, vector<int> ip)
{
    for(unsigned int i = 0 ; i <= 3 ; i++)
        if(i != 3)
            out << ip[i] << ".";
        else out << ip[i] << endl;
}



string int2binary(int x)
{
    int i = 0;
    string binary;
    while (i < INT_MAX)
    {
        i += 1;
        int c = x & 1;
        char* c_char = new char;
        itoa(c,c_char,10);
        binary.append(c_char);
        x >>= 1;
    }
    reverse(binary.begin(), binary.end());
    return binary;
}

void write_ip_binary(ostream& out, vector<int>ip)
{
        for(unsigned int i = 0 ; i <= 3 ; i++)
        if(i != 3)
            out << int2binary(ip[i]) << ".";
        else out << int2binary(ip[i]) << endl;
}

int binary2int(string x)
{
    int y = 0;
    for(auto i = x.begin() ; i != x.end() ; ++i)
    {
        y <<= 1;
        if(*i == '0')
            continue;
        else
            y = y | 1;
    }
    return y;
}

string mask2binary(int x)
{
    string binary;
    string c = ".";
    string one = "1";
    string zero = "0";
    for(int i = 1 ; i <= 32 ; i++)
        {
            if(x != 0){
                binary.append(one);
                x--;}
            else binary.append(zero);
            if(i % 8 == 0 && i != 32)
                binary.append(c);    
        }
    return binary;
}

vector<int> mask_calculator(int x)
{
    vector <int> v;
    for(int i = 1 ; i <= x / 8 ; i++)
        v.push_back(255);
    int y = x - ((x / 8) * 8);
    string y_string;
    for(int i = 0 ; i < 8 ; i++)
        if(y > 0)
            {
                y_string.append("1");
                y--;
            }
        else y_string.append("0");
    v.push_back(binary2int(y_string));
    return v;
}

vector<int> get_network_adress(vector<int> ip , vector<int> mask)
{
    vector<int> na;
    for(int i = 0 ; i <= 3 ; i++)
    {
        if((ip[i] & mask[i]) == ip[i])
             na.push_back(ip[i]);
        else
        {
            string byte;
            string ip_byte = int2binary(ip[i]);
            string mask_byte = int2binary(mask[i]);
            int OK = 1;
            for(int j = 0 ; j < 8 ; ++j)
                {
                    if(mask_byte[j] == '1' && OK == 1)
                    {
                        if(ip_byte[j] == '0')
                            byte.append("0");
                        else byte.append("1");
                    }
                    else if(mask_byte[j] == '0')
                    {   OK = 0;
                        byte.append("0");}
                }
            na.push_back(binary2int(byte));
            byte.erase();
        }
    }
    return na;
}

vector<int> get_broadcast_adress(vector<int> ip , vector<int> mask)
{
    vector<int> ba;
    for(int i = 0 ; i <= 3 ; i++)
    {
        if((ip[i] & mask[i]) == ip[i])
             ba.push_back(ip[i]);
        else
        {
            string byte;
            string ip_byte = int2binary(ip[i]);
            string mask_byte = int2binary(mask[i]);
            int OK = 1;
            for(int j = 0 ; j < 8 ; ++j)
                {
                    if(mask_byte[j] == '1' && OK == 1)
                    {
                        if(ip_byte[j] == '0')
                            byte.append("0");
                        else byte.append("1");
                    }
                    else if(mask_byte[j] == '0')
                    {   OK = 0;
                        byte.append("1");}
                }
            ba.push_back(binary2int(byte));
            byte.erase();
        }
    }
    return ba;
}

vector<int> get_default_gateway(vector<int> na)
{
    vector<int> dgw = na;
    if(dgw[3] < 255)
        dgw[3]++;
    else
    {
        dgw[3] = 0;
        if(dgw[2] < 255)
            dgw[2]++;
            else
            {
                dgw[2] = 0;
                if(dgw[1] < 255)
                    dgw[1]++;
                    else
                    {
                        if(dgw[0] < 255)
                            dgw[0]++;
                            else
                            {
                                cout << "EROARE! NU SE POATE! (DEPASESTE LUNGIMEA POSIBILA IPV4)" << endl;
                                system("pause");
                                exit(EXIT_FAILURE);
                            }
                    }
                    
            }
            
    }
    return dgw;
    

}

vector<int> get_dns_server(vector<int> ba)
{
    vector<int> dns = ba;
    if(dns[3] > 1)
        dns[3]--;
    else
    {
        dns[3] = 255;
        if(dns[2] > 1)
            dns[2]--;
            else
            {
                dns[2] = 0;
                if(dns[1] > 1)
                    dns[1]--;
                    else
                    {
                        if(dns[0] > 1)
                            dns[0]--;
                            else
                            {
                                cout << "EROARE! NU SE POATE! (DEPASESTE LUNGIMEA POSIBILA IPV4)" << endl;
                                system("pause");
                                exit(EXIT_FAILURE);
                            }
                    }
                    
            }
            
    }
    return dns;
    

}

void write_range(ostream& out, vector <int> lower , vector <int> upper)
{
    for(unsigned int i = 0 ; i <= 3 ; i++)
        if(i != 3)
            out << lower[i] << ".";
        else out << lower[i] << " - ";
    for(unsigned int i = 0 ; i <= 3 ; i++)
        if(i != 3)
            out << upper[i] << ".";
        else out << upper[i] << endl;
}

void read_ip(istream& in, vector<int>& ip)
{
    cout << endl;
    cout << "Pentru a citi ip-ul , vei citi fiecare numar ce constituie un octet\n";
    cout << "Adica pentru 192.168.0.1 vei citi pe rand fiecare numar (192, 168, 0 si 1)\n";
    for(int i = 0 ; i < 4 ; i++)
    {
        cout << "Octet " << i + 1 << " : ";
        int x;
        in >> x;
        ip.push_back(x);
    }
}

int mask_ip_to_mask(vector <int> ip)
{
    int cnt = 0;
    for(int i = 0 ; i < 4 ; i++)
    {
        int aux = ip[i];
        while(aux){
            cnt += (aux & 1);
            aux >>= 1;}
    }
    return cnt;
}

class MenuInterface
{
private:
    static int opt;
public:
    MenuInterface(int opt_aleasa = 0)
    {
        opt = opt_aleasa;
    }
    /// constructor prin copiere nu are sens pentru ca am un singur membru private static
    ~MenuInterface()
    {
        opt = 0;
    }
    static void menu_init()
    {
        system("cls");
        cout << "----------------------NICOI ALEXANDRU // tr0yyy // https://github.com/tr0yyy/----------------------\n";
        cout << "---------------------------------------IP CALCULATOR - v0.7----------------------------------------\n";
        cout << "-------------------------CALCULATOR DE IP-URI DE UTILIZAT LA MATERIILE-----------------------------\n";
        cout << "--------------------------------------RETELE 1 & RETELE 2------------------------------------------\n";
        cout << "-------------------ANUL 2 - CALCULATOARE SI TEHNOLOGIA INFORMATIEI - FMI UNIBUC--------------------\n";
        cout << "\n";
        cout << "1. Generare raport IP (masca, network address, broadcast address, range address).\n";
        cout << "2. WIP.\n";
        cout << "3. WIP.\n";
        cout << "0. Iesire.\n";
        cout << "\n\n";
        cout << "Optiunea aleasa: ";
    }
    static void set_opt(int opt_aleasa){opt = opt_aleasa;}
    static int get_opt(){return opt;}
    /// nu voi face supraincarcare pe operatori pentru ca ma voi folosi doar de setter in problema
    static void opt1()
    {
        vector<int> ip;
        read_ip(cin,ip);
        cout << "\nCum vrei sa citesti masca? (1. IP , 2. Numar direct): ";
        int option;
        cin >> option;
        vector <int> mask;
        if(option == 1)
            read_ip(cin,mask);
        else
        {
            int x;
            cin >> x;
            mask = mask_calculator(x);
        }
        vector <int> na = get_network_adress(ip,mask);
        vector <int> ba = get_broadcast_adress(ip,mask);
        vector <int> dgw = get_default_gateway(na);
        vector <int> dns = get_dns_server(ba);
        system("cls");
        cout << "IP SCRIS: ";
        write_ip(cout, ip);
        cout << "\nMASCA DE RETEA: ";
        write_ip(cout, mask);
        cout << "\nNETWORK ADDRESS: ";
        write_ip(cout,na);
        cout << "\nBROADCAST ADDRESS: ";
        write_ip(cout,ba);
        cout << "\nRANGE ADDRESS: ";
        write_range(cout,dgw,dns);
    }
    static void opt2();
    static void opt3();
};

int MenuInterface::opt;

void menu()
{

    MenuInterface m;
    int opt;
    do {
        system("cls");
        m.menu_init();
        cin >> opt;
        m.set_opt(opt);
        switch (m.get_opt())
        {
            case 1:
                m.opt1();
                system("pause");
                break;
            case 2:
                //m.opt2();
                cout << "\n Optiune invalida! \n";
                system("pause");
                break;
            case 3:
                //m.opt3();
                cout << "\n Optiune invalida! \n";
                system("pause");
                break;
            case 0:
                system("pause");
                exit(0);
                break;
            default:
                cout << "\n Optiune invalida! \n";
                system("pause");
                break;
        }
    }while(opt != 0);
}


int main() {
    menu();
    return 0;
}