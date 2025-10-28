#include <iostream>
#include <windows.h>
#include <string>
#include <cctype>
#include <sstream>
#include "StackFunctions.h"
#include "QueueFunctions.h"
#include "QueueTwoStacksFunctions.h"
#include "CircularBufferFunctions.h"
#include "CircularBuffer.h"

using namespace std;

// Установка русской кодировки для Windows
void SetRussianEncoding() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

int GetValidatedInput(const string& prompt) {
    string input;

    while (true) {
        cout << prompt;
        getline(cin, input);

        if (input.empty()) {
            cout << "Ошибка! Введите целое число: ";
            continue;
        }
        bool isValid = true;
        bool hasNonZero = false;

        for (size_t i = 0; i < input.length(); i++) {
            char c = input[i];

            if (!isdigit(static_cast<unsigned char>(c))) {
                isValid = false;
                break;
            }
            if (c != '0') {
                hasNonZero = true;
            }
        }

        if (!hasNonZero && input.length() > 1) {
            cout << "Ошибка! Введите корректное число: "; 
            continue;
        }

        if (!isValid) {
            cout << "Ошибка! Введите целое число: ";
            continue;
        }

        try {
            long value = stol(input);
            return static_cast<int>(value);
        }
        catch (const out_of_range&) {
            cout << "Число слишком большое! Введите меньшее число: ";
        }
        catch (const exception&) {
            cout << "Ошибка! Введите целое число: ";
        }
    }
}

int GetValidatedInputInRange(const string& prompt, int min, int max) {
    int value;

    while (true) {
        value = GetValidatedInput(prompt);
        if (value >= min && value <= max) {
            return value;
        }
        cout << "Ошибка! Введите число от " << min << " до " << max << ": ";
    }
}
// Вспомогательные функции для создания структур
Stack* CreateStructureStack() {
    int capacity = GetValidatedInput("Введите вместимость стека: ");
    if (capacity <= 0) {
        cout << "Ошибка! Вместимость должна быть положительной." << endl;
        return nullptr;
    }
    Stack* stack = CreateStack(capacity);
    if (stack != nullptr) {
        cout << "Стек создан успешно!" << endl;
    }
    else {
        cout << "Ошибка создания стека!" << endl;
    }
    return stack;
}

Queue* CreateStructureQueue() {
    int capacity = GetValidatedInput("Введите вместимость очереди: ");
    if (capacity <= 0) {
        cout << "Ошибка! Вместимость должна быть положительной." << endl;
        return nullptr;
    }
    Queue* queue = CreateQueue(capacity);
    if (queue != nullptr) {
        cout << "Очередь создана успешно!" << endl;
    }
    else {
        cout << "Ошибка создания очереди!" << endl;
    }
    return queue;
}

QueueTwoStacks* CreateStructureQueueTwoStacks() {
    int capacity = GetValidatedInput("Введите вместимость очереди: ");
    if (capacity <= 0) {
        cout << "Ошибка! Вместимость должна быть положительной." << endl;
        return nullptr;
    }
    QueueTwoStacks* queue = CreateQueueTwoStacks(capacity);
    if (queue != nullptr) {
        cout << "Очередь создана успешно!" << endl;
    }
    else {
        cout << "Ошибка создания очереди!" << endl;
    }
    return queue;
}

// Вспомогательные функции для проверки существования структур
bool CheckStructureExists(void* structure, const string& structureName) {
    if (structure == nullptr) {
        cout << structureName << " не создан(а)!" << endl;
        return false;
    }
    return true;
}

bool CheckStructureNotExists(void* structure, const string& structureName) {
    if (structure != nullptr) {
        cout << structureName << " уже существует! Удалите его сначала." << endl;
        return false;
    }
    return true;
}

// Вспомогательные функции для добавления элементов
void AddElementToStack(Stack*& stack) {
    if (!CheckStructureExists(stack, "Стек")) return;

    if (IsFull(stack)) {
        cout << "Стек полон! Невозможно добавить элемент." << endl;
        return;
    }

    int value = GetValidatedInput("Введите значение для добавления: ");
    Push(stack, value);
    cout << "Элемент " << value << " добавлен в стек." << endl;
}

void AddElementToQueue(Queue*& queue) {
    if (!CheckStructureExists(queue, "Очередь")) return;

    if (IsQueueFull(queue)) {
        cout << "Очередь полна! Невозможно добавить элемент." << endl;
        return;
    }

    int value = GetValidatedInput("Введите значение для добавления: ");
    if (Enqueue(queue, value)) {
        cout << "Элемент " << value << " добавлен в очередь." << endl;
    }
    else {
        cout << "Ошибка добавления элемента!" << endl;
    }
}

void AddElementToQueueTwoStacks(QueueTwoStacks*& queue) {
    if (!CheckStructureExists(queue, "Очередь")) return;

    int value = GetValidatedInput("Введите значение для добавления: ");
    EnqueueTwoStacks(queue, value);
    cout << "Элемент " << value << " добавлен в очередь." << endl;
}

// Вспомогательные функции для извлечения элементов
void ExtractElementFromStack(Stack*& stack) {
    if (!CheckStructureExists(stack, "Стек")) return;

    if (IsEmpty(stack)) {
        cout << "Стек пуст! Невозможно извлечь элемент." << endl;
        return;
    }

    int value = Pop(stack);
    cout << "Извлечен элемент: " << value << endl;
}

void ExtractElementFromQueue(Queue*& queue) {
    if (!CheckStructureExists(queue, "Очередь")) return;

    if (IsQueueEmpty(queue)) {
        cout << "Очередь пуста! Невозможно извлечь элемент." << endl;
        return;
    }

    int value = Dequeue(queue);
    if (value != -1) {
        cout << "Извлечен элемент: " << value << endl;
    }
    else {
        cout << "Ошибка извлечения элемента!" << endl;
    }
}

void ExtractElementFromQueueTwoStacks(QueueTwoStacks*& queue) {
    if (!CheckStructureExists(queue, "Очередь")) return;

    if (IsQueueTwoStacksEmpty(queue)) {
        cout << "Очередь пуста! Невозможно извлечь элемент." << endl;
        return;
    }

    int value = DequeueTwoStacks(queue);
    if (value != -1) {
        cout << "Извлечен элемент: " << value << endl;
    }
    else {
        cout << "Ошибка извлечения элемента!" << endl;
    }
}

// Вспомогательные функции для просмотра элементов
void PeekElementFromStack(Stack*& stack) {
    if (!CheckStructureExists(stack, "Стек")) return;

    if (IsEmpty(stack)) {
        cout << "Стек пуст!" << endl;
        return;
    }

    int value = Peek(stack);
    cout << "Верхний элемент: " << value << endl;
}

// Вспомогательные функции для удаления структур
void DeleteStructureStack(Stack*& stack) {
    if (stack != nullptr) {
        DeleteStack(stack);
        stack = nullptr;
        cout << "Стек удален." << endl;
    }
    else {
        cout << "Стек уже удален или не создан." << endl;
    }
}

void DeleteStructureQueue(Queue*& queue) {
    if (queue != nullptr) {
        DeleteQueue(queue);
        queue = nullptr;
        cout << "Очередь удалена." << endl;
    }
    else {
        cout << "Очередь уже удалена или не создана." << endl;
    }
}

void DeleteStructureQueueTwoStacks(QueueTwoStacks*& queue) {
    if (queue != nullptr) {
        DeleteQueueTwoStacks(queue);
        queue = nullptr;
        cout << "Очередь удалена." << endl;
    }
    else {
        cout << "Очередь уже удалена или не создана." << endl;
    }
}

// Функции для вывода характеристик структур
void PrintStackInfo(Stack* stack, const string& name) {
    cout << "=== " << name << " ===" << endl;
    if (stack == nullptr) {
        cout << "Стек не создан или удален" << endl;
        return;
    }
    cout << "Вместимость: " << stack->_capacity << endl;
    cout << "Вершина (top): " << stack->_top << endl;
    cout << "Пуст: " << (IsEmpty(stack) ? "да" : "нет") << endl;
    cout << "Полон: " << (IsFull(stack) ? "да" : "нет") << endl;

    cout << "Содержимое (сверху вниз): ";
    if (IsEmpty(stack)) {
        cout << "пусто";
    }
    else {
        Stack* tempStack = CreateStack(stack->_capacity);
        int count = 0;

        while (!IsEmpty(stack)) {
            int value = Pop(stack);
            Push(tempStack, value);
            count++;
        }

        for (int i = 0; i < count; i++) {
            int value = Pop(tempStack);
            cout << value;
            if (i < count - 1) cout << " <- ";
            Push(stack, value);
        }

        DeleteStack(tempStack);
    }
    cout << endl << endl;
}

void PrintQueueInfo(Queue* queue, const string& name) {
    cout << "=== " << name << " ===" << endl;
    if (queue == nullptr) {
        cout << "Очередь не создана или удалена" << endl;
        return;
    }
    cout << "Пуста: " << (IsQueueEmpty(queue) ? "да" : "нет") << endl;
    cout << "Полна: " << (IsQueueFull(queue) ? "да" : "нет") << endl;
    cout << "Занято мест: " << GetUsedSpace(queue->_circularBuffer) << endl;
    cout << "Свободно мест: " << GetFreeSpace(queue->_circularBuffer) << endl;

    cout << "Содержимое (начало -> конец): ";
    if (IsQueueEmpty(queue)) {
        cout << "пусто";
    }
    else {
        int capacity = GetUsedSpace(queue->_circularBuffer) + GetFreeSpace(queue->_circularBuffer);
        Queue* tempQueue = CreateQueue(capacity);
        int count = 0;

        while (!IsQueueEmpty(queue)) {
            int value = Dequeue(queue);
            cout << value;
            if (!IsQueueEmpty(queue)) cout << " -> ";
            Enqueue(tempQueue, value);
            count++;
        }

        while (!IsQueueEmpty(tempQueue)) {
            int value = Dequeue(tempQueue);
            Enqueue(queue, value);
        }

        DeleteQueue(tempQueue);
    }
    cout << endl << endl;
}

void PrintQueueTwoStacksInfo(QueueTwoStacks* queue, const string& name) {
    cout << "=== " << name << " ===" << endl;
    if (queue == nullptr) {
        cout << "Очередь на двух стеках не создана или удалена" << endl;
        return;
    }
    cout << "Пуста: " << (IsQueueTwoStacksEmpty(queue) ? "да" : "нет") << endl;

    cout << "InputStack: ";
    PrintStackInfo(queue->_inputStack, "InputStack очереди");

    cout << "OutputStack: ";
    PrintStackInfo(queue->_outputStack, "OutputStack очереди");

    cout << "Содержимое очереди (начало -> конец): ";
    if (IsQueueTwoStacksEmpty(queue)) {
        cout << "пусто";
    }
    else {
        int capacity = queue->_inputStack->_capacity;
        QueueTwoStacks* tempQueue = CreateQueueTwoStacks(capacity);
        int count = 0;

        while (!IsQueueTwoStacksEmpty(queue)) {
            int value = DequeueTwoStacks(queue);
            cout << value;
            if (!IsQueueTwoStacksEmpty(queue)) cout << " -> ";
            EnqueueTwoStacks(tempQueue, value);
            count++;
        }

        while (!IsQueueTwoStacksEmpty(tempQueue)) {
            int value = DequeueTwoStacks(tempQueue);
            EnqueueTwoStacks(queue, value);
        }

        DeleteQueueTwoStacks(tempQueue);
    }
    cout << endl << endl;
}

void ShowStackMenu() {
    cout << "0 - Назад в главное меню" << endl;
    cout << "1 - Создать стек" << endl;
    cout << "2 - Добавить элемент (Push)" << endl;
    cout << "3 - Извлечь элемент (Pop)" << endl;
    cout << "4 - Посмотреть верхний элемент (Peek)" << endl;
    cout << "5 - Изменить размер стека" << endl;
    cout << "6 - Удалить стек" << endl;
}

void ShowQueueMenu() {
    cout << "0 - Назад в главное меню" << endl;
    cout << "1 - Создать очередь" << endl;
    cout << "2 - Добавить элемент (Enqueue)" << endl;
    cout << "3 - Извлечь элемент (Dequeue)" << endl;
    cout << "4 - Изменить размер очереди" << endl;
    cout << "5 - Удалить очередь" << endl;
}

void ShowQueueTwoStacksMenu() {
    cout << "0 - Назад в главное меню" << endl;
    cout << "1 - Создать очередь" << endl;
    cout << "2 - Добавить элемент (Enqueue)" << endl;
    cout << "3 - Извлечь элемент (Dequeue)" << endl;
    cout << "4 - Изменить размер очереди" << endl;
    cout << "5 - Удалить очередь" << endl;
}
// Функции для обработки выбора в меню
void HandleStackMenuChoice(int choice, Stack*& stack) {
    switch (choice) {
    case 1: {
        if (CheckStructureNotExists(stack, "Стек")) {
            stack = CreateStructureStack();
        }
        break;
    }
    case 2: {
        AddElementToStack(stack);
        break;
    }
    case 3: {
        ExtractElementFromStack(stack);
        break;
    }
    case 4: {
        PeekElementFromStack(stack);
        break;
    }
    case 5: {
        if (CheckStructureExists(stack, "Стек")) {
            int newCapacity = GetValidatedInput("Введите новый размер стека: ");
            if (ResizeStack(stack, newCapacity)) {
                cout << "Размер стека изменен на " << newCapacity << endl;
            }
            else {
                cout << "Ошибка изменения размера стека!" << endl;
            }
        }
        break;
    }
    case 6: {
        DeleteStructureStack(stack);
        break;
    }
    }
}

void HandleQueueMenuChoice(int choice, Queue*& queue) {
    switch (choice) {
    case 1: {
        if (CheckStructureNotExists(queue, "Очередь")) {
            queue = CreateStructureQueue();
        }
        break;
    }
    case 2: {
        AddElementToQueue(queue);
        break;
    }
    case 3: {
        ExtractElementFromQueue(queue);
        break;
    }
    case 4: {
        if (CheckStructureExists(queue, "Очередь")) {
            int newCapacity = GetValidatedInput("Введите новый размер очереди: ");
            if (ResizeQueue(queue, newCapacity)) {
                cout << "Размер очереди изменен на " << newCapacity << endl;
            }
            else {
                cout << "Ошибка изменения размера очереди!" << endl;
            }
        }
        break;
    }
    case 5: {
        DeleteStructureQueue(queue);
        break;
    }
    }
}

void HandleQueueTwoStacksMenuChoice(int choice, QueueTwoStacks*& queue) {
    switch (choice) {
    case 1: {
        if (CheckStructureNotExists(queue, "Очередь")) {
            queue = CreateStructureQueueTwoStacks();
        }
        break;
    }
    case 2: {
        AddElementToQueueTwoStacks(queue);
        break;
    }
    case 3: {
        ExtractElementFromQueueTwoStacks(queue);
        break;
    }
    case 4: {
        if (CheckStructureExists(queue, "Очередь")) {
            int newCapacity = GetValidatedInput("Введите новый размер очереди: ");
            if (ResizeQueueTwoStacks(queue, newCapacity)) {
                cout << "Размер очереди изменен на " << newCapacity << endl;
            }
            else {
                cout << "Ошибка изменения размера очереди!" << endl;
            }
        }
        break;
    }
    case 5: {
        DeleteStructureQueueTwoStacks(queue);
        break;
    }
    }
}

// Главное меню
int main() {
    SetRussianEncoding(); // Установка русской кодировки

    Stack* myStack = nullptr;
    Queue* myQueue = nullptr;
    QueueTwoStacks* myQueueTwoStacks = nullptr;

    int mainChoice, subChoice;

    cout << "=== ДЕМОНСТРАЦИЯ СТРУКТУР ДАННЫХ ===" << endl;

    do {
        cout << "\n=== ГЛАВНОЕ МЕНЮ ===" << endl;
        cout << "0 - Выход из программы" << endl;
        cout << "1 - Работа со стеком" << endl;
        cout << "2 - Работа с очередью (кольцевой буфер)" << endl;
        cout << "3 - Работа с очередью (два стека)" << endl;
        cout << "4 - Показать все структуры" << endl;

        mainChoice = GetValidatedInputInRange("Выберите действие: ", 0, 5);

        switch (mainChoice) {
        case 0: {
            cout << "Выход из программы..." << endl;
            break;
        }

        case 1: {
            do {
                cout << "\n=== РАБОТА СО СТЕКОМ ===" << endl;
                PrintStackInfo(myStack, "Текущий стек");
                ShowStackMenu();

                subChoice = GetValidatedInputInRange("Выберите действие: ", 0, 6);
                HandleStackMenuChoice(subChoice, myStack);

            } while (subChoice != 0);
            break;
        }

        case 2: {
            do {
                cout << "\n=== ОЧЕРЕДЬ (КОЛЬЦЕВОЙ БУФЕР) ===" << endl;
                PrintQueueInfo(myQueue, "Текущая очередь");
                ShowQueueMenu();

                subChoice = GetValidatedInputInRange("Выберите действие: ", 0, 5);
                HandleQueueMenuChoice(subChoice, myQueue);

            } while (subChoice != 0);
            break;
        }

        case 3: {
            do {
                cout << "\n=== ОЧЕРЕДЬ (ДВА СТЕКА) ===" << endl;
                PrintQueueTwoStacksInfo(myQueueTwoStacks, "Текущая очередь на двух стеках");
                ShowQueueTwoStacksMenu();

                subChoice = GetValidatedInputInRange("Выберите действие: ", 0, 5);
                HandleQueueTwoStacksMenuChoice(subChoice, myQueueTwoStacks);

            } while (subChoice != 0);
            break;
        }

        case 4: {
            cout << "\n=== ВСЕ СТРУКТУРЫ ДАННЫХ ===" << endl;
            PrintStackInfo(myStack, "СТЕК");
            PrintQueueInfo(myQueue, "ОЧЕРЕДЬ (КОЛЬЦЕВОЙ БУФЕР)");
            PrintQueueTwoStacksInfo(myQueueTwoStacks, "ОЧЕРЕДЬ (ДВА СТЕКА)");
            break;
        }
        }

    } while (mainChoice != 0);

    // Очистка памяти перед выходом
    DeleteStructureStack(myStack);
    DeleteStructureQueue(myQueue);
    DeleteStructureQueueTwoStacks(myQueueTwoStacks);

    return 0;
}