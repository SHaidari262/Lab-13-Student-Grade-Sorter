#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;

struct Student {
    long long id;
    double score;
};

const int MAX_STUDENTS = 200;

void selectionSort(Student students[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < size; j++) {
            if (students[j].id < students[minIndex].id) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            Student temp = students[i];
            students[i] = students[minIndex];
            students[minIndex] = temp;
        }
    }
}

void sortScores(double scores[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < size; j++) {
            if (scores[j] < scores[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            double temp = scores[i];
            scores[i] = scores[minIndex];
            scores[minIndex] = temp;
        }
    }
}

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;

    ifstream inputFile("210-lab-13-grades.txt");

    if (!inputFile) {
        cout << "Error: Could not open input file." << endl;
        return 1;
    }

    while (count < MAX_STUDENTS &&
           inputFile >> students[count].id >> students[count].score) {
        count++;
    }

    inputFile.close();

    if (count == 0) {
        cout << "Error: No student records found." << endl;
        return 1;
    }

    cout << "Read " << count << " student records" << endl;

    int minIndex = 0;
    int maxIndex = 0;
    double total = 0.0;

    for (int i = 0; i < count; i++) {
        total += students[i].score;

        if (students[i].score < students[minIndex].score) {
            minIndex = i;
        }

        if (students[i].score > students[maxIndex].score) {
            maxIndex = i;
        }
    }

    double mean = total / count;

    double scores[MAX_STUDENTS];

    for (int i = 0; i < count; i++) {
        scores[i] = students[i].score;
    }

    sortScores(scores, count);

    double median;

    if (count % 2 == 0) {
        median = (scores[count / 2 - 1] + scores[count / 2]) / 2.0;
    } else {
        median = scores[count / 2];
    }

    double sumSquaredDifferences = 0.0;

    for (int i = 0; i < count; i++) {
        double difference = students[i].score - mean;
        sumSquaredDifferences += difference * difference;
    }

    double standardDeviation =
        sqrt(sumSquaredDifferences / count);

    long long minID = students[minIndex].id;
    long long maxID = students[maxIndex].id;

    selectionSort(students, count);

    long long medianID = 0;

    for (int i = 0; i < count; i++) {
        if (students[i].score == median) {
            medianID = students[i].id;
            break;
        }
    }

    ofstream outputFile("210-lab-13-grades-sorted.txt");

    if (!outputFile) {
        cout << "Error: Could not open output file." << endl;
        return 1;
    }

    outputFile << fixed << setprecision(1);

    for (int i = 0; i < count; i++) {
        outputFile << students[i].id << " "
                   << students[i].score << endl;
    }

    outputFile.close();

    cout << "Sorted results written to 210-lab-13-grades-sorted.txt"
         << endl;

    cout << endl;
    cout << "--- Summary Statistics ---" << endl;

    cout << "Minimum Score: "
         << scores[0]
         << " (Student ID: " << minID << ")" << endl;

    cout << "Maximum Score: "
         << scores[count - 1]
         << " (Student ID: " << maxID << ")" << endl;

    cout << setprecision(4);
    cout << "Mean Score: " << mean << endl;

    cout << setprecision(1);
    cout << "Median Score: " << median
         << " (Student ID: " << medianID << ")" << endl;

    cout << setprecision(5);
    cout << "Standard Deviation: "
         << standardDeviation << endl;

    return 0;
}