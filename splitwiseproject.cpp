#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

class person_compare {
public:
    bool operator()(pair<string, int> p1, pair<string, int> p2) {
        return p1.second < p2.second;
    }
};

void settleTransactions(map<string, int>& net) {
    multiset<pair<string, int>, person_compare> m;

    for (auto p : net) {
        string person = p.first;
        int amount = p.second;

        if (amount != 0) {
            m.insert(make_pair(person, amount));
        }
    }

    int cnt = 0;
    while (!m.empty()) {
        auto low = m.begin();
        auto high = prev(m.end());

        int debit = low->second;
        string debit_person = low->first;

        int credit = high->second;
        string credit_person = high->first;

        m.erase(low);
        m.erase(high);

        int settled_amount = min(-debit, credit);
        debit += settled_amount;
        credit -= settled_amount;

        cout << debit_person << " will pay " << settled_amount << " to " << credit_person << endl;

        if (debit != 0) {
            m.insert(make_pair(debit_person, debit));
        }
        if (credit != 0) {
            m.insert(make_pair(credit_person, credit));
        }
        cnt++;
    }

    cout << cnt << " transactions needed to settle all debts." << endl;
}

int main() {
    int no_of_transactions, friends;
    cin >> no_of_transactions >> friends;

    map<string, int> net;
    map<int, string> categories = { {1, "Food"}, {2, "Travel"}, {3, "Entertainment"} };

    cout << "Available categories:\n";
    for (auto& category : categories) {
        cout << category.first << ": " << category.second << "\n";
    }

    for (auto& category : categories) {
        int choice;
        cout << "\nDo you want to add transactions for category '" << category.second << "'? (1 for Yes, 0 for No): ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter transactions for category '" << category.second << "' (format: payer payee amount):\n";

            for (int i = 0; i < no_of_transactions; i++) {
                string x, y;
                int amount;

                cout << "Transaction " << i + 1 << ": ";
                cin >> x >> y >> amount;

                int split_type;
                cout << "Choose split type (1: Equal, 2: Unequal, 3: Percentage): ";
                cin >> split_type;

                if (net.count(x) == 0) net[x] = 0;
                if (net.count(y) == 0) net[y] = 0;

                if (split_type == 1) { // Equal split
                    net[x] -= amount;
                    net[y] += amount;
                } else if (split_type == 2) { // Unequal split
                    int payer_share, payee_share;
                    cout << "Enter payer's share and payee's share: ";
                    cin >> payer_share >> payee_share;

                    net[x] -= payer_share;
                    net[y] += payee_share;
                } else if (split_type == 3) { // Percentage split
                    int payer_percentage, payee_percentage;
                    cout << "Enter payer's percentage and payee's percentage: ";
                    cin >> payer_percentage >> payee_percentage;

                    net[x] -= (amount * payer_percentage) / 100;
                    net[y] += (amount * payee_percentage) / 100;
                }

                cout << "Transaction recorded.\n";
            }
        }
    }

    cout << "\nAll transactions settled:\n";
    settleTransactions(net);

    return 0;
}
