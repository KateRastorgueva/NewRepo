#include <iostream>
#include <windows.h>
#include "TreeConsoleService.h"
#include "Validator.h"
#include "BinarySearchTreeMenu.h"
#include "CartesianTreeMenu.h"

using namespace std;

void SetRussianEncoding()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

void ShowMainMenu()
{
    cout << "\nÃËÀÂÍÎÅ ÌÅÍÞ ÄÅÐÅÂÜÅÂ ÏÎÈÑÊÀ" << endl;
    cout << "0 - Âûõîä èç ïðîãðàììû" << endl;
    cout << "1 - Ðàáîòà ñ áèíàðíûì äåðåâîì ïîèñêà" << endl;
    cout << "2 - Ðàáîòà ñ äåêàðòîâûì äåðåâîì" << endl;
}

int main()
{
    SetRussianEncoding();

    int choice;

    cout << "ÄÅÐÅÂÜß ÏÎÈÑÊÀ" << endl;

    do
    {
        ShowMainMenu();
        choice = GetValidatedInputInRange(0, 2);

        switch (choice)
        {
        case 0:
            cout << "Âûõîä èç ïðîãðàììû..." << endl;
            break;

        case 1:
            BinarySearchTreeMenu();
            break;

        case 2:
            CartesianTreeMenu();
            break;
        }

    } while (choice != 0);

    return 0;
}