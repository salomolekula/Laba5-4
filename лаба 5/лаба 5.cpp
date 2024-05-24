// лаба 5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using std::string;
using std::cout;

int findStrInF(std::string filename, std::string str) {

    string s;
    char temp;
    std::ifstream ifs(filename);

    if (!ifs.is_open()) {
        std::cerr << "File error." << std::endl;
        return -1;
    }
    ifs.unsetf(std::ios::skipws);
    while (ifs >> temp)
        s += temp;

    int i = 0;
    int identificator = s.find(str);
    while (identificator != std::string::npos)
    {
        s.erase(identificator, str.length());
        i++;
        identificator = s.find(str);
    }

    return i;
}


class Matrix {
private:
    int rows;
    int cols;
public:
    Matrix(int r, int c) : rows(r), cols(c) {}

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    friend std::istream& operator>>(std::istream& is, Matrix& matrix);
};

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    os << "Matrix [" << matrix.rows << "x" << matrix.cols << "]";
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& matrix) {
    is >> matrix.rows >> matrix.cols;
    return is;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

struct Book {
    std::string id;
    std::string author;
    std::string title;
    int pages;

    void display() const {
        std::cout << "ID: " << id << ", Author: " << author << ", Title: " << title << ", Pages: " << pages << std::endl;
    }
};

void saveBooksToFile(const std::string& fileName, const std::vector<Book>& books) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return;
    }

    for (const auto& book : books) {
        file << book.id << " " << book.author << " " << book.title << " " << book.pages << std::endl;
    }

    file.close();
}

std::vector<Book> loadBooksFromFile(const std::string& fileName) {
    std::vector<Book> books;
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return books;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Book book;
        if (iss >> book.id >> book.author >> book.title >> book.pages) {
            books.push_back(book);
        }
    }

    file.close();
    return books;
}

void addBook(std::vector<Book>& books) {
    Book book;
    std::cout << "Enter book details:" << std::endl;
    std::cout << "ID: ";
    std::cin >> book.id;
    std::cout << "Author: ";
    std::cin >> book.author;
    std::cout << "Title: ";
    std::cin >> book.title;
    std::cout << "Pages: ";
    std::cin >> book.pages;
    books.push_back(book);
}

void viewAllBooks(const std::vector<Book>& books) {
    if (books.empty()) {
        std::cout << "No books available." << std::endl;
        return;
    }

    std::cout << "All Books:" << std::endl;
    for (const auto& book : books) {
        book.display();
    }
}

void deleteBook(std::vector<Book>& books, const std::string& id) {
    auto it = std::remove_if(books.begin(), books.end(), [&id](const Book& book) {
        return book.id == id;
        });
    if (it != books.end()) {
        books.erase(it, books.end());
        std::cout << "Book with ID " << id << " deleted successfully." << std::endl;
    }
    else {
        std::cout << "Book with ID " << id << " not found." << std::endl;
    }
}

void searchBook(const std::vector<Book>& books, const std::string& id) {
    auto it = std::find_if(books.begin(), books.end(), [&id](const Book& book) {
        return book.id == id;
        });
    if (it != books.end()) {
        std::cout << "Book found:" << std::endl;
        it->display();
    }
    else {
        std::cout << "Book with ID " << id << " not found." << std::endl;
    }
}

void editBook(std::vector<Book>& books, const std::string& id) {
    auto it = std::find_if(books.begin(), books.end(), [&id](const Book& book) {
        return book.id == id;
        });
    if (it != books.end()) {
        std::cout << "Enter new details for book with ID " << id << ":" << std::endl;
        std::cout << "Author: ";
        std::cin >> it->author;
        std::cout << "Title: ";
        std::cin >> it->title;
        std::cout << "Pages: ";
        std::cin >> it->pages;
        std::cout << "Book details updated successfully." << std::endl;
    }
    else {
        std::cout << "Book with ID " << id << " not found." << std::endl;
    }
} 

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// MAIN() /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

int main() {

    setlocale(LC_ALL, "RU");

    std::cout << "//////////////////////////////////////////////////////\n\t\tЗадание №1\n\n";
    std::string str = "include";
    std::string filename = "C:/Users/Владислав/Desktop/text.txt";
    //std::cin >> str;
    std::cout << "Количество упомянаний слова " << str << ": " << findStrInF(filename, str) << std::endl;

    //////////////////////////////////////////////////////////////////////////////////////////////

    std::cout << "//////////////////////////////////////////////////////\n\n\t\tЗадание №2\n\n";

    std::vector<Matrix> matrices;

    // Запись в текстовый файл
    std::ofstream textFile("matrices.txt");
    if (textFile.is_open()) {
        textFile << "3 3\n"; // Пример записи одной матрицы
        textFile.close();
    }
    else {
        std::cerr << "Unable to open text file." << std::endl;
        return 1;
    }

    // Чтение из текстового файла
    std::ifstream textFileRead("matrices.txt");
    if (textFileRead.is_open()) {
        Matrix temp(0, 0);
        while (textFileRead >> temp) {
            matrices.push_back(temp);
        }
        textFileRead.close();
    }
    else {
        std::cerr << "Unable to open text file for reading." << std::endl;
        return 1;
    }

    // Запись в бинарный файл
    std::ofstream binaryFile("matrices.bin", std::ios::binary);
    if (binaryFile.is_open()) {
        for (const auto& matrix : matrices) {
            binaryFile.write(reinterpret_cast<const char*>(&matrix), sizeof(Matrix));
        }
        binaryFile.close();
    }
    else {
        std::cerr << "Unable to open binary file." << std::endl;
        return 1;
    }

    // Чтение из бинарного файла
    std::ifstream binaryFileRead("matrices.bin", std::ios::binary);
    if (binaryFileRead.is_open()) {
        Matrix temp(0, 0);
        while (binaryFileRead.read(reinterpret_cast<char*>(&temp), sizeof(Matrix))) {
            matrices.push_back(temp);
        }
        binaryFileRead.close();
    }
    else {
        std::cerr << "Unable to open binary file for reading." << std::endl;
        return 1;
    }

    // Вывод содержимого вектора
    for (const auto& matrix : matrices) {
        std::cout << matrix << std::endl;
    }

    ////////////////////////////////////////////////////////////////////////////////

    std::cout << "//////////////////////////////////////////////////////\n\n\t\tЗадание №3\n";

    std::vector<Book> books = loadBooksFromFile("books.txt");

    int choice;
    std::string id;

    do {
        std::cout << "\n1. Add Book\n2. View All Books\n3. Delete Book\n4. Search Book\n5. Edit Book\n6. Save and Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            addBook(books);
            break;
        case 2:
            viewAllBooks(books);
            break;
        case 3:
            std::cout << "Enter ID of book to delete: ";
            std::cin >> id;
            deleteBook(books, id);
            break;
        case 4:
            std::cout << "Enter ID of book to search: ";
            std::cin >> id;
            searchBook(books, id);
            break;
        case 5:
            std::cout << "Enter ID of book to edit: ";
            std::cin >> id;
            editBook(books, id);
            break;
        case 6:
            saveBooksToFile("books.txt", books);
            std::cout << "Books saved successfully. Exiting program." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 6);

    return 0;
}
