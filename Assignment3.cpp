// Harshvardhan Borude
// 123B1F013
// 08|08|2025
/*
    PROBLEM STATEMENT:
Scenario: Emergency Relief Supply Distribution
A devastating flood has hit multiple villages in a remote area, and the government, along
with NGOs, is organizing an emergency relief operation. A rescue team has a limited-capacity
boat that can carry a maximum weight of W kilograms. The boat must transport
critical supplies, including food, medicine, and drinking water, from a relief center to the
affected villages.
Each type of relief item has:
● A weight (wi) in kilograms.
● Utility value (vi) indicating its importance (e.g., medicine has higher value than food).
● Some items can be divided into smaller portions (e.g., food and water), while others must
be taken as a whole (e.g., medical kits).
As the logistics manager, you must:
1. Implement the Fractional Knapsack algorithm to maximize the total utility value of the
supplies transported.
2. Prioritize high-value items while considering weight constraints.
3. Allow partial selection of divisible items (e.g., carrying a fraction of food packets).
4. Ensure that the boat carries the most critical supplies given its weight limit W.
    */


#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// Structure to store item details
struct Item {
    string name;
    double weight;
    double value;
    bool divisible; // true = can be taken fractionally
};

// Comparison based on value/weight ratio
bool cmp(Item a, Item b) {
    double r1 = a.value / a.weight;
    double r2 = b.value / b.weight;
    return r1 > r2; // sort in descending order
}

void fractionalKnapsack(vector<Item>& items, double W) {
    // Sort items based on value/weight ratio
    sort(items.begin(), items.end(), cmp);

    double totalValue = 0.0;
    double currentWeight = 0.0;

    cout << "\nSelected Items for Transport:\n";
    cout << "-----------------------------------------------------------\n";
    cout << left << setw(15) << "Item"
         << setw(12) << "Weight(kg)"
         << setw(12) << "Value"
         << setw(12) << "Taken(kg)" << endl;
    cout << "-----------------------------------------------------------\n";

    for (auto& item : items) {
        if (currentWeight >= W) break; // capacity full

        if (currentWeight + item.weight <= W) {
            // Take full item
            totalValue += item.value;
            currentWeight += item.weight;
            cout << left << setw(15) << item.name
                 << setw(12) << item.weight
                 << setw(12) << item.value
                 << setw(12) << item.weight << endl;
        } else if (item.divisible) {
            // Take fractional part
            double remain = W - currentWeight;
            double fraction = remain / item.weight;
            totalValue += item.value * fraction;
            currentWeight += remain;
            cout << left << setw(15) << item.name
                 << setw(12) << item.weight
                 << setw(12) << item.value
                 << setw(12) << fixed << setprecision(2) << remain << endl;
        }
        // Skip indivisible items if can't take full weight
    }

    cout << "-----------------------------------------------------------\n";
    cout << "Total Weight Loaded: " << currentWeight << " kg\n";
    cout << "Maximum Utility Value: " << totalValue << "\n";
}

int main() {
    int n;
    double W;

    cout << "Enter number of relief items: ";
    cin >> n;

    vector<Item> items(n);

    cout << "Enter details for each item:\n";
    for (int i = 0; i < n; i++) {
        cout << "\nItem " << i + 1 << " name: ";
        cin >> items[i].name;
        cout << "Weight (kg): ";
        cin >> items[i].weight;
        cout << "Utility value: ";
        cin >> items[i].value;
        cout << "Divisible (1 for Yes, 0 for No): ";
        cin >> items[i].divisible;
    }

    cout << "\nEnter boat capacity (kg): ";
    cin >> W;

    fractionalKnapsack(items, W);

    return 0;
}
