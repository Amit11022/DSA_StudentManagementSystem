#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

// ==========================================
// DATA STRUCTURES
// ==========================================

// Structure to represent individual book details in the inventory
struct Book {
    int id;       // Unique identification number of the book
    double price; // Price of the book
};

// Node class for Singly Linked List used in Student Membership management
class StudentNode {
public:
    int studentId;    // Unique student identifier
    string name;      // Student full name
    string course;    // Enrolled course/branch
    StudentNode* next;// Pointer to the next student node in the list

    // Constructor to initialize student record
    StudentNode(int id, string n, string c) {
        studentId = id;
        name = n;
        course = c;
        next = nullptr;
    }
};

// ==========================================
// MODULE 1: Inventory Analysis (Arrays & Vectors)
// ==========================================

// Task 1: Counts valid (positive) vs invalid (<= 0) book prices
void task1_counts(const vector<Book>& books) {
    int validCount = 0, invalidCount = 0;
    for (const auto& b : books) {
        if (b.price > 0) validCount++;
        else invalidCount++;
    }
    cout << "\n--- Task 1: Price Validity Counts ---\n";
    cout << "Valid (Positive) Price Books: " << validCount << endl;
    cout << "Invalid (<= 0) Price Books: " << invalidCount << endl;
}

// Task 2: Counts books based on Odd or Even ID parity
void task2_oddEvenIds(const vector<Book>& books) {
    int oddCount = 0, evenCount = 0;
    for (const auto& b : books) {
        if (b.id % 2 == 0) evenCount++;
        else oddCount++;
    }
    cout << "\n--- Task 2: ID Parity Counts ---\n";
    cout << "Even ID Books: " << evenCount << endl;
    cout << "Odd ID Books: " << oddCount << endl;
}

// Task 3: Computes total inventory value, average price, min & max price
void task3_analytics(const vector<Book>& books) {
    if (books.empty()) {
        cout << "\nInventory is empty!\n";
        return;
    }
    double totalValue = 0;
    double minPrice = books[0].price;
    double maxPrice = books[0].price;

    for (const auto& b : books) {
        totalValue += b.price;
        if (b.price < minPrice) minPrice = b.price;
        if (b.price > maxPrice) maxPrice = b.price;
    }

    cout << "\n--- Task 3: Inventory Analytics ---\n";
    cout << "Total Value: " << totalValue << endl;
    cout << "Average Price: " << (totalValue / books.size()) << endl;
    cout << "Cheapest Book (Min Price): " << minPrice << endl;
    cout << "Most Expensive Book (Max Price): " << maxPrice << endl;
}

// Task 4: Removes duplicate books based on identical Book IDs
void task4_removeDuplicates(vector<Book>& books) {
    vector<Book> uniqueBooks;
    for (const auto& b : books) {
        bool duplicate = false;
        for (const auto& u : uniqueBooks) {
            if (u.id == b.id) {
                duplicate = true;
                break;
            }
        }
        if (!duplicate) {
            uniqueBooks.push_back(b);
        }
    }
    books = uniqueBooks;
    cout << "\n--- Task 4: Duplicate Clean Up ---\n";
    cout << "Duplicates removed successfully! Current unique books count: " << books.size() << endl;
}

// Utility function to check if a number is a mathematical Palindrome
bool isPalindrome(int num) {
    int original = num, reversed = 0;
    while (num > 0) {
        reversed = reversed * 10 + (num % 10);
        num /= 10;
    }
    return original == reversed;
}

// Task 5: Identifies Palindrome Book IDs and Leader Books (Price > all books to its right)
void task5_logic(const vector<Book>& books) {
    cout << "\n--- Task 5: Palindrome IDs & Leader Books ---\n";
    cout << "Palindrome Book IDs: ";
    bool foundPal = false;
    for (const auto& b : books) {
        if (isPalindrome(b.id)) {
            cout << b.id << " ";
            foundPal = true;
        }
    }
    if (!foundPal) cout << "None";
    cout << endl;

    cout << "Leader Books (Price > all books to its right): ";
    for (size_t i = 0; i < books.size(); i++) {
        bool isLeader = true;
        for (size_t j = i + 1; j < books.size(); j++) {
            if (books[i].price <= books[j].price) {
                isLeader = false;
                break;
            }
        }
        if (isLeader) {
            cout << "[ID: " << books[i].id << ", Price: " << books[i].price << "] ";
        }
    }
    cout << endl;
}

// ==========================================
// MODULE 2: The Sorting & Searching Studio
// ==========================================

// 1. Bubble Sort: Repeatedly swaps adjacent elements if they are in wrong order
void bubbleSort(vector<Book>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].id > arr[j + 1].id) swap(arr[j], arr[j + 1]);
        }
    }
}

// 2. Selection Sort: Selects minimum element and places it at the beginning
void selectionSort(vector<Book>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].id < arr[minIdx].id) minIdx = j;
        }
        swap(arr[i], arr[minIdx]);
    }
}

// 3. Insertion Sort: Builds sorted array one item at a time by comparison
void insertionSort(vector<Book>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        Book key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].id > key.id) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Helper function for Merge Sort to merge two sorted sub-vectors
void merge(vector<Book>& arr, int l, int m, int r) {
    vector<Book> left(arr.begin() + l, arr.begin() + m + 1);
    vector<Book> right(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;
    while (i < left.size() && j < right.size()) {
        if (left[i].id <= right[j].id) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
}

// 4. Merge Sort: Divide and conquer sorting algorithm
void mergeSort(vector<Book>& arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

// Partition helper for Quick Sort
int partitionQuick(vector<Book>& arr, int low, int high) {
    int pivot = arr[high].id;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].id < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// 5. Quick Sort: Partition-based sorting algorithm
void quickSort(vector<Book>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionQuick(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Binary Search with Closest Match feature if target ID is not found
void binarySearchWithClosest(const vector<Book>& arr, int targetId) {
    if (arr.empty()) {
        cout << "\nInventory is empty!\n";
        return;
    }
    int low = 0, high = arr.size() - 1;
    int closestId = arr[0].id;
    int minDiff = abs(arr[0].id - targetId);
    bool found = false;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Track closest matching ID during binary search traversal
        if (abs(arr[mid].id - targetId) < minDiff) {
            minDiff = abs(arr[mid].id - targetId);
            closestId = arr[mid].id;
        }

        if (arr[mid].id == targetId) {
            cout << "\nBook Found! [ID: " << arr[mid].id << ", Price: " << arr[mid].price << "]\n";
            found = true;
            break;
        }
        if (arr[mid].id < targetId) low = mid + 1;
        else high = mid - 1;
    }

    if (!found) {
        cout << "\nBook with ID " << targetId << " not found!\n";
        cout << "Closest Suggestion -> Book ID: " << closestId << endl;
    }
}

// ==========================================
// MODULE 3: Digital Logbook
// ==========================================

// Singly Linked List Manager for Student Memberships
class MembershipList {
    StudentNode* head; // Pointer to the first student node
public:
    MembershipList() { head = nullptr; }

    // Destructor to prevent memory leaks by freeing allocated heap nodes
    ~MembershipList() {
        StudentNode* current = head;
        while (current != nullptr) {
            StudentNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Insert a new student record at the end of the linked list
    void insertMember(int id, string name, string course) {
        StudentNode* newNode = new StudentNode(id, name, course);
        if (!head) {
            head = newNode;
        } else {
            StudentNode* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
        cout << "Student record added successfully!\n";
    }

    // Update existing student details by matching student ID
    void updateMember(int id, string newName, string newCourse) {
        StudentNode* temp = head;
        while (temp) {
            if (temp->studentId == id) {
                temp->name = newName;
                temp->course = newCourse;
                cout << "Student ID " << id << " updated successfully!\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Student ID not found!\n";
    }

    // Delete a student record by ID from the linked list
    void deleteMember(int id) {
        if (!head) {
            cout << "List is empty!\n";
            return;
        }
        if (head->studentId == id) {
            StudentNode* toDelete = head;
            head = head->next;
            delete toDelete;
            cout << "Student record deleted!\n";
            return;
        }
        StudentNode* temp = head;
        while (temp->next && temp->next->studentId != id) {
            temp = temp->next;
        }
        if (temp->next) {
            StudentNode* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            cout << "Student record deleted!\n";
        } else {
            cout << "Student ID not found!\n";
        }
    }

    // Traverse and display all student records
    void traverse() {
        if (!head) {
            cout << "No student records available.\n";
            return;
        }
        cout << "\n--- Student Membership List ---\n";
        StudentNode* temp = head;
        while (temp) {
            cout << "ID: " << temp->studentId << " | Name: " << temp->name << " | Course: " << temp->course << "\n";
            temp = temp->next;
        }
    }
};

// Stack Data Structure (LIFO - Last In, First Out) for Book Returns
class ReturnStack {
    vector<int> stack;
public:
    // Push returned book ID onto the stack
    void pushBook(int bookId) {
        stack.push_back(bookId);
        cout << "Book ID " << bookId << " returned and added to stack.\n";
    }

    // Pop/remove the top book from the stack (LIFO principle)
    void popBook() {
        if (stack.empty()) {
            cout << "No returned books on the stack!\n";
            return;
        }
        cout << "Book ID " << stack.back() << " moved to main shelf (LIFO).\n";
        stack.pop_back();
    }

    // Display stack contents from top to bottom
    void display() {
        if (stack.empty()) {
            cout << "Return stack is empty.\n";
            return;
        }
        cout << "Return Desk Stack (Top to Bottom): ";
        for (int i = stack.size() - 1; i >= 0; i--) {
            cout << stack[i] << " ";
        }
        cout << endl;
    }
};

// Queue Data Structure (FIFO - First In, First Out) for Book Issuing
class IssueQueue {
    vector<int> queue;
public:
    // Enqueue: Add student to the back of the issue line
    void enqueueStudent(int studentId) {
        queue.push_back(studentId);
        cout << "Student ID " << studentId << " added to issue queue.\n";
    }

    // Dequeue: Serve the student at the front of the queue (FIFO principle)
    void dequeueStudent() {
        if (queue.empty()) {
            cout << "No students in queue!\n";
            return;
        }
        cout << "Issued book to Student ID " << queue.front() << " (FIFO).\n";
        queue.erase(queue.begin());
    }

    // Display all students currently waiting in the queue
    void display() {
        if (queue.empty()) {
            cout << "Issue queue is empty.\n";
            return;
        }
        cout << "Issue Counter Queue (Front to Back): ";
        for (int id : queue) {
            cout << id << " ";
        }
        cout << endl;
    }
};

// Utility function to display the current book inventory list
void displayBooks(const vector<Book>& books) {
    cout << "\n--- Current Book List ---\n";
    for (const auto& b : books) {
        cout << "ID: " << b.id << " | Price: " << b.price << endl;
    }
}

// ==========================================
// MAIN MENU DRIVER FUNCTION
// ==========================================

int main() {
    // Initial sample book inventory data
    vector<Book> books = {
        {121, 450.0}, {102, -50.0}, {131, 600.0}, 
        {102, 350.0}, {105, 0.0}, {144, 200.0}
    };
    
    MembershipList members;
    ReturnStack returnDesk;
    IssueQueue issueCounter;

    int choice;
    do {
        // Main Console UI Menu
        cout << "\n=========================================\n";
        cout << "      STUDENT MANAGEMENT SYSTEM MENU     \n";
        cout << "=========================================\n";
        cout << "1. Module 1: Run All Inventory Analytics\n";
        cout << "2. Module 2: Sort Books & Binary Search\n";
        cout << "3. Module 3: Manage Student Membership List\n";
        cout << "4. Module 3: Book Return Desk (Stack - LIFO)\n";
        cout << "5. Module 3: Issue Counter (Queue - FIFO)\n";
        cout << "6. Display Current Book List\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            task1_counts(books);
            task2_oddEvenIds(books);
            task3_analytics(books);
            task4_removeDuplicates(books);
            task5_logic(books);
            break;
        case 2: {
            cout << "\nChoose Sorting Method:\n";
            cout << "1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n4. Merge Sort\n5. Quick Sort\n";
            int sChoice;
            cin >> sChoice;
            if (sChoice == 1) bubbleSort(books);
            else if (sChoice == 2) selectionSort(books);
            else if (sChoice == 3) insertionSort(books);
            else if (sChoice == 4) mergeSort(books, 0, books.size() - 1);
            else if (sChoice == 5) quickSort(books, 0, books.size() - 1);
            else {
                cout << "Invalid sorting choice!\n";
                break;
            }
            
            cout << "Books sorted by ID successfully!\n";
            displayBooks(books);

            int searchId;
            cout << "\nEnter Book ID to Search: ";
            cin >> searchId;
            binarySearchWithClosest(books, searchId);
            break;
        }
        case 3: {
            int mChoice;
            cout << "\n1. Add Member\n2. Update Member\n3. Delete Member\n4. View All Members\nEnter choice: ";
            cin >> mChoice;
            if (mChoice == 1) {
                int id; string name, course;
                cout << "Enter Student ID: "; cin >> id;
                cout << "Enter Name: "; cin.ignore(); getline(cin, name);
                cout << "Enter Course: "; getline(cin, course);
                members.insertMember(id, name, course);
            } else if (mChoice == 2) {
                int id; string name, course;
                cout << "Enter Student ID to update: "; cin >> id;
                cout << "Enter New Name: "; cin.ignore(); getline(cin, name);
                cout << "Enter New Course: "; getline(cin, course);
                members.updateMember(id, name, course);
            } else if (mChoice == 3) {
                int id;
                cout << "Enter Student ID to delete: "; cin >> id;
                members.deleteMember(id);
            } else if (mChoice == 4) {
                members.traverse();
            } else {
                cout << "Invalid choice!\n";
            }
            break;
        }
        case 4: {
            int rChoice;
            cout << "\n1. Push Returned Book\n2. Pop Book to Shelf\n3. Display Stack\nEnter choice: ";
            cin >> rChoice;
            if (rChoice == 1) {
                int id; cout << "Enter Book ID: "; cin >> id;
                returnDesk.pushBook(id);
            } else if (rChoice == 2) {
                returnDesk.popBook();
            } else if (rChoice == 3) {
                returnDesk.display();
            } else {
                cout << "Invalid choice!\n";
            }
            break;
        }
        case 5: {
            int qChoice;
            cout << "\n1. Add Student to Queue\n2. Issue Book to Next Student\n3. Display Queue\nEnter choice: ";
            cin >> qChoice;
            if (qChoice == 1) {
                int id; cout << "Enter Student ID: "; cin >> id;
                issueCounter.enqueueStudent(id);
            } else if (qChoice == 2) {
                issueCounter.dequeueStudent();
            } else if (qChoice == 3) {
                issueCounter.display();
            } else {
                cout << "Invalid choice!\n";
            }
            break;
        }
        case 6:
            displayBooks(books);
            break;
        case 0:
            cout << "Exiting program. Thank you!\n";
            break;
        default:
            cout << "Invalid Choice! Please enter a valid option.\n";
        }
    } while (choice != 0);

    return 0;
}
