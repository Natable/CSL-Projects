#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const int arraySize = 5;

double calculateFinal(double midtermGrade, double endtermGrade){
    return (midtermGrade + endtermGrade) / 2;
}

void saveToCSVFile(string students[], double midterm[], double endterm[], double finalGrades[]){
    ofstream file("CC103_Gradesheet.csv");
    if(!file.is_open()){
        cout << "Error opening the file!" << endl;
        return;
    }

    for (int i = 0; i < arraySize; i++){
        file << students[i] << "," << midterm[i] << "," << endterm[i] << "," << finalGrades[i] << "\n";
    }

    file.close();
}

void addRecord(string students[], double midterm[], double endterm[], double finalGrades[]){
    bool allFilled = true;
    cout << endl;
    for (int i = 0; i < arraySize; i++) {
        if (students[i].empty()) {
            allFilled = false;
            cin.ignore();
            cout << "Enter Student Name " << i + 1 << ": ";
            getline(cin, students[i]);
            cout << "Enter Midterm Grade " << i + 1 << ": ";
            cin >> midterm[i];
            cout << "Enter Endterm Grade " << i + 1 << ": ";
            cin >> endterm[i];
            finalGrades[i] = calculateFinal(midterm[i], endterm[i]);
            break;
        }
    }

    if (allFilled) {
        cout << "You can no longer add new records! Going back to menu..." << endl;
    } else {
        saveToCSVFile(students, midterm, endterm, finalGrades);
        cout << "Saved to CC103_Gradesheet.csv" << endl;
    }
}

void updateRecords(string students[], double midterm[], double endterm[], double finalGrades[]){
    int index;
    cout << endl;
    cout << "Enter the index (0 - 4) to update: ";
    cin >> index;

    if (index >=0 && index < arraySize){
        cin.ignore();
        cout << "Enter new Student Name: ";
        getline(cin, students[index]);
        cout << "Enter new Midterm Grade: ";
        cin >> midterm[index];
        cout << "Enter new Endterm Grade: ";
        cin >> endterm[index];

        finalGrades[index] = calculateFinal(midterm[index], endterm[index]);
        cout << "New Final Grade is: " << finalGrades[index] << "\n";
    }
    else{
        cout << "Invalid index!\n";
    } 
    
    saveToCSVFile(students, midterm, endterm, finalGrades);
    cout << "Updated record saved to CC103_Gradesheet.csv" << endl;
}

void retrieveRecords(string students[], double midterm[], double endterm[], double finalGrades[]){
    ifstream file("CC103_Gradesheet.csv");
    if (!file.is_open()) {
        cout << "Error opening the file!" << endl;
        return;
    }

    cout << endl;
    string line;
    int i = 0;
    while (getline(file, line) && i < arraySize) {
        stringstream ss(line);
        string studentName;
        double midtermGrade, endtermGrade, finalGrade;

        getline(ss, studentName, ',');
        ss >> midtermGrade;
        ss.ignore(1);
        ss >> endtermGrade;
        ss.ignore(1);
        ss >> finalGrade;

        students[i] = studentName;
        midterm[i] = midtermGrade;
        endterm[i] = endtermGrade;
        finalGrades[i] = finalGrade;

        cout << "Student " << i + 1 << ": " << studentName << endl;
        cout << "  Midterm Grade: " << midtermGrade << endl;
        cout << "  Endterm Grade: " << endtermGrade << endl;
        cout << "  Final Grade: " << finalGrade << endl;

        i++;
    }

    file.close();
    cout << endl;
    cout << "Data loaded from CC103_Gradesheet.csv" << endl;
}

void searchRecord(string students[]){
    string query;
    cout << endl;
    cout << "Enter to name to search for their records: ";
    cin.ignore();
    getline(cin, query);

    bool found = false;

    for(int i = 0; i < arraySize; i++){
        cout << endl;
        if (students[i] == query){
            cout << "Found at index: " << i << endl;
            found = true;
            break;
        }
    }

    if(!found){
        cout << "Record not found!\n";
    }
}

int main() {
    bool run = true;
    string studentNames[arraySize] = {""};
    int choice;

    double studentMidtermGrades[arraySize] = {0};
    double studentEndtermGrades[arraySize] = {0};
    double studentFinalGrades[arraySize] = {0};

    while (run) {
        cout << endl;
        cout << "1. Add Record\n" << "2. Update Records\n" << "3. Retrieve Records\n" << "4. Search Record\n" << "5. Exit Program\n" << endl;
        cout << "Please Choose: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                addRecord(studentNames, studentMidtermGrades, studentEndtermGrades, studentFinalGrades);
            }
            break;
            case 2: {
                updateRecords(studentNames, studentMidtermGrades, studentEndtermGrades, studentFinalGrades);
            }
            break;
            case 3: {
                retrieveRecords(studentNames, studentMidtermGrades, studentEndtermGrades, studentFinalGrades);
            }
            break;
            case 4: {
                searchRecord(studentNames);
            }
            break;
            case 5:{
                cout << endl;
                cout << "Exiting program! Goodbye..." << endl;
                run = false;
                break;
            }
            break;
            default: {
                cout << "Invalid choice" << endl;
            }
        }
    }
    return 0;
}