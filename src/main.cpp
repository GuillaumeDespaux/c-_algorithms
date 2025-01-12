#include "main.hpp"

int main() {
    // List 1
    vector<s_Pizza> pizzas;

    // List 2
    vector<s_Pizza> pizzas2;


    vector<s_Ingredient> ingredients;
    
    load_example_pizzas(pizzas2);
    load_random_pizzas(pizzas, Ingredient_Type);

    int choice;

    do {
        cout << "\n=== Pizza Management Menu ===\n";
        cout << "1. Add Pizza\n";
        cout << "2. Display Pizzas\n";
        cout << "3. Update Pizza\n";
        cout << "4. Remove Pizza\n";
        cout << "5. Sort Pizzas\n";
        cout << "6. Add Ingredient\n";
        cout << "7. Display pizza's IDs\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                add_pizza(pizzas);
                break;
            case 2:
                display_pizzas(pizzas);
                break;
            case 3:
                update_pizza(pizzas);
                break;
            case 4:
                remove_pizza(pizzas);
                break;
            case 5:
                do  {
                    cout << "How do you want to sort your pizzas :\n" ;
                    cout << "1. By prices\n";
                    cout << "2. By names\n";
                    cout << "3. Exit" << endl;
                    cin >> choice;

                    switch (choice){                    
                    case 1:
                        merge_sort(pizzas, 0, pizzas.size() - 1, sort_by_price);
                        display_pizzas(pizzas);
                        break;
                    case 2:
                        merge_sort(pizzas, 0, pizzas.size() - 1, sort_by_name);
                        display_pizzas(pizzas);
                        break;
                    case 3:
                        cout << "Back to the main menu" << endl;
                        break;
                    default:
                        cout << "Invalid choice." << endl;
                        break;
                    }
                } while (choice != 3);
                break;
            case 6:
                add_ingredient(ingredients, Ingredient_Type);
                break;
            case 7:
                display_pizzas_id(pizzas);
                display_pizzas_id(pizzas2);
                break;
            case 11:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 11);

    return 0;
}

void add_ingredient(vector<s_Ingredient> &ingredients, const char *Ingredient_Type[]) {
    s_Ingredient newIngredient;
    int choice;

    // Input ingredient name
    cout << "Enter the name: ";
    cin.ignore();
    getline(cin, newIngredient.name);

    // Display options for Ingredient_Type
    cout << "Enter the number of the type: " << endl;
    for (int i = 0; i < 7; i++) { // Hardcoded 7 since Ingredient_Type has 7 elements
        cout << i << ". " << Ingredient_Type[i] << endl;
    }

    // Get the user's choice
    cin >> choice;
    if (choice < 0 || choice >= 7) {
        cout << "Invalid choice! Please try again." << endl;
        return; // Exit the function on invalid input
    }
    else {
        newIngredient.type = Ingredient_Type[choice];
        cout << "Defined as :" << Ingredient_Type[choice] << endl;
    }
    // Assign the chosen type and other attributes
    cout << "Enter the price: ";
    cin >> newIngredient.price;

    cout << "Enter the quantity: ";
    cin >> newIngredient.quantity;

    // Append the ingredient to the vector
    ingredients.push_back(newIngredient);

    cout << "Ingredient added successfully! Type: " << Ingredient_Type[choice] << endl;
}


void add_pizza(vector<s_Pizza> &pizzas) {
    s_Pizza newPizza;
    int numIngredients;

    cout << "Enter pizza name: ";
    cin.ignore();
    getline(cin, newPizza.name);

    cout << "Enter pizza price: ";
    cin >> newPizza.price;

    cout << "Enter difficulty level (1-5): ";
    cin >> newPizza.difficulty;

    cout << "Enter number of ingredients: ";
    cin >> numIngredients;

    for (int i = 0; i < numIngredients; i++) {
        s_Ingredient ing;
        cout << "Enter ingredient name: ";
        cin.ignore();
        getline(cin, ing.name);

        cout << "Enter ingredient price: ";
        cin >> ing.price;

        cout << "Enter ingredient quantity: ";
        cin >> ing.quantity;

        newPizza.ingredients.push_back(ing);
    }

    pizzas.push_back(newPizza);
    cout << "Pizza added successfully.\n";
}

void display_pizzas(const vector<s_Pizza> &pizzas) {
    if (pizzas.empty()) {
        cout << "No pizzas available.\n";
        return;
    }

    cout << "\n=== Pizza List ===\n";
    // Different way to do an for loop using directly the objects existing
    for (const s_Pizza &pizza : pizzas) {
        cout << "Name: " << pizza.name
             << ", Price: " << pizza.price
             << ", Difficulty: " << pizza.difficulty << "\nIngredients:\n";

        for (const s_Ingredient &ing : pizza.ingredients) {
            cout << "  - " << ing.name
                << " (Type: " << ing.type
                << ", Price: " << ing.price
                << ", Quantity: " << ing.quantity << ")\n";
        }
        cout << "-----------------\n";
    }
}

void display_pizzas_id(const vector<s_Pizza> &pizzas){
    if (pizzas.empty()) {
        cout << "The list is empty." << endl;
    }
    // Classic way to do the for loop
    for (int i = 0; i < pizzas.size(); i++) {
        const s_Pizza &pizza = pizzas[i];
        cout << "ID " << i << " = " << pizza.name << endl;
    }
}

int binary_search(const vector<s_Pizza> &pizzas, const string &name) {
    int left = 0, right = pizzas.size();

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (pizzas[mid].name == name) {
            return mid;
        } else if (pizzas[mid].name < name) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return false;
}

void update_pizza(vector<s_Pizza> &pizzas) {
    string name;
    cout << "Enter the name of the pizza to update: ";
    cin.ignore();
    getline(cin, name);

    int index = binary_search(pizzas, name);

    if (!index) {
        cout << "Pizza found. Enter new details:\n";
        add_pizza(pizzas);  // Reuse addPizza to input new details
        pizzas.erase(pizzas.begin() + index);  // Remove the old pizza
        cout << "Pizza updated successfully.\n";
    } else {
        cout << "Pizza not found.\n";
    }
}

void remove_pizza(vector<s_Pizza> &pizzas) {
    string name;
    cout << "Enter the name of the pizza to remove: ";
    cin.ignore();
    getline(cin, name);

    int index = binary_search(pizzas, name);
    cout << index << endl;
    if (!index) {
        pizzas.erase(pizzas.begin() + index);
        cout << "Pizza removed successfully.\n";
    } else {
        cout << "Pizza not found.\n";
    }
}

void merge_sort(vector<s_Pizza> &pizzas, int left, int right, bool (*compare)(const s_Pizza &, const s_Pizza &)) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(pizzas, left, mid, compare);
        merge_sort(pizzas, mid + 1, right, compare);
        merge(pizzas, left, mid, right, compare);
    }
}

void merge(vector<s_Pizza> &pizzas, int left, int mid, int right, bool (*compare)(const s_Pizza &, const s_Pizza &)) {
    vector<s_Pizza> temp(right - left + 1);

    int i = left, j = mid + 1, k = 0;

    while (i <= mid & j <= right) {
        if (compare(pizzas[i], pizzas[j])) {
            temp[k++] = pizzas[i++];
        } else {
            temp[k++] = pizzas[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = pizzas[i++];
    }

    while (j <= right) {
        temp[k++] = pizzas[j++];
    }

    for (int i = left; i <= right; i++) {
        pizzas[i] = temp[i - left];
    }
}

bool sort_by_price(const s_Pizza &a, const s_Pizza &b) {
    return a.price < b.price;
}

bool sort_by_name(const s_Pizza &a, const s_Pizza &b) {
    return a.name < b.name;
}
