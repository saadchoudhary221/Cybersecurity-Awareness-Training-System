#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// User Class
class User {
private:
    string name;
    int age;
    string email;

public:
    User() : name(""), age(0), email("") {}

    void setName(const string& newName) { name = newName; }

    void setAge(int newAge) {
        if (newAge > 0)
            age = newAge;
        else
            logError("Invalid age entered.");
    }

    void setEmail(const string& newEmail) {
        if (newEmail.find('@') != string::npos)
            email = newEmail;
        else
            logError("Invalid email entered.");
    }

    void displayInfo() const {
        cout << "\nUser Information:\n";
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Email: " << email << endl;
    }

    void logError(const string& errorMsg) const {
        ofstream errorFile("error_log.txt", ios::app);
        if (errorFile.is_open()) {
            errorFile << "Error: " << errorMsg << endl;
            errorFile.close();
        } else {
            cerr << "Unable to open error log file." << endl;
        }
    }
};

// Question Class
class Question {
private:
    string questionText;
    string options[4];
    char correctAnswer;

public:
    Question(string qText, string opt1, string opt2, string opt3, string opt4, char correct)
        : questionText(qText), correctAnswer(correct) {
        options[0] = opt1;
        options[1] = opt2;
        options[2] = opt3;
        options[3] = opt4;
    }

    void displayQuestion() const {
        cout << "\n" << questionText << endl;
        cout << "a) " << options[0] << endl;
        cout << "b) " << options[1] << endl;
        cout << "c) " << options[2] << endl;
        cout << "d) " << options[3] << endl;
    }

    bool checkAnswer(char answer) const {
        return tolower(answer) == tolower(correctAnswer);
    }
};

// Quiz Class
class Quiz {
private:
    vector<Question> questions;
    int score;

public:
    Quiz() : score(0) {}

    void addQuestion(const Question& q) {
        questions.push_back(q);
    }

    void startQuiz() {
        char userAnswer;

        for (size_t i = 0; i < questions.size(); ++i) {
            questions[i].displayQuestion();
            cout << "Enter your answer (a/b/c/d): ";
            cin >> userAnswer;

            if (questions[i].checkAnswer(userAnswer)) {
                cout << "Correct!" << endl;
                score++;
            } else {
                cout << "Wrong answer!" << endl;
            }
        }

        cout << "\nYour final score: " << score << "/" << questions.size() << endl;
    }
};

// Main Program
int main() {
    User user;
    string name, email;
    int age;

    cout << "Welcome to the Cybersecurity Awareness Training System\n";

    cout << "Enter your name: ";
    getline(cin, name);
    user.setName(name);

    cout << "Enter your age: ";
    cin >> age;
    cin.ignore();
    user.setAge(age);

    cout << "Enter your email: ";
    getline(cin, email);
    user.setEmail(email);

    user.displayInfo();

    // Create quiz
    Quiz quiz;
    quiz.addQuestion(Question("What is phishing?",
                              "A virus", "A type of firewall", "A way to catch fish", "A fraud to steal sensitive info", 'd'));

    quiz.addQuestion(Question("Which is a strong password?",
                              "123456", "Password123", "Pa$$w0rd!23", "qwerty", 'c'));

    quiz.addQuestion(Question("What should you do if you suspect a scam email?",
                              "Reply to it", "Click the link", "Report and delete", "Ignore and share", 'c'));

    quiz.startQuiz();

    return 0;
}

