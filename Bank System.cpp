#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Person {
public:
    int bankID;
    string firstname;
    string lastname;
    int cardnumber;
    string pin;
    long balance;
    int lasttransaction;
};
//this is used for identification of a function
void mainmenu(Person members[], int Pass);
void showbalance(Person members[], int i){
  char option;
  cout << "               The Bank of NICE\n\n";
  cout << "Card owner: " << members[i].firstname << members[i].lastname << endl;
  cout << "Card number: " << members[i].cardnumber << endl;
  cout << "Current balance in KZT: " << members[i].balance << endl;
  //to typecast from one class to another we use float(int)
  cout << "Current balance in USD: " << float(members[i].balance)/450 << endl;
  cout << "Last transaction: " << members[i].lasttransaction << "KZT\n\n"; 
  cout << "Would you like to return to the main menu?(Y/N) ";
  cin >> option;
  if (option == 'Y'){
    cout << "\n";
    mainmenu(members, i);
  }
  cout << "\n";
}
void pass(string pin, int Pass, Person members[]){
  cout << "Please, try again: ";
  cin >> pin;
  members[Pass].pin = pin;
  //ascii code
  if (pin[0] < 48 || pin[0] > 57 || pin[1] < 48 || pin[1] > 57 || pin[2] < 48 || pin[2] > 57 || pin[3] < 48 || pin[3] > 57){
          pass(pin, Pass, members);
}
  }

//this is used for identification of a function
void Modifying(Person members[]);
void transfer(Person members[], int i){
  bool notaffordable = true;
  cout << "               The Bank of NICE\n\n";
  char verification;
  char option;
  int amount;
  int id;
  string firstname;
  string lastname;
  int cardnumber;
  cout << "Beneficiary's card number: ";
  cin >> cardnumber;
  //traversing the massive to find if it contains the card number of the beneficiary
  for (int i = 0; i < 45; i++){
    if (members[i].cardnumber == cardnumber){
      id = i;
      break;
    }
  }do{
  cout << "Transfer amount (in KZT): ";
  cin >> amount;
  cout << "\n\nBeneficiary's name: ";
  cout << members[id].firstname << members[id].lastname << endl;
  while((amount + 500)  > members[i].balance){
    cout << "Please use an appropriate amount of money to transfer";
    cin >> amount;
  }
  cout << "Confirm transfer?(Y/N) ";
  cin >> verification;
  if (verification == 'Y'){
    if (amount > 19999){
      if (members[i].bankID != members[id].bankID){
        members[i].balance = members[i].balance - (amount + 700);
    members[id].balance = members[id].balance + amount;
    members[i].lasttransaction = -(amount + 700);
    Modifying(members);
      }
      else{
    members[i].balance = members[i].balance - (amount + 500);
    members[id].balance = members[id].balance + amount;
    members[i].lasttransaction = -(amount + 500);
    Modifying(members);
      }
    }
    else {
      if (members[i].bankID != members[id].bankID){
        members[i].balance = members[i].balance - (amount + 200);
    members[id].balance = members[id].balance + amount;
    members[i].lasttransaction = -(amount + 200);
    Modifying(members);
      }
    else{
    members[i].balance = members[i].balance - amount;
    members[id].balance = members[id].balance + amount;
    members[i].lasttransaction = amount;
    Modifying(members);
    }
    }
    cout << "Transfer successful!\n";
    cout << "Would you like to return to the main menu?(Y/N) ";
    cin >> option;
    if (option == 'Y'){
      mainmenu(members,i);
    }
    else{break;}
  }
  else{
    cout << "Transfer canceled.\n";
  }
  }while(verification != 'Y');
}
void modifyPIN(Person members[], int i){
  cout << "               The Bank of NICE\n\n";
  char option;
  bool is_new = false;
  string pin;
  cout << "Please enter your current PIN: ";
  cin >> pin;
  while (pin != members[i].pin){
    cout << "Please, try again: ";
    cin >> pin;
  }
  cout << "Please enter new PIN code: ";
  cin >> pin;
  members[i].pin = pin;
  Modifying(members);
  cout << "New pin is set successfully.\n";
  cout << "Would you like to return to the main menu?(Y/N) ";
  cin >> option;
  if (option == 'Y'){
    cout << "\n";
    mainmenu(members, i);
  }
  cout << "\n";
}

void Modifying(Person members[]){
  ofstream file;
  file.open("ndatabase.csv");
  file << "Bank ID,Name,Card Number,PIN,Balance,Last Transaction" << endl;
  //writing values ​​from a class-Person-massive into a newly formed database
  for (int i = 0; i < 45; i++){;
  file << members[i].bankID << "," << members[i].firstname << members[i].lastname << "," << members[i].cardnumber << "," << members[i].pin << "," << members[i].balance << "," << members[i].lasttransaction << endl;
  }
  remove("database.csv");
  rename("ndatabase.csv","database.csv");
}
void readresults(Person members[]){
      int i = 0;
      char c;
      string dn;
    ifstream file;
    file.open("database.csv");
    //to skip line in database which contains no data about clients of the bank 
    getline(file, dn);
    //rewrites values ​​from a file to each cell of an array of type Person
      while (!file.eof()) {
        file >> members[i].bankID;
        file.get(c);
        file >> members[i].firstname;
        getline(file, members[i].lastname, ',');
        file >> members[i].cardnumber;
        file.get(c);
        getline(file, members[i].pin, ',');
        file >> members[i].balance;
        file.get(c);
        file >> members[i].lasttransaction;
        file.get(c);
         if (++i > 44){
           break;
          }
        }       
    file.close();
}

int findMem(Person members[], int cardnumber, string pin){
  //traversing the array of class Person to find him/her
    for (int i = 0; i < 45; i++){
      if (cardnumber == members[i].cardnumber && pin == members[i].pin){
        //returning its index
        return i;
      }
    }
    return -1;
}

void withdraw(Person members[],int i){
  int withdraw;
  cout << "               The Bank of NICE\n\n";
  char ch;
  cout << "Current balance: " << members[i].balance;
  cout << "\nEnter the amount to withdraw: ";
  cin >> withdraw;
  //to run even if the amount of money to be withdrawn is too big
  while (true){
  if (withdraw <= members[i].balance){
    members[i].balance = members[i].balance - withdraw;
    members[i].lasttransaction =  -(withdraw);
    Modifying(members);
    cout << "Cash withdrawn successfully!\nRemaining balance: "<< members[i].balance<< "\n\nWould you like to return to the main menu?(Y/N) ";
    cin >> ch;
    if (ch == 'Y'){
      cout << "\n";
      mainmenu(members, i);
    }
    else {
      cout << "\n";
      break;
    }
  }
  else {
    cout << "This amount of money exceeds your current balance. \nPlease, enter the appropriate amount to withdraw: ";
    cin >> withdraw;
    
  }
}
}
void deposit(Person members[], int i){
int deposit;
cout << "               The Bank of NICE\n\n";
  char ch;
  cout << "Current balance: " << members[i].balance;
  cout << "\nEnter the amount to deposit: ";
  while (true){
  cin >> deposit;
    members[i].balance = members[i].balance + deposit;
    members[i].lasttransaction = deposit;
    cout << "Cash deposited successfully!\nRemaining balance: "<< members[i].balance<< "\n\nWould you like to return to the main menu?(Y/N) ";
    Modifying(members);
    cin >> ch;
    if (ch == 'Y'){
      cout << "\n";
      mainmenu(members, i);
    }
    else {
      cout << "\n";
      break;
    }
  }
}


void mainmenu(Person members[], int Pass){
  string pin;
  char ch;
  pin = members[Pass].pin;
  //using ascii to find if a char is a number or not
  if (pin[0] < 48 || pin[0] > 57 || pin[1] < 48 || pin[1] > 57 || pin[2] < 48 || pin[2] > 57 || pin[3] < 48 || pin[3] > 57){
      cout << "Dear new client, \nPlease set new PIN for your card (It must be a pure 4-digit code): \n";
      cin >> members[Pass].pin;
      pin = members[Pass].pin;
        if (pin[0] < 48 || pin[0] > 57 || pin[1] < 48 || pin[1] > 57 || pin[2] < 48 || pin[2] > 57 || pin[3] < 48 || pin[3] > 57){
          pass(pin, Pass, members);
      }
      Modifying(members);
      cout << "Would you like to return to the main menu?(Y/N) ";
      cin >> ch;
      if (ch == 'Y'){
        cout << "\n\n";
        mainmenu(members, Pass);
      }
      else {
        cout << "\n";
      }
    }
  
  else {
    int option;
  cout << "               The Bank of NICE\n";
  cout << "Select one of the following options:\n";
  cout << "1. Withdraw Cash                   2. Deposit Cash\n3. Modify PIN Code                 4. Show Balance\n5. Transfer Between Accounts       6. End Session\n";
  cout<<"Enter your choice here: ";
  cin >> option;
  if (option == 1){
    withdraw(members, Pass);
  }
  else if (option == 2){
    deposit (members, Pass);
  }
  else if (option == 3){
    modifyPIN(members, Pass);
  }
  else if (option == 4){
    showbalance(members, Pass);
  }
  else if (option == 5){
    transfer(members, Pass);
  }
  else if (option == 6){
    cout << "Thank you for being a client of our bank. Session is over. Goodbye and come again! \n\n";
  }
}
}

int main() {
  setvbuf(stdout,NULL,_IONBF,0);
  Person members[45];
  int cardnumber;
  string pin;
  int Pass = 0;
  //to run even after ending the session we use while(true)
  while (true){
    cout << "               Welcome to the bank of NICE\n\n";
    cout << "Card number (6 digits): ";
    cin >> cardnumber;
    cout << "PIN code (4 digits): ";
    cin >> pin;
    readresults(members);
    Pass = findMem(members, cardnumber, pin);
    for (int tries = 2; tries > 0; tries--){
    if (Pass == -1 and tries > 0){
      cout << "The card number or PIN is incorrect. Try again!\n";
      cout << "Card number (6 digits): ";
      cin >> cardnumber;
      cout << "PIN code (4 digits): ";
      cin >> pin;
      Pass = findMem(members, cardnumber, pin);
    }
    }
    if (Pass == -1){
      return 0;
    }
  mainmenu(members, Pass);
  }
  return 0;
}

