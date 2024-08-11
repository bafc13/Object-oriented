#include "h.h"

int main()
{
    setlocale(LC_ALL, "rus");

    {
        cout << "���� 1: Set<int>\n";
        Set<int> set;
        cout << set << '\n';
        cout << "������: " << set.size() << '\n';
        cout << "����: " << set.empty() << '\n';
        set.insert(1);
        set.insert(356);
        set.insert(234);
        set.insert(1);
        set.insert(-710);
        cout << set << '\n';
        cout << "������: " << set.size() << '\n';
        cout << "����: " << set.empty() << '\n';
        cout << "�������� 356: " << set.contains(356) << '\n';
        cout << "�������� 2: " << set.contains(2) << '\n';
        cout << "������ ������� ��������, ������� >= 11: " << set.lower_bound(11) << '\n';
        cout << "������ ������� ��������, ������� > 0: " << set.upper_bound(0) << '\n';
        set.erase(0); // �������� ������� ��������
        cout << set << '\n';
        cout << "������ �������� 234: " << set.find(234) << '\n';
        cout << "������ �������� 5: " << set.find(5) << '\n'; // ����� -1
        set.clear();
        cout << set;
        cout << "\n\n";
    }
    {
        cout << "���� 2: Set<double>\n";
        Set<double> set;
        cout << set << '\n';
        cout << "������: " << set.size() << '\n';
        cout << "����: " << set.empty() << '\n';
        set.insert(-543.4);
        set.insert(2.1);
        set.insert(64.64);
        set.insert(2.1);
        set.insert(6.42);
        cout << set << '\n';
        cout << "������: " << set.size() << '\n';
        cout << "����: " << set.empty() << '\n';
        cout << "�������� 1.5: " << set.contains(1.5) << '\n';
        cout << "�������� 64.64: " << set.contains(64.64) << '\n';
        cout << "������ ������� ��������, ������� >= 0.5: " << set.lower_bound(0.5) << '\n';
        cout << "������ ������� ��������, ������� > 50.4: " << set.upper_bound(50.4) << '\n';
        set.erase(1); // �������� ������� ��������
        cout << set << '\n';
        cout << "������ �������� -543.4: " << set.find(-543.4) << '\n';
        cout << "������ �������� 0.1: " << set.find(0.1) << '\n'; // ����� -1
        set.clear();
        cout << set;
        cout << "\n\n";
    }
    {
        cout << "���� 3: Set<string>\n";
        Set<string> set;
        cout << set << '\n';
        cout << "������: " << set.size() << '\n';
        cout << "����: " << set.empty() << '\n';
        set.insert("a");
        set.insert("bj");
        set.insert("a");
        set.insert("it");
        set.insert("hg");
        cout << set << '\n';
        cout << "������: " << set.size() << '\n';
        cout << "����: " << set.empty() << '\n';
        cout << "�������� abc: " << set.contains("abc") << '\n';
        cout << "�������� g: " << set.contains("g") << '\n';
        cout << "������ ������� ��������, ������� >= a: " << set.lower_bound("a") << '\n';
        cout << "������ ������� ��������, ������� > a: " << set.upper_bound("a") << '\n';
        set.erase(0); // �������� ������� ��������
        cout << set << '\n';
        cout << "������ �������� it: " << set.find("it") << '\n';
        cout << "������ �������� bc: " << set.find("bc") << '\n'; // ����� -1
        set.clear();
        cout << set;
        cout << '\n';
    }

    return 0;
}
