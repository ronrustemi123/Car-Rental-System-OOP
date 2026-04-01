/*Ky projekt eshte nje sistem per dhenien me qira te makinave. Ideja kryesore eshte te krijohet
nje mjedis virtual per organizimin e nje agjencie te makinave me qira, duke lejuar perdoruesin te shtoje
makina, klientë dhe te regjistrojë qiratë. Perdoruesi ka mundesine te shohë te dhenat per makinat e
disponueshme, klientet e regjistruar dhe qirate aktive, si dhe te identifikoje makinen me te qiradhene
bazuar ne numrin e qirave. Sistemi mbeshtet operacionet si: shtimi i makinave te reja, regjistrimi i
klienteve, dhenia me qira e makinave, kthimi i tyre, si dhe llogaritja e kostos bazuar ne ditet e qirase
dhe cmimin ditor. Ky aplikacion siguron nje menyre efikase per menaxhimin e nje agjencie te tille.*/


#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_CARS = 50;
const int MAX_CUSTOMERS = 50;
const int MAX_RENTALS = 100;

// ruan rrugën qytetin dhe kodin postar te klientit
struct Address {
    string street;
    string city;
    string zipCode;
};

// ruan te dhenat e klientit me adresen brenda
struct Customer {
    int ID;
    string name;
    string phone;
    Address address;
};

// ruan te dhenat e makines dhe nese eshte e lire
struct Car {
    int ID;
    string brand;
    string model;
    int year;
    double dailyRate;
    bool isAvailable;
};

// ruan nje qira te tere me klientin makinen datat dhe koston
struct RentalRecord {
    Customer customer;
    Car car;
    int startDay;
    int endDay;
    double totalCost;
};

// struktura kryesore qe mban gjithe te dhenat e sistemit
struct RentalSystem {
    string agencyName;
    Car cars[MAX_CARS];
    Customer customers[MAX_CUSTOMERS];
    RentalRecord rentals[MAX_RENTALS];
    int numCars;
    int numCustomers;
    int numRentals;

    // merr te dhenat e makines nga perdoruesi dhe e shton ne liste
    void addCar();
    // merr te dhenat e klientit nga perdoruesi dhe e shton ne liste
    void addCustomer();
    // shfaq te gjitha makinat me statusin e tyre
    void displayCars() const;
    // shfaq te gjithe klientet e regjistruar
    void displayCustomers() const;
};

// shfaq listen e opsioneve ne ekran
void displayMenu();
// lidh nje klient me nje makine te lire dhe llogarit koston
void rentCar(RentalSystem& system);
// e ben makinen te lire perseri dhe shfaq koston finale
void returnCar(RentalSystem& system);
// shfaq te gjitha qirate aktive me detajet e tyre
void displayRentals(const RentalSystem& system);
// numeron qirat per makine dhe kthen ate me me shume
string findMostRentedCar(const RentalSystem& system);

int main() {
    RentalSystem rentalSystem;
    rentalSystem.agencyName = "AutoQira MK";
    rentalSystem.numCars = 0;
    rentalSystem.numCustomers = 0;
    rentalSystem.numRentals = 0;

    rentalSystem.cars[0] = { 1, "Toyota", "Corolla", 2020, 35.0, true };
    rentalSystem.cars[1] = { 2, "BMW", "Seria 3", 2022, 75.0, true };
    rentalSystem.cars[2] = { 3, "Ford", "Focus", 2019, 30.0, true };
    rentalSystem.numCars = 3;

    rentalSystem.customers[0] = { 1, "Arben Islami", "070123456", {"Rr. Ilindenska", "Tetove", "1200"} };
    rentalSystem.customers[1] = { 2, "Blerina Mehmeti", "071654321", {"Rr. Partizanska", "Shkup", "1000"} };
    rentalSystem.numCustomers = 2;

    int choice;
    do {
        displayMenu();
        cout << "Zgjidhni opsionin: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            rentalSystem.addCar();
            break;
        case 2:
            rentalSystem.addCustomer();
            break;
        case 3:
            rentCar(rentalSystem);
            break;
        case 4:
            returnCar(rentalSystem);
            break;
        case 5:
            rentalSystem.displayCars();
            break;
        case 6:
            rentalSystem.displayCustomers();
            break;
        case 7:
            displayRentals(rentalSystem);
            break;
        case 8:
            cout << "Makina me e qiradhene: " << findMostRentedCar(rentalSystem) << endl;
            break;
        case 9:
            cout << "Po dilni nga programi." << endl;
            break;
        default:
            cout << "Opsion i gabuar." << endl;
        }
    } while (choice != 9);

    return 0;
}

// shfaq menune me te gjitha opsionet
void displayMenu() {
    cout << "\n===== Sistemi i Makinave me Qira =====" << endl;
    cout << "1. Shto Makine" << endl;
    cout << "2. Shto Klient" << endl;
    cout << "3. Jep Makine me Qira" << endl;
    cout << "4. Kthe Makinen" << endl;
    cout << "5. Shfaq Makinat" << endl;
    cout << "6. Shfaq Klientet" << endl;
    cout << "7. Shfaq Qirate" << endl;
    cout << "8. Makina me e Qiradhene" << endl;
    cout << "9. Dil" << endl;
}

// merr inputin nga perdoruesi dhe shton makine te re ne array
void RentalSystem::addCar() {
    cout << "Marka: ";
    getline(cin, cars[numCars].brand);
    cout << "Modeli: ";
    getline(cin, cars[numCars].model);
    cout << "Viti: ";
    cin >> cars[numCars].year;
    cin.ignore();
    cout << "Cmimi ditor ($): ";
    cin >> cars[numCars].dailyRate;
    cin.ignore();

    cars[numCars].ID = numCars + 1;
    cars[numCars].isAvailable = true;
    numCars++;

    cout << "Makina u shtua!" << endl;
}

// merr inputin nga perdoruesi dhe shton klient te ri ne array
void RentalSystem::addCustomer() {
    cout << "Emri: ";
    getline(cin, customers[numCustomers].name);
    cout << "Telefoni: ";
    getline(cin, customers[numCustomers].phone);
    cout << "Rruga: ";
    getline(cin, customers[numCustomers].address.street);
    cout << "Qyteti: ";
    getline(cin, customers[numCustomers].address.city);
    cout << "Kodi Postar: ";
    getline(cin, customers[numCustomers].address.zipCode);

    customers[numCustomers].ID = numCustomers + 1;
    numCustomers++;

    cout << "Klienti u shtua!" << endl;
}

// printon te gjitha makinat ne forme tabele me statusin e tyre
void RentalSystem::displayCars() const {
    cout << "\n===== Lista e Makinave =====" << endl;
    cout << left << setw(5) << "ID" << setw(12) << "Marka" << setw(12) << "Modeli"
        << setw(8) << "Viti" << setw(12) << "$/Dite" << "Statusi" << endl;
    cout << "---------------------------------------------------" << endl;
    for (int i = 0; i < numCars; i++) {
        cout << left << setw(5) << cars[i].ID
            << setw(12) << cars[i].brand
            << setw(12) << cars[i].model
            << setw(8) << cars[i].year
            << setw(12) << cars[i].dailyRate
            << (cars[i].isAvailable ? "E lire" : "E zene") << endl;
    }
}

// printon te gjithe klientet ne forme tabele
void RentalSystem::displayCustomers() const {
    cout << "\n===== Lista e Klienteve =====" << endl;
    cout << left << setw(5) << "ID" << setw(22) << "Emri" << setw(15) << "Telefoni" << "Qyteti" << endl;
    cout << "---------------------------------------------------" << endl;
    for (int i = 0; i < numCustomers; i++) {
        cout << left << setw(5) << customers[i].ID
            << setw(22) << customers[i].name
            << setw(15) << customers[i].phone
            << customers[i].address.city << endl;
    }
}

// lejon perdoruesin te zgjedhe klientin dhe makinen pastaj krijon nje rekord qiraje
void rentCar(RentalSystem& system) {
    cout << "\nKlientet:" << endl;
    for (int i = 0; i < system.numCustomers; i++)
        cout << i + 1 << ". " << system.customers[i].name << endl;

    int customerChoice;
    cout << "Zgjidhni klientin: ";
    cin >> customerChoice;
    cin.ignore();

    cout << "\nMakinat e disponueshme:" << endl;
    for (int i = 0; i < system.numCars; i++) {
        if (system.cars[i].isAvailable)
            cout << i + 1 << ". " << system.cars[i].brand << " " << system.cars[i].model
                << " ($" << system.cars[i].dailyRate << "/dite)" << endl;
    }

    int carChoice;
    cout << "Zgjidhni makinen: ";
    cin >> carChoice;
    cin.ignore();

    RentalRecord newRental;
    newRental.customer = system.customers[customerChoice - 1];
    newRental.car = system.cars[carChoice - 1];

    cout << "Dita e fillimit (1-30): ";
    cin >> newRental.startDay;
    cin.ignore();
    cout << "Dita e mbarimit (1-30): ";
    cin >> newRental.endDay;
    cin.ignore();

    // llogarit koston totale bazuar ne ditet dhe cmimin ditor
    int days = newRental.endDay - newRental.startDay;
    newRental.totalCost = days * newRental.car.dailyRate;

    // e shenom makinen si te zene dhe e ruajme qirane
    system.cars[carChoice - 1].isAvailable = false;
    system.rentals[system.numRentals++] = newRental;

    cout << "Makina u dha me qira! Kostoja: $" << newRental.totalCost << endl;
}

// gjen makinen ne array dhe e ben te lire perseri
void returnCar(RentalSystem& system) {
    cout << "\nQirate aktive:" << endl;
    for (int i = 0; i < system.numRentals; i++)
        cout << i + 1 << ". " << system.rentals[i].customer.name
            << " - " << system.rentals[i].car.brand << " " << system.rentals[i].car.model << endl;

    int rentalChoice;
    cout << "Zgjidhni qirane per kthim: ";
    cin >> rentalChoice;
    cin.ignore();

    string brand = system.rentals[rentalChoice - 1].car.brand;
    string model = system.rentals[rentalChoice - 1].car.model;

    // kerkojme makinen ne array dhe e lirojme
    for (int i = 0; i < system.numCars; i++) {
        if (system.cars[i].brand == brand && system.cars[i].model == model) {
            system.cars[i].isAvailable = true;
            break;
        }
    }

    cout << "Makina u kthye! Kostoja totale: $" << system.rentals[rentalChoice - 1].totalCost << endl;
}

// shfaq te gjitha qirate ne forme tabele
void displayRentals(const RentalSystem& system) {
    cout << "\n===== Qirate =====" << endl;
    cout << left << setw(22) << "Klienti" << setw(18) << "Makina"
        << setw(10) << "Fillimi" << setw(10) << "Mbarimi" << "Kostoja" << endl;
    cout << "---------------------------------------------------" << endl;
    for (int i = 0; i < system.numRentals; i++) {
        const RentalRecord& r = system.rentals[i];
        cout << left << setw(22) << r.customer.name
            << setw(18) << (r.car.brand + " " + r.car.model)
            << setw(10) << r.startDay
            << setw(10) << r.endDay
            << "$" << r.totalCost << endl;
    }
}

// numeron sa here eshte qiradhene secila makine dhe kthen aten me numrin me te madh
string findMostRentedCar(const RentalSystem& system) {
    int carCount[MAX_CARS] = { 0 };

    for (int i = 0; i < system.numRentals; i++) {
        for (int j = 0; j < system.numCars; j++) {
            if (system.cars[j].brand == system.rentals[i].car.brand &&
                system.cars[j].model == system.rentals[i].car.model) {
                carCount[j]++;
                break;
            }
        }
    }

    // gjejme indexin e makines me numrin me te larte
    int max = 0, index = 0;
    for (int i = 0; i < system.numCars; i++) {
        if (carCount[i] > max) {
            max = carCount[i];
            index = i;
        }
    }

    return system.cars[index].brand + " " + system.cars[index].model;
}