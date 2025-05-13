# 🎥 Camera Shop Terminal App

> A simple yet effective terminal-based store management system, written in C++.  

Developed with ❤️ by:  
[@Deekayee](https://github.com/Deekayee)  
[@xd4rk1ng](https://github.com/xd4rk1ng)

---

## 📦 About the Project

Camera Shop is a lightweight, terminal-driven application designed for managing a small retail camera store. It operates entirely via command-line and manages product stock, sales, and checkout—all from a single executable.  

Upon first run, the program checks for a `stockList.csv` file in its folder. If the file is missing, a new blank stock file will be automatically created, ready for use.

---

## 🧭 Main Menu

You'll be greeted with three main options:

1. 🛒 **Shop Sales**
2. 📦 **Shop Stock**
3. 🚪 **Exit**

---

## 🛍️ Shop Sales

This module allows you to browse stock or manage your shopping cart. It includes two views:

- **Products View** – Displays all products available for purchase.
- **Cart View** – Shows all items currently in your cart.

### Available Options:

1. ➕ Add to Cart  
2. 🔁 Change Quantity in Cart  
3. ❌ Remove from Cart  
4. 🔄 Switch View (Products / Cart)  
5. 🧹 Clear Cart  
6. 💰 Checkout  
0. 🔙 Go Back

---

## 🏪 Shop Stock Management

The second main menu option handles store-side stock operations. It displays all items with detailed information useful for inventory management.

### Available Options:

1. 🔍 Search Stock  
2. ➕ Add New Product  
3. ✏️ Edit Existing Product  
4. ❌ Remove Product  
0. 🔙 Go Back

---

## 🎉 Surprise Promotion (Gambling Feature™)

At checkout, you may get lucky and win **one random cart item for free!**  
Try your luck—no risk, all reward!

---

## 📁 File Structure

- `stockList.csv` – Product stock database.
- Receipts are stored internally and displayed at checkout.

---

## 🚀 Getting Started

1. Clone the repository  
   ```bash
   git clone https://github.com/Deekayee/5092-Dmytro-Rui-Project.git
   cd 5092-Dmytro-Rui-Project
   ```
2. Compile the program (example using `g++`)  
   ```bash
   g++ *.cpp -o shop.exe
   ```
3. Run it!  
   ```bash
   ./shop.exe
   ```
