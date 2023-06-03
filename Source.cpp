#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

class Car {
public:
    string name;
    int year;
    float engineVolume;
    float price;

    Car(const string& n, int y, float ev, float p)
        : name(n), year(y), engineVolume(ev), price(p) {}
};

class CarShowroom {
private:
    vector<Car> cars;
public:
    void addCar(const Car& car) { cars.push_back(car); }
    void removeCar(const string& name) {
        cars.erase(remove_if(cars.begin(), cars.end(),
            [&](const Car& car) { return car.name == name; }), cars.end());
    }

    void displayCars() {
        for (const Car& car : cars)
            cout << "Name: " << car.name << ", Year: " << car.year
                << ", Engine Volume: " << car.engineVolume
                << ", Price: " << car.price << "\n";
    }

    void sortCarsByYear() {
        sort(cars.begin(), cars.end(),
            [](const Car& a, const Car& b) { return a.year < b.year; });
    }

    void sortCarsByPrice() {
        sort(cars.begin(), cars.end(),
            [](const Car& a, const Car& b) { return a.price < b.price; });
    }

    vector<Car> searchCarsByYear(int targetYear) {
        vector<Car> result;
        copy_if(cars.begin(), cars.end(), back_inserter(result),
            [&](const Car& car) { return car.year == targetYear; });
        return result;
    }

    vector<Car> searchCarsByEngineVolume(float targetVolume) {
        vector<Car> result;
        copy_if(cars.begin(), cars.end(), back_inserter(result),
            [&](const Car& car) { return car.engineVolume == targetVolume; });
        return result;
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const Car& car : cars)
                file << car.name << "," << car.year << "," << car.engineVolume << "," << car.price << "\n";
            file.close();
            cout << "Data saved to file: " << filename << "\n";
        }
        else cout << "Unable to open file: " << filename << "\n";
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            cars.clear();
            string line;
            while (getline(file, line)) {
                istringstream iss(line);
                string name;
                string yearStr;
                string engineVolumeStr;
                string priceStr;

                if (getline(iss, name, ',') &&
                    getline(iss, yearStr, ',') &&
                    getline(iss, engineVolumeStr, ',') &&
                    getline(iss, priceStr)) {
                    int year = stoi(yearStr);
                    float engineVolume = stof(engineVolumeStr);
                    float price = stof(priceStr);

                    cars.emplace_back(name, year, engineVolume, price);
                }
            }
            file.close();
            cout << "Data loaded from file: " << filename << "\n";
        }
        else cout << "Unable to open file: " << filename << "\n";
    }
};

int main() {
    CarShowroom showroom;
    showroom.loadFromFile("car_data.txt");

    int choice = 0;
    while (choice != 9) {
        cout << "----------------------------------------------------------\n"
            << "1. Add Car\n"
            << "2. Remove Car\n"
            << "3. Display Cars\n"
            << "4. Sort Cars by Year\n"
            << "5. Sort Cars by Price\n"
            << "6. Search Cars by Year\n"
            << "7. Search Cars by Engine Volume\n"
            << "8. Save Cars to File\n"
            << "9. Exit\n"
            << "Enter your choice: ";
        cin >> choice;
        cout << "----------------------------------------------------------\n";
        string name;
        vector<Car> cars;
        int year;
        switch (choice) {
        case 1:
            int year;
            float engineVolume;
            float price;

            cout << "Enter car name: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter year: ";
            cin >> year;

            cout << "Enter engine volume: ";
            cin >> engineVolume;

            cout << "Enter price: ";
            cin >> price;

            showroom.addCar(Car(name, year, engineVolume, price));
            break;
        case 2:
            cout << "Enter car name to remove: ";
            cin.ignore();
            getline(cin, name);

            showroom.removeCar(name);
            break;
        case 3:
            showroom.displayCars();
            break;
        case 4:
            showroom.sortCarsByYear();
            cout << "Cars sorted by year.\n";
            break;
        case 5:
            showroom.sortCarsByPrice();
            cout << "Cars sorted by price.\n";
            break;
        case 6:
            cout << "Enter year to search: ";
            cin >> year;

            cars = showroom.searchCarsByYear(year);
            cout << "Cars found:\n";
            for (const Car& car : cars) {
                cout << "Name: " << car.name << ", Year: " << car.year
                    << ", Engine Volume: " << car.engineVolume
                    << ", Price: " << car.price << "\n";
            }
            break;
        case 7:
            float volume;
            cout << "Enter engine volume to search: ";
            cin >> volume;

           cars = showroom.searchCarsByEngineVolume(volume);
            cout << "Cars found:" << "\n";
            for (const Car& car : cars) {
                cout << "Name: " << car.name << ", Year: " << car.year
                    << ", Engine Volume: " << car.engineVolume
                    << ", Price: " << car.price << "\n";
            }
            break;
        case 8:
            showroom.saveToFile("car_data.txt");
            break;
        case 9:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}
