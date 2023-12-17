#include <iostream>
#include <string>
#include <cstdlib>

template <typename T>
class Stack {
public:

    Stack() {
        capacity = 7;
        size = 0;
        arr = new T[capacity];
    }

    ~Stack() {
        delete[] arr;
    }

    void operator<<(T element) { //&
        if (size == capacity) {
            if (capacity == 0) {
                capacity = 1;
            }
            else {
                capacity = capacity * 2;
            }
            T* newArr = new T[capacity];
            for (int i = 0; i < size; i++) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }
        arr[size++] = element;
    }

    void push(const T& element) {
        if (size == capacity) {
            if (capacity == 0) {
                capacity = 1;
            }
            else {
                capacity = capacity * 2;
            }
            T* newArr = new T[capacity];
            for (int i = 0; i < size; i++) { 
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }
        arr[size] = element;
        size++;
    }

    int operator>>(int& element) { //&
        if (size == 0) {
            std::cout << "Stack is empty!" << std::endl;
            return -1;
        }
        element = arr[--size];
        return element;
    }

    T pop() {
        if (size == 0) {
            std::cout << "Stack is empty!" << std::endl;
            return T();
        }
        size--;
        //for (int i = size; i > 0; i--) {
        //    arr[i] = arr[i - 1];
        //}
        return arr[size];
    }

    T GetTop() {
        if (size == 0) {
            std::cout << "Stack is empty!" << std::endl;
            return T();
        }
        return arr[size-1];
    }

    int GetSize() {
        return size; 
    }

    T& operator[](int index) const {
        if (index < 0 || index >= size) {
            std::cout << "Invalid index!" << std::endl;
            return 0;
        }
        return arr[index];
    }

    bool operator<(const Stack<T>& other) {
        return size < other.size;
    }

    bool operator==(const Stack<T>& other) {
        if (size != other.size) {
            return false;
        }
        for (int i = 0; i < size; i++) {
            if (arr[i] != other.arr[i]) {
                return false;
            }
        }
        return true;
    }

    Stack<T>& operator=(const Stack<T>& other) {
        if (this == &other) {
            return *this;
        }
        delete[] arr;
        size = other.size;
        capacity = other.capacity;
        arr = new T[capacity];
        for (int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
        return *this;
    };



private:
    T* arr;
    int size;
    int capacity;
};
struct Leksema {
    char type;
    double value;
};



template <typename T>
class Calculator {
public:
    Calculator() {}

    void Poschitaem() {
        Leksema item;
        bool flag = 1;

        while (true) {
            Ch = std::cin.peek();
            if (Ch == '\n')break;
            if (Ch == ' ') {
                std::cin.ignore();
                continue;
            }
            if (Ch >= '0' && Ch <= '9' || Ch == '-' && flag == 1) {
                double value;
                std::cin >> value;
                std::cout << value << " ";
                item.type = '0';
                item.value = value;
                stack_n.push(item);
                flag = 0;
                continue;
            }
            if (Ch == '+' || Ch == '-' && flag == 0 || Ch == '*' || Ch == '/') {
                if (stack_o.GetSize() == 0) {
                    Leksema item;
                    item.type = Ch;
                    std::cout << Ch << " ";
                    item.value = 0;
                    stack_o.push(item);
                    std::cin.ignore();
                    continue;
                }
                if (stack_o.GetSize() != 0 && GetRang(Ch) > GetRang(stack_o.GetTop().type)) {
                    Leksema item;
                    item.type = Ch;
                    std::cout << Ch << " ";
                    item.value = 0;
                    stack_o.push(item);
                    std::cin.ignore();
                    continue;
                }
                if (stack_o.GetSize() != 0 && GetRang(Ch) <= GetRang(stack_o.GetTop().type)) {
                    if (Math(stack_n, stack_o, item) == false) {
                        std::cerr << "incorrect expression";
                        exit(0);
                        break;
                    }
                    continue;
                }

                /*               if (stack_o.GetSize() != 0 && GetRang(Ch) <= GetRang(stack_o.GetTop().type) && stack_o.GetTop().type != '(') {
                                   if (Math(stack_n, stack_o, item) == false) {
                                       std::cerr << "incorrect expression";
                                       break;
                                   }
                                   continue;
                               }*/

            }
            if (Ch == '(') {
                Leksema item;
                item.type = Ch;
                std::cout << Ch << " ";
                item.value = 0;
                stack_o.push(item);
                std::cin.ignore();
                continue;
            }
            if (Ch == ')') {
                while (stack_o.GetTop().type != '(') {
                    if (Math(stack_n, stack_o, item) == false) {
                        std::cerr << "incorrect expression";
                        exit(0);
                        break;
                    }
                    else continue;
                }
                stack_o.pop();
                std::cin.ignore();
                continue;
            }
            else {
                std::cerr << "\nincorrect expression\n";
                exit(0);
                break;
            }
        }
        while (stack_o.GetSize() != 0) {
            if (Math(stack_n, stack_o, item) == false) {
                std::cerr << "\nincorrect expression";
                exit(0);
                break;
            }
            else continue;
        }

        std::cout << std::endl;
            std::cout << "answer: " << stack_n.GetTop().value << std::endl;
    }

        bool Math(Stack<Leksema>&stack_n, Stack<Leksema>&stack_o, Leksema & item) {

            if (stack_n.GetSize() < 2 || stack_o.GetSize() < 1) {
                std::cerr << "\nincorrect expression\n";
                exit(0);
                return false;
            }

            double a, b, c;
            a = stack_n.GetTop().value;
            stack_n.pop();//
            switch (stack_o.GetTop().type) {
            case '+':
                b = stack_n.GetTop().value;
                stack_n.pop();
                c = a + b;
                item.type = '0';
                item.value = c;
                stack_n.push(item);
                stack_o.pop();
                break;

            case '-':
                b = stack_n.GetTop().value;
                stack_n.pop();
                c = b - a;
                item.type = '0';
                item.value = c;
                stack_n.push(item);
                stack_o.pop();
                break;

            case '*':
                b = stack_n.GetTop().value;
                stack_n.pop();
                c = a * b;
                item.type = '0';
                item.value = c;
                stack_n.push(item);
                stack_o.pop();
                break;

            case '/':
                b = stack_n.GetTop().value;
                if (a == 0) {
                    std::cerr << std::endl << "can't be divided by 0";
                    exit(0);
                    return false;
                }
                else {
                    stack_n.pop();
                    c = (b / a);
                    item.type = '0';
                    item.value = c;
                    stack_n.push(item);
                    stack_o.pop();
                    break;
                }
            default:
                std::cerr << std::endl << "wrong expression" << std::endl;
                exit(0);
                return false;
                break;
            }
            return true;
        }

        int GetRang(char Ch) {
            if (Ch == '+' || Ch == '-')
                return 1;
            if (Ch == '*' || Ch == '/')
                return 2;
            else return 0;
        }

private:

    Stack<Leksema> stack_n;
    Stack<Leksema> stack_o;
    char Ch;
    };

    int main() {
        Calculator<double> calculator;
        calculator.Poschitaem();
        std::cout << std::endl;
        return 0;
    }
