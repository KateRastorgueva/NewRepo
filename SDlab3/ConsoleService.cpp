#include "ConsoleService.h"
/// <summary>
/// Проверяет существование структуры данных
/// </summary>
/// <param name="structure">Указатель на структуру данных</param>
/// <param name="structureName">Название структуры для сообщений</param>
/// <returns>true если структура существует, иначе false</returns>
bool CheckStructureExists(void* structure, const string& structureName)
{
    if (structure == nullptr)
    {
        cout << structureName << " не создан(а)!" << endl;
        return false;
    }
    return true;
}
/// <summary>
/// Проверяет отсутствие структуры данных
/// </summary>
/// <param name="structure">Указатель на структуру данных</param>
/// <param name="structureName">Название структуры для сообщений</param>
/// <returns>true если структура не существует, иначе false</returns>
bool CheckStructureNotExists(void* structure, const string& structureName)
{
    if (structure != nullptr)
    {
        cout << structureName << " уже существует! Удалите сначала." << endl;
        return false;
    }
    return true;
}
/// <summary>
/// Проверяет, является ли структура данных пустой
/// </summary>
/// <param name="isEmpty">Результат проверки на пустоту</param>
/// <param name="structureName">Название структуры для сообщений</param>
/// <returns>true если структура пуста, иначе false</returns>
bool CheckStructureEmpty(bool isEmpty, const string& structureName)
{
    if (isEmpty)
    {
        cout << structureName << " пуст(а)! Невозможно извлечь элемент." << endl;
        return true;
    }
    return false;
}

/// <summary>
/// Отображает извлеченный элемент
/// </summary>
/// <param name="value">Значение извлеченного элемента</param>
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
/// <summary>
/// Отображает сообщение об успешном создании структуры
/// </summary>
/// <param name="structureName">Название созданной структуры</param>
void ShowCreationSuccess(const string& structureName)
{
    cout << structureName << " создан(а) успешно!" << endl;
}
/// <summary>
/// Отображает сообщение об ошибке создания структуры
/// </summary>
/// <param name="structureName">Название структуры</param>
void ShowCreationError(const string& structureName)
{
    cout << "Ошибка создания " << structureName << "!" << endl;
}
/// <summary>
/// Отображает сообщение об успешном добавлении элемента
/// </summary>
/// <param name="value">Добавленное значение</param>
/// <param name="structureName">Название структуры</param>
void ShowAddSuccess(int value, const string& structureName)
{
    cout << "Элемент " << value << " добавлен в " << structureName << "." << endl;
}
/// <summary>
/// Отображает сообщение об ошибке добавления элемента
/// </summary>
/// <param name="structureName">Название структуры</param>
void ShowAddError(const string& structureName)
{
    cout << structureName << " полон(а)! Невозможно добавить элемент." << endl;
}
/// <summary>
/// Отображает сообщение об успешном изменении размера
/// </summary>
/// <param name="newCapacity">Новый размер структуры</param>
/// <param name="structureName">Название структуры</param>
void ShowResizeSuccess(int newCapacity, const string& structureName)
{
    cout << "Размер " << structureName << " изменен на " << newCapacity << endl;
}
/// <summary>
/// Отображает сообщение об ошибке изменения размера
/// </summary>
/// <param name="structureName">Название структуры</param>
void ShowResizeError(const string& structureName)
{
    cout << "Ошибка изменения размера " << structureName << "!" << endl;
}
/// <summary>
/// Отображает сообщение о результате удаления структуры
/// </summary>
/// <param name="wasDeleted">Факт выполнения удаления</param>
/// <param name="structureName">Название структуры</param>
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
/// <summary>
/// Выводит базовую информацию о структуре
/// </summary>
/// <param name="capacity">Вместимость структуры</param>
/// <param name="top">Индекс вершины/головы</param>
void WriteInfo(int capacity, int top)
{
    cout << "Вместимость: " << capacity << endl;
    cout << "Вершина (top): " << top << endl;
}
/// <summary>
/// Выводит информацию о состоянии заполнения структуры
/// </summary>
/// <param name="isEmpty">Признак пустоты</param>
/// <param name="isFull">Признак полноты</param>
void WriteFullEmptyInfo(bool isEmpty, bool isFull)
{
    cout << "Пуст(а): " << (isEmpty ? "да" : "нет") << endl;
    cout << "Полон(а): " << (isFull ? "да" : "нет") << endl;
}
/// <summary>
/// Выводит подробную информацию о кольцевом буфере
/// </summary>
/// <param name="capacity">Вместимость буфера</param>
/// <param name="head">Индекс головы</param>
/// <param name="tail">Индекс хвоста</param>
/// <param name="count">Количество элементов</param>
void WriteCircularBufferInfo(int capacity, int head, int tail, int count)
{
    cout << "Вместимость: " << capacity << endl;
    cout << "Голова (head): " << head << endl;
    cout << "Хвост (tail): " << tail << endl;
    cout << "Количество элементов: " << count << endl;
}
/// <summary>
/// Выводит информацию о занятом и свободном месте
/// </summary>
/// <param name="used">Количество занятых мест</param>
/// <param name="free">Количество свободных мест</param>
void WriteSpaceInfo(int used, int free)
{
    cout << "Занято мест: " << used << endl;
    cout << "Свободно мест: " << free << endl;
}
/// <summary>
/// Выводит сообщение об отсутствии структуры
/// </summary>
/// <param name="value">Название структуры</param>
void WriteIsDeleteNotCreated(string value)
{
    cout << value << " не создан(а) или удален(а)" << endl;
}
/// <summary>
/// Проверяет и выводит заголовок структуры
/// </summary>
/// <param name="structure">Указатель на структуру</param>
/// <param name="name">Название структуры</param>
/// <returns>true если структура существует, иначе false</returns>
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
/// <summary>
/// Выводит заголовок для содержимого структуры
/// </summary>
/// <param name="isEmpty">Признак пустоты структуры</param>
/// <param name="contentDescription">Описание содержимого</param>
void PrintContentHeader(bool isEmpty, const string& contentDescription)
{
    cout << contentDescription << ": ";
    if (isEmpty)
    {
        cout << "пусто";
    }
}