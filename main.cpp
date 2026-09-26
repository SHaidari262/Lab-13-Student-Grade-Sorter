#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

const int MAX_STUDENTS = 200;

struct Student {
    long long id;
    double score;
};

// Selection sort by student ID
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

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;

    ifstream inputFile("210-lab-13-grades.txt");

    if (!inputFile) {
        cout << "Error opening input file." << endl;
        return 1;
    }

    // Read student records
    while (count < MAX_STUDENTS &&
           inputFile >> students[count].id >> students[count].score) {
        count++;
    }

    inputFile.close();

    if (count == 0) {
        cout << "No student records found." << endl;
        return 1;
    }

    cout << "Read " << count << " student records" << endl;

    // Find minimum, maximum, and mean
    int minIndex = 0;
    int maxIndex = 0;
    double sum = 0;

    for (int i = 0; i < count; i++) {
        sum += students[i].score;

        if (students[i].score < students[minIndex].score) {
            minIndex = i;
        }

        if (students[i].score > students[maxIndex].score) {
            maxIndex = i;
        }
    }

    double mean = sum / count;

    // Standard deviation
    double squaredDifferenceSum = 0;

    for (int i = 0; i < count; i++) {
        double difference = students[i].score - mean;
        squaredDifferenceSum += difference * difference;
    }

    double standardDeviation =
        sqrt(squaredDifferenceSum / count);

    // Save min/max students before sorting
    Student minStudent = students[minIndex];
    Student maxStudent = students[maxIndex];

    // Sort by student ID
    selectionSort(students, count);

    // Write sorted records
    ofstream outputFile("210-lab-13-grades-sorted.txt");

    if (!outputFile) {
        cout << "Error opening output file." << endl;
        return 1;
    }

    for (int i = 0; i < count; i++) {
        outputFile << students[i].id << " "
                   << students[i].score << endl;
    }

    outputFile.close();

    cout << "Sorted results written to "
         << "210-lab-13-grades-sorted.txt" << endl;

    // Make a copy sorted by score to calculate median
    Student scoreSorted[MAX_STUDENTS];

    for (int i = 0; i < count; i++) {
        scoreSorted[i] = students[i];
    }

    // Selection sort by score
    for (int i = 0; i < count - 1; i++) {
        int minScoreIndex = i;

        for (int j = i + 1; j < count; j++) {
            if (scoreSorted[j].score < scoreSorted[minScoreIndex].score) {
                minScoreIndex = j;
            }
        }

        if (minScoreIndex != i) {
            Student temp = scoreSorted[i];
            scoreSorted[i] = scoreSorted[minScoreIndex];
            scoreSorted[minScoreIndex] = temp;
        }
    }

    double median;
    long long medianID;

    if (count % 2 == 1) {
        int middle = count / 2;
        median = scoreSorted[middle].score;
        medianID = scoreSorted[middle].id;
    } else {
        int middle1 = count / 2 - 1;
        int middle2 = count / 2;

        median = (scoreSorted[middle1].score +
                  scoreSorted[middle2].score) / 2.0;

        // Use the upper-middle student's ID
        medianID = scoreSorted[middle2].id;
    }

    cout << endl;
    cout << "--- Summary Statistics ---" << endl;

    cout << "Minimum Score: " << minStudent.score
         << " (Student ID: " << minStudent.id << ")" << endl;

    cout << "Maximum Score: " << maxStudent.score
         << " (Student ID: " << maxStudent.id << ")" << endl;

    cout << "Mean Score: " << mean << endl;

    cout << "Median Score: " << median
         << " (Student ID: " << medianID << ")" << endl;

    cout << "Standard Deviation: "
         << standardDeviation << endl;

    return 0;
}