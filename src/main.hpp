#ifndef MAIN_HPP
#define MAIN_HPP

#pragma once
#include <iostream>

using namespace std;

const char *Ingredient_Type[] = {
    "Kg",
    "gr",
    "mm",
    "L",
    "cl",
    "ml",
    "Unit"
};

typedef struct {
    string name;
    const char *type;
    float price;
    int quantity;
} s_Ingredient;

typedef struct {
    string name;
    float price;
    vector<s_Ingredient> ingredients;
    short difficulty;
} s_Pizza;

/*
    Load example pizzas
    params:
        vector<s_Pizza> &pizzas: list of pizzas
    return:
        void
*/
void load_example_pizzas(vector<s_Pizza> &pizzas) {
    s_Pizza margherita;
    margherita.name = "Reine";
    margherita.price = 500;

    s_Ingredient newIngredient;
    newIngredient.name = "Tomato Sauce";
    newIngredient.price = 50;
    newIngredient.quantity = 1;
    margherita.ingredients.push_back(newIngredient);

    s_Ingredient newIngredient2;
    newIngredient.name = "Mozzarella Cheese";
    newIngredient.price = 100;
    newIngredient.quantity = 1;
    margherita.ingredients.push_back(newIngredient);

    margherita.difficulty = 2;
    pizzas.push_back(margherita);

}

/*
    Load random pizzas
    params:
        vector<s_Pizza> &pizzas: list of pizzas
        const char *Ingredient_Type[]: list of ingredient types
    return:
        void
*/
void load_random_pizzas(vector<s_Pizza> &pizzas, const char *Ingredient_Type[]) {
    const vector<string> pizzaNames = {
        "Pepperoni", "Hawaiian", "BBQ Chicken", "Veggie", "Meat Lovers",
        "Supreme", "Buffalo Chicken", "Mushroom", "Sausage", "Bacon",
        "Four Cheese", "Margherita", "Pesto", "Spinach Alfredo", "Taco",
        "Philly Cheese Steak", "Chicken Alfredo", "Garlic Chicken", "Greek", "Seafood"
    };

    const vector<string> ingredientNames = {
        "Tomato Sauce", "Mozzarella Cheese", "Pepperoni", "Ham", "Pineapple",
        "BBQ Sauce", "Chicken", "Bell Peppers", "Onions", "Mushrooms",
        "Sausage", "Bacon", "Parmesan Cheese", "Basil", "Pesto Sauce",
        "Spinach", "Alfredo Sauce", "Ground Beef", "Feta Cheese", "Shrimp"
    };

    srand(time(0));
    for (int i = 0; i < pizzaNames.size(); ++i) {
        s_Pizza pizza;
        pizza.name = pizzaNames[i % pizzaNames.size()];
        pizza.price = rand() % 20 + 5;
        pizza.difficulty = rand() % 5 + 1; // Random difficulty between 1 and 5

        int numIngredients = rand() % 5 + 1; // Random number of ingredients between 1 and 5
        for (int j = 0; j < numIngredients; ++j) {
            s_Ingredient ingredient;
            ingredient.name = ingredientNames[rand() % ingredientNames.size()];
            ingredient.type = Ingredient_Type[rand() % 7 + 0];
            ingredient.price = rand() % 5 + 1; // Random price between 50 and 250
            ingredient.quantity = rand() % 5 + 1; // Random quantity between 1 and 5
            pizza.ingredients.push_back(ingredient);
        }

        pizzas.push_back(pizza);
    }
}

/*
    Permit to add a new ingredient on the list
    params:
        const vector<s_Ingredient> &ingredients: list of ingredients
    return:
        void
*/
void add_ingredient(vector<s_Ingredient> &ingredients, const char *Ingredient_Type[]);


/*
    Permit to add a new pizza on the list
    params:
        vector<s_Pizza> &pizzas: list of pizzas
    return:
        void
*/
void add_pizza(vector<s_Pizza> &pizzas);

/*
    Display all pizzas with all informations
    params:
        const vector<s_Pizza> &pizzas: list of pizzas
    return:
        void
*/
void display_pizzas(const vector<s_Pizza> &pizzas);

/*

*/
void display_pizzas_id(const vector<s_Pizza> &pizzas);

/*
    Search a pizza by name
    params:
        const vector<s_Pizza> &pizzas: list of pizzas
        const string &name: name of the pizza
    return:
        int: index of the pizza
*/
int binary_search(const vector<s_Pizza> &pizzas, const string &name);

/*
    Update a pizza
    params:
        vector<s_Pizza> &pizzas: list of pizzas
    return:
        void
*/
void update_pizza(vector<s_Pizza> &pizzas);

/*
    Remove a pizza
    params:
        vector<s_Pizza> &pizzas: list of pizzas
    return:
        void
*/
void remove_pizza(vector<s_Pizza> &pizzas);

/*
    Used to compare 2 entry point before merging
    params:
        vector<s_Pizza> &pizzas: list of pizzas
        int left: left index
        int right: right index
        bool (*compare): Assign the pointer of a function to assign dynamicly the pointer of values requested
    return:
        void
*/
void merge_sort(vector<s_Pizza> &pizzas, int left, int right, bool (*compare)(const s_Pizza &, const s_Pizza &));

/*
    Finalize the merge after comparing the the previous sort
    params:
        vector<s_Pizza> &pizzas: list of pizzas
        int left: left index
        int mid: middle index
        int right: right index
        bool (*compare): Assign the pointer of a function to assign dynamicly the pointer of values requested
    return:
        void
*/
void merge(vector<s_Pizza> &pizzas, int left, int mid, int right, bool (*compare)(const s_Pizza &, const s_Pizza &));

/*
    Sort by price
    params:
        const s_Pizza &a: pizza a
        const s_Pizza &b: pizza b
    return:
        bool: true if a is greater than b
*/
bool sort_by_price(const s_Pizza &a, const s_Pizza &b);

/*
    Sort by name
    params:
        const s_Pizza &a: pizza a
        const s_Pizza &b: pizza b
    return:
        bool: true if a is greater than b
*/
bool sort_by_name(const s_Pizza &a, const s_Pizza &b);
#endif
