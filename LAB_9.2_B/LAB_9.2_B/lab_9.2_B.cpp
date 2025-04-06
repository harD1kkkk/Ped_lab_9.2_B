#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <cmath>
#include <limits>
using namespace std;

enum SpecialtyB { ComputerScience, InformaticsB, MathematicsAndEconomicsB, PhysicsAndITB, WorkBasedLearningB };
const string specialtyNamesB[] = { "Computer Science", "Informatics", "Math and Economics", "Physics and IT", "Work-based Learning" };

struct StudentB {
    string lastName;
    int course;
    SpecialtyB specialty;
    double physics;
    double math;
    union {
        double programming;      
        double numericalMethods;  
        double pedagogy;          
    } third;
};

double getThirdGradeB(const StudentB& s) {
    if (s.specialty == ComputerScience) {
        return s.third.programming;
    }
    else if (s.specialty == InformaticsB) {
        return s.third.numericalMethods;
    }
    else {
        return s.third.pedagogy;
    }
}

double averageGradeB(const StudentB& s) {
    return (s.physics + s.math + getThirdGradeB(s)) / 3.0;
}

void CreateB(StudentB* s, const int N) {
    int spec;
    for (int i = 0; i < N; i++) {
        cout << "Student #" << i + 1 << ":\n";
        cout << "Last Name: ";
        getline(cin, s[i].lastName);
        cout << "Course: ";
        cin >> s[i].course;
        cout << "Specialty (0 - Computer Science, 1 - Informatics, 2 - Math and Economics, 3 - Physics and IT, 4 - Work-based Learning): ";
        cin >> spec;
        s[i].specialty = (SpecialtyB)spec;
        cout << "Physics grade: ";
        cin >> s[i].physics;
        cout << "Math grade: ";
        cin >> s[i].math;
        if (s[i].specialty == ComputerScience) {
            cout << "Programming grade: ";
            cin >> s[i].third.programming;
        }
        else if (s[i].specialty == InformaticsB) {
            cout << "Numerical Methods grade: ";
            cin >> s[i].third.numericalMethods;
        }
        else {
            cout << "Pedagogy grade: ";
            cin >> s[i].third.pedagogy;
        }
        cin.ignore();
        cout << endl;
    }
}

void PrintB(StudentB* s, const int N) {
    cout << "===========================================================================================================" << endl;
    cout << "| No. | Last Name        | Course | Specialty          | Physics | Math  | Prog. | Num.Methods | Pedagogy |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << right << i + 1 << "  ";
        cout << "| " << setw(17) << left << s[i].lastName;
        cout << "| " << setw(7) << right << s[i].course;
        cout << "| " << setw(19) << left << specialtyNamesB[s[i].specialty];
        cout << "| " << setw(8) << right << fixed << setprecision(2) << s[i].physics;
        cout << "| " << setw(6) << right << fixed << setprecision(2) << s[i].math;
        if (s[i].specialty == ComputerScience) {
            cout << "| " << setw(6) << right << fixed << setprecision(2) << s[i].third.programming;
            cout << "| " << setw(12) << right << "-";
            cout << "| " << setw(8) << right << "-";
        }
        else if (s[i].specialty == InformaticsB) {
            cout << "| " << setw(6) << right << "-";
            cout << "| " << setw(12) << right << fixed << setprecision(2) << s[i].third.numericalMethods;
            cout << "| " << setw(8) << right << "-";
        }
        else {
            cout << "| " << setw(6) << right << "-";
            cout << "| " << setw(12) << right << "-";
            cout << "| " << setw(8) << right << fixed << setprecision(2) << s[i].third.pedagogy;
        }
        cout << " |" << endl;
    }
    cout << "===========================================================================================================" << endl;
}

void PhysicalSortB(StudentB* s, const int N) {
    StudentB tmp;
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            double avg1 = averageGradeB(s[j]);
            double avg2 = averageGradeB(s[j + 1]);
            if (avg1 > avg2) {
                tmp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = tmp;
            }
            else if (avg1 == avg2) {
                double third1 = getThirdGradeB(s[j]);
                double third2 = getThirdGradeB(s[j + 1]);
                if (third1 > third2) {
                    tmp = s[j];
                    s[j] = s[j + 1];
                    s[j + 1] = tmp;
                }
                else if (third1 == third2) {
                    if (s[j].lastName < s[j + 1].lastName) { 
                        tmp = s[j];
                        s[j] = s[j + 1];
                        s[j + 1] = tmp;
                    }
                }
            }
        }
    }
    cout << "Physical sort completed." << endl;
}

int* IndexSortB(StudentB* s, const int N) {
    int* I = new int[N];
    for (int i = 0; i < N; i++) {
        I[i] = i;
    }
    int i, j, key;
    for (i = 1; i < N; i++) {
        key = I[i];
        j = i - 1;
        while (j >= 0) {
            double avg1 = averageGradeB(s[I[j]]);
            double avg2 = averageGradeB(s[key]);
            if (avg1 > avg2) {
                I[j + 1] = I[j];
                j = j - 1;
            }
            else if (avg1 == avg2) {
                double third1 = getThirdGradeB(s[I[j]]);
                double third2 = getThirdGradeB(s[key]);
                if (third1 > third2) {
                    I[j + 1] = I[j];
                    j = j - 1;
                }
                else if (third1 == third2) {
                    if (s[I[j]].lastName > s[key].lastName) {
                        I[j + 1] = I[j];
                        j = j - 1;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }
        I[j + 1] = key;
    }
    return I;
}

void PrintIndexSortedB(StudentB* s, int* I, const int N) {
    cout << "Index Sorted Student List:" << endl;
    cout << "============================================================================================================" << endl;
    cout << "| No. | Last Name        | Course | Specialty          | Physics | Math  | Prog. | Num.Methods | Pedagogy  |" << endl;
    cout << "------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        int j = I[i];
        cout << "| " << setw(2) << right << i + 1 << "  ";
        cout << "| " << setw(17) << left << s[j].lastName;
        cout << "| " << setw(7) << right << s[j].course;
        cout << "| " << setw(19) << left << specialtyNamesB[s[j].specialty];
        cout << "| " << setw(8) << right << fixed << setprecision(2) << s[j].physics;
        cout << "| " << setw(6) << right << fixed << setprecision(2) << s[j].math;
        if (s[j].specialty == ComputerScience) {
            cout << "| " << setw(6) << right << fixed << setprecision(2) << s[j].third.programming;
            cout << "| " << setw(12) << right << "-";
            cout << "| " << setw(8) << right << "-";
        }
        else if (s[j].specialty == InformaticsB) {
            cout << "| " << setw(6) << right << "-";
            cout << "| " << setw(12) << right << fixed << setprecision(2) << s[j].third.numericalMethods;
            cout << "| " << setw(8) << right << "-";
        }
        else {
            cout << "| " << setw(6) << right << "-";
            cout << "| " << setw(12) << right << "-";
            cout << "| " << setw(9) << right << fixed << setprecision(2) << s[j].third.pedagogy;
        }
        cout << " |" << endl;
    }
    cout << "============================================================================================================" << endl;
}

int BinSearchB(StudentB* s, const int N, const string& lastName, double avg, double thirdGrade, int* I) {
    int L = 0;
    int R = N - 1;
    int m;
    while (L <= R) {
        m = (L + R) / 2;
        int iIndex = I[m];
        double currAvg = averageGradeB(s[iIndex]);
        double currThird = getThirdGradeB(s[iIndex]);
        int cmp = 0;
        if (currAvg < avg) {
            cmp = -1;
        }
        else if (currAvg > avg) {
            cmp = 1;
        }
        else {
            if (currThird < thirdGrade) {
                cmp = -1;
            }
            else if (currThird > thirdGrade) {
                cmp = 1;
            }
            else {
                if (s[iIndex].lastName < lastName) {
                    cmp = -1;
                }
                else if (s[iIndex].lastName > lastName) {
                    cmp = 1;
                }
                else {
                    cmp = 0;
                }
            }
        }
        if (cmp == 0) {
            return iIndex;
        }
        else if (cmp < 0) {
            L = m + 1;
        }
        else {
            R = m - 1;
        }
    }
    return -1;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int N;
    cout << "Enter number of students: ";
    cin >> N;
    cin.ignore();
    StudentB* s = new StudentB[N];
    int menuItem, found;
    do {
        cout << "\n\n================ MENU ==================" << endl;
        cout << " [1] - Enter student data" << endl;
        cout << " [2] - Print student data" << endl;
        cout << " [3] - Physical sort (by average asc, third grade asc, last name desc)" << endl;
        cout << " [4] - Index sort and print sorted data (by average asc, third grade asc, last name asc)" << endl;
        cout << " [5] - Binary search (by last name, average, third grade)" << endl;
        cout << " [0] - Exit" << endl;
        cout << "Choose an option: ";
        cin >> menuItem;
        cin.ignore();
        if (menuItem == 1) {
            CreateB(s, N);
        }
        else if (menuItem == 2) {
            PrintB(s, N);
        }
        else if (menuItem == 3) {
            PhysicalSortB(s, N);
            cout << "Array after physical sort:" << endl;
            PrintB(s, N);
        }
        else if (menuItem == 4) {
            int* idx = IndexSortB(s, N);
            PrintIndexSortedB(s, idx, N);
            delete[] idx;
        }
        else if (menuItem == 5) {
            int* idx = IndexSortB(s, N);
            string searchLast;
            double searchAvg, searchThird;
            cout << "Enter last name to search: ";
            getline(cin, searchLast);
            cout << "Enter average grade to search: ";
            cin >> searchAvg;
            cout << "Enter third subject grade to search: ";
            cin >> searchThird;
            cin.ignore();
            found = BinSearchB(s, N, searchLast, searchAvg, searchThird, idx);
            if (found != -1) {
                cout << "Student found at physical index " << found + 1 << endl;
            }
            else {
                cout << "Student not found." << endl;
            }
            delete[] idx;
        }
        else if (menuItem == 0) {
            cout << "Exiting program..." << endl;
        }
        else {
            cout << "Invalid option. Try again." << endl;
        }
    } while (menuItem != 0);
    delete[] s;
    return 0;
}
