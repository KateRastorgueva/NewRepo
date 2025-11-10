#include "ConsoleService.h"

bool CheckStructureExists(void* structure, const string& structureName)
{
    if (structure == nullptr)
    {
        cout << structureName << " не создан(а)!" << endl;
        return false;
    }
    return true;
}

bool CheckStructureNotExists(void* structure, const string& structureName)
{
    if (structure != nullptr)
    {
        cout << structureName << " уже существует! Удалите сначала." << endl;
        return false;
    }
    return true;
}

bool CheckStructureEmpty(bool isEmpty, const string& structureName)
{
    if (isEmpty)
    {
        cout << structureName << " пуст(а)! Невозможно извлечь элемент." << endl;
        return true;
    }
    return false;
}

void ShowExtractedElement(int value)
{
    if (value != -1)
    {
        cout << "Извлечен элемент: " << value << endl;
    }
    else
    {
        cout << "Ошибка извлечения элемента!" << endl;
    }
}

void ShowCreationSuccess(const string& structureName)
{
    cout << structureName << " создан(а) успешно!" << endl;
}

void ShowCreationError(const string& structureName)
{
    cout << "Ошибка создания " << structureName << "!" << endl;
}

void ShowAddSuccess(int value, const string& structureName)
{
    cout << "Элемент " << value << " добавлен в " << structureName << "." << endl;
}

void ShowAddError(const string& structureName)
{
    cout << structureName << " полон(а)! Невозможно добавить элемент." << endl;
}

void ShowResizeSuccess(int newCapacity, const string& structureName)
{
    cout << "Размер " << structureName << " изменен на " << newCapacity << endl;
}

void ShowResizeError(const string& structureName)
{
    cout << "Ошибка изменения размера " << structureName << "!" << endl;
}

void ShowDeleteMessage(bool wasDeleted, const string& structureName)
{
    if (wasDeleted)
    {
        cout << structureName << " удален(а)." << endl;
    }
    else
    {
        cout << structureName << " уже удален(а) или не создан(а)." << endl;
    }
}

void WriteInfo(int capacity, int top)
{
    cout << "Вместимость: " << capacity << endl;
    cout << "Вершина (top): " << top << endl;
}

void WriteFullEmptyInfo(bool isEmpty, bool isFull)
{
    cout << "Пуст(а): " << (isEmpty ? "да" : "нет") << endl;
    cout << "Полон(а): " << (isFull ? "да" : "нет") << endl;
}

void WriteCircularBufferInfo(int capacity, int head, int tail, int count)
{
    cout << "Вместимость: " << capacity << endl;
    cout << "Голова (head): " << head << endl;
    cout << "Хвост (tail): " << tail << endl;
    cout << "Количество элементов: " << count << endl;
}

void WriteSpaceInfo(int used, int free)
{
    cout << "Занято мест: " << used << endl;
    cout << "Свободно мест: " << free << endl;
}

void WriteIsDeleteNotCreated(string value)
{
    cout << value << " не создан(а) или удален(а)" << endl;
}

bool CheckAndPrintHeader(void* structure, const string& name)
{
    cout << name << endl;
    if (structure == nullptr)
    {
        WriteIsDeleteNotCreated(name);
        return false;
    }
    return true;
}

void PrintContentHeader(bool isEmpty, const string& contentDescription)
{
    cout << contentDescription << ": ";
    if (isEmpty)
    {
        cout << "пусто";
    }
}